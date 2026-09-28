//
// Created by Ayaan on 2026-09-27.
//

#ifndef QTIPUIKIT_SCROLLVIEW_H
#define QTIPUIKIT_SCROLLVIEW_H

#include <Q-Tip/Graphics/RenderTarget.h>

#include "QTipUIKit/Containers/Panel.h"

enum class ScrollDirection {
    Horizontal,
    Vertical,
    Both
};

struct ScrollViewSettings {
    ScrollDirection direction = ScrollDirection::Vertical;
    float scrollSpeed = 30.0f;
    bool showScrollbar = true;
    bool scrollbarAutoHide = true;
};

class ScrollView : public Panel {
public:
    explicit ScrollView(
        QTip::Rect rect,
        ScrollViewSettings settings = {}
    );

    void scrollTo(QTip::Point position);
    void scrollBy(QTip::Point delta);

    [[nodiscard]]
    QTip::Point scrollPosition() const;

    void setContentSize(QTip::Point size);

    [[nodiscard]]
    QTip::Point contentSize() const;

    [[nodiscard]]
    const ScrollViewSettings& settings() const;

    void render(QTip::Window& window) override;
    void handleEvent(const SDL_Event& event) override;

private:
    void clampScrollPosition();

    ScrollViewSettings _settings;
    QTip::Point _scrollPosition{};
    QTip::Point _contentSize{};
};


#endif
