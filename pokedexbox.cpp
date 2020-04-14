#include "pokedexbox.h"
#include <iostream>

#include <QLabel>
#include <QLineEdit>
#include <QVBoxLayout>
#include <QStringBuilder>

PokedexBox::PokedexBox(QWidget *parent)
    : QWidget(parent, Qt::Popup | Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint)
    , input{ new QLineEdit }
    , submitButton{ new QPushButton("Submit") }
    , http{ new QNetworkAccessManager(this) }
{
    // Copy-and-pasted window flags

    // Title
    QLabel *title{ new QLabel("Pokedex") };

    // Content widget
    QLabel *inputPrompt{ new QLabel("Please input a number between 1 and 718") };
    inputPrompt->setWordWrap(true);
    inputPrompt->setBuddy(input);

    // Buttons
    QHBoxLayout *buttonLayout{ new QHBoxLayout };
    QPushButton *backButton { new QPushButton("Back") };
    connect(backButton, &QPushButton::clicked, this, &PokedexBox::close);
    connect(submitButton, &QPushButton::clicked, this, &PokedexBox::validateForm);
    buttonLayout->addWidget(backButton);
    buttonLayout->addWidget(submitButton);

    QVBoxLayout *mainLayout{ new QVBoxLayout };

    // Add title
    mainLayout->addWidget(title);

    // Make content widget
    mainLayout->addWidget(inputPrompt);
    mainLayout->addWidget(input);

    // Add buttons
    mainLayout->addLayout(buttonLayout);
    setLayout(mainLayout);

    setSizePolicy(QSizePolicy(QSizePolicy::Fixed, QSizePolicy::Minimum));
    setStyleSheet("PokedexBox {background: #ffff80}");
}

QSize PokedexBox::sizeHint() const{
    return QSize(200, 150);
}

void PokedexBox::validateForm(){
    bool flag{ false };
    int number{ input->text().toInt(&flag) };
    flag = flag && (number < 719 && number > 0);
    if(flag){
        submitButton->setEnabled(false);
        sendRequest(input->text());
    } else {
        std::cout << "Please type a number." << std::endl;
    }
}

void PokedexBox::sendRequest(QString number){
    QUrl url{ QUrl("https://pokeapi.co/api/v2/pokemon/" % number) };
    connect(http, &QNetworkAccessManager::finished, this, &PokedexBox::parseResponse);
    response = http->get(QNetworkRequest(url));
}

void PokedexBox::parseResponse(){
    std::cout << response->error() << std::endl;
    submitButton->setEnabled(true);
    QJsonParseError *error{};
    QJsonObject jsonResponse { QJsonDocument::fromJson(response->readAll(), error).object() };
    QJsonValue name { jsonResponse["name"] };
    std::cout << name.toString().toStdString() << std::endl;
}
