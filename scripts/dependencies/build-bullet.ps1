[CmdletBinding()]
param (
	[ValidateSet("Debug", "Release")]
	[string[]] $Configuration
)

$ErrorActionPreference = "Stop"

$local:Name = "bullet"
$local:RootDirectory = Split-Path (Split-Path $PSScriptRoot -Parent) -Parent
$local:DepsDirectory = Join-Path -Path $RootDirectory -ChildPath "deps"
$local:ProjectDirectory = Join-Path -Path $DepsDirectory -ChildPath $Name
$local:BuildDirectory = Join-Path -Path $ProjectDirectory -ChildPath "build"

cmake -S $ProjectDirectory -B $BuildDirectory -Wno-dev @(
	"-DBUILD_BULLET2_DEMOS:BOOL=OFF",
	"-DBUILD_BULLET3:BOOL=ON",
	"-DBUILD_EXTRAS:BOOL=OFF",
	"-DBUILD_OPENGL3_DEMOS:BOOL=OFF",
	"-DBUILD_PYBULLET:BOOL=OFF",
	"-DBUILD_SHARED_LIBS:BOOL=OFF",
	"-DBUILD_UNIT_TESTS:BOOL=OFF",
	"-DUSE_MSVC_RUNTIME_LIBRARY_DLL:BOOL=ON"
)

if ($Configuration.Length -eq 0 -or $Configuration.Contains("Debug"))
{
	& "$PSScriptRoot/shared/build.ps1" -Configuration Debug -BuildDirectory $BuildDirectory
}

if ($Configuration.Length -eq 0 -or $Configuration.Contains("Release"))
{
	& "$PSScriptRoot/shared/build.ps1" -Configuration Release -BuildDirectory $BuildDirectory
}
