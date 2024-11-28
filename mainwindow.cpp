#include "mainwindow.h"
#include <QApplication>
#include <QHeaderView>
#include <QTreeWidget>
#include <QTreeWidgetItem>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QToolBar>
#include <QAction>
#include <QIcon>
#include <QSplitter>
#include <QPalette>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    // Set window properties
    setWindowTitle("PurplePocket");
    resize(1200, 800);

    // Create central widget and main layout
    QWidget* centralWidget = new QWidget(this);
    QHBoxLayout* mainLayout = new QHBoxLayout(centralWidget);
    mainLayout->setContentsMargins(0, 0, 0, 0);
    mainLayout->setSpacing(0);
    setCentralWidget(centralWidget);

    // Create splitter for tree and view
    QSplitter* splitter = new QSplitter(Qt::Horizontal, centralWidget);
    mainLayout->addWidget(splitter);

    // Create and setup tree widget
    QTreeWidget* treeWidget = new QTreeWidget(splitter);
    treeWidget->setHeaderLabel("Components");
    treeWidget->setMinimumWidth(250);

    // Create OpenCASCADE view
    myOccView = new OCCView(splitter);

    // Add widgets to splitter
    splitter->addWidget(treeWidget);
    splitter->addWidget(myOccView);

    // Setup toolbar
    setupToolbar();

    // Setup dark theme
    setupDarkTheme();

    // Populate tree with demo items
    populateTree(treeWidget);

    // Resize tree widget to fit content
    treeWidget->setColumnCount(1);
    treeWidget->header()->setSectionResizeMode(QHeaderView::ResizeToContents);
    treeWidget->setMaximumWidth(treeWidget->header()->sectionSize(0) + 50); // Add some padding

    // Show window maximized
    showMaximized();
}

MainWindow::~MainWindow()
{
}

void MainWindow::setupToolbar()
{
    QToolBar* viewToolBar = addToolBar("View");
    viewToolBar->setMovable(false);

    // Top view action
    QAction* topViewAction = new QAction("Top", this);
    connect(topViewAction, &QAction::triggered, this, &MainWindow::onTopView);
    viewToolBar->addAction(topViewAction);

    // Bottom view action
    QAction* bottomViewAction = new QAction("Bottom", this);
    connect(bottomViewAction, &QAction::triggered, this, &MainWindow::onBottomView);
    viewToolBar->addAction(bottomViewAction);

    // Left view action
    QAction* leftViewAction = new QAction("Left", this);
    connect(leftViewAction, &QAction::triggered, this, &MainWindow::onLeftView);
    viewToolBar->addAction(leftViewAction);

    // Right view action
    QAction* rightViewAction = new QAction("Right", this);
    connect(rightViewAction, &QAction::triggered, this, &MainWindow::onRightView);
    viewToolBar->addAction(rightViewAction);

    // Axonometric view action
    QAction* axoViewAction = new QAction("Axo", this);
    connect(axoViewAction, &QAction::triggered, this, &MainWindow::onAxonometricView);
    viewToolBar->addAction(axoViewAction);

    // Apply dark theme to toolbar
    viewToolBar->setStyleSheet(
        "QToolBar {"
        "   background-color: #2b2b2b;"
        "   border: none;"
        "   spacing: 3px;"
        "}"
        "QToolButton {"
        "   background-color: #3f3f3f;"
        "   border: 1px solid #2b2b2b;"
        "   color: #e0e0e0;"
        "   padding: 5px;"
        "   border-radius: 3px;"
        "}"
        "QToolButton:hover {"
        "   background-color: #4f4f4f;"
        "}"
        "QToolButton:pressed {"
        "   background-color: #2979ff;"
        "}"
    );
}

void MainWindow::setupDarkTheme()
{
    // Set dark theme colors
    QPalette darkPalette;
    darkPalette.setColor(QPalette::Window, QColor("#1e1e1e"));
    darkPalette.setColor(QPalette::WindowText, QColor("#e0e0e0"));
    darkPalette.setColor(QPalette::Base, QColor("#2b2b2b"));
    darkPalette.setColor(QPalette::AlternateBase, QColor("#3f3f3f"));
    darkPalette.setColor(QPalette::ToolTipBase, QColor("#e0e0e0"));
    darkPalette.setColor(QPalette::ToolTipText, QColor("#e0e0e0"));
    darkPalette.setColor(QPalette::Text, QColor("#e0e0e0"));
    darkPalette.setColor(QPalette::Button, QColor("#2b2b2b"));
    darkPalette.setColor(QPalette::ButtonText, QColor("#e0e0e0"));
    darkPalette.setColor(QPalette::Link, QColor("#2979ff"));
    darkPalette.setColor(QPalette::Highlight, QColor("#2979ff"));
    darkPalette.setColor(QPalette::HighlightedText, QColor("#e0e0e0"));

    qApp->setPalette(darkPalette);

    // Set stylesheet for QTreeWidget
    QString treeStyle = 
        "QTreeWidget {"
        "   background-color: #2b2b2b;"
        "   border: none;"
        "}"
        "QTreeWidget::item {"
        "   color: #e0e0e0;"
        "   padding: 5px;"
        "}"
        "QTreeWidget::item:selected {"
        "   background-color: #2979ff;"
        "}"
        "QTreeWidget::item:hover {"
        "   background-color: #3f3f3f;"
        "}";

    qApp->setStyleSheet(treeStyle);
}

void MainWindow::populateTree(QTreeWidget* tree)
{
    // Flow Components
    QTreeWidgetItem* flowRoot = new QTreeWidgetItem(tree);
    flowRoot->setText(0, "Flow Components");
    
    QStringList flowComponents = {
        "Pump",
        "Valve",
        "Pipe",
        "Tank",
        "Heat Exchanger",
        "Filter"
    };

    for (const QString& component : flowComponents) {
        QTreeWidgetItem* item = new QTreeWidgetItem(flowRoot);
        item->setText(0, component);
    }

    // Thermal Components
    QTreeWidgetItem* thermalRoot = new QTreeWidgetItem(tree);
    thermalRoot->setText(0, "Thermal Components");
    
    QStringList thermalComponents = {
        "Heater",
        "Cooler",
        "Temperature Sensor",
        "Thermal Insulation",
        "Heat Sink",
        "Radiator"
    };

    for (const QString& component : thermalComponents) {
        QTreeWidgetItem* item = new QTreeWidgetItem(thermalRoot);
        item->setText(0, component);
    }

    // Expand all items
    tree->expandAll();
}

void MainWindow::onTopView()
{
    if (Handle(V3d_View) view = myOccView->getView()) {
        view->SetProj(V3d_Zpos);
        view->FitAll();
    }
}

void MainWindow::onBottomView()
{
    if (Handle(V3d_View) view = myOccView->getView()) {
        view->SetProj(V3d_Zneg);
        view->FitAll();
    }
}

void MainWindow::onLeftView()
{
    if (Handle(V3d_View) view = myOccView->getView()) {
        view->SetProj(V3d_Xneg);
        view->FitAll();
    }
}

void MainWindow::onRightView()
{
    if (Handle(V3d_View) view = myOccView->getView()) {
        view->SetProj(V3d_Xpos);
        view->FitAll();
    }
}

void MainWindow::onAxonometricView()
{
    if (Handle(V3d_View) view = myOccView->getView()) {
        view->SetProj(V3d_XposYnegZpos);
        view->FitAll();
    }
}
