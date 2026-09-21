//
// Created by Ayaan on 2026-09-11.
//

#include "Widgets/Checkbox/Checkbox.h"

#include <SDL3/SDL_events.h>

Checkbox::Checkbox(float x, float y, float width, float height, const CheckboxStyle& style) {
    _style = style;
    _rect = QTip::Rect{x, y, width, height};
    checked = false;
}

Checkbox::Checkbox(QTip::Rect rect, const CheckboxStyle& style) {
    _style = style;
    _rect = rect;
    checked = false;
}

void Checkbox::handleEvent(const SDL_Event& event) {
    if (_disabled) {
        _state = CheckboxState::Disabled;
        return;
    }
    switch (event.type) {
    default:
        break;
    case SDL_EVENT_MOUSE_BUTTON_DOWN:
        if (_rect.isPointInside({
            event.button.x,
            event.button.y
        })) {
            _state = CheckboxState::Pressed;
        }
        break;
    case SDL_EVENT_MOUSE_BUTTON_UP:
        if (_state == CheckboxState::Pressed) {
            if (_rect.isPointInside({
                event.button.x,
                event.button.y
            })) {
                checked = !checked;
                _state = CheckboxState::Hovered;
            } else
                _state = CheckboxState::Normal;
        }
        break;
    case SDL_EVENT_MOUSE_MOTION:
        if (_rect.isPointInside({
            event.motion.x,
            event.motion.y
        })) {
            if (_state != CheckboxState::Pressed)
                _state = CheckboxState::Hovered;
        }
        else {
            if (_state != CheckboxState::Pressed)
                _state = CheckboxState::Normal;
        }
        break;
    }
}

void Checkbox::render(QTip::Window& window) {
    switch (_state) {
    case CheckboxState::Normal:
        window->setRenderColor(_style.color);
        break;
    case CheckboxState::Hovered:
        window->setRenderColor(_style.hoverColor);
        break;
    case CheckboxState::Pressed:
        window->setRenderColor(_style.pressedColor);
        break;
    case CheckboxState::Disabled:
        window->setRenderColor(_style.disabledColor);
        break;
    }
    window->renderRoundedRect(_rect, 5);

    window->setRenderColor(QTip::Color::blue);
    if (checked)
        renderCheckmark(window, {_rect.origin + QTip::Point{5, 5}, _rect.size - QTip::Point{10, 10}});
}

QTip::Point Checkbox::minimumSize() const {
    return {20, 20}; // only best size
}

QTip::Point Checkbox::preferredSize() const {
    return _preferredRect.size; // we want what the user had set
}

void Checkbox::resize(QTip::Point size) {
    _rect.size = size;
    _preferredRect.size = size;
}

void Checkbox::reposition(QTip::Point position) {
    _rect.origin = position;
    _preferredRect.origin = position;
}

void Checkbox::setRect(QTip::Rect rect) {
    _rect = rect;
}

const QTip::Rect& Checkbox::rect() {
    return _rect;
}

void Checkbox::disable() {
    _disabled = true;
    _state = CheckboxState::Disabled;
}

void Checkbox::enable() {
    _disabled = false;
    _state = CheckboxState::Normal;
}

bool Checkbox::isDisabled() const {
    return _disabled;
}

void Checkbox::renderCheckmark(QTip::Window& window, QTip::Rect rect) {
    auto lastRectSize = rect.size;
    rect.size = QTip::Point{1, 1} * std::min(rect.size.x, rect.size.y);
    rect.origin += (lastRectSize - rect.size) / 2.0f;
    QTip::Point a = {0.0f, rect.size.y / 2.0f};
    QTip::Point b = {rect.size.x / 2.0f, rect.size.y};
    QTip::Point c = {rect.size.x, 0.0f};
    a += rect.origin;
    b += rect.origin;
    c += rect.origin;
    float thickness = rect.size.x / 5.0f;
    window->renderThickLine({a, b}, thickness, true);
    window->renderThickLine({c, b}, thickness, true);
}
