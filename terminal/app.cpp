#include <QApplication>
#include <QScreen>
#include <QRect>

#include "include/mainwindow.hpp"

int main(int argc, char** argv)
{
    QApplication app(argc, argv);

    QScreen *screen = QGuiApplication::primaryScreen();
    QRect  screenGeometry = screen->geometry();
    int height = screenGeometry.height();
    int width = screenGeometry.width();

    UserInterface ui(height, width);
    ui.show();

    return app.exec();
}