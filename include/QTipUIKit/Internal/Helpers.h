//
// Created by Ayaan on 2026-09-11.
//

#ifndef QTIPUIKIT_HELPERS_H
#define QTIPUIKIT_HELPERS_H
#include <filesystem>
#include <Q-Tip/Math/Point.h>
#include <SDL3/SDL_events.h>
namespace fs = std::filesystem;

union SDL_Event;

namespace Detail {
    inline fs::path defaultFontPath() {
#ifdef _WIN32
        return "C:/Windows/Fonts/Arial.ttf";
#elif defined(__linux__)
        return "/usr/share/fonts/truetype/dejavu/DejaVuSans.ttf";
#elif defined(__APPLE__)
        return "/System/Library/Fonts/SFNS.ttf";
#else
#error "Unsupported platform"
#endif
    }

    SDL_Event transformEvent(const SDL_Event& event, const QTip::Point& position);

    QTip::Point eventPosition(const SDL_Event& event);

    void printMouseEvent(const SDL_Event& event);
}

#endif //QTIPUIKIT_HELPERS_H
