//
// Created by Ayaan on 2026-09-30.
//

#ifndef QTIPUIKIT_DIALOG_H
#define QTIPUIKIT_DIALOG_H
#include "QTipUIKit/UIObject.h"
#include "QTipUIKit/Containers/HBox.h"
#include "QTipUIKit/Containers/Panel.h"


class Dialog : public UIObject {
public:
    ~Dialog() override;

    void render(QTip::Window& window) override;
    bool handleEvent(const SDL_Event& event) override;

    [[nodiscard]] QTip::Point minimumSize() const override;
    [[nodiscard]] QTip::Point preferredSize() const override;

    void resize(QTip::Point size) override;
    void reposition(QTip::Point position) override;
    void setRect(QTip::Rect rect) override;
    [[nodiscard]] const QTip::Rect& rect() override;

    Panel& content();
    HBox& buttons();

    void close();

    static Dialog& create(QTip::Window& window);

private:
    Dialog();

    void initialize(QTip::Window& window);

    void end();

    void layout();

    Panel _content;

    HBox _buttons;

    QTip::Window* _window = nullptr;

    bool _requestedClose = false;

    QTip::Point _lastWindowSize;

    friend class UIKitMod;
};


#endif //QTIPUIKIT_DIALOG_H
