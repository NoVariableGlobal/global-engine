[CmdletBinding()]
param (
	[ValidateSet("Debug", "Release")]
	[string[]] $Configuration,

	[string] $OutputDirectory
)

$ErrorActionPreference = "Stop"

$local:Name = "drakhtar-i18n"
$local:RootDirectory = Split-Path (Split-Path $PSScriptRoot -Parent) -Parent
$local:OutputDirectory ??= Join-Path -Path $RootDirectory -ChildPath "bin"
$local:DepsDirectory = Join-Path -Path $RootDirectory -ChildPath "deps"
$local:ProjectDirectory = Join-Path -Path $DepsDirectory -ChildPath $Name
$local:BuildDirectory = Join-Path -Path $ProjectDirectory -ChildPath "build"

cmake -S $ProjectDirectory -B $BuildDirectory -Wno-dev @(
	"-DCMAKE_DEBUG_POSTFIX=_d",
	"-DI18N_LANGUAGE_ALL:BOOL=ON"
)

if ($Configuration.Length -eq 0 -or $Configuration.Contains("Debug"))
{
	& "$PSScriptRoot/shared/build.ps1" -Configuration Debug -BuildDirectory $BuildDirectory
	& "$PSScriptRoot/shared/copy.ps1" -Name $Name -OutputDirectory $OutputDirectory -Files @(
		"$BuildDirectory\src\Debug\i18n_d.dll"
	)
}

if ($Configuration.Length -eq 0 -or $Configuration.Contains("Release"))
{
	& "$PSScriptRoot/shared/build.ps1" -Configuration Release -BuildDirectory $BuildDirectory
	& "$PSScriptRoot/shared/copy.ps1" -Name $Name -OutputDirectory $OutputDirectory -Files @(
		"$BuildDirectory\src\Release\i18n.dll"
	)
}
