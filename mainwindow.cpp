#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QRandomGenerator>
#include <QMessageBox>
#include <QApplication>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setWindowTitle("Password generator");
}

MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow::checkStrength(const QString &password)
{
    int score = 0;

    if (password.length() >= 8)  score++;
    if (password.length() >= 12) score++;

    bool hasDigit = false, hasSymbol = false, hasUpper = false;
    for (QChar c : password) {
        if (c.isDigit())       hasDigit  = true;
        if (c.isUpper())       hasUpper  = true;
        if (!c.isLetterOrNumber()) hasSymbol = true;
    }

    if (hasDigit)  score++;
    if (hasUpper)  score++;
    if (hasSymbol) score++;

    if (score <= 2) {
        ui->label_strength->setText("Reliability: Weak");
        ui->label_strength->setStyleSheet("color: red;");
    } else if (score <= 3) {
        ui->label_strength->setText("Reliability: Average");
        ui->label_strength->setStyleSheet("color: orange;");
    } else {
        ui->label_strength->setText("Reliability: Strong");
        ui->label_strength->setStyleSheet("color: green;");
    }
}

void MainWindow::on_btn_gen_clicked()
{
    if (!ui->checkNumber->isChecked() && !ui->checkSymbols->isChecked() && !ui->checkBigSmall->isChecked())
    {
        QMessageBox::warning(this, "Error", "Choose at least one type of character!");
        return;
    }

    if (ui->spinBox->value() < 6) {
        QMessageBox::warning(this, "Error", "The password must be at least 6 characters long!");
        return;
    }

    QString chars = "";
    if (ui->checkNumber->isChecked()) {
        chars += "0123456789";
    }

    if (ui->checkSymbols->isChecked()) {
        chars += "!@#$%^&*()-_+={}[]|;:<>,.?/";
    }

    if (ui->checkBigSmall->isChecked()) {
        chars += "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
        chars += "abcdefghijklmnopqrstuvwxyz";
    }

    int length = ui->spinBox->value();

    QString password = "";
    for (int i = 0; i < length; i++) {
        int index = QRandomGenerator::global()->bounded(chars.length());
        password += chars.at(index);
    }
    ui->lineEdit->setText(password);
    checkStrength(password);
}

void MainWindow::on_btn_cop_clicked()
{
    ui->lineEdit->selectAll();
    ui->lineEdit->copy();
}

void MainWindow::on_btn_exit_clicked()
{
    QApplication::quit();
}
