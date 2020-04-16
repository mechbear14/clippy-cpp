#include "wikiboxui.h"

StartPage::StartPage(QWidget *parent, WikiBoxFrontend *frontend)
    : QWidget(parent, Qt::Popup | Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint)
    , frontend { frontend }
    , title { new QLabel(tr("What would you like to know?")) }
    , message { new QLabel }
    , query { new QLineEdit }
    , searchButton { new QPushButton(tr("Search")) }
    , backButton { new QPushButton(tr("Back")) }
    , mainLayout { new QVBoxLayout }
    , buttonLayout { new QHBoxLayout }
{
    setStyleSheet("StartPage, QPushButton, QLineEdit {background: #ffff80} QPushButton::hover{background: #ffff40}");
    title->setStyleSheet("QLabel {font: bold}");
    title->setWordWrap(true);
    message->setStyleSheet("QLabel {color: red}");

    buttonLayout->addWidget(backButton);
    buttonLayout->addWidget(searchButton);
    mainLayout->addWidget(title);
    mainLayout->addWidget(message);
    mainLayout->addWidget(query);
    mainLayout->addLayout(buttonLayout);
    setLayout(mainLayout);

    setSizePolicy(QSizePolicy(QSizePolicy::Fixed, QSizePolicy::MinimumExpanding));

    connect(backButton, &QPushButton::clicked, frontend, &WikiBoxFrontend::quitProgram);
    connect(searchButton, &QPushButton::clicked, frontend, &WikiBoxFrontend::startSearch);
}

QSize StartPage::sizeHint() const{
    return QSize(200, 100);
}

SearchingPage::SearchingPage(QWidget *parent, WikiBoxFrontend *frontend)
    : QWidget(parent, Qt::Popup | Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint)
    , frontend { frontend }
    , title { new QLabel(tr("Searching...")) }
    , cancelButton { new QPushButton(tr("Cancel")) }
    , mainLayout { new QVBoxLayout }
{
    setStyleSheet("SearchingPage, QPushButton, QLineEdit {background: #ffff80} QPushButton::hover{background: #ffff40}");
    title->setWordWrap(true);

    mainLayout->addWidget(title);
    mainLayout->addWidget(cancelButton);
    mainLayout->setStretchFactor(title, 1);
    setLayout(mainLayout);

    setSizePolicy(QSizePolicy(QSizePolicy::Fixed, QSizePolicy::MinimumExpanding));

    connect(cancelButton, &QPushButton::clicked, frontend, &WikiBoxFrontend::cancelSearch);
}

QSize SearchingPage::sizeHint() const{
    return QSize(200, 100);
}

ResultPage::ResultPage(QWidget *parent, WikiBoxFrontend *frontend)
    : QWidget(parent, Qt::Popup | Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint)
    , frontend { frontend }
    , title { new QLabel(tr("")) }
    , content { new QLabel(tr("No WikiPedia result found. I'm opening the browser for you though")) }
    , exploreButton { new QPushButton(tr("Explore")) }
    , backButton { new QPushButton(tr("Back")) }
    , buttonLayout { new QHBoxLayout }
    , mainLayout { new QVBoxLayout }
{
    setStyleSheet("ResultPage, QPushButton, QLineEdit {background: #ffff80} QPushButton::hover{background: #ffff40}");
    title->setStyleSheet("QLabel {font: bold}");
    content->setWordWrap(true);

    buttonLayout->addWidget(backButton);
    buttonLayout->addWidget(exploreButton);
    mainLayout->addWidget(title);
    mainLayout->addWidget(content);
    mainLayout->addLayout(buttonLayout);
    mainLayout->setStretchFactor(content, 1);
    setLayout(mainLayout);

    setSizePolicy(QSizePolicy(QSizePolicy::Fixed, QSizePolicy::MinimumExpanding));

    connect(backButton, &QPushButton::clicked, frontend, &WikiBoxFrontend::newSearch);
    connect(exploreButton, &QPushButton::clicked, frontend, &WikiBoxFrontend::explore);
}

QSize ResultPage::sizeHint() const{
    return QSize(200, 100);
}
