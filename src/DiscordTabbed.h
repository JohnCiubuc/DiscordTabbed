#ifndef DISCORDTABBED_H
#define DISCORDTABBED_H

#include <QMainWindow>
#include <QUrl>
#include <QWebEngineView>
#include <QKeyEvent>

#include <QDebug>
#include <QSplitter>
#include <QWebEngineSettings>
#include <QWebEngineProfile>
#include <QKeySequence>
#include <QShortcut>

#include "DiscordTabbedPage.h"
#include "PreferencesForm.h"
#define db qDebug() << this <<

QT_BEGIN_NAMESPACE
namespace Ui
{
class DiscordTabbed;
}

QT_END_NAMESPACE

class DiscordTabbed : public QMainWindow
{
    Q_OBJECT

public:
    DiscordTabbed(QWidget *parent = nullptr);
    ~DiscordTabbed();

    void stripDiscord(QWebEnginePage * page);
private slots:
    void urlChanged(QUrl url);
    void generateNewView();
    void removeLastView();
    void on_actionReload_Far_Left_View_triggered();

    void on_actionExpand_Retract_Left_View_triggered();
    void generateViewWithURL(QUrl url);
    void on_actionOpen_Preferences_triggered();
    void preferencesUpdated();
    void on_actionEmbed_Current_Channel_triggered();

private:
    Ui::DiscordTabbed *ui;
    QUrl _lastDiscordChannel;
    QList<QWebEngineView*> _views;
    QSplitter * _split;
    PreferencesForm * _Preferences;
    int _ctrlD = 0;
protected:
    bool eventFilter(QObject *obj, QEvent *ev);
};
#endif // DISCORDTABBED_H
