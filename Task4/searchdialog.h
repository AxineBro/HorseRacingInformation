#ifndef SEARCHDIALOG_H
#define SEARCHDIALOG_H

#include <QDialog>

namespace Ui {
class SearchDialog;
}

class SearchDialog : public QDialog {
    Q_OBJECT

public:
    explicit SearchDialog(QWidget *parent = nullptr);
    ~SearchDialog();
    QString getSearchType();
    QString getSearchValue();

private:
    Ui::SearchDialog *ui;
};

#endif // SEARCHDIALOG_H
