#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QVBoxLayout>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    const QString INSTRUCTIONS_PROMPT = "1. Input your name in the textbox.\n\n"
                                        "2. Click the Add button.\n\n"
                                        "3. Repeat with the next person.\n\n"
                                        "4. Click the Done button when everyone playing has entered their information.\n\n";
    ui->setupUi(this);
    ui->lblAddVerify->setText("");
    ui->lblInstructions->setText(INSTRUCTIONS_PROMPT);
    ui->cboPartner->setVisible(false);
    ui->lblPartner->setVisible(false);
    ui->stackedWidget->setCurrentWidget(ui->setupPage);

}

MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow::on_btnAdd_clicked()
{
    QString name = ui->txtName->text();
    if (name.isEmpty()) {
        ui->lblAddVerify->setText("Name cannot be empty.");
        ui->lblAddVerify->setStyleSheet("color: red;");
    }
    else {
        if (santaBag.add(name)){
            int pCount = santaBag.getPlayerCount();
            QString playerCount = "Player Count: " + QString::number(pCount);
            ui->txtName->clear();
            //santaBag.printHelp();
            ui->lblAddVerify->setText("Player added successfully!");
            ui->lblAddVerify->setStyleSheet("color: green;");
            ui->lblPlayerCount->setText(playerCount);
        }
    }
}


void MainWindow::on_btnDone_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->detailsPage);
    ui->cboNameChoosing->addItem("", -1);
    ui->cboPartner->addItem("", -1);
    for (int i = 0; i < santaBag.getPlayerCount(); i++) {
        QString name = santaBag.getPlayerNameAt(i);
        ui->cboNameChoosing->addItem(name, i);
        ui->cboPartner->addItem(name, i);
    }
}

void MainWindow::on_chkHasPartner_toggled(bool checked)
{
    if(checked) {
        ui->cboPartner->setVisible(true);
        ui->lblPartner->setVisible(true);
    }
    else {
        ui->cboPartner->setVisible(false);
        ui->lblPartner->setVisible(false);
    }
}


void MainWindow::on_btnAdd_2_clicked()
{
    QString name = ui->cboNameChoosing->currentText();
    QString gift = ui->txtGift->toPlainText();
    QString partner = ui->cboPartner->currentText();
    if(gift.isEmpty()){
        ui->lblGiftAdd->setText("Gift cannot be empty.");
        ui->lblGiftAdd->setStyleSheet("color: red;");
    }
    else {
        if(santaBag.add(name, gift) && santaBag.add(name, partner, true)) {
            santaBag.printHelp();
            ui->txtGift->clear();
            ui->lblGiftAdd->setText("Gift added successfully!");
            ui->lblGiftAdd->setStyleSheet("color: green;");
            ui->cboNameChoosing->setCurrentText("");
            ui->cboPartner->setCurrentText("");
            ui->chkHasPartner->setChecked(false);
        }
    }
}


void MainWindow::on_btnDone_2_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->assignmentPage);
    ui->cboChoosing->addItem("", -1);
    for (int i = 0; i < santaBag.getBagSize(); i++) {
        QString name = santaBag.getPlayerNameAt(i);
        ui->cboChoosing->addItem(name, i);
    }
    santaBag.draw();
}


void MainWindow::on_btnDraw_clicked()
{
    QString name = ui->cboChoosing->currentText();
    ui->txtAssignedName->setText(santaBag.getAssignedName(name));
    ui->txtAssignedGift->setText(santaBag.getAssignedGift(name));
}


void MainWindow::on_btnClear_clicked()
{
    ui->cboChoosing->setCurrentText("");
    ui->txtAssignedName->clear();
    ui->txtAssignedGift->clear();
    // Figure out way to gray out and make unselectable person who just chose.
}

