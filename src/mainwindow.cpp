#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "santaBag.h"

SantaBag primaryBag;            // Unchanging bag - keeps dropdown menu populated properly
SantaBag backupBag;             // Performs operations such as removal

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    const QString INSTRUCTIONS_PROMPT = "1. Input your name and list in the textboxes.\n\n"
                                        "2. Click the Add button.\n\n"
                                        "3. Repeat with the next person.\n\n"
                                        "4. Click the Done button when everyone playing has entered their information.\n\n";
    ui->setupUi(this);
    ui->lblAddVerify->setText("");
    ui->lblInstructions->setText(INSTRUCTIONS_PROMPT);
    ui->cboPartner->setVisible(false);
    ui->lblPartner->setVisible(false);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_btnAdd_clicked()
{
    bool success;
    std::string name = ui->txtName->text().toStdString();
    std::string list = ui->txtList->toPlainText().toStdString();
    if(!name.empty() && !list.empty()) {
        success = primaryBag.addToBag(name, list);
    }
    else {
        success = false;
        ui->lblAddVerify->setText("Please add your name and list in the textboxes.");
    }
    if (success) {
        ui->lblAddVerify->setText(QStringLiteral("Player ") + name.c_str() + QStringLiteral(" added successfully!"));
        ui->txtName->setText("");
        ui->txtList->setText("");
    }
    ui->txtName->setFocus();
    qDebug() << "Bag size: " << primaryBag.getSize() << "\n";
    primaryBag.printBag();
}



void MainWindow::on_btnDone_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->revealPage);
    ui->cboNameChoosing->addItem("", -1);
    ui->cboPartner->addItem("", -1);
    for(int i = 0; i < primaryBag.getSize(); i++) {
        QString playerName = QString::fromStdString(primaryBag.getPlayerName(i));
        ui->cboNameChoosing->addItem(playerName, i);
        ui->cboPartner->addItem(playerName, i);
    }
    backupBag = primaryBag;
}


void MainWindow::on_chkHasPartner_toggled(bool checked)
{
    if(checked){
        ui->cboPartner->setVisible(true);
        ui->lblPartner->setVisible(true);
    }
    else {
        ui->cboPartner->setVisible(false);
        ui->lblPartner->setVisible(false);
    }

}


void MainWindow::on_btnDraw_clicked()
{
    int currIndex = ui->cboNameChoosing->currentIndex() - 1;
    qDebug() << "Player Name current is " << backupBag.getPlayerName(currIndex) << "\n";
    int partIndex = ui->cboPartner->currentIndex() - 1;
    qDebug() << "Partner Name current is " << backupBag.getPlayerName(partIndex) << "\n";
    if(backupBag.removeTemp(currIndex, partIndex)) {
        qDebug() << "The backup bag has removed some items. \n";
    }
    int assignedIndex = backupBag.randomBag();
    qDebug() << "The assigned person is " << backupBag.getPlayerName(assignedIndex) << "\n";
    QString assignedName = QString::fromStdString(backupBag.getPlayerName(assignedIndex));
    ui->txtNameAssign->setText(assignedName);
    QString assignedList = QString::fromStdString(backupBag.getPlayerList(assignedIndex));
    ui->txtListAssign->setText(assignedList);
    backupBag.printBag();
    if(backupBag.removePerm(assignedIndex)) {
        qDebug() << "Removed person " << backupBag.getPlayerName(assignedIndex) << " from the bag.\n";
    }
    backupBag.printBag();
}


void MainWindow::on_btnClear_clicked()
{
    int currIndex = ui->cboNameChoosing->currentIndex();
    ui->cboNameChoosing->setItemData(currIndex, 0, Qt::UserRole - 1);
    ui->cboNameChoosing->setCurrentIndex(-1);
    ui->cboPartner->setCurrentIndex(-1);
    on_chkHasPartner_toggled(false);
    ui->chkHasPartner->setChecked(false);
    ui->txtNameAssign->setText("");
    ui->txtListAssign->setText("");
    backupBag.replaceTemp();
    backupBag.printBag();
}

