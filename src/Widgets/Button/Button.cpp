//
// Created by Ayaan on 2026-09-11.
//

#include "Widgets/Button/Button.h"

#include <SDL3/SDL_events.h>

#include <utility>

Button::Button(float x, float y, float width, float height, std::string_view text, const ButtonStyle& style) {
    _style = style;
    _rect = QTip::Rect{x, y, width, height};
    _text = std::string(text);
}

Button::Button(QTip::Rect rect, std::string_view text, const ButtonStyle& style) {
    _style = style;
    _rect = rect;
    _text = std::string(text);
}

void Button::handleEvent(const SDL_Event& event) {
    if (_disabled) {
        _state = ButtonState::Disabled;
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
            _state = ButtonState::Pressed;
        }
        break;
    case SDL_EVENT_MOUSE_BUTTON_UP:
        if (_state == ButtonState::Pressed) {
            if (_rect.isPointInside({
                event.button.x,
                event.button.y
            })) {
                if (_onClick) _onClick();
                _state = ButtonState::Hovered;
            } else
                _state = ButtonState::Normal;
        }
        break;
    case SDL_EVENT_MOUSE_MOTION:
        if (_rect.isPointInside({
            event.motion.x,
            event.motion.y
        })) {
            if (_state != ButtonState::Pressed)
                _state = ButtonState::Hovered;
        }
        else {
            if (_state != ButtonState::Pressed)
                _state = ButtonState::Normal;
        }
        break;
    }
}

void Button::render(QTip::Window& window) {
    switch (_state) {
    case ButtonState::Normal:
        window->setRenderColor(_style.color);
        break;
    case ButtonState::Hovered:
        window->setRenderColor(_style.hoverColor);
        break;
    case ButtonState::Pressed:
        window->setRenderColor(_style.pressedColor);
        break;
    case ButtonState::Disabled:
        window->setRenderColor(_style.disabledColor);
        break;
    }
    window->renderRoundedRect(_rect, 10);

    window->renderTextCentered(_style.font, _text.c_str(), _rect.center().x, _rect.center().y, _style.fontColor);
}

void Button::setText(std::string text) {
    _text = std::move(text);
}

const std::string& Button::text() const {
    return _text;
}

void Button::resize(QTip::Rect rect) {
    _rect = rect;
}

const QTip::Rect& Button::rect() const {
    return _rect;
}

void Button::setOnClick(std::function<void()> callback) {
    _onClick = std::move(callback);
}

void Button::disable() {
    if (!_disabled)
        _state = ButtonState::Disabled;
    _disabled = true;
}

void Button::enable() {
    if (_disabled)
        _state = ButtonState::Normal;
    _disabled = false;
}

void Button::setDisabled(bool disabled) {
    if (disabled)
        disable();
    else
        enable();
}

bool Button::isDisabled() const {
    return _disabled;
}
