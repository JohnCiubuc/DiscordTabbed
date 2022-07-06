#ifndef DISCORDTABBEDPAGE_H
#define DISCORDTABBEDPAGE_H

#include <QWebEnginePage>
#include <QObject>
#include <QDesktopServices>
#include <QWebEngineUrlRequestInterceptor>
#include <QUrl>
#include <QTimer>
#include <QDebug>
#define db qDebug() << this <<

class WebUrlRequestInterceptor : public QWebEngineUrlRequestInterceptor
{
    Q_OBJECT

public:
    void setEmbedLinks(QStringList list)
    {
        _embedLinks = list;
    }
    WebUrlRequestInterceptor(QObject *p = Q_NULLPTR)
    {

    }
    void interceptRequest(QWebEngineUrlRequestInfo &info)
    {
//        db info.requestUrl();
//        QString urlString = info.requestUrl().toString();
//        for (auto link : _embedLinks)
//        {
//            if(urlString.contains(link))
//            {
//                db "BLOCKING";
//                info.block(true);
//                return;
//            }
//        }
    }
private:
    QStringList _embedLinks;
};


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
    explicit DiscordTabbedPage(QWebEngineProfile * profile = nullptr, QObject *parent = nullptr);
    void setEmbedLinks(QStringList list);
    bool acceptNavigationRequest(const QUrl & url, QWebEnginePage::NavigationType type, bool isMainFrame);
    void requestDelete();
private:
    bool _bNewLink = false;
    bool _bYoutubeEmbed;
    bool _bTwitchEmbed;
    QStringList _embedLinks;
    WebUrlRequestInterceptor * interp;
protected:

    QWebEnginePage  *createWindow(WebWindowType type)
    {

        if(type == QWebEnginePage::WebBrowserTab)
        {
            db "create new web browser tab";
            FakePage *webView = new FakePage();
//            emit new_tab(webView);
            return webView;
        }

//        if(type == QWebEnginePage::WebBrowserBackgroundTab)
//        {
//            db "create mew backgrouind";
//            FakePage *webView = new FakePage();
////            emit new_tab(webView);
//            return webView;
//        }
        return nullptr;
    }

};

#endif // DISCORDTABBEDPAGE_H
