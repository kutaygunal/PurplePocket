#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTreeWidget>
#include "occview.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    void setupUI();
    void createTreeWidget();
    void populateTreeWidget();

    OCCView* myOccView;
    QTreeWidget* treeWidget;
};

#endif // MAINWINDOW_H
