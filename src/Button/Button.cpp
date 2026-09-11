//
// Created by Ayaan on 2026-09-11.
//

#include "Button/Button.h"

#include <SDL3/SDL_events.h>

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
    switch (event.type) {
    default:
        break;
        
    }
}
