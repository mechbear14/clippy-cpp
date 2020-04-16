#ifndef WIKIBOX_H
#define WIKIBOX_H

#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QBoxLayout>
#include <QWidget>
#include <QNetworkAccessManager>
#include <QNetworkReply>

class WikiBox;
class WikiStartPage;
class WikiSearchingPage;
class WikiResultPage;

class WikiBox : public QWidget
{
    Q_OBJECT
public:
    explicit WikiBox(QWidget *parent = nullptr);
    QSize sizeHint() const override;

signals:

public slots:
    void tryCallParent();
    void onSearchStart();
    void onSearchCancel();
    void onSearchComplete();
    void onRestart();
    void onExplore();

private:
    QVBoxLayout *mainLayout;
    WikiStartPage *startPage;
    WikiSearchingPage *searchingPage;
    WikiResultPage *resultPage;
    QWidget * currentPage;

    QString queryText;
    QUrl urlToOpen;
    QNetworkAccessManager *http;
    QNetworkReply *response;

    void toPage(QWidget * page);
};

class WikiStartPage : public QWidget
{
    Q_OBJECT
public:
    explicit WikiStartPage(QWidget *parent = nullptr);
    QString getQueryText();
    void setMessage(QString message);

signals:

public slots:

private:
    QLabel *title;
    QLabel *message;
    QLineEdit *query;
    QPushButton *searchButton;
    QPushButton *backButton;
    QVBoxLayout *mainLayout;
    QHBoxLayout *buttonLayout;
};

class WikiSearchingPage : public QWidget
{
    Q_OBJECT
public:
    explicit WikiSearchingPage(QWidget *parent = nullptr);

signals:

public slots:

private:
    QLabel *title;
    QPushButton *cancelButton;
    QVBoxLayout *mainLayout;
};

class WikiResultPage : public QWidget
{
    Q_OBJECT
public:
    explicit WikiResultPage(QWidget *parent = nullptr);
    void setContent(QString title, QString content);

signals:

public slots:

private:
    QString title;
    QString content;
    QLabel *titleBox;
    QLabel *contentBox;
    QPushButton *exploreButton;
    QPushButton *backButton;
    QHBoxLayout *buttonLayout;
    QVBoxLayout *mainLayout;
};

#endif // WIKIBOX_H
