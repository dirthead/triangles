#include "mainwindow.h"


MainWindow::MainWindow(QWidget * parent)
    : QMainWindow(parent)
    , _scene(new Scene(this))
{
    setCentralWidget(new QWidget());

    QVBoxLayout * mainLayout = new QVBoxLayout();

    mainLayout->addWidget(_scene);
    centralWidget()->setLayout(mainLayout);

    statusBar();
}

