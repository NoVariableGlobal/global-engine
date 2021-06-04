[CmdletBinding()]
param (
	[ValidateSet("Debug", "Release")]
	[string[]] $Configuration,

	[string] $OutputDirectory
)

$ErrorActionPreference = "Stop"

& "$PSScriptRoot/build-bullet.ps1" -Configuration $Configuration
& "$PSScriptRoot/build-ogre.ps1" -Configuration $Configuration -OutputDirectory $OutputDirectory
& "$PSScriptRoot/build-cegui-dependencies.ps1" -Configuration $Configuration
& "$PSScriptRoot/build-cegui.ps1" -Configuration $Configuration -OutputDirectory $OutputDirectory
& "$PSScriptRoot/build-fmod.ps1" -Configuration $Configuration -OutputDirectory $OutputDirectory
& "$PSScriptRoot/build-jsoncpp.ps1" -Configuration $Configuration -OutputDirectory $OutputDirectory
& "$PSScriptRoot/build-SDL2.ps1" -Configuration $Configuration -OutputDirectory $OutputDirectory
& "$PSScriptRoot/build-drakhtar-i18n.ps1" -Configuration $Configuration -OutputDirectory $OutputDirectory

exit $LastExitCode
