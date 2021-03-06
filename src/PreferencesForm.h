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
    void embedGPUView();
public:
    explicit PreferencesForm(QWidget *parent = nullptr);
    ~PreferencesForm();

    QStringList getEmbedLinks()
    {
        return _embedLinks;
    }
private slots:

    void on_plainTextEdit_textChanged();

    void on_pushButton_clicked();

    void on_checkBox_SS_clicked(bool checked);

private:
    void loadSettings();
    Ui::PreferencesForm *ui;
    QStringList _embedLinks;
};

#endif // PREFERENCESFORM_H
