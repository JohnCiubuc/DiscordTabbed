#include "DiscordTabbed.h"
#include "ui_DiscordTabbed.h"

DiscordTabbed::DiscordTabbed(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::DiscordTabbed)
{
    ui->setupUi(this);
//    ui->webEngineView->set
    this->installEventFilter(this);

    _firstView = new QWebEngineView();
    _firstView->setMinimumWidth(100);

    _split = new QSplitter();
    ui->horizontalLayout->addWidget(_split);

    _split->addWidget(_firstView);
    _firstView->show();

    DiscordTabbedPage * page = new DiscordTabbedPage(_firstView);
    _firstView->setPage(page);
    connect(page, &DiscordTabbedPage::generateViewWithURL, this, &DiscordTabbed::generateViewWithURL);
//    ui->webEngineView->load(QUrl("https://discord.com/login?redirect_to=%2Fchannels%2F%40me"));
    _firstView->load(QUrl("https://discord.com/channels/122962330165313536/246318973019357196"));
    connect(_firstView, &QWebEngineView::urlChanged, this, &DiscordTabbed::urlChanged);
    connect(_firstView, &QWebEngineView::loadFinished, this, [=]()
    {
        db "finished";
//        generateNewView();

    });
}

DiscordTabbed::~DiscordTabbed()
{
    delete ui;
}

void DiscordTabbed::stripDiscord(QWebEnginePage *page)
{
    page->runJavaScript(
        "\
            var elem = document.querySelector('div[class^=\"sidebar\"]');\
            elem.parentNode.removeChild(elem);\
            var elem = document.querySelector('nav[class^=\"wrapper\"]');\
            elem.parentNode.removeChild(elem);\
        "
    );
//    ui->webEngineView->page()->runJavaScript(
//        "\
//                       var elem = document.querySelector('div[class^=\"chat\"]');\
//                       elem.parentNode.removeChild(elem);\
//        "
//    );
}


void DiscordTabbed::urlChanged(QUrl url)
{

//    if (url == QUrl("https://discord.com/app") && views.size() < 1)
//    {
//        ui->webEngineView->setMaximumWidth(330);
//        generateNewView();

//    }
//    if(url.toString().contains("https://discord.com/channels/"))
//    {
//        views.last()->setPage(ui->webEngineView->page());
//    }
    db url;
    lastDiscordChannel = url;
}

void DiscordTabbed::generateNewView()
{
    ctrlD = 0;
    views << new QWebEngineView(this);
    DiscordTabbedPage * page = new DiscordTabbedPage(views.last());
    views.last()->setPage(page);
    connect(page, &DiscordTabbedPage::generateViewWithURL, this, &DiscordTabbed::generateViewWithURL);
    views.last()->load(lastDiscordChannel);
//    ui->horizontalLayout->addWidget(views.last());
    _split->addWidget(views.last());
    connect(views.last(), &QWebEngineView::urlChanged, this, [=]()
    {
        stripDiscord(views.last()->page());
    });
//    _split->setRubberBand(views.size());
}

void DiscordTabbed::removeLastView()
{
    ctrlD = 0;
    if (views.size() < 1) return;
    views.last()->hide();
//    ui->horizontalLayout->removeWidget(views.last());
    auto a = views.takeLast();
    a->deleteLater();
}

bool DiscordTabbed::eventFilter(QObject *obj, QEvent *ev)
{
    if (ev->type() == QEvent::KeyPress)
    {
        db static_cast<QKeyEvent*>(ev)->key();
        if (static_cast<QKeyEvent*>(ev)->key() == Qt::Key_Control ||
                static_cast<QKeyEvent*>(ev)->key() == Qt::Key_Shift)
            ctrlD++;
        else if (static_cast<QKeyEvent*>(ev)->key() == Qt::Key_D)
        {
            switch(ctrlD)
            {
            case 1:
                generateNewView();
                break;
            case 2:
                removeLastView();
                break;
            }

        }
        else if (ev->type() == QEvent::KeyRelease)
        {
            if (static_cast<QKeyEvent*>(ev)->key() == Qt::Key_Control ||
                    static_cast<QKeyEvent*>(ev)->key() == Qt::Key_Shift)
            {
                ctrlD--;
                if (ctrlD<0)
                    ctrlD = 0;
            }
        }
    }
    return QMainWindow::eventFilter(obj, ev);
}


void DiscordTabbed::on_actionReload_Far_Left_View_triggered()
{
    _firstView->reload();
}


void DiscordTabbed::on_actionExpand_Retract_Left_View_triggered()
{
    removeLastView();
//    if(ui->webEngineView->geometry().width() <= 330)
//    {
//        for(QWebEngineView* view : views)
//            view->hide();
//        ui->webEngineView->setMaximumWidth(99999);
//    }
//    else
//    {

//        for(QWebEngineView* view : views)
//            view->show();
//        ui->webEngineView->setMaximumWidth(330);
//    }
}

void DiscordTabbed::generateViewWithURL(QUrl url)
{
    auto old = lastDiscordChannel;
    lastDiscordChannel = url;
    generateNewView();
    lastDiscordChannel = old;
}

