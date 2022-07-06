#ifndef PREFERENCESFORM_H
#define PREFERENCESFORM_H

#include <QWidget>
#include <QDebug>
#include <QSettings>
#define db qDebug() << this <<
namespace Ui
{
class PreferencesForm;
}

class PreferencesForm : public QWidget
{
    Q_OBJECT

public:
    explicit PreferencesForm(QWidget *parent = nullptr);
    ~PreferencesForm();

    bool getYoutubeEmbed();
    bool getTwitchEmbed();
private slots:

    void on_checkBox_clicked(bool checked);

    void on_checkBox_2_clicked(bool checked);

private:
    void loadSettings();
    Ui::PreferencesForm *ui;
};

#endif // PREFERENCESFORM_H
