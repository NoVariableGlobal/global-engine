param (
    [Alias("MsBuild")]
    [Parameter(Position = 0)]
    [ValidateScript( { Test-Path -LiteralPath $_ -PathType Leaf })]
    [string]
    $MsBuildPath = "",

    [Alias("CMake")]
    [string] $CMakePath,
    [switch] $Build,
    [switch] $Release,
    [string] $Target,
    [string] $Property,
    [string] $Platform = "x64",

    [switch] $DependenciesOnly,
    [switch] $EngineOnly,

    [Alias("Parallel")]
    [switch] $SequentialBuild,
    [switch] $AllCores,

    [ValidateSet('q', 'quiet', 'm', 'minimal', 'n', 'normal', 'd', 'detailed', 'diag', 'diagnostic')]
    [string] $Verbosity = "normal",
    [switch] $DisplayLogo,

    [Alias("Parameters", "Params", "P")]
    [string[]] $MsBuildParameters
)

If ($DependenciesOnly -And $EngineOnly) {
    Write-Host "You cannot specify " -ForegroundColor Red  -NoNewline
    Write-Host "-DependenciesOnly"   -ForegroundColor Blue -NoNewline
    Write-Host " and "               -ForegroundColor Red  -NoNewline
    Write-Host "-EngineOnly"         -ForegroundColor Blue -NoNewline
    Write-Host " at the same time."  -ForegroundColor Red
    Exit 1
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
        Write-Host ".\build.ps1 `"Path\To\MSBuild.exe`""                       -ForegroundColor Cyan   -NoNewline
        Write-Host " or "                                                      -ForegroundColor Yellow -NoNewline
        Write-Host ".\build.ps1 -MsBuild `"Path\To\MSBuild.exe`""              -ForegroundColor Cyan   -NoNewline
        Write-Host " to set the path."                                         -ForegroundColor Yellow
        Write-Host "  # Alternatively, do "                                    -ForegroundColor Yellow -NoNewline
        Write-Host "`$Env:MsBuild=`"Path\To\MSBuild.exe`""                     -ForegroundColor Cyan   -NoNewline
        Write-Host ", afterwards you will be able to execute "                 -ForegroundColor Yellow -NoNewline
        Write-Host ".\build.ps1"                                               -ForegroundColor Cyan   -NoNewline
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
        Write-Host ".\build.ps1 -CMake `"Path\To\cmake.exe`""                -ForegroundColor Cyan   -NoNewline
        Write-Host " to set the path."                                       -ForegroundColor Yellow
        Write-Host "  # Alternatively, do "                                  -ForegroundColor Yellow -NoNewline
        Write-Host "`$Env:CMake=`"Path\To\cmake.exe`""                       -ForegroundColor Cyan   -NoNewline
        Write-Host ", afterwards you will be able to execute "               -ForegroundColor Yellow -NoNewline
        Write-Host ".\build.ps1"                                             -ForegroundColor Cyan   -NoNewline
        Write-Host " normally."                                              -ForegroundColor Yellow
        Exit 1
    }
}

# Find and assert MSBuild
$local:MsBuild = Find-MsBuild
Assert-MsBuildPath($MsBuild)

# Build a MSVC project given a path and optional arguments
function Step-VisualStudioRaw([string] $Path, [string[]] $Arguments) {
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
        Write-Host "'. With code $LastExitCode Took: " -ForegroundColor Red  -NoNewLine
        Write-Host ("{0:g}" -f $duration)              -ForegroundColor Cyan -NoNewLine
        Write-Host "."                                 -ForegroundColor Red
    }
}

# Builds a third-party library as debug, ignoring all warnings and verbosity
function Step-VisualStudioThirdPartyDebug([string] $Path) {
    Write-Host "# Now building '" -ForegroundColor Blue -NoNewline
    Write-Host $Path              -ForegroundColor Cyan -NoNewline
    Write-Host "' as Debug."      -ForegroundColor Blue

    Step-VisualStudioRaw $Path @("-t:build", "-p:Configuration=Debug;Platform=x64", "-m", "-maxCpuCount", "-noLogo", "-verbosity:minimal")
}

# Builds a third-party library as release, ignoring all warnings and verbosity
function Step-VisualStudioThirdPartyRelease([string] $Path) {
    Write-Host "# Now building '" -ForegroundColor Blue -NoNewline
    Write-Host $Path              -ForegroundColor Cyan -NoNewline
    Write-Host "' as Release."    -ForegroundColor Blue

    Step-VisualStudioRaw $Path @("-t:build", "-p:Configuration=Release;Platform=x64", "-m", "-maxCpuCount", "-noLogo", "-verbosity:minimal")
}

# Builds the project library
function Step-VisualStudio([string] $Path) {
    Write-Host "# Now building '"             -ForegroundColor Blue -NoNewline
    Write-Host $Path                          -ForegroundColor Cyan -NoNewline
    Write-Host "' as $PropertyConfiguration." -ForegroundColor Blue

    Step-VisualStudioRaw $Path $MsBuildParameters
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
    & $CMake -S $Path -B "$Path\build" $Arguments
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
        Write-Host "'. With code $LastExitCode Took: " -ForegroundColor Red  -NoNewLine
        Write-Host ("{0:g}" -f $duration)              -ForegroundColor Cyan -NoNewLine
        Write-Host "."                                 -ForegroundColor Red
    }
}

$local:RootFolder = "$($PSScriptRoot)"
$local:BinaryDirectory = "$RootFolder\P3\ProyectoBase\bin"
$local:DependenciesRoot = "$RootFolder\P3\ProyectoBase\lib"

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
    If (!$EngineOnly.ToBool()) {
        # Build Bullet
        $private:BulletFolder = "$DependenciesRoot\bullet3-2.89"
        Step-CMake $BulletFolder  @(
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

        # Build FMod
        # $private:FModFolder = "$DependenciesRoot\fmod"

        # Build JsonCPP
        $private:JsonFolder = "$DependenciesRoot\jsoncpp-master"
        Step-CMake $JsonFolder @()
        Step-VisualStudioThirdPartyDebug "$JsonFolder\build\JSONCPP.sln"
        Step-VisualStudioThirdPartyRelease "$JsonFolder\build\JSONCPP.sln"

        # Build Ogre
        $private:OgreFolder = "$DependenciesRoot\ogre-1.12.5"
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

        # Build SDL2
        $private:Sdl2Folder = "$DependenciesRoot\SDL2-2.0.10"
        Step-CopyToBinaryDirectory "SDL2" @(
            "$Sdl2Folder\lib\x64\SDL2.dll"
        )
    }

    If (!$DependenciesOnly.ToBool()) {
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
            $local:MsBuildParameters = @($Target, $Property, $VerbosityArgument, $BuildInParallelArgument, $MaxCpuCountArgument, $NoLogoArgument)
        }

        # Build Global Engine
        Step-VisualStudio "$RootFolder\P3\ProyectoBase\ProyectoBase.sln"
    }

    Exit 0
} Catch {
    # Write the exception
    Write-Host -Object $_
    Write-Host -Object $_.Exception
    Write-Host -Object $_.ScriptStackTrace

    Exit 1
}
