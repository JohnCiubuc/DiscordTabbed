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
#include "ViewForm.h"
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
    void on_actionReload_Far_Left_View_triggered();

    void generateViewWithURL(QUrl url);
    void on_actionOpen_Preferences_triggered();
    void preferencesUpdated();
    void on_actionEmbed_Current_Channel_triggered();

private:
    Ui::DiscordTabbed *ui;
    QUrl _lastDiscordChannel;
    QList<QWebEngineView*> _views;
    QMap<QWebEngineView*, QWidget*> _viewMaps;
    QSplitter * _split;
    PreferencesForm * _Preferences;

};
#endif // DISCORDTABBED_H
