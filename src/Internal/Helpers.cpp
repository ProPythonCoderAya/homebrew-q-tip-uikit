//
// Created by Ayaan on 2026-09-14.
//

#include "QTipUIKit/Internal/Helpers.h"
#include <SDL3/SDL_events.h>

namespace Detail {
    SDL_Event transformEvent(const SDL_Event& event, const QTip::Point& position) {
        SDL_Event transformed = event;

        switch (transformed.type) {

            // Mouse
        case SDL_EVENT_MOUSE_MOTION:
            transformed.motion.x -= position.x;
            transformed.motion.y -= position.y;
            break;

        case SDL_EVENT_MOUSE_BUTTON_DOWN:
        case SDL_EVENT_MOUSE_BUTTON_UP:
            transformed.button.x -= position.x;
            transformed.button.y -= position.y;
            break;

        case SDL_EVENT_MOUSE_WHEEL:
            transformed.wheel.mouse_x -= position.x;
            transformed.wheel.mouse_y -= position.y;
            break;


            // Touch
        case SDL_EVENT_FINGER_DOWN:
        case SDL_EVENT_FINGER_UP:
        case SDL_EVENT_FINGER_MOTION:
        case SDL_EVENT_FINGER_CANCELED:
            // Touch coordinates are normalized [0, 1], so these
            // should NOT simply have a pixel position subtracted.
            //
            // They need to be converted into the coordinate space
            // of the UI object separately.
            break;


            // Drag and drop
        case SDL_EVENT_DROP_POSITION:
            transformed.drop.x -= position.x;
            transformed.drop.y -= position.y;
            break;


            // Pinch gestures
        case SDL_EVENT_PINCH_BEGIN:
        case SDL_EVENT_PINCH_UPDATE:
        case SDL_EVENT_PINCH_END:
            // No ordinary window-space x/y position to transform.
            break;


        default:
            break;
        }

        return transformed;
    }
}
