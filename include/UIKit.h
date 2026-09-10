//
// Created by Ayaan on 2026-09-10.
//

#ifndef QTIPUIKIT_UIKIT_H
#define QTIPUIKIT_UIKIT_H
#include <Q-Tip/Mods/Mod.h>

#include <vector>

class UIObject;

class UIKitMod : public QTip::Mod {
public:
    UIKitMod();

    ~UIKitMod() override;

    std::string_view id() const override;

    std::string_view name() const override;

    void init() override;

    void shutdown() override;

    void handleEvent(const SDL_Event& event) override;
private:
    std::vector<UIObject*> _objects;

    friend class UIObject;
};

#include <Textbox.h>

#endif //QTIPUIKIT_UIKIT_H
