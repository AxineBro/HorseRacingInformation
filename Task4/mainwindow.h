#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTableWidget>
#include <QVector>
#include <QFile>
#include <QDataStream>
#include <QMessageBox>

struct Horse {
    QString name;
    QString sex;
    int age;
};

struct Owner {
    QString fio;
    QString address;
    QString phone;
};

struct Jockey {
    QString fio;
    QString address;
    int age;
    double rating;
};

struct RaceParticipant {
    QString competitionName;
    QString competitionDate;
    Horse horse;
    Owner owner;
    Jockey jockey;
};

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_addButton_clicked();
    void on_searchButton_clicked();
    void on_saveButton_clicked();
    void on_loadButton_clicked();

private:
    Ui::MainWindow *ui;
    QVector<RaceParticipant> participants;
    QString fileName = "races.dat";

    void loadData();
    void saveData();
    void displayData(const QVector<RaceParticipant>& data, bool isSearch = false);

protected:
    void dragEnterEvent(QDragEnterEvent *event) override;
    void dropEvent(QDropEvent *event) override;
};

#endif // MAINWINDOW_H
