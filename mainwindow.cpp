#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include "paramsetdlg.h"
#include "namemapsetdlg.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //// 将菜单的信号与其处理函数关联起来 //////////////////////////////////////////////////////////////
    connect(ui->menuParamSet, &QAction::triggered, this, &MainWindow::OnMenuParamSet);
    connect(ui->menuNameMap, &QAction::triggered, this, &MainWindow::OnMenuNameMapSet);
    connect(ui->menuTemplateSet, &QAction::triggered, this, &MainWindow::OnMenuTemplateSet);
    connect(ui->menuStart, &QAction::triggered, this, &MainWindow::OnStopPick);
    connect(ui->menuStop, &QAction::triggered, this, &MainWindow::OnStopPick);
    connect(ui->menuAbout, &QAction::triggered, this, &MainWindow::OnAboutPicker);
    //////////////////////////////////////////////////////////////////////////////////////////////
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::OnMenuParamSet()
{
    ParamSetDlg dlg(this);

    dlg.exec();
}


void MainWindow::OnMenuNameMapSet()
{
    NameMapSetDlg dlg(this);

    dlg.exec();
}


void MainWindow::OnMenuTemplateSet()
{

}

void MainWindow::OnStartPick()
{

}


void MainWindow::OnStopPick()
{

}


void MainWindow::OnAboutPicker()
{

}

