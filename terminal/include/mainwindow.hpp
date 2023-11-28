#ifndef MAINWINDOW_HPP_
#define MAINWINDOW_HPP_

#include <QMainWindow>
#include "toolbar.hpp"

class UserInterface : public QMainWindow
{
private:
    ToolBar GetToolBar;

public:
    UserInterface();
    ~UserInterface() = default;

};

#endif /* MAINWINDOW_HPP_ */