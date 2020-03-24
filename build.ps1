param (
    [Parameter(Position = 0)]
    [ValidateScript( { Test-Path -LiteralPath $_ -PathType Leaf })]
    [string]
    $MsBuild = "",

    [string] $CMake = "cmake",
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
    }
    ElseIf ($Env:MSBUILD) {
        $MsBuild = (Resolve-Path $Env:MSBUILD)[0]
        Write-Host "MsBuild not providen, using '"           -ForegroundColor Blue -NoNewline
        Write-Host $MsBuild                                  -ForegroundColor Cyan -NoNewline
        Write-Host "' from environmental variables instead." -ForegroundColor Blue
    }

    If (!(Test-Path -LiteralPath $MsBuild -PathType Leaf)) {
        Write-Host "I was not able to find MSBuild.exe, please check https://docs.microsoft.com/visualstudio/msbuild/msbuild?view=vs-2019 for more information." -ForegroundColor Red
        Write-Host "  # Please specify the route to the MSBuild.exe by doing " -ForegroundColor Yellow -NoNewline
        Write-Host ".\build.ps1 `"Path\To\MSBuild.exe`""                       -ForegroundColor Cyan   -NoNewline
        Write-Host " or "                                                      -ForegroundColor Yellow -NoNewline
        Write-Host ".\build.ps1 -MsBuild `"Path\To\MSBuild.exe`""              -ForegroundColor Cyan   -NoNewline
        Write-Host " to set the path."                                         -ForegroundColor Yellow
        Write-Host "  # Alternatively, do "                                    -ForegroundColor Yellow -NoNewline
        Write-Host "`$Env:MsBuild=`"Path\To\MSBuild.exe`""                     -ForegroundColor Cyan   -NoNewline
        Write-Host ", afterwards you will be able to execute "                 -ForegroundColor Yellow -NoNewline
        Write-Host ".\build.ps1"                                               -ForegroundColor Cyan   -NoNewline
        Write-Host " normally."                                                -ForegroundColor Yellow
        Exit 1
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
$BinaryDirectory = "$RootFolder\P3\ProyectoBase\bin"
$DependenciesRoot = "$RootFolder\P3\ProyectoBase\lib"

function Step-VisualStudioRaw([string] $Path, [string[]] $Arguments) {
    & $MsBuild $Path $Arguments
}

function Step-VisualStudioThirdPartyDebug([string] $Path) {
    Write-Host "# Now building '" -ForegroundColor Blue -NoNewline
    Write-Host $Path              -ForegroundColor Cyan -NoNewline
    Write-Host "' as Debug."      -ForegroundColor Blue

    Step-VisualStudioRaw $Path @("-t:Build", "-p:Configuration=Debug;Platform=x64;WarningLevel=0", "-m", "-maxCpuCount", "-noLogo", "-verbosity:quiet")
}

function Step-VisualStudioThirdPartyRelease([string] $Path) {
    Write-Host "# Now building '" -ForegroundColor Blue -NoNewline
    Write-Host $Path              -ForegroundColor Cyan -NoNewline
    Write-Host "' as Release."    -ForegroundColor Blue

    Step-VisualStudioRaw $Path @("-t:Build", "-p:Configuration=Release;Platform=x64;WarningLevel=0", "-m", "-maxCpuCount", "-noLogo", "-verbosity:quiet")
}

function Step-VisualStudio([string] $Path) {
    Write-Host "# Now building '"             -ForegroundColor Blue -NoNewline
    Write-Host $Path                          -ForegroundColor Cyan -NoNewline
    Write-Host "' as $PropertyConfiguration." -ForegroundColor Blue

    Step-VisualStudioRaw $Path $MsBuildParameters
}

function Step-CopyToBinaryDirectory([string] $From, [string[]] $Paths) {
    Write-Host "# Now copying " -ForegroundColor Blue -NoNewline
    Write-Host $Paths.Length    -ForegroundColor Cyan -NoNewline
    Write-Host " file(s) from " -ForegroundColor Blue -NoNewline
    Write-Host $From            -ForegroundColor Cyan -NoNewline
    Write-Host " to '"          -ForegroundColor Blue -NoNewline
    Write-Host $BinaryDirectory -ForegroundColor Cyan -NoNewline
    Write-Host "'... "          -ForegroundColor Blue -NoNewLine

    Copy-Item -Path $Paths -Destination $BinaryDirectory

    Write-Host "Finished!"      -ForegroundColor Green
}

function Step-CMake([string] $Path, [string[]] $Arguments) {
    New-Item -ItemType Directory -Force -Path "$Path\build"
    & $CMake -S $Path -B "$Path\build" $Arguments
}

# Bullet
$BulletFolder = "$DependenciesRoot\bullet3-2.89"
Step-CMake $BulletFolder  @(
    "-DBUILD_BULLET2_DEMOS:BOOL=OFF",
    "-DBUILD_BULLET3:BOOL=ON",
    "-DBUILD_CLSOCKET:BOOL=OFF",
    "-DBUILD_CPU_DEMOS:BOOL=OFF",
    "-DBUILD_ENET:BOOL=OFF",
    "-DBUILD_EXTRAS:BOOL=OFF",
    "-DBUILD_OPENGL3_DEMOS:BOOL=OFF",
    "-DBUILD_PYBULLET:BOOL=OFF",
    "-DBUILD_SHARED_LIBS:BOOL=OFF",
    "-DBUILD_UNIT_TESTS:BOOL=OFF",
    "-DUSE_MSCV_RUNTIME_LIBRARY_DLL:BOOL=ON"
)
Step-VisualStudioThirdPartyDebug "$BulletFolder\build\ALL_BUILD.vcxproj"
Step-VisualStudioThirdPartyRelease "$BulletFolder\build\ALL_BUILD.vcxproj"

# FMod
# $FModFolder = "$DependenciesRoot\fmod"

# JsonCPP
$JsonFolder = "$DependenciesRoot\jsoncpp-master"
Step-CMake $JsonFolder @()
Step-VisualStudioThirdPartyRelease "$JsonFolder\build\ALL_BUILD.vcxproj"

# Ogre
$OgreFolder = "$DependenciesRoot\ogre-1.12.5"
Step-CMake $OgreFolder @("-DOGRE_BUILD_COMPONENT_OVERLAY:BOOL=OFF")
Step-VisualStudioThirdPartyDebug "$OgreFolder\build\ALL_BUILD.vcxproj"
Step-VisualStudioThirdPartyRelease "$OgreFolder\build\ALL_BUILD.vcxproj"
Step-CopyToBinaryDirectory "Ogre" @(
    "$OgreFolder\build\bin\debug\OgreMain_d.dll",
    "$OgreFolder\build\bin\debug\RenderSystem_Direct3D11_d.dll",
    "$OgreFolder\build\bin\debug\RenderSystem_GL_d.dll",
    "$OgreFolder\build\bin\debug\OgreRTShaderSystem_d.dll",
    "$OgreFolder\build\bin\debug\Codec_STBI_d.dll",
    "$OgreFolder\build\bin\release\OgreMain.dll",
    "$OgreFolder\build\bin\release\RenderSystem_Direct3D11.dll",
    "$OgreFolder\build\bin\release\RenderSystem_GL.dll",
    "$OgreFolder\build\bin\release\zlib.dll",
    "$OgreFolder\build\bin\release\OgreRTShaderSystem.dll",
    "$OgreFolder\build\bin\release\Codec_STBI.dll"
)

# SDL2
$Sdl2Folder = "$DependenciesRoot\SDL2-2.0.10"
Step-CopyToBinaryDirectory "SDL2" @(
    "$Sdl2Folder\lib\x64\SDL2.dll"
)

# Global Engine
Step-VisualStudio "$RootFolder\P3\ProyectoBase\ProyectoBase.sln"
