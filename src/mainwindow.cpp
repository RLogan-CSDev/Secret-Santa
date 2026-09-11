#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "santaBag.h"

SantaBag bag;

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
        success = bag.addToBag(name, list);
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
    qDebug() << "Bag size: " << bag.getSize() << "\n";
    bag.printBag();
}


void MainWindow::on_btnDone_clicked(bool checked)
{

}

