#pragma once

// Port of the demo trainer's WordTestFeature + HotkeyManager.
//
// Demo (C#/BepInEx):
//   Global.testword = Enabled;
//   foreach (var c in Object.FindObjectsOfType<AlienCharacter>())
//       c.UpdateEarthText();
//   F9 toggles Enabled.
//
// Retail (IL2CPP): same two game calls, driven from the mod's main-thread
// update instead of a MonoBehaviour.Update.

namespace WordTest {
/// Current toggle state as last written to Global.testword.
bool enabled();

/// Writes Global.testword and refreshes every AlienCharacter in the scene.
/// Leaves the previous state untouched when the game write fails.
void set_enabled(bool value);

/// Re-applies the current state (used after a scene load spawns new
/// characters).
void refresh();

/// One-time setup; logs the hotkey so it shows up in URKit_logs.log.
void initialize();

/// Main-thread tick: edge-detects F9.
void update();

/// Scene hook: clears Global.isDemo when a demo build is running, then
/// refreshes.
void on_scene_loaded();
} // namespace WordTest
