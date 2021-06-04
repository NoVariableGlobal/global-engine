param (
	[ValidateSet("Debug", "Release")]
	[string[]] $Configuration = @("Debug", "Release")
)

$ErrorActionPreference = "Stop"

$local:RootDirectory = Split-Path $PSScriptRoot -Parent
$local:Path = Join-Path -Path $RootDirectory -ChildPath "one-thousand-years.sln"

# Find and assert MSBuild
$local:MsBuild = $Env:MsBuild                                                                                                                   `
	?? (Get-Command "MSBuild.exe" -ErrorAction SilentlyContinue)?.Path                                                                          `
	?? (Resolve-Path "${Env:ProgramFiles(x86)}\Microsoft Visual Studio\2019\*\MSBuild\*\Bin\MSBuild.exe" -ErrorAction SilentlyContinue)?[0].Path;

if ([string]::IsNullOrEmpty($MsBuild))
{
	Write-Host "I was not able to find MSBuild.exe, please check https://docs.microsoft.com/visualstudio/msbuild/msbuild?view=vs-2019 for more information." -ForegroundColor Red
	Write-Host "  # Please specify the route to the MSBuild.exe by doing " -ForegroundColor Yellow -NoNewline
	Write-Host ".\scripts\build.ps1 `"Path\To\MSBuild.exe`""               -ForegroundColor Cyan   -NoNewline
	Write-Host " or "                                                      -ForegroundColor Yellow -NoNewline
	Write-Host ".\scripts\build.ps1 -MsBuild `"Path\To\MSBuild.exe`""      -ForegroundColor Cyan   -NoNewline
	Write-Host " to set the path."                                         -ForegroundColor Yellow
	Write-Host "  # Alternatively, do "                                    -ForegroundColor Yellow -NoNewline
	Write-Host "`$Env:MsBuild=`"Path\To\MSBuild.exe`""                     -ForegroundColor Cyan   -NoNewline
	Write-Host ", afterwards you will be able to execute "                 -ForegroundColor Yellow -NoNewline
	Write-Host ".\scripts\build.ps1"                                       -ForegroundColor Cyan   -NoNewline
	Write-Host " normally."                                                -ForegroundColor Yellow
	exit 1
}

function Step-VisualStudio
{
	param (
		[string] $BuildType
	)

	Write-Host "# Now building '"     -ForegroundColor Blue -NoNewline
	Write-Host $Path                  -ForegroundColor Cyan -NoNewline
	Write-Host "' as $BuildType." -ForegroundColor Blue

	# Run the process
	$private:startTime = Get-Date
	& $MsBuild $Path @("-t:build", "-p:Configuration=$BuildType;Platform=x64;WarningLevel=3", "-verbosity:minimal", "-m", "-noLogo")
	$private:exitTime = Get-Date

	# Print information to the screen
	$private:duration = $exitTime - $startTime
	if ($LastExitCode -eq 0)
	{
		Write-Host "# Finished building '" -ForegroundColor Green -NoNewLine
		Write-Host $Path                   -ForegroundColor Cyan  -NoNewLine
		Write-Host "'. Took: "             -ForegroundColor Green -NoNewLine
		Write-Host ("{0:g}" -f $duration)  -ForegroundColor Cyan  -NoNewLine
		Write-Host "."                     -ForegroundColor Green
	}
	else
	{
		Write-Host "# Errored when building '"        -ForegroundColor Red  -NoNewLine
		Write-Host $Path                              -ForegroundColor Cyan -NoNewLine
		Write-Host "' with code $LastExitCode Took: " -ForegroundColor Red  -NoNewLine
		Write-Host ("{0:g}" -f $duration)             -ForegroundColor Cyan -NoNewLine
		Write-Host "."                                -ForegroundColor Red
		exit 1
	}
}

foreach ($local:BuildType in $Configuration) {
	Step-VisualStudio -BuildType $BuildType
}
