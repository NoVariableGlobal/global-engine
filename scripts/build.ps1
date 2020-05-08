# Version: 1.0.0

param (
    [Alias("MsBuild")]
    [Parameter(Position = 0)]
    [ValidateScript( { Test-Path -LiteralPath $_ -PathType Leaf })]
    [string]
    $MsBuildPath = "",

    [Alias("CMake")]
    [string] $CMakePath,
    [switch] $Clean,

    # Configurations
    [switch] $NDebug,
    [switch] $NRelease,

    # Dependencies
    [switch] $BuildDependencies,
    [switch] $BuildBullet,
    [switch] $BuildCegui,
    [switch] $BuildCeguiDependencies,
    [switch] $BuildFmod,
    [switch] $BuildJsonCpp,
    [switch] $BuildOgre,
    [switch] $BuildSdl2,

    # Project
    [switch] $BuildProject,

    # Misc
    [switch] $BuildAll
)

$ErrorActionPreference = "Stop"

$local:RootFolder = Split-Path $PSScriptRoot -Parent
$local:ModulesFolder = "$RootFolder\scripts\modules"
$local:BinaryDirectory = "$RootFolder\bin"
$local:DependenciesRoot = "$RootFolder\deps"

Import-Module -Name (Join-Path -Path $ModulesFolder -ChildPath "MsBuild")
Import-Module -Name (Join-Path -Path $ModulesFolder -ChildPath "CMake")
Import-Module -Name (Join-Path -Path $ModulesFolder -ChildPath "Shared")

$local:BulletFolder = Join-Path -Path $DependenciesRoot -ChildPath "bullet"
$local:FModFolder = Join-Path -Path $DependenciesRoot -ChildPath "fmod"
$local:JsonFolder = Join-Path -Path $DependenciesRoot -ChildPath "jsoncpp"
$local:OgreFolder = Join-Path -Path $DependenciesRoot -ChildPath "ogre"
$local:Sdl2Folder = Join-Path -Path $DependenciesRoot -ChildPath "SDL2"
$local:CeguiFolder = Join-Path -Path $DependenciesRoot -ChildPath "cegui"
$local:CeguiDependenciesFolder = Join-Path -Path $DependenciesRoot -ChildPath "cegui-dependencies"

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
}

# Whether or not any dependency was specified
$private:BuildDependenciesSpecified = $BuildDependencies.ToBool() -Or
    $BuildBullet.ToBool() -Or
    $BuildCegui.ToBool() -Or
    $BuildCeguiDependencies.ToBool() -Or
    $BuildFmod.ToBool() -Or
    $BuildJsonCpp.ToBool() -Or
    $BuildOgre.ToBool() -Or
    $BuildSdl2.ToBool()

# Whether or not any build step was specified
$private:BuildSpecified = $BuildDependenciesSpecified -Or $BuildAll.ToBool() -Or $BuildProject.ToBool()

# Whether or not any build type was specified
$private:BuildTypeSpecified = $NDebug.ToBool() -Or $NRelease.ToBool();

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
    If (!$BuildSdl2.IsPresent) { $BuildSdl2 = $true }
}

If (!$BuildTypeSpecified) {
    If (!$NDebug.IsPresent) { $NDebug = $true }
    If (!$NRelease.IsPresent) { $NRelease = $true }
}

# Find and assert MSBuild and CMake
$local:MsBuild = Find-MsBuild -MsBuildPath $MsBuildPath
$local:CMake = Find-CMake -CMakePath $CMakePath

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
        Step-CMake $CMake $BulletFolder @(
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

        If ($NDebug) {
            Step-VisualStudioDebug $MsBuild "$BulletFolder\build\BULLET_PHYSICS.sln"
        }

        If ($NRelease) {
            Step-VisualStudioRelease $MsBuild "$BulletFolder\build\BULLET_PHYSICS.sln"
        }
    }

    # Build Ogre
    If ($BuildOgre) {
        Step-CMake $CMake $OgreFolder @("-DOGRE_BUILD_COMPONENT_OVERLAY:BOOL=OFF")

        If ($NDebug) {
            Step-VisualStudioDebug $MsBuild "$OgreFolder\build\OGRE.sln"
            Step-CopyToBinaryDirectory "Ogre" @(
                "$OgreFolder\build\bin\debug\OgreMain_d.dll",
                "$OgreFolder\build\bin\debug\RenderSystem_Direct3D11_d.dll",
                "$OgreFolder\build\bin\debug\RenderSystem_GL_d.dll",
                "$OgreFolder\build\bin\debug\OgreRTShaderSystem_d.dll",
                "$OgreFolder\build\bin\debug\Codec_STBI_d.dll",
                "$OgreFolder\build\bin\debug\Plugin_ParticleFX_d.dll"
            )
        }

        If ($NRelease) {
            Step-VisualStudioRelease $MsBuild "$OgreFolder\build\OGRE.sln"
            Step-CopyToBinaryDirectory "Ogre" @(
                "$OgreFolder\build\bin\release\OgreMain.dll",
                "$OgreFolder\build\bin\release\RenderSystem_Direct3D11.dll",
                "$OgreFolder\build\bin\release\RenderSystem_GL.dll",
                "$OgreFolder\build\bin\release\zlib.dll",
                "$OgreFolder\build\bin\release\OgreRTShaderSystem.dll",
                "$OgreFolder\build\bin\release\Codec_STBI.dll",
                "$OgreFolder\build\bin\release\Plugin_ParticleFX.dll"
            )
        }
    }

    # Build CEGUI's dependencies
    If ($BuildCeguiDependencies) {
        Step-CMake $CMake $CeguiDependenciesFolder @()

        If ($NDebug) {
            Step-VisualStudioDebug $MsBuild "$CeguiDependenciesFolder\build\CEGUI-DEPS.sln"
        }

        If ($NRelease) {
            Step-VisualStudioRelease $MsBuild "$CeguiDependenciesFolder\build\CEGUI-DEPS.sln"
        }
    }

    # Build CEGUI
    If ($BuildCegui) {
        $local:CeguiBuiltDependencies = Join-Path -Path $CeguiDependenciesFolder -ChildPath "build/dependencies"
        Step-CMake $CMake $CeguiFolder @(
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
            "-DOGRE_LIB_DBG:FILEPATH=$OgreFolder/build/lib/Debug/OgreMain_d.lib"
        )

        # Let's be honest, I got done with MSBuild here. The world would be beautiful if it'd let me define constants
        # via CLI, but looks like it's impossible without CMake.
        $private:Content = Get-Content -Path "$CeguiFolder\build\cegui\include\CEGUI\Config.h"
        $private:Content = $Content -replace "define CEGUI_OGRE_VERSION_MAJOR 0", "define CEGUI_OGRE_VERSION_MAJOR 1"
        $private:Content = $Content -replace "define CEGUI_OGRE_VERSION_MINOR 0", "define CEGUI_OGRE_VERSION_MINOR 9"
        Set-Content -Path "$CeguiFolder\build\cegui\include\CEGUI\Config.h" -Value $Content
        Remove-Variable Content

        If ($NDebug) {
            Step-VisualStudioDebug $MsBuild "$CeguiFolder\build\cegui.sln"
            Step-CopyToBinaryDirectory "CEGUI" @(
                "$CeguiFolder\build\bin\CEGUIBase-0_d.dll",
                "$CeguiFolder\build\bin\CEGUIOgreRenderer-0_d.dll",
                "$CeguiBuiltDependencies\bin\freetype_d.dll",
                "$CeguiBuiltDependencies\bin\glew_d.dll",
                "$CeguiBuiltDependencies\bin\glfw_d.dll",
                "$CeguiBuiltDependencies\bin\jpeg_d.dll",
                "$CeguiBuiltDependencies\bin\libexpat_d.dll",
                "$CeguiBuiltDependencies\bin\libpng_d.dll",
                "$CeguiBuiltDependencies\bin\pcre_d.dll",
                "$CeguiBuiltDependencies\bin\SILLY_d.dll"
            )
        }

        If ($NRelease) {
            Step-VisualStudioRelease $MsBuild "$CeguiFolder\build\cegui.sln"
            Step-CopyToBinaryDirectory "CEGUI" @(
                "$CeguiFolder\build\bin\CEGUIBase-0.dll",
                "$CeguiFolder\build\bin\CEGUIOgreRenderer-0.dll",
                "$CeguiBuiltDependencies\bin\freetype.dll",
                "$CeguiBuiltDependencies\bin\glew.dll",
                "$CeguiBuiltDependencies\bin\glfw.dll",
                "$CeguiBuiltDependencies\bin\jpeg.dll",
                "$CeguiBuiltDependencies\bin\libexpat.dll",
                "$CeguiBuiltDependencies\bin\libpng.dll",
                "$CeguiBuiltDependencies\bin\pcre.dll",
                "$CeguiBuiltDependencies\bin\SILLY.dll"
            )
        }

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
        Step-CMake $CMake $JsonFolder @()

        If ($NDebug) {
            Step-VisualStudioDebug $MsBuild "$JsonFolder\build\JSONCPP.sln"
        }

        If ($NRelease) {
            Step-VisualStudioRelease $MsBuild "$JsonFolder\build\JSONCPP.sln"
        }
    }

    # Build SDL2
    If ($BuildSdl2) {
        Step-CopyToBinaryDirectory "SDL2" @(
            "$Sdl2Folder\lib\x64\SDL2.dll"
        )
    }

    # Build project
    If ($BuildProject) {
        If ($NDebug) {
            Step-VisualStudio $MsBuild "$RootFolder\one-thousand-years.sln" -ThrowOnError $True
        }

        If ($NRelease) {
            Step-VisualStudio $MsBuild "$RootFolder\one-thousand-years.sln" -ThrowOnError $True
        }
    }

    Exit 0
} Catch {
    # Write the exception
    Write-Host -Object $_
    Write-Host -Object $_.Exception
    Write-Host -Object $_.ScriptStackTrace

    Exit 1
} Finally {
    # Unregister modules
    Remove-Module MsBuild
    Remove-Module CMake
    Remove-Module Shared
}
