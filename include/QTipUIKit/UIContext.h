//
// Created by Ayaan on 2026-10-09.
//

#ifndef QTIPUIKIT_UICONTEXT_H
#define QTIPUIKIT_UICONTEXT_H
#include <vector>
#include <Q-Tip/Clock.h>

#include "Dialogs/Dialog.h"

class UIObject;
union SDL_Event;

class UIContext {
public:
    UIContext();

    ~UIContext();

private:
    std::vector<UIObject*> _objects;
    std::vector<std::unique_ptr<Dialog>> _dialogs;
    std::vector<Dialog*> _removalPendingDialogs;

    void add(UIObject* object);
    void remove(UIObject* object);

    void beforePresent(QTip::Window& window, QTip::Clock& clock, double dt);

    void handleEvent(const SDL_Event& event);

    void removeDialog(Dialog* dialog);

    bool _addingChildren = false;

    QTip::Window* _window = nullptr;

    friend class UIObject;
    friend class Panel;
    friend class UIKitMod;
};


#endif //QTIPUIKIT_UICONTEXT_H
