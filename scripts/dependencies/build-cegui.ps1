[CmdletBinding()]
param (
	[ValidateSet("Debug", "Release")]
	[string[]] $Configuration
)

$ErrorActionPreference = "Stop"

$local:Name = "cegui"
$local:RootDirectory = Split-Path (Split-Path $PSScriptRoot -Parent) -Parent
$local:OutputDirectory = Join-Path -Path $RootDirectory -ChildPath "bin"
$local:DepsDirectory = Join-Path -Path $RootDirectory -ChildPath "deps"
$local:ProjectDirectory = Join-Path -Path $DepsDirectory -ChildPath $Name
$local:BuildDirectory = Join-Path -Path $ProjectDirectory -ChildPath "build"

$local:OgreDirectory = Join-Path -Path $DepsDirectory -ChildPath "ogre"
$local:CeguiDependenciesBuildDirectory = Join-Path -Path $DepsDirectory -ChildPath "cegui-dependencies/build/dependencies"

cmake -S $ProjectDirectory -B $BuildDirectory -Wno-dev @(
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
	"-DCMAKE_PREFIX_PATH:PATH=$CeguiDependenciesBuildDirectory",
	"-DOGRE_H_BUILD_SETTINGS_PATH:PATH=$OgreDirectory/build/include",
	"-DOGRE_H_PATH:PATH=$OgreDirectory/OgreMain/include",
	"-DOGRE_LIB:FILEPATH=$OgreDirectory/build/lib/Release/OgreMain.lib",
	"-DOGRE_LIB_DBG:FILEPATH=$OgreDirectory/build/lib/Debug/OgreMain_d.lib"
)

# CEGUI detects Ogre's version **way** incorrectly.
$private:Content = Get-Content -Path "$BuildDirectory\cegui\include\CEGUI\Config.h"
$private:Content = $Content -replace "define CEGUI_OGRE_VERSION_MAJOR 0", "define CEGUI_OGRE_VERSION_MAJOR 1"
$private:Content = $Content -replace "define CEGUI_OGRE_VERSION_MINOR 0", "define CEGUI_OGRE_VERSION_MINOR 12"
$private:Content = $Content -replace "define CEGUI_OGRE_VERSION_PATCH 0", "define CEGUI_OGRE_VERSION_PATCH 5"
Set-Content -Path "$BuildDirectory\cegui\include\CEGUI\Config.h" -Value $Content
Remove-Variable Content

if ($Configuration.Length -eq 0 -or $Configuration.Contains("Debug"))
{
	& "$PSScriptRoot/shared/build.ps1" -Configuration Debug -BuildDirectory $BuildDirectory
	& "$PSScriptRoot/shared/copy.ps1" -Name $Name -OutputDirectory $OutputDirectory -Files @(
		"$BuildDirectory\bin\CEGUIBase-0_d.dll",
		"$BuildDirectory\bin\CEGUIOgreRenderer-0_d.dll",
		"$CeguiDependenciesBuildDirectory\bin\freetype_d.dll",
		"$CeguiDependenciesBuildDirectory\bin\glew_d.dll",
		"$CeguiDependenciesBuildDirectory\bin\glfw_d.dll",
		"$CeguiDependenciesBuildDirectory\bin\jpeg_d.dll",
		"$CeguiDependenciesBuildDirectory\bin\libexpat_d.dll",
		"$CeguiDependenciesBuildDirectory\bin\libpng_d.dll",
		"$CeguiDependenciesBuildDirectory\bin\pcre_d.dll",
		"$CeguiDependenciesBuildDirectory\bin\SILLY_d.dll"
	)
}

if ($Configuration.Length -eq 0 -or $Configuration.Contains("Release"))
{
	& "$PSScriptRoot/shared/build.ps1" -Configuration Release -BuildDirectory $BuildDirectory
	& "$PSScriptRoot/shared/copy.ps1" -Name $Name -OutputDirectory $OutputDirectory -Files @(
		"$BuildDirectory\bin\CEGUIBase-0.dll",
		"$BuildDirectory\bin\CEGUIOgreRenderer-0.dll",
		"$CeguiDependenciesBuildDirectory\bin\freetype.dll",
		"$CeguiDependenciesBuildDirectory\bin\glew.dll",
		"$CeguiDependenciesBuildDirectory\bin\glfw.dll",
		"$CeguiDependenciesBuildDirectory\bin\jpeg.dll",
		"$CeguiDependenciesBuildDirectory\bin\libexpat.dll",
		"$CeguiDependenciesBuildDirectory\bin\libpng.dll",
		"$CeguiDependenciesBuildDirectory\bin\pcre.dll",
		"$CeguiDependenciesBuildDirectory\bin\SILLY.dll"
	)
}
