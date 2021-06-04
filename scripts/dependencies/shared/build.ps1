[CmdletBinding()]
param (
	[ValidateSet("Debug", "Release")]
	[string] $Configuration,

	[Parameter(Mandatory = $true)]
	[string] $BuildDirectory,

	[string[]] $CompilerOptions
)

Write-Host "# Now building '"     -ForegroundColor Blue -NoNewline
Write-Host $BuildDirectory        -ForegroundColor Cyan -NoNewline
Write-Host "' as $Configuration." -ForegroundColor Blue

# Run the process
$private:start = Get-Date
& cmake --build $BuildDirectory --config $Configuration -j -- -m -noLogo "-p:WarningLevel=0" $CompilerOptions
$private:end = Get-Date

# Print information to the screen
$private:duration = $end - $start
if ($?)
{
	Write-Host "# Finished building '" -ForegroundColor Green -NoNewLine
	Write-Host $BuildDirectory         -ForegroundColor Cyan  -NoNewLine
	Write-Host "' as "                 -ForegroundColor Green -NoNewLine
	Write-Host $Configuration          -ForegroundColor Cyan  -NoNewLine
	Write-Host ". Took: "              -ForegroundColor Green -NoNewLine
	Write-Host ("{0:g}" -f $duration)  -ForegroundColor Cyan  -NoNewLine
	Write-Host "."                     -ForegroundColor Green
}
else
{
	Write-Host "# Errored when building '"       -ForegroundColor Red  -NoNewLine
	Write-Host $BuildDirectory                   -ForegroundColor Cyan -NoNewLine
	Write-Host "' as "                           -ForegroundColor Red  -NoNewLine
	Write-Host $Configuration                    -ForegroundColor Cyan -NoNewLine
	Write-Host " with code $LastExitCode Took: " -ForegroundColor Red  -NoNewLine
	Write-Host ("{0:g}" -f $duration)            -ForegroundColor Cyan -NoNewLine
	Write-Host "."                               -ForegroundColor Red
}

exit $LastExitCode
