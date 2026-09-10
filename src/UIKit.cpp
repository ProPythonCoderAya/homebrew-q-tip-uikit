#include <UIKit.h>
#include <UIObject.h>

UIKitMod::UIKitMod() {
}

UIKitMod::~UIKitMod() {
}

std::string_view UIKitMod::id() const {
    return "propythoncoderaya/uikit";
}

std::string_view UIKitMod::name() const {
    return "UIKit";
}

void UIKitMod::init() {
}

void UIKitMod::shutdown() {
}

void UIKitMod::handleEvent(const SDL_Event& event) {
    for (auto* mod : _objects) {
        mod->handleEvent(event);
    }
}
