#include <QApplication>

#include "include/mainwindow.hpp"

int main(int argc, char** argv)
{
	QApplication app(argc, argv);

	QIcon logo(":/Resources/logo/logo.png");
	app.setWindowIcon(logo);

	QFont font("Helvetica");
	QApplication::setFont(font);

	UserInterface ui;
	ui.show();

	return app.exec();
}