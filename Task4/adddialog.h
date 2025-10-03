#ifndef ADDDIALOG_H
#define ADDDIALOG_H

#include <QDialog>
#include "mainwindow.h"

namespace Ui {
class AddDialog;
}

class AddDialog : public QDialog {
    Q_OBJECT

public:
    explicit AddDialog(QWidget *parent = nullptr);
    ~AddDialog();
    RaceParticipant getParticipant();

private:
    Ui::AddDialog *ui;
};

#endif // ADDDIALOG_H
