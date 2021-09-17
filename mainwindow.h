#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

public slots:
    void OnMenuParamSet();
    void OnMenuNameMap();
    void OnMenuTemplateSet();

    void OnStartPick();
    void OnStopPick();

    void OnAboutPicker();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
