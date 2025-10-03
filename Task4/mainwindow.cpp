#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "adddialog.h"
#include "searchdialog.h"
#include <QDragEnterEvent>
#include <QDropEvent>
#include <QMimeData>
#include <QUrl>
#include <QFileInfo>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);
    setAcceptDrops(true);
    loadData();
    displayData(participants);
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::loadData() {
    QFile file(fileName);
    if (!file.open(QIODevice::ReadOnly)) {
        QMessageBox::information(this, "Info", "Файл не найден, создадим новый.");
        return;
    }
    QDataStream in(&file);
    participants.clear();
    while (!in.atEnd()) {
        RaceParticipant p;
        in >> p.competitionName >> p.competitionDate
            >> p.horse.name >> p.horse.sex >> p.horse.age
            >> p.owner.fio >> p.owner.address >> p.owner.phone
            >> p.jockey.fio >> p.jockey.address >> p.jockey.age >> p.jockey.rating;
        participants.append(p);
    }
    file.close();
}

void MainWindow::saveData() {
    QFile file(fileName);
    if (!file.open(QIODevice::WriteOnly)) {
        QMessageBox::warning(this, "Error", "Не удалось сохранить файл.");
        return;
    }
    QDataStream out(&file);
    for (const auto& p : participants) {
        out << p.competitionName << p.competitionDate
            << p.horse.name << p.horse.sex << p.horse.age
            << p.owner.fio << p.owner.address << p.owner.phone
            << p.jockey.fio << p.jockey.address << p.jockey.age << p.jockey.rating;
    }
    file.close();
    QMessageBox::information(this, "Success", "Данные сохранены.");
}

void MainWindow::displayData(const QVector<RaceParticipant>& data, bool isSearch) {
    ui->tableWidget->clear();
    ui->tableWidget->setRowCount(data.size());
    ui->tableWidget->setColumnCount(12);
    QStringList headers = {"Состязание", "Дата", "Лошадь: Кличка", "Пол", "Возраст",
                           "Владелец: ФИО", "Адрес", "Телефон",
                           "Жокей: ФИО", "Адрес", "Возраст", "Рейтинг"};
    ui->tableWidget->setHorizontalHeaderLabels(headers);

    for (int i = 0; i < data.size(); ++i) {
        const auto& p = data[i];
        ui->tableWidget->setItem(i, 0, new QTableWidgetItem(p.competitionName));
        ui->tableWidget->setItem(i, 1, new QTableWidgetItem(p.competitionDate));
        ui->tableWidget->setItem(i, 2, new QTableWidgetItem(p.horse.name));
        ui->tableWidget->setItem(i, 3, new QTableWidgetItem(p.horse.sex));
        ui->tableWidget->setItem(i, 4, new QTableWidgetItem(QString::number(p.horse.age)));
        ui->tableWidget->setItem(i, 5, new QTableWidgetItem(p.owner.fio));
        ui->tableWidget->setItem(i, 6, new QTableWidgetItem(p.owner.address));
        ui->tableWidget->setItem(i, 7, new QTableWidgetItem(p.owner.phone));
        ui->tableWidget->setItem(i, 8, new QTableWidgetItem(p.jockey.fio));
        ui->tableWidget->setItem(i, 9, new QTableWidgetItem(p.jockey.address));
        ui->tableWidget->setItem(i, 10, new QTableWidgetItem(QString::number(p.jockey.age)));
        ui->tableWidget->setItem(i, 11, new QTableWidgetItem(QString::number(p.jockey.rating)));
    }
    ui->tableWidget->resizeColumnsToContents();

    if (data.isEmpty() && isSearch) {
        QMessageBox::information(this, "Поиск", "Результатов не найдено.");
    }
}

void MainWindow::on_addButton_clicked() {
    AddDialog dialog(this);
    if (dialog.exec() == QDialog::Accepted) {
        RaceParticipant p = dialog.getParticipant();
        participants.append(p);
        displayData(participants);
    }
}

void MainWindow::on_searchButton_clicked() {
    SearchDialog dialog(this);
    if (dialog.exec() == QDialog::Accepted) {
        QString type = dialog.getSearchType();
        QString value = dialog.getSearchValue().trimmed();
        QVector<RaceParticipant> results;

        if (type.contains("horse")) {
            for (const auto& p : participants) {
                if (p.horse.name == value) {
                    results.append(p);
                }
            }
        } else if (type.contains("competition")) {
            for (const auto& p : participants) {
                if (p.competitionName == value) {
                    results.append(p);
                }
            }
        } else if (type.contains("horse_age")) {
            bool ok;
            int age = value.toInt(&ok);
            if (ok && !value.isEmpty()) {
                for (const auto& p : participants) {
                    if (p.horse.age > age) {
                        results.append(p);
                    }
                }
            } else {
                QMessageBox::warning(this, "Ошибка", "Введите корректный возраст.");
                return;
            }
        }

        displayData(results, true);
    }
}

void MainWindow::on_saveButton_clicked() {
    saveData();
}

void MainWindow::on_loadButton_clicked() {
    loadData();
    displayData(participants);
}

void MainWindow::dragEnterEvent(QDragEnterEvent *event) {
    if (event->mimeData()->hasUrls()) {
        event->acceptProposedAction();
    }
}

void MainWindow::dropEvent(QDropEvent *event) {
    const QMimeData *mimeData = event->mimeData();
    if (mimeData->hasUrls()) {
        QList<QUrl> urlList = mimeData->urls();
        if (!urlList.isEmpty()) {
            QString droppedFile = urlList.at(0).toLocalFile();
            QFileInfo fileInfo(droppedFile);
            if (fileInfo.suffix() == "dat") {
                fileName = droppedFile;
                loadData();
                displayData(participants);
                QMessageBox::information(this, "Успех", "Данные загружены из " + fileName);
            } else {
                QMessageBox::warning(this, "Ошибка", "Поддерживаются только .dat файлы.");
            }
        }
    }
}
