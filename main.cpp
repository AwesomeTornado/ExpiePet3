#include <QApplication>
#include "mainsprite.h"

int main(int argc, char *argv[]) {
    // Set WAYLAND_DISPLAY to an invalid value to force Qt to use X11
    setenv("WAYLAND_DISPLAY", "", 1);
    setenv("XDG_SESSION_TYPE", "xcb", 1);
    QApplication a(argc, argv);
    mainsprite MainSprite;
    MainSprite.show();
    return QApplication::exec();
}
