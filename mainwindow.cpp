#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "qduration.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_result_pushButton_clicked()
{
    QDuration du1, du2;
    QStringList pices = ui->first_duration_value_lineEdit->text().split( " " );
    du1 = du1.fromString(pices[1], pices[0]);
    pices = ui->second_duration_value_lineEdit->text().split(" ");
    du2 = du2.fromString(pices[1], pices[0]);
    ui->result_value_textEdit->setText(du1.toDuration(du2).toString());
}
