//
// Created by Ayaan on 2026-09-12.
//

#ifndef QTIPUIKIT_LABEL_H
#define QTIPUIKIT_LABEL_H
#include <UIObject.h>

class Label : public UIObject {
MODDABLE_DERIVED(Label, UIObject)

public:
    Label(const std::string& text, QTip::Color color, QTip::Point position, const std::optional<QTip::Font>& font, bool centered = false);

    void render(QTip::Window& window) override;

    void reposition(QTip::Point position);

    void setText(const std::string& text);
    [[nodiscard]] const std::string& text() const;

private:
    std::string _text;
    QTip::Color _color;
    QTip::Font _font;
    bool _centered;
    QTip::Point _position{};
};

#endif //QTIPUIKIT_LABEL_H
