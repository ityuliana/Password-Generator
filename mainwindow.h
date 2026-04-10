#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void checkStrength(const QString &password);
    void on_btn_gen_clicked();

    void on_btn_cop_clicked();

    void on_btn_exit_clicked();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
