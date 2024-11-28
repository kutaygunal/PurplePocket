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
    setWindowTitle("OpenCascade Qt Application");
    resize(1024, 768);

    // Create OpenCASCADE view widget
    myOccView = new OCCView(this);
    setCentralWidget(myOccView);

    // Create menu bar
    QMenuBar* menuBar = this->menuBar();
    QMenu* fileMenu = menuBar->addMenu("&File");
    fileMenu->addAction("&Exit", this, &QWidget::close);

    QMenu* viewMenu = menuBar->addMenu("&View");
    viewMenu->addAction("&Fit All", myOccView, &OCCView::fitAll);

    // Create toolbar
    QToolBar* toolbar = addToolBar("Main Toolbar");
    toolbar->addAction("Fit All", myOccView, &OCCView::fitAll);

    // Create status bar
    statusBar()->showMessage("Ready");
}
