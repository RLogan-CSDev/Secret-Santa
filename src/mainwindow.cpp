#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QVBoxLayout>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    const QString SANTA_VERIFY = "Please make sure that everyone that is playing has added their information.";
    ui->setupUi(this);
    ui->lblVerify->setText(SANTA_VERIFY);
    ui->stackedWidget->setCurrentWidget(ui->initialPage);
    setGameState(INITIAL);
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
    const QString INSTRUCTIONS = "1. Input a player's name in the textbox.\n2. Click the Add button to register the player.\n"
                                 "3. There is a counter on the left side of the screen to show how many players have been registered.\n"
                                 "4. Once everyone has been added, press the Done button.";
    ui->lblInstructionsSetup->setText(INSTRUCTIONS);
    ui->lblFeedbackSetup->setText("");
    ui->lblCounterSetup->setText("Player Count: 0");
    setGameState(SETUP);
}

// SCREEN 2 - Adding Players
void MainWindow::on_btnAddSetup_clicked()
{
    QString name = ui->txtNameSetup->text();
    if (name.isEmpty()) {
        ui->lblFeedbackSetup->setText("Name cannot be empty.");
        ui->lblFeedbackSetup->setStyleSheet("color: #ff6b6b; background-color: rgba(192, 57, 43, 0.3); border-radius: 4px; padding: 6px;");
    }
    else {
        if (santaBag.addPlayer(name)){
            int pCount = santaBag.getPlayerCount();
            QString playerCount = "Player Count: " + QString::number(pCount);
            ui->txtNameSetup->clear();
            //santaBag.printHelp();
            ui->lblFeedbackSetup->setText("Player added successfully!");
            ui->lblFeedbackSetup->setStyleSheet("color: #2ecc71; background-color: rgba(39, 174, 96, 0.3); border-radius: 4px; padding: 6px;");
            ui->lblCounterSetup->setText(playerCount);
            ui->txtNameSetup->setFocus();
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
    setGameState(DETAILS);
}


// SCREEN 3 - Adding Gifts / Partners
void MainWindow::on_btnAddDetails_clicked()
{
    QString name = ui->cboNameDetails->currentText();
    QString gift = ui->txtGiftDetails->toPlainText();
    QString partner = ui->cboPartnerDetails->currentText();
    int pCount = santaBag.getPlayerCount();
    int index = ui->cboNameDetails->currentIndex();
    if(gift.isEmpty()){
        ui->lblFeedbackDetails->setText("Gift cannot be empty.");
        ui->lblFeedbackDetails->setStyleSheet("color: #ff6b6b; background-color: rgba(192, 57, 43, 0.3); border-radius: 4px; padding: 6px;");
    }
    else if (!ui->chkHasPartnerDetails) {
        ui->lblFeedbackDetails->setText("You must choose a partner.");
        ui->lblFeedbackDetails->setStyleSheet("color: #ff6b6b; background-color: rgba(192, 57, 43, 0.3); border-radius: 4px; padding: 6px;");
    }
    else {
        if(santaBag.updatePlayer(name, gift, partner)) {
            //santaBag.printHelp();
            ui->txtGiftDetails->clear();
            ui->lblFeedbackDetails->setText("Gift added successfully!");
            ui->lblFeedbackDetails->setStyleSheet("color: #2ecc71; background-color: rgba(39, 174, 96, 0.3); border-radius: 4px; padding: 6px;");
            ui->cboNameDetails->setCurrentText("");
            ui->cboPartnerDetails->setCurrentText("");
            ui->chkHasPartnerDetails->setChecked(false);
            ui->cboNameDetails->setItemData(index, 0, Qt::UserRole - 1);
            ui->cboNameDetails->setItemData(index, QColor("#1e293b"), Qt::BackgroundRole);

            rotation++;
            pCount = pCount - getRotation();
            ui->lblCounterDetails->setText("Player Count: " + QString::number(pCount));
        }
    }
    if(pCount == 0) {
        ui->lblCounterDetails->setStyleSheet("border: 2px solid #2ecc71;");
        ui->lblFeedbackDetails->setText("All gifts have been entered.");
        ui->lblFeedbackDetails->setStyleSheet("color: #34d399; background-color: rgba(5, 150, 105, 0.25); border-radius: 4px; padding: 6px;");
    }
}

void MainWindow::on_btnDoneDetails_clicked()
{
    // Before transition, ensure all gifts are added...
    if(!santaBag.isGiftFull()) {
        ui->stackedWidget->setCurrentWidget(ui->verifyPage);
        return;
    }
    if(!santaBag.generateAssignments()) {
        ui->stackedWidget->setCurrentWidget(ui->verifyPage);
        ui->lblVerify->setText("Could not generate valid assignments.");
        ui->lblVerify->setStyleSheet("color: #ff6b6b; background-color: rgba(192, 57, 43, 0.3); border-radius: 4px; padding: 6px;");
        return;
    }

    // Transitions to next screen
    ui->stackedWidget->setCurrentWidget(ui->assignmentPage);
    const QString INSTRUCTIONS = "1. Choose your name in the drop down menu on the left.\n2. Make sure no one is able to see the screen at the same time as you and have your phone or"
                                 " some paper and pen with you to take note of who you have.\n3. Press the Draw button to become someone's Secret Santa.\n"
                                 "4. After you note who you have, click the Clear button.\n5. Send the next person to draw.";
    ui->lblInstructionsAssignment->setText(INSTRUCTIONS);
    ui->cboChoosingAssignment->addItem("", -1);
    for (int i = 0; i < santaBag.getPlayerCount(); i++) {
        QString name = santaBag.getPlayerNameAt(i);
        ui->cboChoosingAssignment->addItem(name, i);
    }
    int pCount = santaBag.getPlayerCount();
    ui->lblCounterAssignment->setText("Player Count: " + QString::number(pCount));
    setRotation(0);
    setGameState(ASSIGNMENT);

    // Future Upgrades
    ui->lblTimerAssignment->setText("Timer: 20 seconds");
    ui->lblTimerAssignment->setVisible(false);

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
    int pCount = santaBag.getPlayerCount();
    santaBag.setGiver(name);
    if(santaBag.drawPlayer()) {
        QString assignedName = santaBag.getAssignedName();
        QString assignedGift = santaBag.getAssignedGift();
        ui->txtNameAssignment->setText(assignedName);
        ui->txtGiftAssignment->setText(assignedGift);
        ui->txtGiftAssignment->setStyleSheet("background-color: rgba(0, 0, 0, 100); color: white; border: 1px solid #ccc; border-radius: 4px;");
        ui->cboChoosingAssignment->setItemData(index, 0, Qt::UserRole - 1);       // Grays out and makes current item unselectable.
        ui->cboChoosingAssignment->setItemData(index, QColor("#1e293b"), Qt::BackgroundRole);
        ui->cboChoosingAssignment->setCurrentText("");
        rotation++;
        pCount = pCount - rotation;
        ui->lblCounterAssignment->setText("Player Count: " + QString::number(pCount));
    }
    else {
        ui->txtNameAssignment->clear();
        ui->txtGiftAssignment->setText("Could not complete draw.");
        ui->txtGiftAssignment->setStyleSheet("color: #ff6b6b; background-color: rgba(192, 57, 43, 0.3); border-radius: 4px; padding: 6px;");
    }
    if(pCount == 0) {
        ui->lblCounterAssignment->setStyleSheet("border: 2px solid #2ecc71;");
        ui->lblTimerAssignment->setText("All Secret Santas have been assigned.");
        ui->lblTimerAssignment->setStyleSheet("color: #34d399; background-color: rgba(5, 150, 105, 0.25); border-radius: 4px; padding: 6px;");
    }
}

void MainWindow::on_btnClearAssignment_clicked()
{
    ui->cboChoosingAssignment->setCurrentText("");
    ui->txtNameAssignment->clear();
    ui->txtGiftAssignment->clear();
}

void MainWindow::on_btnDoneAssignment_clicked()
{
    this->close();
}

// SCREEN 5 - All Input Verification
void MainWindow::on_btnVerify_clicked()
{
    // Returns to necessary location...
    int gs = getGameState();
    switch(gs) {
    case 1:
        ui->stackedWidget->setCurrentWidget(ui->initialPage);
        break;
    case 2:
        ui->stackedWidget->setCurrentWidget(ui->setupPage);
        break;
    case 3:
        ui->stackedWidget->setCurrentWidget(ui->detailsPage);
        break;
    case 4:
        ui->stackedWidget->setCurrentWidget(ui->assignmentPage);
        break;
    default:
        ui->lblVerify->setText("Something went wrong.");
        ui->lblVerify->setStyleSheet("color: #ff6b6b; background-color: rgba(192, 57, 43, 0.3); border-radius: 4px; padding: 6px;");
        break;
    }
}
