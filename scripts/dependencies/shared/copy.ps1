[CmdletBinding()]
param (
	[Parameter(Mandatory = $true, Position = 0)]
	[string] $Name,

	[Parameter(Mandatory = $true, Position = 1)]
	[string] $OutputDirectory,

	[Parameter(Mandatory = $true, Position = 2)]
	[string[]] $Files
)

Write-Host "# Now copying " -ForegroundColor Blue -NoNewline
Write-Host $Files.Length    -ForegroundColor Cyan -NoNewline
Write-Host " file(s) from " -ForegroundColor Blue -NoNewline
Write-Host $Name            -ForegroundColor Cyan -NoNewline
Write-Host " to '"          -ForegroundColor Blue -NoNewline
Write-Host $OutputDirectory -ForegroundColor Cyan -NoNewline
Write-Host "'... "          -ForegroundColor Blue -NoNewLine

Copy-Item -Path $Files -Destination $OutputDirectory

Write-Host "Finished!"      -ForegroundColor Green
