#include <ranges>

#include "QTipUIKit/UIKitMod.h"
#include "QTipUIKit/UIObject.h"
#include "QTipUIKit/Internal/Helpers.h"
#include "QTipUIKit/Dialogs/Dialog.h"

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
    for (const auto& dialog : _dialogs | std::views::values) {
        dialog->end();
    }
}

void UIKitMod::handleEvent(const SDL_Event& event) {
    if (!_dialogs.empty()) {
        _dialogs.back().second->handleEvent(event);
        return;
    }
    for (auto* object : _objects) {
        if (!object) {
            std::cerr << "UIKit: NULL object in _objects!\n";
            continue;
        }

        object->handleEvent(event);
    }
}

void UIKitMod::beforePresent(QTip::Window& window) {
    double dt = clock.elapsedFromLastCall() / 1000.0;
    for (auto object : _objects) {
        object->tick(clock, dt);
    }

    for (auto& [w, dialog] : _dialogs) {
        if (w == &window) {
            dialog->render(window);
            dialog->tick(clock, dt);
        }
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
