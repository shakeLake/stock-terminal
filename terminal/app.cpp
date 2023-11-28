#include <QApplication>
#include "include/mainwindow.hpp"

int main(int argc, char** argv)
{
    QApplication app(argc, argv);

    UserInterface ui;
    ui.show();

    return app.exec();
}