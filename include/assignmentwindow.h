#ifndef ASSIGNMENTWINDOW_H
#define ASSIGNMENTWINDOW_H

#include <QMainWindow>

namespace Ui {
class AssignmentWindow;
}

class AssignmentWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit AssignmentWindow(QWidget *parent = nullptr);
    ~AssignmentWindow();

private slots:
    void on_chkHasPartner_toggled(bool checked);

    void on_btnDraw_clicked();

    void on_btnClear_clicked();

    void on_btnDone_clicked(bool checked);

private:
    Ui::AssignmentWindow *ui;
};

#endif // ASSIGNMENTWINDOW_H
