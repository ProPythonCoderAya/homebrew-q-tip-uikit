#include <Q-Tip/QTip.h>
#include <UIKit.h>

using namespace QTip;

int main() {
    ModLoader::load<UIKitMod>();

    Window window("Hello", 800, 600);

    Font font("/System/Library/Fonts/SFNSMono.ttf", 20);

    Textbox textbox({10, 10, 780, 580}, font);

    Point size = window.size();

    while (!window.shouldClose()) {
        window.pollEvents();

        if (window.size() != size) {
            size = window.size();
            textbox.resize(size - Point{20, 20});
        }

        window->setRenderColor(Color::black);
        window->clear();

        textbox.render(window);

        window->present();
    }

    return 0;
}
