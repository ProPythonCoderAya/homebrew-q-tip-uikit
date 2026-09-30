//
// Created by Ayaan on 2026-09-29.
//

#include <Q-Tip/QTip.h>
#include <QTipUIKit/UIKit.h>
using namespace QTip;

int main() {
    ModLoader::load<UIKitMod>();

    Window window("helloo", 800, 600);

    ButtonStyle style;
    style.color = Color::white;
    style.disabledColor = Color::blue;
    style.hoverColor = Color::green;
    style.pressedColor = Color::red;

    {
        Button button(0, 0, 100, 100, "hello", style);

        bool shouldClose = false;

        button.setOnClick([&shouldClose] {
            shouldClose = true;
        });

        while (!window.shouldClose() && !shouldClose) {
            QTipRuntime::pollEvents();

            window->setRenderColor(Color::black);
            window->clear();

            button.render(window);

            window->present();
        }
    }

    Button button(100, 100, 100, 100, "hello2", style);

    while (!window.shouldClose()) {
        QTipRuntime::pollEvents();

        window->setRenderColor(Color::black);
        window->clear();

        button.render(window);

        window->present();
    }

    return 0;
}
