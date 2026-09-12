//
// Created by Ayaan on 2026-09-12.
//

#include "Widgets/Label/Label.h"

#include "Internal/Helpers.h"

Label::Label(const std::string& text, QTip::Color color, QTip::Point position, const std::optional<QTip::Font>& font, bool centered) : _font(Detail::defaultFontPath(), 16) {
    if (font.has_value()) {
        _font = font.value();
    }
    _text = text;
    _color = color;
    _position = position;
    _centered = centered;
}

void Label::render(QTip::Window& window) {
    if (_centered)
        window->renderTextCentered(_font, _text.c_str(), _position.x, _position.y, _color);
    else
        window->renderText(_font, _text.c_str(), _position.x, _position.y, _color);
}

void Label::reposition(QTip::Point position) {
    _position = position;
}

void Label::setText(const std::string& text) {
    _text = text;
}

const std::string& Label::text() const {
    return _text;
}
