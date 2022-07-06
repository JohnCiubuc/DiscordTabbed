#include "DiscordTabbedPage.h"

DiscordTabbedPage::DiscordTabbedPage(QObject *parent)
    : QWebEnginePage{parent}
{

}

void DiscordTabbedPage::setEmbedLinks(bool y, bool t)
{
    _bYoutubeEmbed = y;
    _bTwitchEmbed = t;
}
bool DiscordTabbedPage::acceptNavigationRequest(const QUrl &url, NavigationType type, bool isMainFrame)
{
    qDebug() << "acceptNavigationRequest("<<url << "," << type << "," << isMainFrame<<")";

    // can i use less if statements please, shesh
    if(type == QWebEnginePage::NavigationTypeLinkClicked)
    {
        if (_bYoutubeEmbed)
        {
            if (url.toString().contains("youtube.com") ||
                    url.toString().contains("youtu.be"))
            {
                emit generateViewWithURL(url);
                return false;
            }
        }
        else if (_bTwitchEmbed && url.toString().contains("twitch.tv"))
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
