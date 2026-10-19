#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "santaBag.h"

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
    void on_btnClear_clicked();

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

private:
    Ui::MainWindow *ui;
    SantaBag santaBag;
};
#endif // MAINWINDOW_H
