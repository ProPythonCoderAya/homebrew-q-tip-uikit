//
// Created by Ayaan on 2026-09-12.
//

#include "UIKit/Layout/Panel.h"

#include <Q-Tip/Graphics/RenderTarget.h>
#include <SDL3/SDL_events.h>

#include "UIKit/Internal/Helpers.h"

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
    const SDL_Event localEvent =
        Detail::transformEvent(event, _rect.origin);

    for (const auto& object : _objects) {
        object->handleEvent(localEvent);
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

QTip::Point Panel::minimumSize() const {
    if (_objects.empty())
        return {0, 0};
    float left = std::numeric_limits<float>::max();
    float top = std::numeric_limits<float>::max();
    float right = std::numeric_limits<float>::lowest();
    float bottom = std::numeric_limits<float>::lowest();
    for (const auto& object : _objects) {
        const QTip::Rect rect = object->rect();
        left = std::min(left, rect.origin.x);
        top = std::min(top, rect.origin.y);
        right = std::max(right, rect.origin.x + rect.size.x);
        bottom = std::max(bottom, rect.origin.y + rect.size.y);
    }
    return {right - left, bottom - top};
}

QTip::Point Panel::preferredSize() const {
    return _rect.size;
}

void Panel::resize(QTip::Point size) {
    _rect.size = size;
}

void Panel::reposition(QTip::Point position) {
    _rect.origin = position;
}

void Panel::setRect(QTip::Rect rect) {
    _rect = rect;
}

const QTip::Rect& Panel::rect() {
    return _rect;
}
