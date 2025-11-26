#include "recordmanager.h"
#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    manager = new RecordManager("students.txt");

    records = manager->readAll();
    currentIndex = -1;

    ui->btnUpdate->setEnabled(false);
    ui->btnDelete->setEnabled(false);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_btnAdd_clicked()
{
    Student s;
    s.roll = ui->leRoll->text();
    s.name = ui->leName->text();
    s.father = ui->leFather->text();
    s.caste = ui->leCaste->text();
    s.district = ui->leDistrict->text();
    s.gpa = ui->leGPA->text();

    if (s.roll.isEmpty() || s.name.isEmpty()) {
        ui->lblStatus->setText("Roll and Name cannot be empty.");
        return;
    }

    if (manager->addRecord(s)) {
        ui->lblStatus->setText("Record added.");
        records = manager->readAll();
    } else {
        ui->lblStatus->setText("Roll already exists.");
    }
}

void MainWindow::on_btnUpdate_clicked()
{
    Student s;
    s.roll = ui->leRoll->text();
    s.name = ui->leName->text();
    s.father = ui->leFather->text();
    s.caste = ui->leCaste->text();
    s.district = ui->leDistrict->text();
    s.gpa = ui->leGPA->text();

    if (manager->updateRecord(s.roll, s)) {
        ui->lblStatus->setText("Record updated.");
        records = manager->readAll();
    } else {
        ui->lblStatus->setText("Update failed.");
    }
}

void MainWindow::on_btnDelete_clicked()
{
    QString roll = ui->leRoll->text();

    if (manager->deleteRecord(roll)) {
        ui->lblStatus->setText("Record deleted.");
        records = manager->readAll();
    } else {
        ui->lblStatus->setText("Delete failed.");
    }
}

void MainWindow::on_btnNext_clicked()
{
    if (records.isEmpty()) {
        ui->lblStatus->setText("No records found.");
        return;
    }

    currentIndex++;
    if (currentIndex >= records.size())
        currentIndex = 0;

    Student s = records[currentIndex];

    ui->leRoll->setText(s.roll);
    ui->leName->setText(s.name);
    ui->leFather->setText(s.father);
    ui->leCaste->setText(s.caste);
    ui->leDistrict->setText(s.district);
    ui->leGPA->setText(s.gpa);

    ui->btnUpdate->setEnabled(true);
    ui->btnDelete->setEnabled(true);
}
