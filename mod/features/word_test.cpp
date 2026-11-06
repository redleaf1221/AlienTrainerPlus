#include "word_test.h"

#include "config/mod_config.h"
#include "game/game_types.h"
#include "support/mod_log.h"

#include <string_view>
#include <vector>

#include <windows.h>

namespace {

bool g_enabled = false;
bool g_hotkey_was_down = false;

// URKit keeps the last failure in a thread-local slot; return it only when set.
const char *last_error_text() {
    const char *error = URK::Unity::last_error();
    return (error && error[0]) ? error : nullptr;
}

bool write_testword(bool value) {
    URK::Unity::clear_error();
    AlienTrainer::Global::set_testword(value);
    if (const char *error = last_error_text()) {
        ModLog::warn("wordtest: Global.testword write failed: %s", error);
        return false;
    }
    return true;
}

// The demo called Object.FindObjectsOfType<AlienCharacter>(); the generated
// wrapper does the same lookup through UnityEngine.Object.
void refresh_characters() {
    URK::Unity::clear_error();
    const std::vector<AlienTrainer::AlienCharacter> characters = AlienTrainer::AlienCharacter::FindAll();
    if (const char *error = last_error_text()) {
        // FindAll() reports "no non-null instances found" for an empty scene; that
        // is a normal state (main menu), not a failure.
        if (std::string_view(error).find("no non-null instances found") != std::string_view::npos) {
            URK::Unity::clear_error();
            ModLog::info("wordtest: no alien characters in the current scene");
            return;
        }
        ModLog::warn("wordtest: AlienCharacter lookup failed: %s", error);
        return;
    }

    std::size_t refreshed = 0;
    for (const AlienTrainer::AlienCharacter &character : characters) {
        if (!character)
            continue;
        URK::Unity::clear_error();
        character.UpdateEarthText();
        if (const char *error = last_error_text()) {
            ModLog::warn("wordtest: UpdateEarthText failed on instance %d: %s", static_cast<int>(refreshed), error);
            return;
        }
        ++refreshed;
    }
    ModLog::info("wordtest: refreshed %zu alien character(s)", refreshed);
}

} // namespace

namespace WordTest {

bool enabled() {
    return g_enabled;
}

void initialize() {
    ModLog::info("wordtest: ready, hotkey VK=0x%02X (toggle also lives in the "
                 "Trainer tab)",
                 ModConfig::word_test_hotkey);
}

void update() {
    const int hotkey = ModConfig::word_test_hotkey;
    if (hotkey == 0) {
        g_hotkey_was_down = false;
        return;
    }
    const bool down = (::GetAsyncKeyState(hotkey) & 0x8000) != 0;
    if (down && !g_hotkey_was_down)
        set_enabled(!g_enabled);
    g_hotkey_was_down = down;
}

void set_enabled(bool value) {
    if (value == g_enabled) {
        // Still refresh: the field may have been reset by the game.
        if (value)
            refresh_characters();
        return;
    }
    if (!write_testword(value)) {
        ModLog::warn("wordtest: keeping previous state (%s)", g_enabled ? "on" : "off");
        return;
    }
    g_enabled = value;
    ModLog::info("wordtest: %s", value ? "on" : "off");
    refresh_characters();
}

void refresh() {
    if (!g_enabled)
        return;
    if (write_testword(true))
        refresh_characters();
}

void on_scene_loaded() {
    // Retail ships isDemo == false; a demo build still has it set. The original
    // trainer cleared it in a Harmony prefix on Global.Init.
    URK::Unity::clear_error();
    if (AlienTrainer::Global::isDemo()) {
        AlienTrainer::Global::set_isDemo(false);
        if (const char *error = last_error_text())
            ModLog::warn("wordtest: clearing Global.isDemo failed: %s", error);
        else
            ModLog::info("wordtest: cleared Global.isDemo");
    }

    // The new scene spawned fresh AlienCharacter instances.
    refresh();
}

} // namespace WordTest
