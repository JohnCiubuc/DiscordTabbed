#include "DiscordTabbedPage.h"

DiscordTabbedPage::DiscordTabbedPage(QObject *parent)
    : QWebEnginePage{parent}
{
    interp = new WebUrlRequestInterceptor;
    this->setUrlRequestInterceptor(interp);

}

void DiscordTabbedPage::setEmbedLinks(QStringList list)
{
    _embedLinks = list;
    db _embedLinks;
    interp->setEmbedLinks(_embedLinks);
}
bool DiscordTabbedPage::acceptNavigationRequest(const QUrl &url, NavigationType type, bool isMainFrame)
{
    qDebug() << "acceptNavigationRequest("<<url << "," << type << "," << isMainFrame<<")";

    // can i use less if statements please, shesh
    if(type == QWebEnginePage::NavigationTypeLinkClicked)
    {
        QString urlString = url.toString();
        for (auto link : _embedLinks)
        {
            if(urlString.contains(link))
            {
                emit generateViewWithURL(url);
                return false;
            }
        }
        QDesktopServices::openUrl(url);
        return false;
    }
    return true;
}
