#include "include/review.hpp"

Review::Review()
{
	// setFeatures(QDockWidget::NoDockWidgetFeatures);

	// hides title bar
	setTitleBarWidget(new QWidget);	

	QWidget* container = new QWidget;
	setWidget(container);

	container->setStyleSheet("background-color: black");

	QVBoxLayout* layout = new QVBoxLayout(container);
}

QDockWidget* Review::operator()()
{
	return this;
}
