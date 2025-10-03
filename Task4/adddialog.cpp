#include "adddialog.h"
#include "ui_adddialog.h"

AddDialog::AddDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddDialog)
{
    ui->setupUi(this);
    ui->horseSexCombo->setCurrentIndex(0);
}

AddDialog::~AddDialog()
{
    delete ui;
}

RaceParticipant AddDialog::getParticipant() {
    RaceParticipant p;

    p.competitionName = ui->competitionNameEdit->text().trimmed();
    p.competitionDate = ui->dateEdit->text().trimmed();
    p.horse.name = ui->horseNameEdit->text().trimmed();
    p.horse.sex = ui->horseSexCombo->currentText().contains("male") ? "male" : "female";
    p.horse.age = ui->horseAgeEdit->value();
    p.owner.fio = ui->ownerFioEdit->text().trimmed();
    p.owner.address = ui->ownerAddressEdit->text().trimmed();
    p.owner.phone = ui->ownerPhoneEdit->text().trimmed();
    p.jockey.fio = ui->jockeyFioEdit->text().trimmed();
    p.jockey.address = ui->jockeyAddressEdit->text().trimmed();
    p.jockey.age = ui->jockeyAgeEdit->value();
    p.jockey.rating = ui->jockeyRatingEdit->value();

    return p;
}
