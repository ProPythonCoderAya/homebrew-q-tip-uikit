//
// Created by Ayaan on 2026-08-31.
//

#ifndef QTIP_UIOBJECT_H
#define QTIP_UIOBJECT_H

#include <Q-Tip/Window/Window.h>
#include <Q-Tip/Mods/ModLoader/ModLoader.h>

#include "QTipUIKit/UIKitMod.h"

union SDL_Event;
struct SDL_Window;

class UIObject {
MODDABLE_ROOT(UIObject)

public:
    UIObject() {
        UIKitMod::instance()->add(this);
    }

    virtual ~UIObject() {
        UIKitMod::instance()->remove(this);
    }

    int zIndex() const {return _z;}
    void setZIndex(const int z) {
        _z = z;
        if (parent)
            parent->_zVersion++;
    }

    virtual void render(QTip::Window& window) = 0;
    virtual bool handleEvent(const SDL_Event& event) {return true;}

    [[nodiscard]] virtual QTip::Point minimumSize() const = 0;
    [[nodiscard]] virtual QTip::Point preferredSize() const = 0;

    virtual void resize(QTip::Point size) = 0;
    virtual void reposition(QTip::Point position) = 0;
    virtual void setRect(QTip::Rect rect) = 0;
    [[nodiscard]] virtual const QTip::Rect& rect() = 0;

    UIObject* parent = nullptr;

protected:
    QTip::Rect _rect{};
    QTip::Rect _preferredRect{};
    static SDL_Window* window(QTip::Window& window) {
        return window;
    }
    int _z;

    // Mostly only for panels, just helps with sorting
    int _zVersion = 0;
};

#endif //QTIP_UIOBJECT_H
