#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include <string>

double num_first;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect(ui->pushButton_0,SIGNAL(clicked()),this,SLOT(digit_numbers()));
    connect(ui->pushButton_1,SIGNAL(clicked()),this,SLOT(digit_numbers()));
    connect(ui->pushButton_2,SIGNAL(clicked()),this,SLOT(digit_numbers()));
    connect(ui->pushButton_3,SIGNAL(clicked()),this,SLOT(digit_numbers()));
    connect(ui->pushButton_4,SIGNAL(clicked()),this,SLOT(digit_numbers()));
    connect(ui->pushButton_5,SIGNAL(clicked()),this,SLOT(digit_numbers()));
    connect(ui->pushButton_6,SIGNAL(clicked()),this,SLOT(digit_numbers()));
    connect(ui->pushButton_7,SIGNAL(clicked()),this,SLOT(digit_numbers()));
    connect(ui->pushButton_8,SIGNAL(clicked()),this,SLOT(digit_numbers()));
    connect(ui->pushButton_9,SIGNAL(clicked()),this,SLOT(digit_numbers()));
    connect(ui->pushButton_plusminus,SIGNAL(clicked()),this,SLOT(operations()));
    connect(ui->pushButton_percent,SIGNAL(clicked()),this,SLOT(operations()));
    connect(ui->pushButton_div,SIGNAL(clicked()),this,SLOT(math_operations()));
    connect(ui->pushButton_plus,SIGNAL(clicked()),this,SLOT(math_operations()));
    connect(ui->pushButton_minus,SIGNAL(clicked()),this,SLOT(math_operations()));
    connect(ui->pushButton_times,SIGNAL(clicked()),this,SLOT(math_operations()));

    ui->pushButton_div->setCheckable(true);
    ui->pushButton_plus->setCheckable(true);
    ui->pushButton_minus->setCheckable(true);
    ui->pushButton_times->setCheckable(true);

    math_checked = false;

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::digit_numbers()
{
   QPushButton *button = (QPushButton *)sender();
   QString new_label;
   double all_numbers;

   if(math_checked == true) {
       ui->label->setText("0");
       math_checked = false;
   }

   if(ui->label->text().contains(".") && button->text() == "0"){
       new_label = ui->label->text() + button->text();
   } else {
   all_numbers = (ui->label->text()+ button->text()).toDouble(); // ноль после точки не доб-ся если не сделать проверку выше.
   new_label = QString::number(all_numbers, 'g', 15);
   }
    ui->label->setText(new_label);
}

void MainWindow::on_pushButton_dot_clicked()
{
    if(!(ui->label->text().contains('.')))
    ui->label->setText(ui->label->text()+"."); //добавляем точку
}

void MainWindow::operations()
{
   QPushButton *button = (QPushButton *)sender();
   QString new_label;
   double all_numbers;

   if(button->text() == "+/-") {
   all_numbers = (ui->label->text()).toDouble();
   all_numbers = all_numbers * -1;
   new_label = QString::number(all_numbers, 'g', 15);
    ui->label->setText(new_label);
   }
   else if(button->text() == "%") {
       all_numbers = (ui->label->text()).toDouble();
       all_numbers = all_numbers * 0.01;
       new_label = QString::number(all_numbers, 'g', 15);
        ui->label->setText(new_label);
       }
}

void MainWindow::math_operations()
{
    QPushButton *button = (QPushButton *)sender();

    num_first = ui->label->text().toDouble();
    checkout();
    button->setChecked(true);
    math_checked = true;
}

void MainWindow::on_pushButton_ac_clicked()
{
    checkout();
    ui->label->setText("0");
}

void MainWindow::checkout()
{
    ui->pushButton_plus->setChecked(false);
    ui->pushButton_minus->setChecked(false);
    ui->pushButton_div->setChecked(false);
    ui->pushButton_times->setChecked(false);

}

void MainWindow::on_pushButton_equal_clicked()
{
    double LabelNumber, num_second;
    QString new_label;
    num_second = ui->label->text().toDouble();
    math_checked = true;
    if(ui->pushButton_plus->isChecked()) {
        LabelNumber = num_first + num_second;
        new_label = QString::number(LabelNumber, 'g', 14);

        ui->label->setText(new_label);
        ui->pushButton_plus->setChecked(false);
    } else if(ui->pushButton_minus->isChecked()) {
        std::string new_labelstring;
        LabelNumber = num_first - num_second;
        new_labelstring = std::to_string(LabelNumber);
        new_label = QString::number(LabelNumber, 'g', (new_labelstring.length()/2));
        qDebug() << "значение LabelNumber = " << LabelNumber;
        qDebug() << num_first << " - " << num_second << " = " << new_label;
        qDebug() << new_labelstring.length();
        ui->label->setText(new_label);
        ui->pushButton_minus->setChecked(false);
    }  else if(ui->pushButton_div->isChecked()) {
        if (num_second == 0){
         ui->label->setText("error");
        } else {
        LabelNumber = num_first / num_second;
        new_label = QString::number(LabelNumber, 'g', 14);

        ui->label->setText(new_label);
        }
        ui->pushButton_div->setChecked(false);
    }  else if(ui->pushButton_times->isChecked()) {
        LabelNumber = num_first * num_second;
        new_label = QString::number(LabelNumber, 'g', 14);

        ui->label->setText(new_label);
        ui->pushButton_times->setChecked(false);
    }
}
