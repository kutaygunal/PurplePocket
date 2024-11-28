#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "occview.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    void setupUI();
    OCCView* myOccView;
};

#endif // MAINWINDOW_H
