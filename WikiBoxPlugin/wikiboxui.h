#ifndef WIKIBOXUI_H
#define WIKIBOXUI_H

#include "wikiboxfrontend.h"

#include <QBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QWidget>

class StartPage : public QWidget
{
    Q_OBJECT
public:
    explicit StartPage(QWidget *parent = nullptr, WikiBoxFrontend *frontend = nullptr);
    QSize sizeHint() const override;

signals:

private slots:

private:
    WikiBoxFrontend * frontend;
    QLabel *title;
    QLabel *message;
    QLineEdit *query;
    QPushButton *searchButton;
    QPushButton *backButton;
    QVBoxLayout *mainLayout;
    QHBoxLayout *buttonLayout;
};

class SearchingPage : public QWidget
{
    Q_OBJECT
public:
    explicit SearchingPage(QWidget *parent = nullptr, WikiBoxFrontend *frontend = nullptr);
    QSize sizeHint() const override;

signals:

private slots:

private:
    WikiBoxFrontend * frontend;
    QLabel *title;
    QPushButton *cancelButton;
    QVBoxLayout *mainLayout;
};

class ResultPage : public QWidget
{
    Q_OBJECT
public:
    explicit ResultPage(QWidget *parent = nullptr, WikiBoxFrontend *frontend = nullptr);
    QSize sizeHint() const override;

signals:

private slots:

private:
    WikiBoxFrontend * frontend;
    QLabel *title;
    QLabel *content;
    QPushButton *exploreButton;
    QPushButton *backButton;
    QHBoxLayout *buttonLayout;
    QVBoxLayout *mainLayout;
};

#endif // WIKIBOXUI_H
