#include "include/toolbar.hpp"

ToolBar::ToolBar()
{
    test_label = new QLabel("Test Label");
    addWidget(test_label);
}

QToolBar* ToolBar::operator()()
{
    return this;
}