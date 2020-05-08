function New-Directory([string[]] $Path) {
	If (!(Test-Path -Path $Path)) {
		New-Item -Path $Path -Force -ItemType Directory | Out-Null
	}
}

Export-ModuleMember -Function New-Directory
