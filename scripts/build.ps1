param (
    [Alias("MsBuild")]
    [Parameter(Position = 0)]
    [ValidateScript( { Test-Path -LiteralPath $_ -PathType Leaf })]
    [string]
    $MsBuildPath = "",

    [Alias("CMake")]
    [string] $CMakePath,
    [switch] $Build,
    [switch] $Clean,
    [switch] $Release,
    [string] $Target,
    [string] $Property,
    [string] $Platform = "x64",

    # Dependencies
    [switch] $BuildDependencies,
    [switch] $BuildBullet,
    [switch] $BuildCegui,
    [switch] $BuildCeguiDependencies,
    [switch] $BuildFmod,
    [switch] $BuildJsonCpp,
    [switch] $BuildOgre,
    [switch] $BuildOis,
    [switch] $BuildSdl2,

    # Project
    [switch] $BuildProject,

    # Misc
    [switch] $BuildAll,

    [Alias("Parallel")]
    [switch] $SequentialBuild,
    [switch] $AllCores,

    [ValidateSet('q', 'quiet', 'm', 'minimal', 'n', 'normal', 'd', 'detailed', 'diag', 'diagnostic')]
    [string] $Verbosity = "normal",
    [switch] $DisplayLogo,

    [Alias("Parameters", "Params", "P")]
    [string[]] $MsBuildParameters
)

$ErrorActionPreference = "Stop"

$local:RootFolder = Split-Path $PSScriptRoot -Parent
$local:BinaryDirectory = "$RootFolder\bin"
$local:DependenciesRoot = "$RootFolder\deps"

$local:BulletFolder = Join-Path -Path $DependenciesRoot -ChildPath "bullet"
$local:FModFolder = Join-Path -Path $DependenciesRoot -ChildPath "fmod"
$local:JsonFolder = Join-Path -Path $DependenciesRoot -ChildPath "jsoncpp"
$local:OgreFolder = Join-Path -Path $DependenciesRoot -ChildPath "ogre"
$local:Sdl2Folder = Join-Path -Path $DependenciesRoot -ChildPath "SDL2"
$local:CeguiFolder = Join-Path -Path $DependenciesRoot -ChildPath "cegui"
$local:CeguiDependenciesFolder = Join-Path -Path $DependenciesRoot -ChildPath "cegui-dependencies"
$local:OisFolder = Join-Path -Path $DependenciesRoot -ChildPath "OIS"

If ($Clean) {
    $local:DllFiles = Get-ChildItem -Path $BinaryDirectory -Filter "*.dll";

    Write-Host "# Now deleting " -ForegroundColor Blue -NoNewline
    Write-Host $DllFiles.Length  -ForegroundColor Cyan -NoNewline
    Write-Host " file(s) from "  -ForegroundColor Blue -NoNewline
    Write-Host $BinaryDirectory  -ForegroundColor Cyan -NoNewline
    Write-Host "'... "           -ForegroundColor Blue -NoNewLine

    If ($DllFiles.Length -Ne 0) {
        $DllFiles | Remove-Item | Out-Null
        Write-Host "Finished!"           -ForegroundColor Green
    } Else {
        Write-Host "Skipped."            -ForegroundColor DarkGray
    }

    Remove-Variable DllFiles

    function Remove-Directory([string[]] $Path) {
        Write-Host "# Now deleting folder '" -ForegroundColor Blue -NoNewline
        Write-Host $Path                     -ForegroundColor Cyan -NoNewline
        Write-Host "'... "                   -ForegroundColor Blue -NoNewLine

        If (Test-Path -Path $Path) {
            Remove-Item -LiteralPath $Path -Recurse | Out-Null
            Write-Host "Finished!"           -ForegroundColor Green
        } Else {
            Write-Host "Skipped."            -ForegroundColor DarkGray
        }
    }

    Remove-Directory -Path (Join-Path -Path $BulletFolder -ChildPath "build")
    Remove-Directory -Path (Join-Path -Path $FModFolder -ChildPath "build")
    Remove-Directory -Path (Join-Path -Path $JsonFolder -ChildPath "build")
    Remove-Directory -Path (Join-Path -Path $OgreFolder -ChildPath "build")
    Remove-Directory -Path (Join-Path -Path $Sdl2Folder -ChildPath "build")
    Remove-Directory -Path (Join-Path -Path $CeguiFolder -ChildPath "build")
    Remove-Directory -Path (Join-Path -Path $CeguiDependenciesFolder -ChildPath "build")
    Remove-Directory -Path (Join-Path -Path $OisFolder -ChildPath "build")
}

# Whether any dependency was specified
$private:BuildDependenciesSpecified = $BuildDependencies.ToBool() -Or
    $BuildBullet.ToBool() -Or
    $BuildCegui.ToBool() -Or
    $BuildCeguiDependencies.ToBool() -Or
    $BuildFmod.ToBool() -Or
    $BuildJsonCpp.ToBool() -Or
    $BuildOgre.ToBool() -Or
    $BuildOis.ToBool() -Or
    $BuildSdl2.ToBool()

# Whether any build step was specified
$private:BuildSpecified = $BuildDependenciesSpecified -Or
    $BuildAll.ToBool() -Or
    $BuildProject.ToBool()

If ($BuildAll -Or !$BuildSpecified) {
    # If BuildAll is set or no build step was specified, set defaults to build all dependencies and the project itself
    # This will happen with the following cases:
    #   ./scripts/build.ps1
    #   ./scripts/build.ps1 -BuildAll

    $BuildDependencies = $true
    $BuildProject = $true
} ElseIf (!$BuildProject.IsPresent -And !$BuildDependenciesSpecified) {
    # If -BuildProject was not specified and no dependencies were as well
    # This will happen with the following case:
    #   ./scripts/build.ps1 -BuildProject
    #
    # This will *not* happen with the following case:
    #   ./scripts/build.ps1 -BuildBullet

    $BuildProject = $true
}

If ($BuildDependencies) {
    If (!$BuildBullet.IsPresent) { $BuildBullet = $true }
    If (!$BuildCegui.IsPresent) { $BuildCegui = $true }
    If (!$BuildCeguiDependencies.IsPresent) { $BuildCeguiDependencies = $true }
    If (!$BuildFmod.IsPresent) { $BuildFmod = $true }
    If (!$BuildJsonCpp.IsPresent) { $BuildJsonCpp = $true }
    If (!$BuildOgre.IsPresent) { $BuildOgre = $true }
    If (!$BuildOis.IsPresent) { $BuildOis = $true }
    If (!$BuildSdl2.IsPresent) { $BuildSdl2 = $true }
}

function New-Directory([string[]] $Path) {
    If (!(Test-Path -Path $Path)) {
        New-Item -Path $Path -Force -ItemType Directory | Out-Null
    }
}

# Finds MSBuild.exe from the user's input, falling back in the following order:
#  - Environmental Variable
#  - Get-Command (PATH)
#  - Program Files typical installation path scan
function Find-MsBuild {
    # Check if a path was given:
    if ($MsBuildPath.Length -Eq 0) {
        # Find from environmental variable:
        If ($Env:MsBuild) {
            $MsBuild = (Resolve-Path $Env:MsBuild)[0].Path
            Write-Host "MsBuild not provided, using '"           -ForegroundColor Blue -NoNewline
            Write-Host $MsBuild                                  -ForegroundColor Cyan -NoNewline
            Write-Host "' from environmental variables instead." -ForegroundColor Blue
            return $MsBuild;
        }

        # Find from PATH environmental variables:
        If (Get-Command "MSBuild.exe" -ErrorAction SilentlyContinue) {
            $MsBuild = (Get-Command "MSBuild.exe").Path;
            Write-Host "MsBuild not provided, using '" -ForegroundColor Blue -NoNewline
            Write-Host $MsBuild                        -ForegroundColor Cyan -NoNewline
            Write-Host "' from PATH instead."          -ForegroundColor Blue
            return $MsBuild;
        }

        # Find from ProgramFiles:
        $local:PossibleMsBuild = Resolve-Path "${Env:ProgramFiles(x86)}\Microsoft Visual Studio\2019\*\MSBuild\*\Bin\MSBuild.exe" -ErrorAction SilentlyContinue
        If (($PossibleMsBuild) -And ($PossibleMsBuild.Length -Ge 0)) {
            $MsBuild = $PossibleMsBuild[0].Path
            Write-Host "MsBuild not provided, using '" -ForegroundColor Blue -NoNewline
            Write-Host $MsBuild                        -ForegroundColor Cyan -NoNewline
            Write-Host "' instead."                    -ForegroundColor Blue
            return $MsBuild;
        }
    } Else {
        $MsBuild = $MsBuildPath;
        return $MsBuild;
    }
}

# Asserts that the variable assigned to $MsBuild is a valid file path, discarding files that do not exist and folders.
function Assert-MsBuildPath([string] $private:MsBuild) {
    If (($MsBuild -Eq "") -Or !(Test-Path -LiteralPath $MsBuild -PathType Leaf)) {
        Write-Host "I was not able to find MSBuild.exe, please check https://docs.microsoft.com/visualstudio/msbuild/msbuild?view=vs-2019 for more information." -ForegroundColor Red
        Write-Host "  # Please specify the route to the MSBuild.exe by doing " -ForegroundColor Yellow -NoNewline
        Write-Host ".\scripts\build.ps1 `"Path\To\MSBuild.exe`""               -ForegroundColor Cyan   -NoNewline
        Write-Host " or "                                                      -ForegroundColor Yellow -NoNewline
        Write-Host ".\scripts\build.ps1 -MsBuild `"Path\To\MSBuild.exe`""      -ForegroundColor Cyan   -NoNewline
        Write-Host " to set the path."                                         -ForegroundColor Yellow
        Write-Host "  # Alternatively, do "                                    -ForegroundColor Yellow -NoNewline
        Write-Host "`$Env:MsBuild=`"Path\To\MSBuild.exe`""                     -ForegroundColor Cyan   -NoNewline
        Write-Host ", afterwards you will be able to execute "                 -ForegroundColor Yellow -NoNewline
        Write-Host ".\scripts\build.ps1"                                       -ForegroundColor Cyan   -NoNewline
        Write-Host " normally."                                                -ForegroundColor Yellow
        Exit 1
    }
}

# Finds cmake.exe from the user's input, falling back in the following order:
#  - Environmental Variable
#  - Get-Command (PATH)
#  - Program Files typical installation path scan
function Find-CMake {
    # Check if a path was given:
    if ($CMakePath.Length -Eq 0) {
        # Find from environmental variable:
        If ($Env:CMake) {
            $CMake = (Resolve-Path $Env:CMake)[0].Path
            Write-Host "CMake not provided, using '"             -ForegroundColor Blue -NoNewline
            Write-Host $CMake                                    -ForegroundColor Cyan -NoNewline
            Write-Host "' from environmental variables instead." -ForegroundColor Blue
            return $CMake;
        }

        # Find from PATH environmental variables:
        If (Get-Command "cmake.exe" -ErrorAction SilentlyContinue) {
            $CMake = (Get-Command "cmake.exe").Path;
            Write-Host "CMake not provided, using '" -ForegroundColor Blue -NoNewline
            Write-Host $CMake                        -ForegroundColor Cyan -NoNewline
            Write-Host "' from PATH instead."        -ForegroundColor Blue
            return $CMake;
        }

        # Find from ProgramFiles:
        $local:PossibleCMake = Resolve-Path "${Env:ProgramFiles}\CMake\bin\cmake.exe" -ErrorAction SilentlyContinue
        If (($PossibleCMake) -And ($PossibleCMake.Length -Ge 0)) {
            $CMake = $PossibleCMake[0].Path
            Write-Host "MsBuild not provided, using '" -ForegroundColor Blue -NoNewline
            Write-Host $CMake                          -ForegroundColor Cyan -NoNewline
            Write-Host "' instead."                    -ForegroundColor Blue
            return $CMake;
        }
    }
    Else {
        $CMake = $CMakePath;
        return $CMake;
    }
}

# Asserts that the variable assigned to $CMake is a valid file path, discarding files that do not exist and folders.
function Assert-CMakePath([string] $private:CMake) {
    If (($CMake -Eq "") -Or !(Test-Path -LiteralPath $CMake -PathType Leaf)) {
        Write-Host "I was not able to find cmake.exe, please download the binary at https://cmake.org." -ForegroundColor Red
        Write-Host "  # Please specify the route to the cmake.exe by doing " -ForegroundColor Yellow -NoNewline
        Write-Host ".\scripts\build.ps1 -CMake `"Path\To\cmake.exe`""        -ForegroundColor Cyan   -NoNewline
        Write-Host " to set the path."                                       -ForegroundColor Yellow
        Write-Host "  # Alternatively, do "                                  -ForegroundColor Yellow -NoNewline
        Write-Host "`$Env:CMake=`"Path\To\cmake.exe`""                       -ForegroundColor Cyan   -NoNewline
        Write-Host ", afterwards you will be able to execute "               -ForegroundColor Yellow -NoNewline
        Write-Host ".\scripts\build.ps1"                                     -ForegroundColor Cyan   -NoNewline
        Write-Host " normally."                                              -ForegroundColor Yellow
        Exit 1
    }
}

# Find and assert MSBuild
$local:MsBuild = Find-MsBuild
Assert-MsBuildPath($MsBuild)

# Build a MSVC project given a path and optional arguments
function Step-VisualStudioRaw([string] $Path, [switch] $ThrowOnError, [string[]] $Arguments) {
    # Run the process
    $private:startTime = Get-Date
    & $MsBuild $Path $Arguments
    $private:exitTime = Get-Date

    # Print information to the screen
    $private:duration = $exitTime - $startTime
    If ($LastExitCode -Eq 0) {
        Write-Host "# Finished building '" -ForegroundColor Green -NoNewLine
        Write-Host $Path                   -ForegroundColor Cyan  -NoNewLine
        Write-Host "'. Took: "             -ForegroundColor Green -NoNewLine
        Write-Host ("{0:g}" -f $duration)  -ForegroundColor Cyan  -NoNewLine
        Write-Host "."                     -ForegroundColor Green
    } Else {
        Write-Host "# Errored when building '"         -ForegroundColor Red  -NoNewLine
        Write-Host $Path                               -ForegroundColor Cyan -NoNewLine
        Write-Host "' with code $LastExitCode Took: " -ForegroundColor Red  -NoNewLine
        Write-Host ("{0:g}" -f $duration)              -ForegroundColor Cyan -NoNewLine
        Write-Host "."                                 -ForegroundColor Red
        If ($ThrowOnError.ToBool()) {
            Throw "Failed to build project project, please read the logs above.";
        }
    }
}

# Builds a third-party library as debug, ignoring all warnings and verbosity
function Step-VisualStudioThirdPartyDebug([string] $Path) {
    Write-Host "# Now building '" -ForegroundColor Blue -NoNewline
    Write-Host $Path              -ForegroundColor Cyan -NoNewline
    Write-Host "' as Debug."      -ForegroundColor Blue

    Step-VisualStudioRaw -Path $Path -Arguments @("-t:build", "-p:Configuration=Debug;Platform=x64;WarningLevel=0", "-m", "-maxCpuCount", "-noLogo", "-verbosity:minimal")
}

# Builds a third-party library as release, ignoring all warnings and verbosity
function Step-VisualStudioThirdPartyRelease([string] $Path) {
    Write-Host "# Now building '" -ForegroundColor Blue -NoNewline
    Write-Host $Path              -ForegroundColor Cyan -NoNewline
    Write-Host "' as Release."    -ForegroundColor Blue

    Step-VisualStudioRaw -Path $Path -Arguments @("-t:build", "-p:Configuration=Release;Platform=x64;WarningLevel=0", "-m", "-maxCpuCount", "-noLogo", "-verbosity:minimal")
}

# Builds the project library
function Step-VisualStudio([string] $Path) {
    Write-Host "# Now building '"             -ForegroundColor Blue -NoNewline
    Write-Host $Path                          -ForegroundColor Cyan -NoNewline
    Write-Host "' as $PropertyConfiguration." -ForegroundColor Blue

    Step-VisualStudioRaw -Path $Path -ThrowOnError -Arguments $MsBuildParameters
}

$local:CMake = Find-CMake
Assert-CMakePath($CMake)

# Find and assert CMake
function Step-CMake([string] $Path, [string[]] $Arguments) {
    Write-Host "# Generating CMake Project for '" -ForegroundColor Blue -NoNewline
    Write-Host $Path                              -ForegroundColor Cyan -NoNewline
    Write-Host "'."                               -ForegroundColor Blue

    New-Directory -Path "$Path\build"
    $private:startTime = Get-Date
    & $CMake -S $Path -B "$Path\build" $Arguments -Wno-dev
    $private:exitTime = Get-Date

    # Print information to the screen
    $private:duration = $exitTime - $startTime
    If ($LastExitCode -Eq 0) {
        Write-Host "# Finished generating '" -ForegroundColor Green -NoNewLine
        Write-Host $Path                     -ForegroundColor Cyan  -NoNewLine
        Write-Host "'. Took: "               -ForegroundColor Green -NoNewLine
        Write-Host ("{0:g}" -f $duration)    -ForegroundColor Cyan  -NoNewLine
        Write-Host "."                       -ForegroundColor Green
    }
    Else {
        Write-Host "# Errored when generating '"       -ForegroundColor Red  -NoNewLine
        Write-Host $Path                               -ForegroundColor Cyan -NoNewLine
        Write-Host "' with code $LastExitCode Took: " -ForegroundColor Red  -NoNewLine
        Write-Host ("{0:g}" -f $duration)              -ForegroundColor Cyan -NoNewLine
        Write-Host "."                                 -ForegroundColor Red
        Throw "Failed to generate CMake project, please read the logs above.";
    }
}

# Copies one or more files from one place to the project's binary directory
function Step-CopyToBinaryDirectory([string] $From, [string[]] $Paths) {
    Write-Host "# Now copying " -ForegroundColor Blue -NoNewline
    Write-Host $Paths.Length    -ForegroundColor Cyan -NoNewline
    Write-Host " file(s) from " -ForegroundColor Blue -NoNewline
    Write-Host $From            -ForegroundColor Cyan -NoNewline
    Write-Host " to '"          -ForegroundColor Blue -NoNewline
    Write-Host $BinaryDirectory -ForegroundColor Cyan -NoNewline
    Write-Host "'... "          -ForegroundColor Blue -NoNewLine

    Copy-Item -Path $Paths -Destination $BinaryDirectory

    Write-Host "Finished!"      -ForegroundColor Green
}

Try {
    # Build Bullet
    If ($BuildBullet) {
        Step-CMake $BulletFolder @(
            "-DBUILD_BULLET2_DEMOS:BOOL=OFF",
            "-DBUILD_BULLET3:BOOL=ON",
            "-DBUILD_CLSOCKET:BOOL=OFF",
            "-DBUILD_CPU_DEMOS:BOOL=OFF",
            "-DBUILD_ENET:BOOL=OFF",
            "-DBUILD_EXTRAS:BOOL=OFF",
            "-DBUILD_OPENGL3_DEMOS:BOOL=OFF",
            "-DBUILD_PYBULLET:BOOL=OFF",
            "-DBUILD_SHARED_LIBS:BOOL=OFF",
            "-DBUILD_UNIT_TESTS:BOOL=OFF",
            "-DUSE_MSVC_RUNTIME_LIBRARY_DLL:BOOL=ON"
        )
        Step-VisualStudioThirdPartyDebug "$BulletFolder\build\BULLET_PHYSICS.sln"
        Step-VisualStudioThirdPartyRelease "$BulletFolder\build\BULLET_PHYSICS.sln"
    }

    # Build Ogre
    If ($BuildOgre) {
        Step-CMake $OgreFolder @("-DOGRE_BUILD_COMPONENT_OVERLAY:BOOL=OFF")
        Step-VisualStudioThirdPartyDebug "$OgreFolder\build\OGRE.sln"
        Step-VisualStudioThirdPartyRelease "$OgreFolder\build\OGRE.sln"
        Step-CopyToBinaryDirectory "Ogre" @(
            "$OgreFolder\build\bin\debug\OgreMain_d.dll",
            "$OgreFolder\build\bin\debug\RenderSystem_Direct3D11_d.dll",
            "$OgreFolder\build\bin\debug\RenderSystem_GL_d.dll",
            "$OgreFolder\build\bin\debug\OgreRTShaderSystem_d.dll",
            "$OgreFolder\build\bin\debug\Codec_STBI_d.dll",
            "$OgreFolder\build\bin\release\OgreMain.dll",
            "$OgreFolder\build\bin\release\RenderSystem_Direct3D11.dll",
            "$OgreFolder\build\bin\release\RenderSystem_GL.dll",
            "$OgreFolder\build\bin\release\zlib.dll",
            "$OgreFolder\build\bin\release\OgreRTShaderSystem.dll",
            "$OgreFolder\build\bin\release\Codec_STBI.dll"
        )
    }

    # Build OIS
    If ($BuildOis) {
        Step-CMake $OisFolder @()
        Step-VisualStudioThirdPartyDebug "$OisFolder\build\OIS.sln"
        Step-VisualStudioThirdPartyRelease "$OisFolder\build\OIS.sln"
        Step-CopyToBinaryDirectory "OIS" @(
            "$OisFolder\build\Release\OIS.dll",
            "$OisFolder\build\Debug\OIS_d.dll"
        )
    }

    # Build CEGUI's dependencies
    If ($BuildCeguiDependencies) {
        Step-CMake $CeguiDependenciesFolder @()
        Step-VisualStudioThirdPartyDebug "$CeguiDependenciesFolder\build\CEGUI-DEPS.sln"
        Step-VisualStudioThirdPartyRelease "$CeguiDependenciesFolder\build\CEGUI-DEPS.sln"
    }

    # Build CEGUI
    If ($BuildCegui) {
        $local:CeguiBuiltDependencies = Join-Path -Path $CeguiDependenciesFolder -ChildPath "build/dependencies"
        Step-CMake $CeguiFolder @(
            "-DCEGUI_BUILD_RENDERER_DIRECT3D10:BOOL=OFF",
            "-DCEGUI_BUILD_RENDERER_DIRECT3D11:BOOL=OFF",
            "-DCEGUI_BUILD_RENDERER_DIRECT3D9:BOOL=OFF",
            "-DCEGUI_BUILD_RENDERER_DIRECTFB:BOOL=OFF",
            "-DCEGUI_BUILD_RENDERER_IRRLICHT:BOOL=OFF",
            "-DCEGUI_BUILD_RENDERER_NULL:BOOL=OFF",
            "-DCEGUI_BUILD_RENDERER_OGRE:BOOL=ON",
            "-DCEGUI_BUILD_RENDERER_OPENGL:BOOL=OFF",
            "-DCEGUI_BUILD_RENDERER_OPENGL3:BOOL=OFF",
            "-DCEGUI_BUILD_RENDERER_OPENGLES:BOOL=OFF",
            "-DCMAKE_PREFIX_PATH:PATH=$CeguiBuiltDependencies",
            "-DOGRE_H_BUILD_SETTINGS_PATH:PATH=$OgreFolder/build/include",
            "-DOGRE_H_PATH:PATH=$OgreFolder/OgreMain/include",
            "-DOGRE_LIB:FILEPATH=$OgreFolder/build/lib/Release/OgreMain.lib",
            "-DOGRE_LIB_DBG:FILEPATH=$OgreFolder/build/lib/Debug/OgreMain_d.lib",
            "-DOIS_H_PATH:PATH=$OisFolder/includes",
            "-DOIS_LIB:FILEPATH=$OisFolder/build/Release/OIS.lib",
            "-DOIS_LIB_DBG:FILEPATH=$OisFolder/build/Debug/OIS_d.lib"
        )

        # Let's be honest, I got done with MSBuild here. The world would be beautiful if it'd let me define constants
        # via CLI, but looks like it's impossible without CMake.
        $private:Content = Get-Content -Path "$CeguiFolder\build\cegui\include\CEGUI\Config.h"
        $private:Content = $Content -replace "define CEGUI_OGRE_VERSION_MAJOR 0", "define CEGUI_OGRE_VERSION_MAJOR 1"
        $private:Content = $Content -replace "define CEGUI_OGRE_VERSION_MINOR 0", "define CEGUI_OGRE_VERSION_MINOR 9"
        Set-Content -Path "$CeguiFolder\build\cegui\include\CEGUI\Config.h" -Value $Content
        Remove-Variable Content

        Step-VisualStudioThirdPartyDebug "$CeguiFolder\build\cegui.sln"
        Step-VisualStudioThirdPartyRelease "$CeguiFolder\build\cegui.sln"
        Step-CopyToBinaryDirectory "CEGUI" @(
            "$CeguiFolder\build\bin\CEGUIBase-0.dll",
            "$CeguiFolder\build\bin\CEGUIBase-0_d.dll",
            "$CeguiFolder\build\bin\CEGUIOgreRenderer-0.dll",
            "$CeguiFolder\build\bin\CEGUIOgreRenderer-0_d.dll",
            "$CeguiBuiltDependencies\bin\freetype.dll",
            "$CeguiBuiltDependencies\bin\freetype_d.dll",
            "$CeguiBuiltDependencies\bin\glew.dll",
            "$CeguiBuiltDependencies\bin\glew_d.dll",
            "$CeguiBuiltDependencies\bin\glfw.dll",
            "$CeguiBuiltDependencies\bin\glfw_d.dll",
            "$CeguiBuiltDependencies\bin\jpeg.dll",
            "$CeguiBuiltDependencies\bin\jpeg_d.dll",
            "$CeguiBuiltDependencies\bin\libexpat.dll",
            "$CeguiBuiltDependencies\bin\libexpat_d.dll",
            "$CeguiBuiltDependencies\bin\libpng.dll",
            "$CeguiBuiltDependencies\bin\libpng_d.dll",
            "$CeguiBuiltDependencies\bin\pcre.dll",
            "$CeguiBuiltDependencies\bin\pcre_d.dll",
            "$CeguiBuiltDependencies\bin\SILLY.dll",
            "$CeguiBuiltDependencies\bin\SILLY_d.dll"
        )

        Remove-Variable CeguiBuiltDependencies
    }

    # Build FMod
    If ($BuildFmod) {
        Step-CopyToBinaryDirectory "FMod" @(
            "$FModFolder\fmod64.dll"
        )
    }

    # Build JsonCPP
    If ($BuildJsonCpp) {
        Step-CMake $JsonFolder @()
        Step-VisualStudioThirdPartyDebug "$JsonFolder\build\JSONCPP.sln"
        Step-VisualStudioThirdPartyRelease "$JsonFolder\build\JSONCPP.sln"
    }

    # Build SDL2
    If ($BuildSdl2) {
        Step-CopyToBinaryDirectory "SDL2" @(
            "$Sdl2Folder\lib\x64\SDL2.dll"
        )
    }

    If ($BuildProject) {
        # Sets up $MsBuildParameters, building one from the other parameters
        If ($MsBuildParameters.Length -Eq 0) {
            If ($Target -Eq "" -And (!$Build.IsPresent -Or $Build.ToBool())) {
                $Target = "-t:build"
            }

            If ($Property -Eq "") {
                $PropertyConfiguration = If ($Release.ToBool()) { "Release" } Else { "Debug" }
                $Property = "-p:Configuration=$PropertyConfiguration;Platform=$Platform"
            }

            $local:BuildInParallelArgument = If ($SequentialBuild.ToBool()) { "" } Else { "-m" }
            $local:MaxCpuCountArgument = If (!$AllCores.IsPresent -Or $AllCores.ToBool()) { "-maxCpuCount" } Else { "" }
            $local:NoLogoArgument = If ($DisplayLogo.ToBool()) { "" } Else { "-noLogo" }
            $local:VerbosityArgument = "-verbosity:$Verbosity"
            $MsBuildParameters = @($Target, $Property, $VerbosityArgument, $BuildInParallelArgument, $MaxCpuCountArgument, $NoLogoArgument)
        }

        # Build One Thousand Years
        Step-VisualStudio "$RootFolder\one-thousand-years.sln"
    }

    Exit 0
} Catch {
    # Write the exception
    Write-Host -Object $_
    Write-Host -Object $_.Exception
    Write-Host -Object $_.ScriptStackTrace

    Exit 1
}

Remove-Variable RootFolder
Remove-Variable BinaryDirectory
Remove-Variable DependenciesRoot
Remove-Variable BulletFolder
Remove-Variable FModFolder
Remove-Variable JsonFolder
Remove-Variable OgreFolder
Remove-Variable Sdl2Folder
Remove-Variable CeguiFolder
Remove-Variable CeguiDependenciesFolder
Remove-Variable OisFolder
Remove-Variable BuildInParallelArgument
Remove-Variable MaxCpuCountArgument
Remove-Variable NoLogoArgument
Remove-Variable VerbosityArgument
