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
    //ui->lblFeedbackSetup->setText("");
    //ui->lblInstructionsSetup->setText(INSTRUCTIONS_PROMPT);
    //ui->cboPartnerDetails->setVisible(false);
    //ui->lblPartnerDetails->setVisible(false);
    ui->stackedWidget->setCurrentWidget(ui->initialPage);

}

MainWindow::~MainWindow()
{
    delete ui;
}

// SCREEN 1 - Setup
void MainWindow::on_btnStartInitial_clicked()
{
    // Transitions to next screen
    ui->stackedWidget->setCurrentWidget(ui->setupPage);
    const QString INSTRUCTIONS = "Input a player's name in the textbox.\nClick the Add button to register the player.\n"
                                 "There is a counter on the left side of the screen to show how many players have been registered.\n"
                                 "Once everyone has been added, press the Done button.";
    ui->lblInstructionsSetup->setText(INSTRUCTIONS);
    ui->lblFeedbackSetup->setText("");
    ui->lblCounterSetup->setText("Player Count: 0");
}

// SCREEN 2 - Adding Players
void MainWindow::on_btnAddSetup_clicked()
{
    QString name = ui->txtNameSetup->text();
    if (name.isEmpty()) {
        ui->lblFeedbackSetup->setText("Name cannot be empty.");
        ui->lblFeedbackSetup->setStyleSheet("color: red;");
    }
    else {
        if (santaBag.addPlayer(name)){
            int pCount = santaBag.getPlayerCount();
            QString playerCount = "Player Count: " + QString::number(pCount);
            ui->txtNameSetup->clear();
            //santaBag.printHelp();
            ui->lblFeedbackSetup->setText("Player added successfully!");
            ui->lblFeedbackSetup->setStyleSheet("color: green;");
            ui->lblCounterSetup->setText(playerCount);
        }
    }
}

void MainWindow::on_btnDoneSetup_clicked()
{
    // Transitions to next screen
    ui->stackedWidget->setCurrentWidget(ui->detailsPage);
    const QString INSTRUCTIONS = "1. Choose who is adding their gift.\n2. If you are playing with a partner, make sure you use the checkbox and select your partner.\n"
                                 "3. Input your gift in the textbox and press the Add button.\n4. There is a counter on the right side of the screen to show how many players"
                                 " still need to add their gifts.\n5. Once everyone has added their gift, press the Done button.";
    ui->lblInstructionsDetails->setText(INSTRUCTIONS);
    ui->cboNameDetails->addItem("", -1);
    ui->cboPartnerDetails->addItem("", -1);
    for (int i = 0; i < santaBag.getPlayerCount(); i++) {
        QString name = santaBag.getPlayerNameAt(i);
        ui->cboNameDetails->addItem(name, i);
        ui->cboPartnerDetails->addItem(name, i);
    }
    ui->cboPartnerDetails->setVisible(false);
    ui->lblPartnerDetails->setVisible(false);
    int pCount = santaBag.getPlayerCount();
    ui->lblCounterDetails->setText("Player Count: " + QString::number(pCount));
    ui->lblFeedbackDetails->setText("");
}


// SCREEN 3 - Adding Gifts / Partners
void MainWindow::on_btnAddDetails_clicked()
{
    QString name = ui->cboNameDetails->currentText();
    QString gift = ui->txtGiftDetails->toPlainText();
    QString partner = ui->cboPartnerDetails->currentText();
    if(gift.isEmpty()){
        ui->lblFeedbackDetails->setText("Gift cannot be empty.");
        ui->lblFeedbackDetails->setStyleSheet("color: red;");
    }
    else if (!ui->chkHasPartnerDetails) {
        ui->lblFeedbackDetails->setText("You must choose a partner.");
        ui->lblFeedbackDetails->setStyleSheet("color: red;");
    }
    else {
        if(santaBag.updatePlayer(name, gift, partner)) {
            //santaBag.printHelp();
            ui->txtGiftDetails->clear();
            ui->lblFeedbackDetails->setText("Gift added successfully!");
            ui->lblFeedbackDetails->setStyleSheet("color: green;");
            ui->cboNameDetails->setCurrentText("");
            ui->cboPartnerDetails->setCurrentText("");
            ui->chkHasPartnerDetails->setChecked(false);
        }
    }
}

void MainWindow::on_btnDoneDetails_clicked()
{
    // Transitions to next screen
    ui->stackedWidget->setCurrentWidget(ui->assignmentPage);
    const QString INSTRUCTIONS = "1. Choose your name in the drop down menu on the left.\n2. Make sure no one is able to see the screen at the same time as you and have your phone or"
                                 " some paper and pen with you to take note of who you have.\n3. Press the Draw button to become someone's Secret Santa.\n"
                                 "4. After 15 seconds, your assignment will disappear for the next person to get theirs.";
    ui->lblInstructionsAssignment->setText(INSTRUCTIONS);
    ui->cboChoosingAssignment->addItem("", -1);
    for (int i = 0; i < santaBag.getPlayerCount(); i++) {
        QString name = santaBag.getPlayerNameAt(i);
        ui->cboChoosingAssignment->addItem(name, i);
    }
    int pCount = santaBag.getPlayerCount();
    ui->lblCounterAssignment->setText("Player Count: " + QString::number(pCount));
    ui->lblTimerAssignment->setText("Timer: 20 seconds");
}

void MainWindow::on_chkHasPartnerDetails_toggled(bool checked)
{
    if(checked) {
        ui->cboPartnerDetails->setVisible(true);
        ui->lblPartnerDetails->setVisible(true);
    }
    else {
        ui->cboPartnerDetails->setVisible(false);
        ui->lblPartnerDetails->setVisible(false);
    }
}

// SCREEN 4 - Secret Santa Assignment
void MainWindow::on_btnDrawAssignment_clicked()
{
    QString name = ui->cboChoosingAssignment->currentText();
    int index = ui->cboChoosingAssignment->currentIndex();
    santaBag.setGiver(name);
    if(santaBag.drawPlayer()) {
        QString assignedName = santaBag.getAssignedName();
        QString assignedGift = santaBag.getAssignedGift();
        ui->txtNameAssignment->setText(assignedName);
        ui->txtGiftAssignment->setText(assignedGift);
        ui->cboChoosingAssignment->setItemData(index, 0, Qt::UserRole - 1);       // Grays out and makes current item unselectable.
        ui->cboChoosingAssignment->setCurrentText("");
        qDebug() << "recipient is " << assignedName << " with giver " << name;
    }
    else {
        ui->txtNameAssignment->clear();
        ui->txtGiftAssignment->setText("Could not complete draw.");
    }
}

void MainWindow::on_btnDoneAssignment_clicked()
{
    this->close();
}

void MainWindow::on_btnClear_clicked()
{
    ui->cboChoosingAssignment->setCurrentText("");
    ui->txtNameAssignment->clear();
    ui->txtGiftAssignment->clear();
}