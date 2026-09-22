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
    static constexpr std::string_view ID = "propythoncoderaya/uikit";
    static constexpr std::string_view NAME = "UIKit";

    UIKitMod();

    ~UIKitMod() override;

    [[nodiscard]] std::string_view id() const override;

    [[nodiscard]] std::string_view name() const override;

    void init() override;

    void shutdown() override;

    void handleEvent(const SDL_Event& event) override;

    static UIKitMod* instance();
private:
    std::vector<UIObject*> _objects;

    bool _addingChildren = false;

    void add(UIObject* object);

    friend class UIObject;
    friend class Panel;
};

#endif //QTIPUIKIT_UIKITMOD_H
