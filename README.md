# AlienTrainerPlus

Cheat for game *Message From Aliens* full version.

## Features

- Press F9 to see official translation for words.

## Build

Use Clang from PowerShell or MSVC from an x64 Visual Studio Developer PowerShell.

```powershell
cmake --preset clang-debug
cmake --build --preset clang-debug --parallel
# Or, from an x64 Visual Studio Developer PowerShell:
cmake --preset msvc-debug
cmake --build --preset msvc-debug --parallel
```

Use `clang-release` or `msvc-release` for release builds. Builds deploy to the selected game's `Mods` directory.

## LICENSE

AGPL-3.0
