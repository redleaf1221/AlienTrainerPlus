#pragma once

namespace ModConfig {
inline constexpr const char* project_name = "AlienTrainerPlus";
// Stable namespace for this mod's deployed resources. Do not change it after release.
inline constexpr const char* mod_id = "AlienTrainerPlus_8eaa1031";
inline constexpr const char* display_name = "AlienTrainerPlus";
inline constexpr const char* author = "MathTangent";
inline constexpr const char* version = "0.1.0";
inline constexpr const char* url = "";
inline constexpr const char* social = "";
inline constexpr const char* description = "I HAVE APHASIA";
inline constexpr bool is_il2cpp_backend = true;
// Closed at start, so the game keeps its input; a one-time hint names the key.
inline bool show_menu = false;
// English is used as the fixed language when localization support is not generated.
inline bool enable_localization = true;
inline constexpr const char* default_language = "zh";
// Lets ImGui windows move to another monitor.
inline bool enable_detached_viewports = false;
// Win32 virtual-key code for the word test (official translation) toggle.
// Default: VK_F9 (0x78). 0 disables the hotkey; the Trainer tab still works.
inline int word_test_hotkey = 0x78;
// Win32 virtual-key code used by the generated ImGui WndProc toggle.
// Default: VK_TAB (0x09). Change this value to customize the menu key.
inline int menu_toggle_key = 0x09;
} // namespace ModConfig
