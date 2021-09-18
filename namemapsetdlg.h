#ifndef NAMEMAPSETDLG_H
#define NAMEMAPSETDLG_H

#include <QDialog>

namespace Ui {
class NameMapSetDlg;
}

class NameMapSetDlg : public QDialog
{
    Q_OBJECT

public:
    explicit NameMapSetDlg(QWidget *parent = nullptr);
    ~NameMapSetDlg();

    /// 自定义的初始化函数 ////////////////////////////////////////////
    void MyInitFunc();

private:
    Ui::NameMapSetDlg *ui;
};

#endif // NAMEMAPSETDLG_H
