param(
    [Alias("ClangFormat")]
    [Parameter(Position = 0)]
    [ValidateScript( { Test-Path -LiteralPath $_ -PathType Leaf })]
    [string]
    $ClangFormatPath = "",

    [switch] $Test
)

$ErrorActionPreference = "Stop"

# Finds clang-format.exe from the user's input, falling back in the following order:
#  - Environmental Variable
#  - Get-Command (PATH)
#  - Program Files typical installation path scan
function Find-ClangFormat {
    # Check if a path was given:
    if ($ClangFormatPath.Length -Eq 0) {
        # Find from environmental variable:
        If ($Env:ClangFormat) {
            $ClangFormat = (Resolve-Path $Env:ClangFormat)[0].Path
            Write-Host "ClangFormat not provided, using '"       -ForegroundColor Blue -NoNewline
            Write-Host $ClangFormat                              -ForegroundColor Cyan -NoNewline
            Write-Host "' from environmental variables instead." -ForegroundColor Blue
            return $ClangFormat;
        }

        # Find from PATH environmental variables:
        If (Get-Command "clang-format.exe" -ErrorAction SilentlyContinue) {
            $ClangFormat = (Get-Command "clang-format.exe").Path;
            Write-Host "ClangFormat not provided, using '" -ForegroundColor Blue -NoNewline
            Write-Host $ClangFormat                        -ForegroundColor Cyan -NoNewline
            Write-Host "' from PATH instead."              -ForegroundColor Blue
            return $ClangFormat;
        }

        # Find from ProgramFiles:
        $local:PossibleClangFormat = Resolve-Path "${Env:ProgramFiles(x86)}\Microsoft Visual Studio\2019\*\VC\Tools\Llvm\bin\clang-format.exe" -ErrorAction SilentlyContinue
        If (($PossibleClangFormat) -And ($PossibleClangFormat.Length -Ge 0)) {
            $ClangFormat = $PossibleClangFormat[0].Path
            Write-Host "ClangFormat not provided, using '" -ForegroundColor Blue -NoNewline
            Write-Host $ClangFormat                        -ForegroundColor Cyan -NoNewline
            Write-Host "' from file detection instead."    -ForegroundColor Blue
            return $ClangFormat;
        }
    } Else {
        $ClangFormat = $ClangFormatPath;
        return $ClangFormat;
    }
}

# Asserts that the variable assigned to $ClangFormat is a valid file path, discarding files that do not exist and folders.
function Assert-ClangFormatPath([string] $private:ClangFormat) {
    If (($ClangFormat -Eq "") -Or !(Test-Path -LiteralPath $ClangFormat -PathType Leaf)) {
        Write-Host "I was not able to find clang-format.exe, please check https://docs.microsoft.com/en-us/visualstudio/?view=vs-2019 for more information." -ForegroundColor Red
        Write-Host "  # Please specify the route to the clang-format.exe by doing " -ForegroundColor Yellow -NoNewline
        Write-Host ".\scripts\format.ps1 `"Path\To\clang-format.exe`""              -ForegroundColor Cyan   -NoNewline
        Write-Host " or "                                                           -ForegroundColor Yellow -NoNewline
        Write-Host ".\scripts\format.ps1 -ClangFormat `"Path\To\clang-format.exe`"" -ForegroundColor Cyan   -NoNewline
        Write-Host " to set the path."                                              -ForegroundColor Yellow
        Write-Host "  # Alternatively, do "                                         -ForegroundColor Yellow -NoNewline
        Write-Host "`$Env:ClangFormat=`"Path\To\clang-format.exe`""                 -ForegroundColor Cyan   -NoNewline
        Write-Host ", afterwards you will be able to execute "                      -ForegroundColor Yellow -NoNewline
        Write-Host ".\scripts\format.ps1"                                           -ForegroundColor Cyan   -NoNewline
        Write-Host " normally."                                                     -ForegroundColor Yellow
        Exit 1
    }
}

$ClangFormat = Find-ClangFormat
Assert-ClangFormatPath $ClangFormat

# Formats all files in-place.
function Step-Format([string[]] $Files) {
    # Prints information about the step being taken
    Write-Host "Formatting... " -ForegroundColor Blue -NoNewLine

    # Run the process
    $private:duration = Measure-Command {
        & $ClangFormat -style=file -i $FormatFiles
    }

    # Print information to the screen
    If ($LastExitCode -Eq 0) {
        Write-Host "Took: "               -ForegroundColor Green -NoNewLine
        Write-Host ("{0:g}" -f $duration) -ForegroundColor Cyan  -NoNewLine
        Write-Host "."                    -ForegroundColor Green
    } Else {
        Write-Host "Errored with code $LastExitCode. Took: " -ForegroundColor Red  -NoNewLine
        Write-Host ("{0:g}" -f $duration)                    -ForegroundColor Cyan -NoNewLine
        Write-Host "."                                       -ForegroundColor Red
        Throw "Failed to format file.";
    }
}

# Tests if any of the files need formatting.
function Test-Format([string[]] $Files) {
    # Prints information about the step being taken
    Write-Host "Testing style... " -ForegroundColor Blue -NoNewLine

    # Run the process
    $private:duration = Measure-Command {
        $Replacements = & $ClangFormat -style=file -output-replacements-xml $FormatFiles
    }

    # Print information to the screen
    If ($LastExitCode -Eq 0) {
        Write-Host "Took: "               -ForegroundColor Green -NoNewLine
        Write-Host ("{0:g}" -f $duration) -ForegroundColor Cyan  -NoNewLine
        Write-Host ". "                   -ForegroundColor Green -NoNewLine
    } Else {
        Write-Host "Errored with code $LastExitCode. Took: " -ForegroundColor Red  -NoNewLine
        Write-Host ("{0:g}" -f $duration)                    -ForegroundColor Cyan -NoNewLine
        Write-Host "."                                       -ForegroundColor Red
        Throw "Failed to format file.";
    }

    # Count the amount of replacements
    $Changes = $Replacements | grep -c "<replacement "
    If ($Changes -Eq "0") {
        Write-Host "No replacements needed!" -ForegroundColor Green
    } Else {
        Write-Host "$Changes replacements needed!" -ForegroundColor Red
        Write-Host $Replacements                   -ForegroundColor Magenta
        Throw "$Changes replacements needed!"
    }
}

Try {
    # Scan the files
    Write-Host "Scanning files... " -ForegroundColor Blue -NoNewline
    $private:Duration = Measure-Command {
        $FormatFiles = (Get-ChildItem src | Select-Object -ExpandProperty FullName)
    }
    Write-Host "Found "            -ForegroundColor Green -NoNewLine
    Write-Host $FormatFiles.Length -ForegroundColor Cyan  -NoNewLine
    Write-Host " files."           -ForegroundColor Green

    # If -Test is present, test if the formatting is correct,
    # else format the files in-place.
    If ($Test) {
        Test-Format -Files $FormatFiles
    } Else {
        Step-Format -Files $FormatFiles
    }

    Exit 0
} Catch {
    # Write the exception
    Write-Host -Object $_
    Write-Host -Object $_.Exception
    Write-Host -Object $_.ScriptStackTrace

    Exit 1
}
