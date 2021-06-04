# Version: 2.0.1

param (
	[switch] $Clean,

	[ValidateSet("Debug", "Release")]
	[string[]] $Configuration = @("Debug", "Release"),

	# Dependencies
	[bool] $BuildDependencies = $true,

	# Project
	[bool] $BuildProject = $true
)

$ErrorActionPreference = "Stop"

If ($Clean)
{
	& "$PSScriptRoot/clean.ps1"
}

if ($BuildDependencies)
{
	& "$PSScriptRoot/dependencies/build-all.ps1" -Configuration $Configuration
}

if ($BuildProject)
{
	& "$PSScriptRoot/build-project.ps1" -Configuration $Configuration
}
