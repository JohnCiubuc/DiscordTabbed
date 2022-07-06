#ifndef DISCORDTABBED_H
#define DISCORDTABBED_H

#include <QMainWindow>
#include <QUrl>
#include <QWebEngineView>
#include <QKeyEvent>

#include <QDebug>
#include <QSplitter>
#include "DiscordTabbedPage.h"
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
private:
    Ui::DiscordTabbed *ui;
    QUrl lastDiscordChannel;
    QList<QWebEngineView*> views;
    QSplitter * _split;
    QWebEngineView * _firstView;
protected:
    bool eventFilter(QObject *obj, QEvent *ev);
    int ctrlD = 0;
};
#endif // DISCORDTABBED_H
