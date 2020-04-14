#ifndef WIKIBOX_H
#define WIKIBOX_H

#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QBoxLayout>
#include <QWidget>

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

private:
    QVBoxLayout *mainLayout;
    WikiStartPage *startPage;
    WikiSearchingPage *searchingPage;
    WikiResultPage *resultPage;

    QWidget * currentPage;

    void toPage(QWidget * page);
};

class WikiStartPage : public QWidget
{
    Q_OBJECT
public:
    explicit WikiStartPage(QWidget *parent = nullptr);

signals:

public slots:

private:
    QLabel *title;
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
    void setContent(QString resultContent);

signals:

public slots:

private:
    QString content;
    QLabel *contentBox;
    QPushButton *exploreButton;
    QPushButton *backButton;
    QHBoxLayout *buttonLayout;
    QVBoxLayout *mainLayout;
};

#endif // WIKIBOX_H
