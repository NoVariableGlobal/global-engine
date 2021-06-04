[CmdletBinding()]
param (
	[ValidateSet("Debug", "Release")]
	[string[]] $Configuration
)

$ErrorActionPreference = "Stop"

$local:Name = "ogre"
$local:RootDirectory = Split-Path (Split-Path $PSScriptRoot -Parent) -Parent
$local:OutputDirectory = Join-Path -Path $RootDirectory -ChildPath "bin"
$local:DepsDirectory = Join-Path -Path $RootDirectory -ChildPath "deps"
$local:ProjectDirectory = Join-Path -Path $DepsDirectory -ChildPath $Name
$local:BuildDirectory = Join-Path -Path $ProjectDirectory -ChildPath "build"

cmake -S $ProjectDirectory -B $BuildDirectory -Wno-dev @(
	"-DOGRE_BUILD_COMPONENT_OVERLAY:BOOL=OFF"
)

if ($Configuration.Length -eq 0 -or $Configuration.Contains("Debug"))
{
	& "$PSScriptRoot/shared/build.ps1" -Configuration Debug -BuildDirectory $BuildDirectory
	& "$PSScriptRoot/shared/copy.ps1" -Name $Name -OutputDirectory $OutputDirectory -Files @(
		"$BuildDirectory\bin\debug\OgreMain_d.dll",
		"$BuildDirectory\bin\debug\RenderSystem_Direct3D11_d.dll",
		"$BuildDirectory\bin\debug\RenderSystem_GL_d.dll",
		"$BuildDirectory\bin\debug\OgreRTShaderSystem_d.dll",
		"$BuildDirectory\bin\debug\Codec_STBI_d.dll",
		"$BuildDirectory\bin\debug\Plugin_ParticleFX_d.dll",
		"$BuildDirectory\bin\debug\zlib.dll"
	)
}

if ($Configuration.Length -eq 0 -or $Configuration.Contains("Release"))
{
	& "$PSScriptRoot/shared/build.ps1" -Configuration Release -BuildDirectory $BuildDirectory
	& "$PSScriptRoot/shared/copy.ps1" -Name $Name -OutputDirectory $OutputDirectory -Files @(
		"$BuildDirectory\bin\release\OgreMain.dll",
		"$BuildDirectory\bin\release\RenderSystem_Direct3D11.dll",
		"$BuildDirectory\bin\release\RenderSystem_GL.dll",
		"$BuildDirectory\bin\release\OgreRTShaderSystem.dll",
		"$BuildDirectory\bin\release\Codec_STBI.dll",
		"$BuildDirectory\bin\release\Plugin_ParticleFX.dll",
		"$BuildDirectory\bin\release\zlib.dll"
	)
}
