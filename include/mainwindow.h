#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "SantaBag.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow() override;

private slots:
    // Screen 1 - Setup
    void on_btnStartInitial_clicked();

    // Screen 2 - Adding Players
    void on_btnAddSetup_clicked();
    void on_btnDoneSetup_clicked();

    // Screen 3 - Adding Gifts / Partners
    void on_btnAddDetails_clicked();
    void on_btnDoneDetails_clicked();
    void on_chkHasPartnerDetails_toggled(bool checked);

    // Screen 4 - Secret Santa Assignment
    void on_btnDrawAssignment_clicked();
    void on_btnDoneAssignment_clicked();
    void on_btnClearAssignment_clicked();

    void on_btnVerify_clicked();

private:
    Ui::MainWindow *ui;
    SantaBag santaBag;
    int rotation = 0;
    void setRotation(int r) { rotation = r; }
    int getRotation() { return rotation; }
    int gameState;
    void setGameState(int s) { gameState = s; }
    int getGameState() { return gameState; }
    const int INITIAL = 1;
    const int SETUP = 2;
    const int DETAILS = 3;
    const int ASSIGNMENT = 4;
};
#endif // MAINWINDOW_H
