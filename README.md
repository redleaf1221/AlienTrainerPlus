# AlienTrainerPlus

Generated URKit IL2CPP mod project for Windows x64. The output DLL is a URKit loader plugin, not a standalone injectable DLL.

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

## Documentation

See the [URKit SDK Handbook](https://github.com/Jadis0x/URKit/blob/main/docs/SDK_HANDBOOK.md) for the complete GameObject/component API, Unity access, threading, lifecycle, hooks, UI, highlight rendering, and unload rules. The highlight chapter explains exactly how generated overlays are submitted through DX11, DX12, or OpenGL.

Include `sdk/unity/unity.h` for Unity work. Resolve the target object and component, then access the required member. Keep Unity calls on the main thread and check `Unity::last_error()` after an unexpected empty result.

## Project files

- `mod/lifecycle/mod_runtime.cpp`: game/runtime and main-thread work.
- `mod/hooks/mod_hooks.cpp`: exact, validated hook installation.
- `mod/lifecycle/mod_network.cpp`: HTTPS setup and policy.
- `mod/support/mod_log.cpp`: shared logging.
- `mod/config/mod_config.h` and `mod/ui/theme.h`: metadata and styling.

Files under `sdk/`, `mod/generated/`, native hook support, and the build profiles are refreshed by the generator. Files under `mod/ui/`, other user-owned files, and new sources under `mod/` are preserved.

## MCP runtime tests

Generated projects include `sdk/dev_test.h`. Export `URK_DevTestCount`, `URK_DevTestDescribe`, and `URK_DevTestRun` from a user-owned source under `mod/` to make runtime tests discoverable through `URKitDevBridge.dll`. The development MCP guide is available in the URKit release documentation.

## Runtime constraints

- `sdk/mod_sdk.h` is the ABI source of truth. Check version, size, backend, capability, and function pointers before use.
- Include `sdk/unity/unity.h` for normal Unity work. Use exact overload helpers when required and keep Unity calls on the main thread.
- Resolve stable metadata once instead of repeating lookups in update/render callbacks.
- Detach hooks, callbacks, coroutines, workers, and UI before unload.
- DX11, DX12, and OpenGL overlays are supported; Vulkan is not.
- `sdk/il2cpp/il2cpp_runtime.h`, `sdk/il2cpp/il2cpp_helpers.h`: generated IL2CPP runtime adapter headers.
- Locale JSON files under `locales/` are preserved and deployed beside the DLL.

## Stripped members

IL2CPP and Mono builds drop UnityEngine members the game never calls. A stripped member returns the default value, which reads the same as a legitimate empty result.

- Probe first: `Unity::has_method(Unity::GameObjectType, "get_scene", 0)`, `Unity::has_property(type, "tag")`, or a wrapper helper such as `Unity::GameObject::scene_available()`.
- Disable the feature when the member is gone. Do not report the default as data.
- Against your own Unity project, `Assets/link.xml` with `<linker><assembly fullname="UnityEngine.CoreModule" preserve="all"/></linker>` keeps the member. A shipped game gives you no such option.

Start troubleshooting with `URKit_logs.log` beside the game executable.
