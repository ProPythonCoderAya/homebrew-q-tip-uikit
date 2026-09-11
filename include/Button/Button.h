//
// Created by Ayaan on 2026-09-11.
//

#ifndef QTIPUIKIT_BUTTON_H
#define QTIPUIKIT_BUTTON_H
#include <UIObject.h>

#include "Internal/Helpers.h"

struct ButtonStyle {
    QTip::Color color;
    QTip::Color hoverColor;
    QTip::Color pressedColor;
    QTip::Color disabledColor;

    QTip::Font font{Detail::defaultFontPath(), 16};
};

class Button : public UIObject {
MODDABLE_DERIVED(Button, UIObject)

public:
    Button(float x, float y, float width, float height, std::string_view text, const ButtonStyle& style);
    Button(QTip::Rect rect, std::string_view text, const ButtonStyle& style);

    void handleEvent(const SDL_Event& event) override;

private:
    ButtonStyle _style;
    std::string _text;
    QTip::Rect _rect{};
};

#endif //QTIPUIKIT_BUTTON_H
