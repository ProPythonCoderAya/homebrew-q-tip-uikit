//
// Created by Ayaan on 2026-09-11.
//

#ifndef QTIPUIKIT_UIKITMOD_H
#define QTIPUIKIT_UIKITMOD_H
#include <Q-Tip/Mods/Mod.h>

#include <vector>

class UIObject;

class UIKitMod : public QTip::Mod {
public:
    UIKitMod();

    ~UIKitMod() override;

    [[nodiscard]] std::string_view id() const override;

    [[nodiscard]] std::string_view name() const override;

    void init() override;

    void shutdown() override;

    void handleEvent(const SDL_Event& event) override;
private:
    std::vector<UIObject*> _objects;

    friend class UIObject;
};

#endif //QTIPUIKIT_UIKITMOD_H
