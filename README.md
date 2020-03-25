# One Thousand Years

One Thousand Years is an utility engine powered by [Ogre3D], [BulletPhysics], [SDL2], [FMod], [JsonCPP], and more.
Written in C++, it aims to give a base for our games, [Mood] and [G.Shift].

## Set-Up

There are two ways to set-up, we provide a [PowerShell] script to make things easier, but you can also set up everything
manually if you prefer or if the automated script gives you problems (please open an issue or contact the team if this
happens!).

In advance, we require you to have installed [CMake] and [Visual Studio 2019][VisualStudio2019].

### Automated Set-Up

First of all, you might need to change [PowerShell]'s policy settings to run our script, it is because we provide an
unofficial script, to allow it, you will need to use the [Set-ExecutionPolicy] command, you can safely do the following:

```ps1
Set-ExecutionPolicy Unrestricted -Scope Process
```

> The `-Scope Process` sets the execution policy for the [PowerShell]'s session, meaning it will reset to default once
you close the window. If you drop it, `Scope`'s value will be `LocalMachine`, affecting all users of the computer.

To run the script, we will use an existing [PowerShell] window, you can open it by pressing `Shift` and then do right
click anywhere in the project's folder, it will show you some extra options, including `Open PowerShell window here`.
Alternatively, open a new window and `cd` to the project's folder.

Once you have your [PowerShell] window in this project's folder, run the following command to set up all dependencies
and compile the project:

```ps1
.\build.ps1
```

That's all!

### Manual Set-Up

All the steps will be done with [CMake]'s GUI and [VS2019][VisualStudio2019], you are welcome to use scripts in the
shell of your preference.

#### BulletPhysics

1. Open CMake-GUI and set up the following parameters:
    - Source Code: `P3/ProyectoBase/lib/bullet3-2.89`
    - Build Folder: `P3/ProyectoBase/lib/bullet3-2.89/build`
1. Click on the `Configure` button.
1. Set up the following values:
    - `BUILD_BULLET2_DEMOS`: `OFF`
    - `BUILD_BULLET3`: `ON`
    - `BUILD_CLSOCKET`: `OFF`
    - `BUILD_CPU_DEMOS`: `OFF`
    - `BUILD_ENET`: `OFF`
    - `BUILD_EXTRAS`: `OFF`
    - `BUILD_OPENGL3_DEMOS`: `OFF`
    - `BUILD_PYBULLET`: `OFF`
    - `BUILD_SHARED_LIBS`: `OFF`
    - `BUILD_UNIT_TESTS`: `OFF`
    - `USE_MSVC_RUNTIME_LIBRARY_DLL`: `ON`
1. Click on the `Generate` button.
1. Compile the project (`ALL_BUILD` by default) in `Debug` and `Release`.

#### JsonCPP

1. Open CMake-GUI and set up the following parameters:
    - Source Code: `P3/ProyectoBase/jsoncpp-master`
    - Build Folder: `P3/ProyectoBase/lib/jsoncpp-master/build`
1. Click on the `Configure` button.
1. Click on the `Generate` button.
1. Compile the project (`ALL_BUILD` by default) in `Debug` and `Release`.

#### Ogre

1. Open CMake-GUI and set up the following parameters:
    - Source Code: `P3/ProyectoBase/lib/ogre-1.12.5`
    - Build Folder: `P3/ProyectoBase/lib/ogre-1.12.5/build`
1. Click on the `Configure` button.
1. Set up the following values:
    - `OGRE_BUILD_COMPONENT_OVERLAY`: `OFF`
1. Click on the `Generate` button.
1. Compile the project (`ALL_BUILD` by default) in `Debug` and `Release`.
1. Copy the following files to `P3/ProyectoBase/bin/`:
    - `P3/ProyectoBase/lib/ogre-1.12.5/build/bin/debug/OgreMain_d.dll`
    - `P3/ProyectoBase/lib/ogre-1.12.5/build/bin/debug/RenderSystem_Direct3D11_d.dll`
    - `P3/ProyectoBase/lib/ogre-1.12.5/build/bin/debug/RenderSystem_GL_d.dll`
    - `P3/ProyectoBase/lib/ogre-1.12.5/build/bin/debug/OgreRTShaderSystem_d.dll`
    - `P3/ProyectoBase/lib/ogre-1.12.5/build/bin/debug/Codec_STBI_d.dll`
    - `P3/ProyectoBase/lib/ogre-1.12.5/build/bin/release/OgreMain.dll`
    - `P3/ProyectoBase/lib/ogre-1.12.5/build/bin/release/RenderSystem_Direct3D11.dll`
    - `P3/ProyectoBase/lib/ogre-1.12.5/build/bin/release/RenderSystem_GL.dll`
    - `P3/ProyectoBase/lib/ogre-1.12.5/build/bin/release/zlib.dll`
    - `P3/ProyectoBase/lib/ogre-1.12.5/build/bin/release/OgreRTShaderSystem.dll`
    - `P3/ProyectoBase/lib/ogre-1.12.5/build/bin/release/Codec_STBI.dll`

#### SDL2

1. Copy the following files to `P3/ProyectoBase/bin/`:
    - `P3/ProyectoBase/lib/SDL2-2.0.10/lib/x64/SDL2.dll`

> If you encountered any issues, please open an issue including the steps taken and the warnings or errors you
encountered. If you found no problem so far, you should be able to compile this project without problems.

## Contributing

1. Fork it!
1. Create your feature branch: `git checkout -b my-new-feature`
1. Commit your changes: `git commit -am 'Add some feature'`
1. Push to the branch: `git push origin my-new-feature`
1. Submit a pull request!

## Author

**One Thousand Years** © [NoVariableGlobal][author], released under the
[MIT][license] License.
Authored and maintained by NoVariableGlobal.

> Github [NoVariableGlobal][author] - Twitter [@\_\_NVG\_\_][twitter]

[license]: https://github.com/NoVariableGlobal/global-engine/blob/master/LICENSE
[author]: https://github.com/NoVariableGlobal
[twitter]: https://twitter.com/__NVG__

[Mood]: https://github.com/NoVariableGlobal/mood
[G.Shift]: https://github.com/NoVariableGlobal/g.shift
[Ogre3D]: https://www.ogre3d.org/
[BulletPhysics]: https://github.com/bulletphysics/bullet3
[SDL2]: https://www.libsdl.org/
[FMod]: https://fmod.com/
[JsonCPP]: https://github.com/open-source-parsers/jsoncpp
[PowerShell]: https://wikipedia.org/wiki/PowerShell
[Set-ExecutionPolicy]: https://docs.microsoft.com/powershell/module/microsoft.powershell.security/set-executionpolicy
[CMake]: https://cmake.org/
[VisualStudio2019]: https://visualstudio.microsoft.com/vs/
