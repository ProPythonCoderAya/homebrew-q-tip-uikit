#include "QTipUIKit/UIKitMod.h"
#include "QTipUIKit/UIObject.h"
#include "QTipUIKit/Internal/Helpers.h"

UIKitMod::UIKitMod() = default;

UIKitMod::~UIKitMod() = default;

std::string_view UIKitMod::id() const {
    return ID;
}

std::string_view UIKitMod::name() const {
    return NAME;
}

void UIKitMod::init() {
}

void UIKitMod::shutdown() {
}

void UIKitMod::handleEvent(const SDL_Event& event) {
    for (auto* object : _objects) {
        object->handleEvent(event);
    }
}

UIKitMod* UIKitMod::instance() {
    return QTip::ModLoader::mod<UIKitMod>();
}

void UIKitMod::add(UIObject* object) {
    if (_addingChildren) return;
    _objects.push_back(object);
}

void UIKitMod::remove(UIObject* object) {
    const auto it = std::ranges::find_if(_objects,
         [&object](const UIObject* ptr) {
             return ptr == object;
         }
    );

    if (it != _objects.end()) {
        _objects.erase(it);
    }
}
