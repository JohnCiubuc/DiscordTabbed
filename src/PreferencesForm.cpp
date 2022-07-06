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

//bool PreferencesForm::getYoutubeEmbed()
//{
//    return ui->checkBox->isChecked();
//}

//bool PreferencesForm::getTwitchEmbed()
//{
//    return ui->checkBox_2->isChecked();
//}


void PreferencesForm::on_checkBox_clicked(bool checked)
{
    QSettings settings("DiscordTabbed");
    settings.setValue("youtube-embed", checked);
    emit preferencesUpdated();
}


void PreferencesForm::on_checkBox_2_clicked(bool checked)
{

    QSettings settings("DiscordTabbed");
    settings.setValue("twitch-embed", checked);
    emit preferencesUpdated();
}

void PreferencesForm::loadSettings()
{

    QSettings settings("DiscordTabbed");
    _embedLinks = settings.value("embed-links", QStringList()).toStringList();
    if (!_embedLinks.isEmpty())
        ui->plainTextEdit->setPlainText(_embedLinks.join('\n'));
    else
        _embedLinks = ui->plainTextEdit->toPlainText().split('\n');
//    ui->checkBox->setChecked(settings.value("youtube-embed", true).toBool());
//    ui->checkBox_2->setChecked(settings.value("twitch-embed", true).toBool());
}


void PreferencesForm::on_plainTextEdit_textChanged()
{
    QString plainText = ui->plainTextEdit->toPlainText();
    _embedLinks = plainText.split('\n');

    QSettings settings("DiscordTabbed");
    settings.setValue("embed-links", _embedLinks);
    emit preferencesUpdated();
}

