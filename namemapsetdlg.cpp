#include "namemapsetdlg.h"
#include "ui_namemapsetdlg.h"

NameMapSetDlg::NameMapSetDlg(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::NameMapSetDlg)
{
    ui->setupUi(this);

    MyInitFunc();
}

NameMapSetDlg::~NameMapSetDlg()
{
    delete ui;
}

void NameMapSetDlg::MyInitFunc()
{
    ui->tableWidgetNameMapTable->setColumnCount(5);
    ui->tableWidgetNameMapTable->setHorizontalHeaderLabels(QStringList()<<"图片前缀"<<"中文姓名"<<"英文姓名"<<"所属部门"<<"部门ID");
    ui->tableWidgetNameMapTable->setColumnWidth(0, 100);
    ui->tableWidgetNameMapTable->setColumnWidth(1, 160);
    ui->tableWidgetNameMapTable->setColumnWidth(2, 160);
    ui->tableWidgetNameMapTable->setColumnWidth(3, 200);
    ui->tableWidgetNameMapTable->setColumnWidth(4, 200);

    ui->tableWidgetNameMapTable->setRowCount(1);
    ui->tableWidgetNameMapTable->setItem(0, 0, new QTableWidgetItem("ZCG"));
    //ui->tableWidgetNameMapTable->setItem(1, 0, new QTableWidgetItem("ZGF"));
    ui->tableWidgetNameMapTable->setRowCount(2);
    ui->tableWidgetNameMapTable->setItem(0, 0, new QTableWidgetItem("ZGF"));
}
