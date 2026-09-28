//
// Created by Ayaan on 2026-09-27.
//

#include "QTipUIKit/Containers/ScrollView.h"

#include <algorithm>
#include <SDL3/SDL_events.h>

#include "include/Helpers.h"

bool overlap(const QTip::Rect& rect1, const QTip::Rect& rect2) {
    return !(rect1.origin.x + rect1.size.x <= rect2.origin.x ||
             rect1.origin.x >= rect2.origin.x + rect2.size.x ||
             rect1.origin.y + rect1.size.y <= rect2.origin.y ||
             rect1.origin.y >= rect2.origin.y + rect2.size.y);
}

ScrollView::ScrollView(
    QTip::Rect rect,
    ScrollViewSettings settings
)
    : Panel(rect),
      _settings(settings) {
}

void ScrollView::scrollTo(QTip::Point position) {
    _scrollPosition = position;

    clampScrollPosition();
}

void ScrollView::scrollBy(QTip::Point delta) {
    _scrollPosition += delta;

    clampScrollPosition();
}

QTip::Point ScrollView::scrollPosition() const {
    return _scrollPosition;
}

void ScrollView::setContentSize(QTip::Point size) {
    _contentSize = size;

    clampScrollPosition();
}

QTip::Point ScrollView::contentSize() const {
    return _contentSize;
}

const ScrollViewSettings& ScrollView::settings() const {
    return _settings;
}

void ScrollView::clampScrollPosition() {
    const float viewportWidth = rect().size.x;
    const float viewportHeight = rect().size.y;

    const float maxX = std::max(0.0f, _contentSize.x - viewportWidth);
    const float maxY = std::max(0.0f, _contentSize.y - viewportHeight);

    switch (_settings.direction) {
        case ScrollDirection::Horizontal:
            _scrollPosition.x = std::clamp(_scrollPosition.x, 0.0f, maxX);
            _scrollPosition.y = 0.0f;
            break;

        case ScrollDirection::Vertical:
            _scrollPosition.x = 0.0f;
            _scrollPosition.y = std::clamp(_scrollPosition.y, 0.0f, maxY);
            break;

        case ScrollDirection::Both:
            _scrollPosition.x = std::clamp(_scrollPosition.x, 0.0f, maxX);
            _scrollPosition.y = std::clamp(_scrollPosition.y, 0.0f, maxY);
            break;
    }
}

void ScrollView::render(QTip::Window& window) {
    QTip::RenderTarget target{
        window.getRenderer(),
        _contentSize
    };

    window->setTarget(target);

    for (const auto& child : _objects) {
        const QTip::Rect childRect = child->rect();

        if (!overlap(childRect, {
            0,
            0,
            _contentSize.x,
            _contentSize.y
        }))
            continue;

        child->render(window);
    }

    window->resetTarget();

    window->renderTexture(
        target,
        QTip::Rect{
            _scrollPosition.x,
            _scrollPosition.y,
            rect().size.x,
            rect().size.y
        },
        rect()
    );

    DrawScrollbar(window.getRenderer(), 20, 20, rect().size.y - 40, _scrollPosition.y / rect().size.y, _contentSize.y / rect().size.y);
}

void ScrollView::handleEvent(const SDL_Event& event) {
    Panel::handleEvent(event);

    if (event.type == SDL_EVENT_MOUSE_WHEEL) {
        QTip::Point delta{
            event.wheel.x * _settings.scrollSpeed,
            -event.wheel.y * _settings.scrollSpeed
        };

        std::cout << "delta: " << delta.x << ", " << delta.y << std::endl;

        switch (_settings.direction) {
            case ScrollDirection::Horizontal:
                delta.y = 0.0f;
                break;

            case ScrollDirection::Vertical:
                delta.x = 0.0f;
                break;

            case ScrollDirection::Both:
                break;
        }

        std::cout << "scrollPosition: " << _scrollPosition.x << ", " << _scrollPosition.y << std::endl;
        scrollBy(delta);
        std::cout << "scrollPosition: " << _scrollPosition.x << ", " << _scrollPosition.y << std::endl;
    }
}
