[CmdletBinding()]
param (
	[ValidateSet("Debug", "Release")]
	[string[]] $Configuration
)

& "$PSScriptRoot/build-bullet.ps1" @args
& "$PSScriptRoot/build-ogre.ps1" @args
& "$PSScriptRoot/build-cegui-dependencies.ps1" @args
& "$PSScriptRoot/build-cegui.ps1" @args
& "$PSScriptRoot/build-fmod.ps1" @args
& "$PSScriptRoot/build-jsoncpp.ps1" @args
& "$PSScriptRoot/build-SDL2.ps1" @args
& "$PSScriptRoot/build-drakhtar-i18n.ps1" @args
