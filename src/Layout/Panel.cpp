//
// Created by Ayaan on 2026-09-12.
//

#include "Layout/Panel.h"

#include <Q-Tip/Graphics/RenderTarget.h>

Panel::Panel(const QTip::Rect rect) {
    _rect = rect;
}

void Panel::render(QTip::Window& window) {
    QTip::RenderTarget target{window.getRenderer(), _rect.size};

    window->setTarget(target);

    for (const auto& object : _objects) {
        object->render(window);
    }

    window->resetTarget();

    window->renderTexture(target, QTip::Rect::zero, _rect);
}

void Panel::handleEvent(const SDL_Event& event) {
    for (const auto& object : _objects) {
        object->handleEvent(event);
    }
}

void Panel::resize(const QTip::Rect rect) {
    _rect = rect;
}

const QTip::Rect& Panel::rect() const {
    return _rect;
}

void Panel::remove(UIObject& object) {
    const auto it = std::ranges::find_if(_objects,
         [&object](const std::unique_ptr<UIObject>& ptr) {
             return ptr.get() == &object;
         }
    );

    if (it != _objects.end()) {
        _objects.erase(it);
    }
}

void Panel::clear() {
    _objects.clear();
}
