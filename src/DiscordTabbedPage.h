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
    void setEmbedLinks(bool y,bool t);
    bool acceptNavigationRequest(const QUrl & url, QWebEnginePage::NavigationType type, bool isMainFrame);
private:
    bool _bNewLink = false;
    bool _bYoutubeEmbed;
    bool _bTwitchEmbed;
};

#endif // DISCORDTABBEDPAGE_H
