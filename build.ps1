function Step-Run {
    [CmdletBinding()]
    param (
        [Parameter(Mandatory = $true, Position = 0)]
        [ValidateScript( { Test-Path -LiteralPath $_ -PathType Leaf })]
        [string]
        $MsBuild,

        [ValidateScript( { Test-Path -LiteralPath $_ -PathType Leaf })]
        [string]
        $ProjectPath = "$($PSScriptRoot)\P3\ProyectoBase\ProyectoBase.sln",

        [switch] $Build,
        [switch] $Release = $false,
        [string] $Target,
        [string] $Property,
        [string] $Platform = "x64",

        [Alias("Parallel")]
        [switch] $BuildInParallel,
        [switch] $AllCores,

        [ValidateSet('q', 'quiet', 'm', 'minimal', 'n', 'normal', 'd', 'detailed', 'diag', 'diagnostic')]
        [string] $Verbosity = "normal",
        [switch] $NoLogo,

        [Alias("Parameters", "Params", "P")]
        [string] $MsBuildParameters
    )

    begin {
        If ($MsBuildParameters -Eq "") {
            If ($Target -Eq "" -And (!$Build.IsPresent -Or $Build.ToBool())) {
                $Target = "-t:Build"
            }

            If ($Property -Eq "") {
                $PropertyConfiguration = If ($Release.ToBool()) { "Release" } Else { "Debug" }
                $Property = "-p:Configuration=$PropertyConfiguration;Platform=$Platform"
            }

            $BuildInParallelArgument = If (!$BuildInParallel.IsPresent -Or $BuildInParallel.ToBool()) { "-m" } Else { "" }
            $MaxCpuCountArgument = If (!$AllCores.IsPresent -Or $AllCores.ToBool()) { "-maxCpuCount" } Else { "" }
            $NoLogoArgument = If (!$NoLogo.IsPresent -Or $NoLogo.ToBool()) { "-noLogo" } Else { "" }
            $VerbosityArgument = "-verbosity:$Verbosity"
            $MsBuildParameters = "$Target $Property $VerbosityArgument $BuildInParallelArgument $MaxCpuCountArgument $NoLogoArgument"
        }
    }

    process {
        & $MsBuild $ProjectPath @($Target, $Property, $BuildInParallelArgument, $VerbosityArgument, $MaxCpuCountArgument, $NoLogoArgument)
    }

    end {
        Write-Host ""
        Write-Host "All jobs finished!"
    }
}

Step-Run
