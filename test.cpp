#include <Q-Tip/QTip.h>
#include <UIKit.h>

using namespace QTip;

int main() {
    ModLoader::load<UIKitMod>();

    Window window("UIKit Test", 800, 600);

    Font font("/System/Library/Fonts/SFNSMono.ttf", 20);

    Textbox textbox(
        {20, 20, 760, 460},
        font
    );

    ButtonStyle buttonStyle;
    buttonStyle.font = font;
    buttonStyle.color = Color{50, 50, 50, 255};
    buttonStyle.hoverColor = Color{70, 70, 70, 255};
    buttonStyle.pressedColor = Color{30, 30, 30, 255};
    buttonStyle.disabledColor = Color{20, 20, 20, 255};
    buttonStyle.fontColor = Color::white;

    Button button(
        {20, 500, 200, 60},
        "Click me",
        buttonStyle
    );

    button.setOnClick([&] {
        textbox.setText("Button clicked!");
        button.disable();
    });

    Point size = window.size();

    while (!window.shouldClose()) {
        window.pollEvents();

        if (window.input().keyWasPressed(Key::Key_ESCAPE))
            button.enable();

        if (window.size() != size) {
            size = window.size();

            textbox.resize({
                size.x - 40,
                460
            });

            button.resize({
                20,
                size.y - 80,
                200,
                60
            });
        }

        window->setRenderColor(Color::black);
        window->clear();

        textbox.render(window);
        button.render(window);

        window->present();
    }

    return 0;
}