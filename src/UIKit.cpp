#include "UIKit/UIKitMod.h"
#include "UIKit/UIObject.h"

UIKitMod::UIKitMod() = default;

UIKitMod::~UIKitMod() = default;

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

UIKitMod* UIKitMod::instance() {
    return QTip::ModLoader::mod<UIKitMod>();
}

void UIKitMod::add(UIObject* object) {
    if (_addingChildren) return;
    _objects.push_back(object);
}
