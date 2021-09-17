#ifndef PARAMSETDLG_H
#define PARAMSETDLG_H

#include <QDialog>
#include <QLineEdit>

namespace Ui {
class ParamSetDlg;
}

class ParamSetDlg : public QDialog
{
    Q_OBJECT

public:
    explicit ParamSetDlg(QWidget *parent = nullptr);
    ~ParamSetDlg();

    /// 自定义的初始化函数 ////////////////////////////////////////////
    void MyInitFunc();

    /// 检查参数文件是否存在 //////////////////////////////////////////
    bool CheckFileExist(QString strFileName);

    /// 从设置参数文件中读参数 ////////////////////////////////////////
    void ReadSetParameters(QString strFileName);

    /// 将参数保存到配置文件中 ////////////////////////////////////////
    void WriteParameters(QString strFileName);

public slots:
    void SelectWorkDir(QLineEdit* dirWidget);
    void SaveParameters();
    void ExitDialog();

private:
    Ui::ParamSetDlg *ui;
    bool m_bUsePort;
    bool m_bRecvUseFtp;
};

#endif // PARAMSETDLG_H
