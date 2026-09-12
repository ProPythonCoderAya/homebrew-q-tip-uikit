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
    QTip::Color fontColor;
};

enum class ButtonState {
    Normal,
    Hovered,
    Pressed,
    Disabled
};

class Button : public UIObject {
MODDABLE_DERIVED(Button, UIObject)

public:
    Button(float x, float y, float width, float height, std::string_view text, const ButtonStyle& style);
    Button(QTip::Rect rect, std::string_view text, const ButtonStyle& style);

    void handleEvent(const SDL_Event& event) override;

    void render(QTip::Window& window) override;

    void setText(std::string text);
    [[nodiscard]] const std::string& text() const;

    void resize(QTip::Rect rect);
    [[nodiscard]] const QTip::Rect& rect() const;

    void setOnClick(std::function<void()> callback);

    void disable();
    void enable();
    void setDisabled(bool disabled);
    [[nodiscard]] bool isDisabled() const;

private:
    ButtonStyle _style;
    ButtonState _state = ButtonState::Normal;
    std::string _text;
    QTip::Rect _rect{};
    std::function<void()> _onClick;

    bool _disabled = false;
};

#endif //QTIPUIKIT_BUTTON_H
