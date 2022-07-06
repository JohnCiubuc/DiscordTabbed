#ifndef DISCORDTABBEDPAGE_H
#define DISCORDTABBEDPAGE_H

#include <QWebEnginePage>
#include <QObject>
#include <QDesktopServices>
#include <QUrl>
#include <QTimer>
#include <QDebug>


class FakePage : public QWebEnginePage
{
public:
    explicit FakePage()
    {
        connect(this, &QWebEnginePage::urlChanged, this, [=](QUrl url)
        {
            QDesktopServices::openUrl(url);
            this->deleteLater();
        });
    }
};

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
protected:

    QWebEnginePage  *createWindow(WebWindowType type)
    {
        return new FakePage;
    }
};

#endif // DISCORDTABBEDPAGE_H
