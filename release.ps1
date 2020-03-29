function New-Directory([string[]] $Path) {
    If (!(Test-Path -Path $Path)) {
        New-Item -Path $Path -Force -ItemType Directory | Out-Null
    }
}

function Remove-Directory([string[]] $Path) {
    Remove-Item -Path $TempFolder -Recurse
}

function New-TemporaryDirectory {
    $private:Path = Join-Path -Path $Env:TEMP -ChildPath (New-Guid)
    New-Directory -Path $Path
    return $Path;
}

function Find-7Zip {
    # Find from PATH environmental variables:
    If (Get-Command "7z" -ErrorAction SilentlyContinue) {
        $private:7ZipPath = (Get-Command "7z").Path;
        Write-Host "Using '"      -ForegroundColor Blue -NoNewline
        Write-Host $7ZipPath      -ForegroundColor Cyan -NoNewline
        Write-Host "' from PATH." -ForegroundColor Blue
        return $7ZipPath
    }

    # Find from ProgramFiles:
    $local:ProgramFiles7Zip = Join-Path -Path $Env:ProgramFiles -ChildPath "7-Zip/7z.exe"
    If (Test-Path -Path $ProgramFiles7Zip) {
        Write-Host "Using '"         -ForegroundColor Blue -NoNewline
        Write-Host $ProgramFiles7Zip -ForegroundColor Cyan -NoNewline
        Write-Host "'."              -ForegroundColor Blue
        return $ProgramFiles7Zip
    }

    Write-Host "7-Zip not installed in this system, falling back to download and install..." -ForegroundColor Magenta

    # Create a temporary directory in which 7-Zip's installer will be downloaded:
    $private:TempFolder = New-TemporaryDirectory

    # Define the source to download the installer from, and invoke a web request:
    $private:Source = "https://www.7-zip.org/a/7z1900-x64.msi"
    Invoke-WebRequest $Source -OutFile $TempFolder

    Write-Host " - Successfully downloaded 7-Zip." -ForegroundColor Green

    # Resolve the path to the 7-Zip installer, execute msiexec on it for install:
    $private:7ZipInstaller = Join-Path -Path $TempFolder -ChildPath "7-Zip.msi"
    & msiexec.exe -i "$7ZipInstaller" -q -n

    Write-Host " - Successfully installed 7-Zip." -ForegroundColor Green

    # Remove the temporary directory:
    Remove-Directory -Path $TempFolder

    # Ideally, the executable should be at "C:/Program Files/7-Zip/7z.exe", test:
    If (Test-Path -Path $ProgramFiles7Zip) {
        Write-Host "Using '"         -ForegroundColor Blue -NoNewline
        Write-Host $ProgramFiles7Zip -ForegroundColor Cyan -NoNewline
        Write-Host "'."              -ForegroundColor Blue
        return $ProgramFiles7Zip
    }

    # All previous steps failed and 7-Zip was not installed, throw an error:
    throw "I could not find 7-Zip, and installation failed."
}

$private:7Zip = Find-7Zip

$private:RootFolder = "$($PSScriptRoot)"
$private:BinFolder = Join-Path -Path $RootFolder -ChildPath "P3/ProyectoBase/bin"

$private:ReleaseOS = If ($Env:RELEASE_OS) { $Env:RELEASE_OS } Else { "unknown" }
$private:ReleaseName = If ($Env:RELEASE_NAME) { $Env:RELEASE_NAME } Else { "unknown" }
$private:ReleasePath = Join-Path -Path $RootFolder -ChildPath ".release/GlobalEngine-$ReleaseOS-$ReleaseName.zip"

Push-Location -Path $BinFolder
& $7Zip a -tzip $ReleasePath "*"
Pop-Location

Write-Host "Finished all tasks! Release available at: '" -ForegroundColor Green -NoNewline
Write-Host $ReleasePath                                  -ForegroundColor Cyan  -NoNewline
Write-Host "'. Enjoy!"                                   -ForegroundColor Green
