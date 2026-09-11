//
// Created by Ayaan on 2026-09-11.
//

#ifndef QTIPUIKIT_HELPERS_H
#define QTIPUIKIT_HELPERS_H
#include <filesystem>
namespace fs = std::filesystem;

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
}

#endif //QTIPUIKIT_HELPERS_H
