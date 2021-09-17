#include "paramsetdlg.h"
#include "ui_paramsetdlg.h"
#include "QFileInfo"
#include "QSettings"
#include "QMessageBox"
#include "QDebug"
#include "QTextCodec"
#include "QFileDialog"

ParamSetDlg::ParamSetDlg(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ParamSetDlg)
{
    ui->setupUi(this);

    MyInitFunc();
}

ParamSetDlg::~ParamSetDlg()
{
    delete ui;
}

void ParamSetDlg::MyInitFunc()
{
    /// 关联保存按钮的clicked信号与保存数据的槽 /////////////////////////////////////////////
    connect(ui->btnSave, &QPushButton::clicked, this, &ParamSetDlg::SaveParameters);

    /// 关联退出按钮的clicked信号与推出对话框的槽 /////////////////////////////////////////////
    connect(ui->btnExit, &QPushButton::clicked, this, &ParamSetDlg::ExitDialog);

    /// 关联radioUserPort的clicked信号与m_bUsePort变量 ///////////////////////////////////
    connect(ui->radioPort, &QRadioButton::clicked, [=]{
        m_bUsePort = true;
    });
    connect(ui->radioPassive, &QRadioButton::clicked, [=]{
        m_bUsePort = false;
    });

    /// 关联radioUseFtp的clicked信号与m_bRecvUseFtp变量 //////////////////////////////////
    connect(ui->radioUseFtp, &QRadioButton::clicked, [=]{
        m_bRecvUseFtp = true;
    });
    connect(ui->radioUseSmb, &QRadioButton::clicked, [=]{
        m_bRecvUseFtp = false;
    });

    connect(ui->btnSelRecvDir, &QPushButton::clicked, this, &ParamSetDlg::SelectWorkDir);
    connect(ui->btnSelPickDir, &QPushButton::clicked, this, &ParamSetDlg::SelectWorkDir);
    connect(ui->btnSelBackDir, &QPushButton::clicked, this, &ParamSetDlg::SelectWorkDir);
    connect(ui->btnSelSendDir, &QPushButton::clicked, this, &ParamSetDlg::SelectWorkDir);

    QString strParamFileName;

    strParamFileName = QCoreApplication::applicationDirPath() + "/parameters.ini";
    if(!CheckFileExist(strParamFileName))
    {
        /// 如果运行未发现设置参数文件，需要进行一些默认赋值 //////////////////////////////////
        ui->editRecvDir->setText("d:/paramfile/recv");
        ui->editPickDir->setText("d:/paramfile/pick");
        ui->editBackDir->setText("d:/paramfile/back");
        ui->editSendDir->setText("d:/paramfile/send");

        ui->editSendFtpServer->setText("127.0.0.1");
        ui->editSendFtpUser->setText("xh");
        ui->editSendFtpPwd->setText("password");
        ui->editSendFtpTextDir->setText("text");
        ui->editSendFtpNameDir->setText("name");

        ui->editRecvFtpServer->setText("127.0.0.1");
        ui->editRecvFtpUser->setText("xhs");
        ui->editRecvFtpPwd->setText("password");

        /// 发稿默认使用主动模式 /////
        m_bUsePort = true;
        /// 收稿默认使用smb协议 /////
        m_bRecvUseFtp = false;

        ui->radioPort->setChecked(m_bUsePort);
        ui->radioUseSmb->setChecked(!m_bRecvUseFtp);


        ui->editCheckDirInterval->setText("100");
        ui->editCheckFileTimes->setText("10");
        ui->editCheckFileInterval->setText("10");
        //////////////////////////////////////////////////////////////////////////
    }
    else
    {
        ReadSetParameters(strParamFileName);
    }
}

bool ParamSetDlg::CheckFileExist(QString strFileName)
{
    QFileInfo paramSetFile(strFileName);

    return paramSetFile.isFile();
}

void ParamSetDlg::SelectWorkDir(QLineEdit* dirWidget)
{
    QString strWorkDir;

    strWorkDir = QFileDialog::getExistingDirectory(this, "请选择目录", "/");

    qDebug()<<"你选择的目录是 ： "<<strWorkDir;

    if(!strWorkDir.isEmpty())
    {
        dirWidget->setText(strWorkDir);
    }
}

void ParamSetDlg::ReadSetParameters(QString strFileName)
{
    QSettings settings(strFileName, QSettings::IniFormat);

    ui->editRecvDir->setText(settings.value("WorkDirParams/RecvDir").toString());
    ui->editPickDir->setText(settings.value("WorkDirParams/PickDir").toString());
    ui->editBackDir->setText(settings.value("WorkDirParams/BackDir").toString());
    ui->editSendDir->setText(settings.value("WorkDirParams/SendDir").toString());

    ui->editSendFtpServer->setText(settings.value("SendFtpServer/FTPAddress").toString());
    ui->editSendFtpUser->setText(settings.value("SendFtpServer/FTPUser").toString());
    ui->editSendFtpPwd->setText(settings.value("SendFtpServer/FTPPwd").toString());
    ui->editSendFtpTextDir->setText(settings.value("SendFtpServer/TextDir").toString());
    ui->editSendFtpNameDir->setText(settings.value("SendFtpServer/NameDir").toString());
    m_bUsePort = settings.value("SendFtpServer/PortMode").toBool();
    ui->radioPort->setChecked(m_bUsePort);
    ui->radioPassive->setChecked(!m_bUsePort);

    ui->editRecvFtpServer->setText(settings.value("RecvFtpServer/FTPAddress").toString());
    ui->editRecvFtpUser->setText(settings.value("RecvFtpServer/FTPUser").toString());
    ui->editRecvFtpPwd->setText(settings.value("RecvFtpServer/FTPPwd").toString());
    m_bRecvUseFtp = settings.value("RecvFtpServer/UseFtp").toBool();
    ui->radioUseFtp->setChecked(m_bRecvUseFtp);
    ui->radioUseSmb->setChecked(!m_bRecvUseFtp);

    ui->editCheckDirInterval->setText(settings.value("FileCheckParams/DirCheckInterval").toString());
    ui->editCheckFileTimes->setText(settings.value("FileCheckParams/FileCheckTimes").toString());
    ui->editCheckFileInterval->setText(settings.value("FileCheckParams/FileCheckInterval").toString());
}

void ParamSetDlg::SaveParameters()
{
    QString strParamFileName;

    strParamFileName = QCoreApplication::applicationDirPath() + "/parameters.ini";

    WriteParameters(strParamFileName);

    //QMessageBox::information(this, "成功", "参数保存成功!");
    QMessageBox msgBox;

    msgBox.resize(500,100);
    msgBox.information(this, "成功", "参数保存成功!");

    this->accept();
}

void ParamSetDlg::WriteParameters(QString strFileName)
{
    QSettings settings(strFileName, QSettings::IniFormat);
    //settings.setIniCodec(QTextCodec::codecForName("UTF-8"));
    settings.setIniCodec("UTF-8");

    settings.setValue("WorkDirParams/RecvDir", ui->editRecvDir->text());
    settings.setValue("WorkDirParams/PickDir", ui->editPickDir->text());
    settings.setValue("WorkDirParams/BackDir", ui->editBackDir->text());
    settings.setValue("WorkDirParams/SendDir", ui->editSendDir->text());

    settings.setValue("SendFtpServer/FTPAddress", ui->editSendFtpServer->text());
    settings.setValue("SendFtpServer/FTPUser", ui->editSendFtpUser->text());
    settings.setValue("SendFtpServer/FTPPwd", ui->editSendFtpPwd->text());
    settings.setValue("SendFtpServer/TextDir", ui->editSendFtpTextDir->text());
    settings.setValue("SendFtpServer/NameDir", ui->editSendFtpNameDir->text());
    settings.setValue("SendFtpServer/PortMode", m_bUsePort);

    settings.setValue("RecvFtpServer/FTPAddress", ui->editRecvFtpServer->text());
    settings.setValue("RecvFtpServer/FTPUser", ui->editRecvFtpUser->text());
    settings.setValue("RecvFtpServer/FTPPwd", ui->editRecvFtpPwd->text());
    settings.setValue("RecvFtpServer/UseFtp", m_bRecvUseFtp);

    settings.setValue("FileCheckParams/DirCheckInterval", ui->editCheckDirInterval->text());
    settings.setValue("FileCheckParams/FileCheckTimes", ui->editCheckFileTimes->text());
    settings.setValue("FileCheckParams/FileCheckInterval", ui->editCheckFileInterval->text());
}

void ParamSetDlg::ExitDialog()
{
    this->reject();
}
