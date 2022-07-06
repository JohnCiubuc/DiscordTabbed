#include "DiscordTabbed.h"
#include "ui_DiscordTabbed.h"

DiscordTabbed::DiscordTabbed(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::DiscordTabbed)
{
    ui->setupUi(this);
    this->installEventFilter(this);
    _Preferences = new PreferencesForm();
    connect(_Preferences, &PreferencesForm::preferencesUpdated, this, &DiscordTabbed::preferencesUpdated);

    _split = new QSplitter();
    ui->horizontalLayout->addWidget(_split);

    _lastDiscordChannel = QUrl("https://discord.com/login?redirect_to=%2Fchannels%2F%40me");
    generateNewView();
// Shortcuts
    connect(new QShortcut(QKeySequence(Qt::CTRL + Qt::Key_D), this), &QShortcut::activated,
            this, &DiscordTabbed::generateNewView);
    connect(new QShortcut(QKeySequence(Qt::CTRL + Qt::SHIFT + Qt::Key_D), this), &QShortcut::activated,
            this, &DiscordTabbed::removeLastView);
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
}


void DiscordTabbed::urlChanged(QUrl url)
{
    db url;
    _lastDiscordChannel = url;
}

void DiscordTabbed::generateNewView()
{
    // Create new view, set minimal width for splitter
    _ctrlD = 0;
    _views << new QWebEngineView(this);
    _views.last()->setMinimumWidth(200);

    QWebEngineProfile::defaultProfile()
    ->setPersistentCookiesPolicy(QWebEngineProfile::ForcePersistentCookies);

//    // Make it spiffy
//    _views.last()->settings()
//    ->setAttribute(QWebSettings::JavascriptEnabled, true);
//    _views.last()->settings()
//    ->setAttribute(QWebEngineSettings::JavascriptCanOpenWindows,true);

    // If this is the first view, its the one with channels
    if (_views.size() == 1)
        connect(_views.last(), &QWebEngineView::urlChanged, this, &DiscordTabbed::urlChanged);
    connect(_views.last()->page(), &QWebEnginePage::linkHovered, this, [=](const QString &url)
    {
        db url;
    });

    // Create page
    DiscordTabbedPage * page = new DiscordTabbedPage(_views.last());
    page->setEmbedLinks(_Preferences->getYoutubeEmbed(), _Preferences->getTwitchEmbed());
    connect(page, &DiscordTabbedPage::generateViewWithURL, this, &DiscordTabbed::generateViewWithURL);
    _views.last()->setPage(page);

    // Add view to splitter
    _split->addWidget(_views.last());

    // If this is a sub-view, strip channels
    if (_views.size() != 1)
    {
        connect(_views.last(), &QWebEngineView::urlChanged, this, [=]()
        {
            stripDiscord(_views.last()->page());
        });
    }

    // Load view
    _views.last()->load(_lastDiscordChannel);
}

void DiscordTabbed::removeLastView()
{
    _ctrlD = 0;
    if (_views.size() < 2) return;
    _views.last()->hide();
    _views.takeLast()->deleteLater();
}

bool DiscordTabbed::eventFilter(QObject *obj, QEvent *ev)
{
//    if (ev->type() == QEvent::KeyPress)
//    {
//        db static_cast<QKeyEvent*>(ev)->key();
//        if (static_cast<QKeyEvent*>(ev)->key() == Qt::Key_Control ||
//                static_cast<QKeyEvent*>(ev)->key() == Qt::Key_Shift)
//            _ctrlD++;
//        else if (static_cast<QKeyEvent*>(ev)->key() == Qt::Key_D)
//        {
//            switch(_ctrlD)
//            {
//            case 1:
//                generateNewView();
//                break;
//            case 2:
//                removeLastView();
//                break;
//            }

//        }
//        else if (ev->type() == QEvent::KeyRelease)
//        {
//            if (static_cast<QKeyEvent*>(ev)->key() == Qt::Key_Control ||
//                    static_cast<QKeyEvent*>(ev)->key() == Qt::Key_Shift)
//            {
//                _ctrlD--;
//                if (_ctrlD<0)
//                    _ctrlD = 0;
//            }
//        }
//    }
    return QMainWindow::eventFilter(obj, ev);
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
        dynamic_cast<DiscordTabbedPage*>(view->page())
        ->setEmbedLinks(_Preferences->getYoutubeEmbed(),
                        _Preferences->getTwitchEmbed());
}

