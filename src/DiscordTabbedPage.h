#ifndef DISCORDTABBEDPAGE_H
#define DISCORDTABBEDPAGE_H

#include <QWebEnginePage>
#include <QObject>
#include <QDesktopServices>
#include <QUrl>
#include <QTimer>
class DiscordTabbedPage : public QWebEnginePage
{
    Q_OBJECT
signals:
    void generateViewWithURL(QUrl);
public:
    explicit DiscordTabbedPage(QObject *parent = nullptr);
    bool acceptNavigationRequest(const QUrl & url, QWebEnginePage::NavigationType type, bool isMainFrame)
    {
        qDebug() << "acceptNavigationRequest("<<url << "," << type << "," << isMainFrame<<")";

        if(type == QWebEnginePage::NavigationTypeLinkClicked)
        {
            if (url.toString().contains("youtube.com") ||
                    url.toString().contains("twitch.tv")||
                    url.toString().contains("youtu.be") )
            {
                emit generateViewWithURL(url);
                return false;
            }
            else
            {
                QDesktopServices::openUrl(url);
                return false;
            }
        }
        return true;
    }
private:
    bool _bNewLink = false;
};

#endif // DISCORDTABBEDPAGE_H
