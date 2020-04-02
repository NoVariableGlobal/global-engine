param(
    [switch] $Interactive,
    [switch] $Format,
    [switch] $Build,
    [switch] $Release,
    [string[]] $ReleaseArguments
)

$ErrorActionPreference = "Stop"

$local:ProjectName = "One Thousand Years"
$local:RootFolder = Split-Path $PSScriptRoot -Parent

function Read-Boolean {
    [OutputType([bool])]
    param (
        [string] $Message
    )

    $private:value = Read-Host -Prompt "$Message [y/n]"
    Switch -regex ($value.ToLower()) {
        "y(es?|eah?)?" { Return $True }
        "n(o|ah?)?" { Return $False }
        Default { Return Read-Boolean -Message $Message }
    }
}

If ($Interactive) {
    If (!$Format.IsPresent) {
        $Format = Read-Boolean -Message "Format all of $ProjectName's source files"
    }

    If (!$Build.IsPresent) {
        $Build = Read-Boolean -Message "Build all dependencies and $ProjectName"
    }

    If (!$Release.IsPresent) {
        $Release = Read-Boolean -Message "Generate a release ZIP for $ProjectName"
    }
}

If ($Format) {
    # Prints information about the step being taken
    Write-Host "Formatting " -ForegroundColor Blue -NoNewline
    Write-Host $ProjectName  -ForegroundColor Cyan -NoNewline
    Write-Host "... "        -ForegroundColor Blue

    # Run the process
    $private:duration = Measure-Command {
        & "$RootFolder\scripts\format.ps1"
    }

    # Print information to the screen
    If ($LastExitCode -Eq 0) {
        Write-Host "# Finished in "       -ForegroundColor Green -NoNewLine
        Write-Host ("{0:g}" -f $duration) -ForegroundColor Cyan  -NoNewLine
        Write-Host "."                    -ForegroundColor Green
    } Else {
        Write-Host "# Errored with code $LastExitCode in " -ForegroundColor Red  -NoNewLine
        Write-Host ("{0:g}" -f $duration)                  -ForegroundColor Cyan -NoNewLine
        Write-Host "."                                     -ForegroundColor Red
        Throw "Failed to format the project.";
    }
}

If ($Build) {
    # Prints information about the step being taken
    Write-Host "Building "  -ForegroundColor Blue -NoNewline
    Write-Host $ProjectName -ForegroundColor Cyan -NoNewline
    Write-Host "... "       -ForegroundColor Blue

    # Run the process
    $private:startTime = Get-Date
    & "$RootFolder\scripts\build.ps1"
    $private:exitTime = Get-Date

    # Print information to the screen
    $private:duration = $exitTime - $startTime
    If ($LastExitCode -Eq 0) {
        Write-Host "# Finished in "       -ForegroundColor Green -NoNewLine
        Write-Host ("{0:g}" -f $duration) -ForegroundColor Cyan  -NoNewLine
        Write-Host "."                    -ForegroundColor Green
    } Else {
        Write-Host "# Errored with code $LastExitCode in " -ForegroundColor Red  -NoNewLine
        Write-Host ("{0:g}" -f $duration)                  -ForegroundColor Cyan -NoNewLine
        Write-Host "."                                     -ForegroundColor Red
        Throw "Failed to build the project.";
    }
}

If ($Release) {
    # Prints information about the step being taken
    Write-Host "Releasing " -ForegroundColor Blue -NoNewline
    Write-Host $ProjectName -ForegroundColor Cyan -NoNewline
    Write-Host "... "       -ForegroundColor Blue

    # Run the process
    $private:startTime = Get-Date
    & "$RootFolder\scripts\release.ps1" $ReleaseArguments
    $private:exitTime = Get-Date

    # Print information to the screen
    $private:duration = $exitTime - $startTime
    If ($LastExitCode -Eq 0) {
        Write-Host "# Finished in "       -ForegroundColor Green -NoNewLine
        Write-Host ("{0:g}" -f $duration) -ForegroundColor Cyan  -NoNewLine
        Write-Host "."                    -ForegroundColor Green
    } Else {
        Write-Host "# Errored with code $LastExitCode in " -ForegroundColor Red  -NoNewLine
        Write-Host ("{0:g}" -f $duration)                  -ForegroundColor Cyan -NoNewLine
        Write-Host "."                                     -ForegroundColor Red
        Throw "Failed to release the project.";
    }
}
