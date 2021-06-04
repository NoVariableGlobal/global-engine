[CmdletBinding()]
param (
	[ValidateSet("Debug", "Release")]
	[string[]] $Configuration,

	[string] $OutputDirectory
)

$ErrorActionPreference = "Stop"

$local:Name = "SDL2"
$local:RootDirectory = Split-Path (Split-Path $PSScriptRoot -Parent) -Parent
$local:OutputDirectory ??= Join-Path -Path $RootDirectory -ChildPath "bin"
$local:DepsDirectory = Join-Path -Path $RootDirectory -ChildPath "deps"
$local:ProjectDirectory = Join-Path -Path $DepsDirectory -ChildPath $Name

& "$PSScriptRoot/shared/copy.ps1" -Name $Name -OutputDirectory $OutputDirectory -Files @(
	"$ProjectDirectory\lib\x64\SDL2.dll"
)
