[CmdletBinding()]
param (
	[ValidateSet("Debug", "Release")]
	[string[]] $Configuration
)

$ErrorActionPreference = "Stop"

$local:Name = "cegui-dependencies"
$local:RootDirectory = Split-Path (Split-Path $PSScriptRoot -Parent) -Parent
$local:DepsDirectory = Join-Path -Path $RootDirectory -ChildPath "deps"
$local:ProjectDirectory = Join-Path -Path $DepsDirectory -ChildPath $Name
$local:BuildDirectory = Join-Path -Path $ProjectDirectory -ChildPath "build"

cmake -S $ProjectDirectory -B $BuildDirectory -Wno-dev

if ($Configuration.Length -eq 0 -or $Configuration.Contains("Debug"))
{
	& "$PSScriptRoot/shared/build.ps1" -Configuration Debug -BuildDirectory $BuildDirectory
}

if ($Configuration.Length -eq 0 -or $Configuration.Contains("Release"))
{
	& "$PSScriptRoot/shared/build.ps1" -Configuration Release -BuildDirectory $BuildDirectory
}
