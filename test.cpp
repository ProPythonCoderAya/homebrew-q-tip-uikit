#include <Q-Tip/QTip.h>
#include "QTipUIKit//UIKit.h"

using namespace QTip;

int main() {
    ModLoader::load<UIKitMod>();

    Window window("QTipUIKit Test", 800, 600);

    Font font(Detail::defaultFontPath(), 20);

    VBox vbox{{10, 10, 780, 580}};
    vbox.setSpacing(10);
    vbox.setSizing(Sizing::Stretch);
    vbox.setCrossSizing(CrossSizing::Stretch);

    auto& textbox = vbox.add<Textbox>(
        Rect{20, 20, 740, 250},
        font
    );

    auto& hbox = vbox.add<HBox>(Rect{20, 500, 760, 60});
    hbox.setSpacing(10);
    hbox.setSizing(Sizing::Stretch);
    hbox.setCrossSizing(CrossSizing::Stretch);

    Point windowSize = window.size();

    vbox.layout();

    ButtonStyle buttonStyle;
    buttonStyle.font = font;
    buttonStyle.color = Color{50, 50, 50, 255};
    buttonStyle.hoverColor = Color{70, 70, 70, 255};
    buttonStyle.pressedColor = Color{30, 30, 30, 255};
    buttonStyle.disabledColor = Color{20, 20, 20, 255};
    buttonStyle.fontColor = Color::white;

    auto& button = hbox.add<Button>(
        Rect{20, 500, 200, 60},
        "Click me",
        buttonStyle
    );

    CheckboxStyle checkboxStyle;
    checkboxStyle.color = Color{50, 50, 50, 255};
    checkboxStyle.hoverColor = Color{70, 70, 70, 255};
    checkboxStyle.pressedColor = Color{30, 30, 30, 255};
    checkboxStyle.disabledColor = Color{20, 20, 20, 255};

    auto& checkbox = hbox.add<Checkbox>(Rect{240, 520, 20, 20}, checkboxStyle);
    checkbox.checked = true;

    auto& checkboxLabel = hbox.add<Label>("Button Enabled", Color::white, Point{270, 520}, font);

    button.setOnClick([&] {
        textbox.setText("Button clicked!");
        checkbox.checked = false;
    });

    while (!window.shouldClose()) {
        QTipRuntime::pollEvents();

        if (window.input().keyWasPressed(Key::Key_ESCAPE))
            checkbox.checked = true;

        if (window.size() != windowSize) {
            windowSize = window.size();
            Point size = windowSize - Point{20, 20};

            vbox.resize(size);
        }

        button.setDisabled(!checkbox.checked); // disable if NOT checked

        if (checkbox.checked)
            checkboxLabel.setText("Button Enabled");
        else
            checkboxLabel.setText("Button Disabled");

        window->setRenderColor(Color::black);
        window->clear();

        vbox.render(window);

        window->present();
    }

    return 0;
}
