#include "assignmentwindow.h"
#include "ui_assignmentwindow.h"

AssignmentWindow::AssignmentWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::AssignmentWindow)
{
    ui->setupUi(this);
}

AssignmentWindow::~AssignmentWindow()
{
    delete ui;
}

void AssignmentWindow::on_chkHasPartner_toggled(bool checked)
{
    if(checked) {

    }
}


void AssignmentWindow::on_btnDraw_clicked()
{

}


void AssignmentWindow::on_btnClear_clicked()
{

}


void AssignmentWindow::on_btnDone_clicked(bool checked)
{

}

