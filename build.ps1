param (
    [Parameter(Position = 0)]
    [ValidateScript( { Test-Path -LiteralPath $_ -PathType Leaf })]
    [string]
    $MsBuild = "",

    [switch] $Build,
    [switch] $Release,
    [string] $Target,
    [string] $Property,
    [string] $Platform = "x64",

    [Alias("Parallel")]
    [switch] $SequentialBuild,
    [switch] $AllCores,

    [ValidateSet('q', 'quiet', 'm', 'minimal', 'n', 'normal', 'd', 'detailed', 'diag', 'diagnostic')]
    [string] $Verbosity = "normal",
    [switch] $DisplayLogo,

    [Alias("Parameters", "Params", "P")]
    [string[]] $MsBuildParameters
)

if ($MsBuild.Length -Eq 0) {
    $PossibleMsBuild = Resolve-Path "${Env:ProgramFiles(x86)}\Microsoft Visual Studio\2019\*\MSBuild\*\Bin\MSBuild.exe"
    If ($PossibleMsBuild.Length -Ge 0) {
        $MsBuild = $PossibleMsBuild[0]
        Write-Host "MsBuild not providen, using '" -ForegroundColor Blue -NoNewline
        Write-Host $MsBuild                        -ForegroundColor Cyan -NoNewline
        Write-Host "' instead."                    -ForegroundColor Blue
        Write-Host ""
    } Else {
        throw "I could not find MsBuild"
    }
}

If ($MsBuildParameters.Length -Eq 0) {
    If ($Target -Eq "" -And (!$Build.IsPresent -Or $Build.ToBool())) {
        $Target = "-t:Build"
    }

    If ($Property -Eq "") {
        $PropertyConfiguration = If ($Release.ToBool()) { "Release" } Else { "Debug" }
        $Property = "-p:Configuration=$PropertyConfiguration;Platform=$Platform"
    }

    $BuildInParallelArgument = If ($SequentialBuild.ToBool()) { "" } Else { "-m" }
    $MaxCpuCountArgument = If (!$AllCores.IsPresent -Or $AllCores.ToBool()) { "-maxCpuCount" } Else { "" }
    $NoLogoArgument = If ($DisplayLogo.ToBool()) { "" } Else { "-noLogo" }
    $VerbosityArgument = "-verbosity:$Verbosity"
    $MsBuildParameters = @($Target, $Property, $VerbosityArgument, $BuildInParallelArgument, $MaxCpuCountArgument, $NoLogoArgument)
}

$RootFolder = "$($PSScriptRoot)"

function Step-VisualStudio ([string] $ProjectPath) {
    & $MsBuild $ProjectPath $MsBuildParameters
}

Step-VisualStudio "$RootFolder\P3\ProyectoBase\ProyectoBase.sln"
