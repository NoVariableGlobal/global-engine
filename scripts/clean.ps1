$local:RootDirectory = Split-Path $PSScriptRoot -Parent
$local:OutputDirectory = Join-Path -Path $RootDirectory -ChildPath "bin"
$local:DepsDirectory = Join-Path -Path $RootDirectory -ChildPath "deps"

$local:DllFiles = Get-ChildItem -Path $OutputDirectory -Filter "*.dll";

Write-Host "# Now deleting " -ForegroundColor Blue -NoNewline
Write-Host $DllFiles.Length  -ForegroundColor Cyan -NoNewline
Write-Host " file(s) from '" -ForegroundColor Blue -NoNewline
Write-Host $OutputDirectory  -ForegroundColor Cyan -NoNewline
Write-Host "'... "           -ForegroundColor Blue -NoNewLine

if ($DllFiles.Length -ne 0) {
	$DllFiles | Remove-Item | Out-Null
	Write-Host "Finished!"           -ForegroundColor Green
} else {
	Write-Host "Skipped."            -ForegroundColor DarkGray
}

Remove-Variable DllFiles

function Remove-Directory([string] $Path) {
	Write-Host "# Now deleting folder '" -ForegroundColor Blue -NoNewline
	Write-Host $Path                     -ForegroundColor Cyan -NoNewline
	Write-Host "'... "                   -ForegroundColor Blue -NoNewLine

	If (Test-Path -Path $Path) {
		Remove-Item -LiteralPath $Path -Recurse | Out-Null
		Write-Host "Finished!" -ForegroundColor Green
	} Else {
		Write-Host "Skipped."  -ForegroundColor DarkGray
	}
}

Remove-Directory -Path (Join-Path -Path $DepsDirectory -ChildPath "bullet/build")
Remove-Directory -Path (Join-Path -Path $DepsDirectory -ChildPath "cegui/build")
Remove-Directory -Path (Join-Path -Path $DepsDirectory -ChildPath "cegui-dependencies/build")
Remove-Directory -Path (Join-Path -Path $DepsDirectory -ChildPath "drakhtar-i18n/build")
Remove-Directory -Path (Join-Path -Path $DepsDirectory -ChildPath "jsoncpp/build")
Remove-Directory -Path (Join-Path -Path $DepsDirectory -ChildPath "ogre/build")
