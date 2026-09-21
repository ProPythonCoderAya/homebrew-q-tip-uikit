//
// Created by Ayaan on 2026-09-14.
//

#include "QTipUIKit/Internal/Helpers.h"
#include <SDL3/SDL_events.h>

namespace Detail {
    SDL_Event transformEvent(const SDL_Event& event, const QTip::Point& position) {
        SDL_Event transformed = event;

        switch (transformed.type) {

        case SDL_EVENT_MOUSE_MOTION:
            transformed.motion.x -= position.x;
            transformed.motion.y -= position.y;
            break;

        case SDL_EVENT_MOUSE_BUTTON_DOWN:
        case SDL_EVENT_MOUSE_BUTTON_UP:
            transformed.button.x -= position.x;
            transformed.button.y -= position.y;
            break;

        default:
            break;
        }

        return transformed;
    }
}
