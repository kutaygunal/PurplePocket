#include "mainwindow.h"
#include <QLabel>
#include <QMenuBar>
#include <QMenu>
#include <QToolBar>
#include <QStatusBar>
#include <QVBoxLayout>
#include <QSplitter>

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
    resize(1200, 800);

    // Set dark theme for the entire application
    setStyleSheet(
        "QMainWindow {"
        "    background-color: #1e1e1e;"
        "}"
        "QMenuBar {"
        "    background-color: #2b2b2b;"
        "    color: #e0e0e0;"
        "}"
        "QMenuBar::item:selected {"
        "    background-color: #3f3f3f;"
        "}"
        "QMenu {"
        "    background-color: #2b2b2b;"
        "    color: #e0e0e0;"
        "    border: 1px solid #3f3f3f;"
        "}"
        "QMenu::item:selected {"
        "    background-color: #3f3f3f;"
        "}"
        "QToolBar {"
        "    background-color: #2b2b2b;"
        "    border: 1px solid #3f3f3f;"
        "}"
        "QToolBar::separator {"
        "    background-color: #3f3f3f;"
        "}"
        "QStatusBar {"
        "    background-color: #2b2b2b;"
        "    color: #e0e0e0;"
        "}"
        "QSplitter::handle {"
        "    background-color: #3f3f3f;"
        "}"
    );

    // Create central widget and layout
    QWidget* centralWidget = new QWidget(this);
    QHBoxLayout* mainLayout = new QHBoxLayout(centralWidget);
    mainLayout->setContentsMargins(0, 0, 0, 0);
    mainLayout->setSpacing(0);

    // Create splitter
    QSplitter* splitter = new QSplitter(Qt::Horizontal, centralWidget);
    mainLayout->addWidget(splitter);

    // Create and add tree widget to the left side
    createTreeWidget();
    splitter->addWidget(treeWidget);

    // Create OpenCASCADE view widget on the right side
    myOccView = new OCCView(this);
    splitter->addWidget(myOccView);

    // Set the initial sizes of the splitter
    QList<int> sizes;
    sizes << 200 << 1000;  // Left panel: 200px, Right panel: 1000px
    splitter->setSizes(sizes);

    setCentralWidget(centralWidget);

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

    // Populate the tree widget
    populateTreeWidget();
}

void MainWindow::createTreeWidget()
{
    treeWidget = new QTreeWidget(this);
    treeWidget->setHeaderLabel("Categories");
    treeWidget->setMinimumWidth(200);
    treeWidget->setMaximumWidth(400);

    // Set style for dark mode
    treeWidget->setStyleSheet(
        "QTreeWidget {"
        "    background-color: #2b2b2b;"
        "    color: #e0e0e0;"
        "    border: 1px solid #3f3f3f;"
        "}"
        "QTreeWidget::item {"
        "    padding: 4px;"
        "    border-radius: 2px;"
        "}"
        "QTreeWidget::item:hover {"
        "    background-color: #3f3f3f;"
        "}"
        "QTreeWidget::item:selected {"
        "    background-color: #2979ff;"
        "    color: #ffffff;"
        "}"
        "QTreeWidget::branch {"
        "    background-color: #2b2b2b;"
        "}"
        "QTreeWidget::branch:has-siblings:!adjoins-item {"
        "    border-image: url(none.png) 0;"
        "}"
        "QTreeWidget::branch:has-siblings:adjoins-item {"
        "    border-image: url(none.png) 0;"
        "}"
        "QTreeWidget::branch:!has-children:!has-siblings:adjoins-item {"
        "    border-image: url(none.png) 0;"
        "}"
        "QTreeWidget::branch:has-children:!has-siblings:closed,"
        "QTreeWidget::branch:closed:has-children:has-siblings {"
        "    border-image: none;"
        "    image: url(none.png);"
        "}"
        "QTreeWidget::branch:open:has-children:!has-siblings,"
        "QTreeWidget::branch:open:has-children:has-siblings {"
        "    border-image: none;"
        "    image: url(none.png);"
        "}"
        "QHeaderView::section {"
        "    background-color: #2b2b2b;"
        "    color: #e0e0e0;"
        "    padding: 4px;"
        "    border: 1px solid #3f3f3f;"
        "}"
    );
}

void MainWindow::populateTreeWidget()
{
    // Create Flow category
    QTreeWidgetItem* flowCategory = new QTreeWidgetItem(treeWidget);
    flowCategory->setText(0, "Flow");
    flowCategory->setExpanded(true);
    flowCategory->setIcon(0, style()->standardIcon(QStyle::SP_DriveNetIcon));

    // Add Chambers subcategory under Flow
    QTreeWidgetItem* chambersCategory = new QTreeWidgetItem(flowCategory);
    chambersCategory->setText(0, "Chambers");
    chambersCategory->setIcon(0, style()->standardIcon(QStyle::SP_DirIcon));
    chambersCategory->setExpanded(true);

    // Add chamber types
    QTreeWidgetItem* momentumChamber = new QTreeWidgetItem(chambersCategory);
    momentumChamber->setText(0, "Momentum");
    momentumChamber->setIcon(0, style()->standardIcon(QStyle::SP_FileIcon));

    QTreeWidgetItem* plenumChamber = new QTreeWidgetItem(chambersCategory);
    plenumChamber->setText(0, "Plenum");
    plenumChamber->setIcon(0, style()->standardIcon(QStyle::SP_FileIcon));

    // Add Elements subcategory under Flow
    QTreeWidgetItem* elementsCategory = new QTreeWidgetItem(flowCategory);
    elementsCategory->setText(0, "Elements");
    elementsCategory->setIcon(0, style()->standardIcon(QStyle::SP_DirIcon));
    elementsCategory->setExpanded(true);

    // Add element types
    QTreeWidgetItem* tubeElement = new QTreeWidgetItem(elementsCategory);
    tubeElement->setText(0, "Tube");
    tubeElement->setIcon(0, style()->standardIcon(QStyle::SP_FileIcon));

    QTreeWidgetItem* orificeElement = new QTreeWidgetItem(elementsCategory);
    orificeElement->setText(0, "Orifice");
    orificeElement->setIcon(0, style()->standardIcon(QStyle::SP_FileIcon));

    // Create Thermal category
    QTreeWidgetItem* thermalCategory = new QTreeWidgetItem(treeWidget);
    thermalCategory->setText(0, "Thermal");
    thermalCategory->setExpanded(true);
    thermalCategory->setIcon(0, style()->standardIcon(QStyle::SP_DriveHDIcon));

    // Add Thermal Nodes subcategory
    QTreeWidgetItem* thermalNodesCategory = new QTreeWidgetItem(thermalCategory);
    thermalNodesCategory->setText(0, "Thermal Nodes");
    thermalNodesCategory->setIcon(0, style()->standardIcon(QStyle::SP_DirIcon));
    thermalNodesCategory->setExpanded(true);

    // Add thermal node types
    QTreeWidgetItem* boundaryNode = new QTreeWidgetItem(thermalNodesCategory);
    boundaryNode->setText(0, "Boundary Thermal Node");
    boundaryNode->setIcon(0, style()->standardIcon(QStyle::SP_FileIcon));

    QTreeWidgetItem* internalNode = new QTreeWidgetItem(thermalNodesCategory);
    internalNode->setText(0, "Internal Thermal Node");
    internalNode->setIcon(0, style()->standardIcon(QStyle::SP_FileIcon));

    // Add Resistors subcategory
    QTreeWidgetItem* resistorsCategory = new QTreeWidgetItem(thermalCategory);
    resistorsCategory->setText(0, "Resistors");
    resistorsCategory->setIcon(0, style()->standardIcon(QStyle::SP_DirIcon));
    resistorsCategory->setExpanded(true);

    // Add resistor types
    QTreeWidgetItem* conductorResistor = new QTreeWidgetItem(resistorsCategory);
    conductorResistor->setText(0, "Conductor");
    conductorResistor->setIcon(0, style()->standardIcon(QStyle::SP_FileIcon));

    QTreeWidgetItem* convectorResistor = new QTreeWidgetItem(resistorsCategory);
    convectorResistor->setText(0, "Convector");
    convectorResistor->setIcon(0, style()->standardIcon(QStyle::SP_FileIcon));

    QTreeWidgetItem* heatTransferResistor = new QTreeWidgetItem(resistorsCategory);
    heatTransferResistor->setText(0, "Heat Transfer");
    heatTransferResistor->setIcon(0, style()->standardIcon(QStyle::SP_FileIcon));
}
