# Version: 2.0.1

param (
	[switch] $Clean,

	[ValidateSet("Debug", "Release")]
	[string[]] $Configuration = @("Debug", "Release"),

	# Dependencies
	[bool] $BuildDependencies = $true,

	# Project
	[bool] $BuildProject = $true,

	[string] $OutputDirectory
)

$ErrorActionPreference = "Stop"

If ($Clean)
{
	& "$PSScriptRoot/clean.ps1"
}

if ($BuildDependencies)
{
	if ([string]::IsNullOrEmpty($OutputDirectory))
	{
		$OutputDirectory = Join-Path -Path (Split-Path $PSScriptRoot -Parent) -ChildPath "bin"
	}
	& "$PSScriptRoot/dependencies/build-all.ps1" -Configuration $Configuration -OutputDirectory $OutputDirectory
}

if ($BuildProject)
{
	& "$PSScriptRoot/build-project.ps1" -Configuration $Configuration
}

exit $LastExitCode
