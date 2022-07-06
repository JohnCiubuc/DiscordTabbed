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
signals:
    void preferencesUpdated();
public:
    explicit PreferencesForm(QWidget *parent = nullptr);
    ~PreferencesForm();

    QStringList getEmbedLinks()
    {
        return _embedLinks;
    }
//    bool getYoutubeEmbed();
//    bool getTwitchEmbed();
private slots:

    void on_checkBox_clicked(bool checked);

    void on_checkBox_2_clicked(bool checked);

    void on_plainTextEdit_textChanged();

private:
    void loadSettings();
    Ui::PreferencesForm *ui;
    QStringList _embedLinks;
};

#endif // PREFERENCESFORM_H
