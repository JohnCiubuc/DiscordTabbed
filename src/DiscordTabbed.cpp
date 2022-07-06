#include "DiscordTabbed.h"
#include "ui_DiscordTabbed.h"

#define MINIMAL_VIEWS 1

DiscordTabbed::DiscordTabbed(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::DiscordTabbed)
{
    ui->setupUi(this);
//    ui->menubar->hide();
    _profile = new QWebEngineProfile(QString::fromLatin1("DiscordTabbed"));  // unique profile store per qtwbengine version
    _profile->setPersistentCookiesPolicy(QWebEngineProfile::ForcePersistentCookies);

    QSettings settings("DiscordTabbed");
    this->setGeometry(settings.value("geometry", this->geometry()).toRect());

    this->installEventFilter(this);
    _Preferences = new PreferencesForm();
    connect(_Preferences, &PreferencesForm::preferencesUpdated, this, &DiscordTabbed::preferencesUpdated);

    connect(_Preferences, &PreferencesForm::embedGPUView, this, [=]()
    {
        _lastDiscordChannel = QUrl("chrome://gpu");
        generateNewView();
    });

    _split = new QSplitter();
    ui->horizontalLayout->addWidget(_split);

    _lastDiscordChannel = QUrl("https://discord.com/login?redirect_to=%2Fchannels%2F%40me");
//    _lastDiscordChannel = QUrl("chrome://gpu");
    generateNewView();
// Shortcuts
    connect(new QShortcut(QKeySequence(Qt::CTRL | Qt::Key_D), this), &QShortcut::activated,
            this, &DiscordTabbed::generateNewView);
    connect(new QShortcut(QKeySequence(Qt::CTRL | Qt::SHIFT | Qt::Key_D), this), &QShortcut::activated,
            this, &DiscordTabbed::removeLastView);
}

DiscordTabbed::~DiscordTabbed()
{
    for (auto view : _views)
    {
        view->setPage(new QWebEnginePage());
//        view->deleteLater();
    }
//    for (int i = 0; i < _split->count(); ++i)
//    {
//        auto w = _split->widget(i);
//        dynamic_cast<ViewForm*>(w)->getView()->deleteLater();
//        w->deleteLater();
//    }
    QSettings settings("DiscordTabbed");
    settings.setValue("geometry", this->geometry());
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
}


void DiscordTabbed::urlChanged(QUrl url)
{
    db url;
    _lastDiscordChannel = url;
}

void DiscordTabbed::generateNewView()
{
    // Create new view, set minimal width for splitter
    {
//        auto profile = QWebEngineProfile::defaultProfile();
//        profile->setPersistentCookiesPolicy(QWebEngineProfile::AllowPersistentCookies);
//        _ctrlD = 0;
//        _views << new QWebEngineView();
//        _views.last()->setMinimumWidth(200);
//        _views.last()->setAttribute(Qt::WA_DeleteOnClose);

//        // Create page
//        DiscordTabbedPage * page = new DiscordTabbedPage(profile, _views.last());
////    page->profile()-
//        page->setEmbedLinks(_Preferences->getEmbedLinks());

//        connect(page, &DiscordTabbedPage::generateViewWithURL, this, &DiscordTabbed::generateViewWithURL);
//        _views.last()->setPage(page);

//        ViewForm * w = new ViewForm();
//        w->setViewWidget(_views.last());
//        w->updateIndex(_split->count());
//        // Add view to splitter
//        _split->addWidget(w);
//        _views.last()->load(QUrl("https://youtu.be/Qjh1EBktSuU"));
    }
    auto profile = QWebEngineProfile::defaultProfile();
    profile->setPersistentCookiesPolicy(QWebEngineProfile::AllowPersistentCookies);
    _ctrlD = 0;
    _views << new QWebEngineView();
    _views.last()->setMinimumWidth(200);
    _views.last()->setAttribute(Qt::WA_DeleteOnClose);
//    _views.last()->page()->createWindow(1);
    // If this is the first view, its the one with channels
    if (_views.size() == MINIMAL_VIEWS)
        connect(_views.last(), &QWebEngineView::urlChanged, this, &DiscordTabbed::urlChanged);

    // Create page
    DiscordTabbedPage * page = new DiscordTabbedPage(profile, _views.last());
//    page->profile()-
    page->setEmbedLinks(_Preferences->getEmbedLinks());

    connect(page, &DiscordTabbedPage::generateViewWithURL, this, &DiscordTabbed::generateViewWithURL);
    _views.last()->setPage(page);

    ViewForm * w = new ViewForm();
    w->setViewWidget(_views.last());
    w->updateIndex(_split->count());

    if (_views.size() >MINIMAL_VIEWS)
    {
        connect(w, &ViewForm::moveSplitterView, this, [=](QWidget * w, int index)
        {
            auto count = _split->count();
            if (index >= count)
            {
                index= count-1;
                dynamic_cast<ViewForm*>(w)->updateIndex(index);
            }
            _split->insertWidget(index, w);
        });
        connect(w, &ViewForm::closeSplitterView, this, [=](QWidget * w)
        {
//            w->hide();
//            _views.removeOne(dynamic_cast<QWebEngineView*>(dynamic_cast<ViewForm*>(w)->getView()));
            dynamic_cast<ViewForm*>(w)->getView()->deleteLater();
            w->deleteLater();
        });
    }
    else
    {
        w->hideLayoutButtons();
    }

    // Add view to splitter
    _split->addWidget(w);

    // If this is a sub-view, strip channels
    if (_views.size() > MINIMAL_VIEWS)
    {
        connect(_views.last(), &QWebEngineView::urlChanged, this, [=]()
        {
            stripDiscord(_views.last()->page());
        });
        connect(_views.last(), &QWebEngineView::loadFinished, this, [=]()
        {
            stripDiscord(_views.last()->page());
        });
    }

    // Load view
    _views.last()->load(_lastDiscordChannel);
}

void DiscordTabbed::removeLastView()
{
    return;
    _ctrlD = 0;
    if (_views.size() < MINIMAL_VIEWS) return;
    _views.last()->hide();
    auto view = _views.takeLast();

    QWidget * w = new QWidget;
    view->setParent(w);
    view->page()->deleteLater();
    view->deleteLater();
    w->deleteLater();

//    dynamic_cast<DiscordTabbedPage*>(view->page())->requestDelete();
//    delete view->page()->profile();
//    delete view->page();
//    delete view;

}

void DiscordTabbed::on_actionReload_Far_Left_View_triggered()
{

    _lastDiscordChannel = QUrl("https://discord.com/login?redirect_to=%2Fchannels%2F%40me");
    _views.first()->load(_lastDiscordChannel);
}


void DiscordTabbed::on_actionExpand_Retract_Left_View_triggered()
{
    removeLastView();
}

void DiscordTabbed::generateViewWithURL(QUrl url)
{
    auto old = _lastDiscordChannel;
    _lastDiscordChannel = url;
    generateNewView();
    _lastDiscordChannel = old;
}

void DiscordTabbed::on_actionOpen_Preferences_triggered()
{
    _Preferences->show();
}

void DiscordTabbed::preferencesUpdated()
{
    for (auto view : _views)
        if (view)
        {
            dynamic_cast<DiscordTabbedPage*>(view->page())
            ->setEmbedLinks(_Preferences->getEmbedLinks());
        }
}


void DiscordTabbed::on_actionEmbed_Current_Channel_triggered()
{
    generateNewView();
}

