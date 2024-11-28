#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "occview.h"

class QTreeWidget;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void onTopView();
    void onBottomView();
    void onLeftView();
    void onRightView();
    void onAxonometricView();

private:
    void setupToolbar();
    void setupDarkTheme();
    void populateTree(QTreeWidget* tree);

    OCCView* myOccView;
};

#endif // MAINWINDOW_H
