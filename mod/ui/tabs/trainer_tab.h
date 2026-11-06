#pragma once

#include "config/mod_config.h"
#include <imgui.h>
#include <string>

#include "features/word_test.h"
#include "ui/localization.h"
#include "ui/theme.h"
#include "ui/widgets.h"

namespace ModUI::Tabs::Trainer {
inline void section_label(const char *text) {
    const ModUI::Theme::Palette &p = ModUI::Theme::palette();
    ImGui::PushStyleColor(ImGuiCol_Text, ModUI::Theme::with_alpha(p.text_primary, 0.62f));
    ImGui::TextUnformatted(text && text[0] ? text : "Section");
    ImGui::PopStyleColor();
    ImGui::Dummy(ImVec2(0.0f, 5.0f));
}

inline void render_word_test() {
    section_label(ModUI::Localization::translate("trainer.section.wordtest"));

    bool enabled = WordTest::enabled();
    if (ModUI::Widgets::toggle(ModUI::Localization::translate("trainer.wordtest"), &enabled))
        WordTest::set_enabled(enabled);

    const ModUI::Theme::Palette &p = ModUI::Theme::palette();
    ImGui::PushStyleColor(ImGuiCol_Text, ModUI::Theme::with_alpha(p.text_primary, 0.62f));
    ImGui::PushTextWrapPos(0.0f);
    ImGui::TextUnformatted(ModUI::Localization::translate("trainer.wordtest.hint"));
    ImGui::PopTextWrapPos();
    ImGui::PopStyleColor();

    ImGui::Dummy(ImVec2(0.0f, 10.0f));
    const std::string hotkey =
        ModConfig::word_test_hotkey ? ModUI::Widgets::key_name(ModConfig::word_test_hotkey)
                                    : std::string(ModUI::Localization::translate("trainer.hotkey.disabled"));
    ModUI::Widgets::key_value(ModUI::Localization::translate("trainer.hotkey"), hotkey.c_str());
}

inline void render() {
    render_word_test();
}
} // namespace ModUI::Tabs::Trainer
