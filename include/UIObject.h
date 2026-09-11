//
// Created by Ayaan on 2026-08-31.
//

#ifndef QTIP_UIOBJECT_H
#define QTIP_UIOBJECT_H

#include <Q-Tip/Window/Window.h>
#include <Q-Tip/Mods/ModLoader/ModLoader.h>

#include "UIKitMod.h"

union SDL_Event;
struct SDL_Window;

class UIObject {
MODDABLE_ROOT(UIObject)

public:
    UIObject() {
        QTip::ModLoader::mod<UIKitMod>()->_objects.push_back(this);
    }

    virtual ~UIObject() = default;

    virtual void handleEvent(const SDL_Event& event) = 0;
protected:
    static SDL_Window* window(QTip::Window& window) {
        return window;
    }
};

#endif //QTIP_UIOBJECT_H
