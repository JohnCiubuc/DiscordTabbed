#include "PreferencesForm.h"
#include "ui_PreferencesForm.h"

PreferencesForm::PreferencesForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::PreferencesForm)
{
    ui->setupUi(this);
    this->hide();

    loadSettings();
}

PreferencesForm::~PreferencesForm()
{
    delete ui;
}

void PreferencesForm::loadSettings()
{

    QSettings settings("DiscordTabbed");
    _embedLinks = settings.value("embed-links", QStringList()).toStringList();
    if (!_embedLinks.isEmpty())
        ui->plainTextEdit->setPlainText(_embedLinks.join('\n'));
    else
        _embedLinks = ui->plainTextEdit->toPlainText().split('\n');


    ui->checkBox_SS->setChecked(settings.value("smooth-scroll", true).toBool());
}


void PreferencesForm::on_plainTextEdit_textChanged()
{
    QString plainText = ui->plainTextEdit->toPlainText();
    _embedLinks = plainText.split('\n');

    QSettings settings("DiscordTabbed");
    settings.setValue("embed-links", _embedLinks);
    emit preferencesUpdated();
}


void PreferencesForm::on_pushButton_clicked()
{
    emit embedGPUView();
}


void PreferencesForm::on_checkBox_SS_clicked(bool checked)
{
    QSettings settings("DiscordTabbed");
    settings.setValue("smooth-scroll", checked);
    emit preferencesUpdated();
}

