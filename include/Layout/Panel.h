//
// Created by Ayaan on 2026-09-12.
//

#ifndef QTIPUIKIT_PANEL_H
#define QTIPUIKIT_PANEL_H
#include "UIObject.h"

class Panel : UIObject {
public:
    Panel(QTip::Rect rect);

    void render(QTip::Window& window) override;
    void handleEvent(const SDL_Event& event) override;

    void resize(QTip::Rect rect);
    [[nodiscard]] const QTip::Rect& rect() const;

    template<std::derived_from<UIObject> T, typename... Args>
    T& add(Args&&... args) {
        auto object = std::make_unique<T>(
            std::forward<Args>(args)...
        );

        T& result = *object;
        _objects.push_back(std::move(object));

        return result;
    }

    void remove(UIObject& object);

    void clear();

private:
    QTip::Rect _rect{};
    std::vector<std::unique_ptr<UIObject>> _objects;
};

#endif //QTIPUIKIT_PANEL_H
