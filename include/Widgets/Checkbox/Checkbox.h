//
// Created by Ayaan on 2026-09-11.
//

#ifndef QTIPUIKIT_CHECKBOX_H
#define QTIPUIKIT_CHECKBOX_H
#include <UIObject.h>

#include "Internal/Helpers.h"

struct CheckboxStyle {
    QTip::Color color;
    QTip::Color hoverColor;
    QTip::Color pressedColor;
    QTip::Color disabledColor;
};

enum class CheckboxState {
    Normal,
    Hovered,
    Pressed,
    Disabled
};

class Checkbox : public UIObject {
MODDABLE_DERIVED(Checkbox, UIObject)

public:
    Checkbox(float x, float y, float width, float height, const CheckboxStyle& style);
    Checkbox(QTip::Rect rect, const CheckboxStyle& style);

    void handleEvent(const SDL_Event& event) override;

    void render(QTip::Window& window) override;

    void resize(QTip::Rect rect);
    [[nodiscard]] const QTip::Rect& rect() const;

    void disable();
    void enable();
    [[nodiscard]] bool isDisabled() const;

    bool checked;

private:
    CheckboxStyle _style;
    CheckboxState _state = CheckboxState::Normal;
    QTip::Rect _rect{};

    bool _disabled = false;

    static void renderCheckmark(QTip::Window& window, QTip::Rect rect);
};

#endif //QTIPUIKIT_CHECKBOX_H
