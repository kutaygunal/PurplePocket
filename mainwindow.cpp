#include "mainwindow.h"
#include <QLabel>
#include <QMenuBar>
#include <QMenu>
#include <QToolBar>
#include <QStatusBar>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    setupUI();
}

MainWindow::~MainWindow()
{
}

void MainWindow::setupUI()
{
    // Set window title and size
    setWindowTitle("Qt Application");
    resize(800, 600);

    // Create central widget with a welcome message
    QLabel* centralWidget = new QLabel("Welcome to Qt Application!", this);
    centralWidget->setAlignment(Qt::AlignCenter);
    setCentralWidget(centralWidget);

    // Create menu bar
    QMenuBar* menuBar = this->menuBar();
    QMenu* fileMenu = menuBar->addMenu("&File");
    fileMenu->addAction("&Exit", this, &QWidget::close);

    // Create toolbar
    QToolBar* toolbar = addToolBar("Main Toolbar");
    toolbar->addAction("Action 1");
    toolbar->addAction("Action 2");

    // Create status bar
    statusBar()->showMessage("Ready");
}
