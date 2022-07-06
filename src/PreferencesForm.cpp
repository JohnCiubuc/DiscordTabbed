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

bool PreferencesForm::getYoutubeEmbed()
{
    return ui->checkBox->isChecked();
}

bool PreferencesForm::getTwitchEmbed()
{
    return ui->checkBox_2->isChecked();
}


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
    ui->checkBox->setChecked(settings.value("youtube-embed", true).toBool());
    ui->checkBox_2->setChecked(settings.value("twitch-embed", true).toBool());
}

