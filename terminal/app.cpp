#include <QApplication>

#include "include/mainwindow.hpp"

int main(int argc, char** argv)
{
	QApplication app(argc, argv);

	QFont font("Helvetica");
	QApplication::setFont(font);

	UserInterface ui();
	ui.show();

	return app.exec();
}