#ifndef POKEDEXBOX_H
#define POKEDEXBOX_H

#include <QLineEdit>
#include <QPushButton>
#include <QWidget>

#include <QtNetwork>

class PokedexBox : public QWidget
{
    Q_OBJECT
public:
    explicit PokedexBox(QWidget *parent = nullptr);
    QSize sizeHint() const override;

signals:

private slots:
    void validateForm();
    void parseResponse();

private:
    QLineEdit *input;
    QPushButton *submitButton;
    QNetworkAccessManager *http;
    QNetworkReply *response;
    void sendRequest(QString number);
};

#endif // POKEDEXBOX_H
