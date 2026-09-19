#include <Q-Tip/QTip.h>
#include <UIKit.h>

using namespace QTip;

int main() {
    ModLoader::load<UIKitMod>();

    Window window("UIKit Test", 800, 600);

    Panel panel({10, 10, 780, 580});

    Font font("/System/Library/Fonts/SFNSMono.ttf", 20);

    auto& textbox = panel.add<Textbox>(
        Rect{20, 20, 760, 460},
        font
    );

    CheckboxStyle checkboxStyle;
    checkboxStyle.color = Color{50, 50, 50, 255};
    checkboxStyle.hoverColor = Color{70, 70, 70, 255};
    checkboxStyle.pressedColor = Color{30, 30, 30, 255};
    checkboxStyle.disabledColor = Color{20, 20, 20, 255};

    auto& checkbox = panel.add<Checkbox>(Rect{240, 520, 20, 20}, checkboxStyle);
    checkbox.checked = true;

    auto& checkboxLabel = panel.add<Label>("Button Enabled", Color::white, Point{270, 520}, font);

    ButtonStyle buttonStyle;
    buttonStyle.font = font;
    buttonStyle.color = Color{50, 50, 50, 255};
    buttonStyle.hoverColor = Color{70, 70, 70, 255};
    buttonStyle.pressedColor = Color{30, 30, 30, 255};
    buttonStyle.disabledColor = Color{20, 20, 20, 255};
    buttonStyle.fontColor = Color::white;

    auto& button = panel.add<Button>(
        Rect{20, 500, 200, 60},
        "Click me",
        buttonStyle
    );

    button.setOnClick([&] {
        textbox.setText("Button clicked!");
        checkbox.checked = false;
    });

    Point windowSize = window.size();

    while (!window.shouldClose()) {
        window.pollEvents();

        if (window.input().keyWasPressed(Key::Key_ESCAPE))
            checkbox.checked = true;

        if (window.size() != windowSize) {
            windowSize = window.size();
            panel.resize(windowSize - Point{20, 20});
            Point size = panel.rect().size;

            textbox.resize({
                size.x - 40,
                460
            });

            button.reposition({
                20,
                size.y - 80
            });

            checkbox.reposition({
                240,
                size.y - 60
            });

            checkboxLabel.reposition({
                270,
                size.y - 60
            });
        }

        button.setDisabled(!checkbox.checked); // disable if NOT checked

        if (checkbox.checked)
            checkboxLabel.setText("Button Enabled");
        else
            checkboxLabel.setText("Button Disabled");

        window->setRenderColor(Color::black);
        window->clear();

        panel.render(window);

        window->present();
    }

    return 0;
}