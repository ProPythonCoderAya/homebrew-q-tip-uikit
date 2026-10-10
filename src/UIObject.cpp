//
// Created by Ayaan on 2026-10-09.
//

#include <QTipUIKit/UIObject.h>
#include <QTipUIKit/UIContext.h>

#include "QTipUIKit/UIKitMod.h"

UIObject::~UIObject() {
    if (_context)
        _context->remove(this);
}

void UIObject::regWindow(QTip::Window& window) {
    if (_window)
        return;

    auto& storedContext =
        window.v<std::shared_ptr<UIContext>>("context");

    if (!storedContext) {
        UIKitMod::instance()->log("Window does not have a UIContext", LOG_ERROR);
        return;
    }

    _window = &window;
    _context = storedContext.get();

    if (parent)
        return;
    _context->add(this);
}
