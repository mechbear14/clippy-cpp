#ifndef DICTSTARTPAGE_H
#define DICTSTARTPAGE_H

#include "dictfrontend.h"

#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QWidget>

class DictStartPage : public QWidget
{
    Q_OBJECT

public:
    explicit DictStartPage(QWidget *parent = nullptr);
    QSize sizeHint() const override;
    void setFSM(DictFrontend *fsm);

signals:
    void quit();
    void startSearch(QString query);
    void validationError(QString error);

public slots:
    void onError(const QString & error);
    void onNewSearch();
    void onTurnPage(const char & pageNumber);

private slots:
    void onInput(const QString & text);
    void onBack();
    void onSubmit();

private:
    char pageNumber;

    QLabel *title;
    QLabel *prompt;
    QLineEdit *input;
    QLabel *message;
    QPushButton *backButton;
    QPushButton *searchButton;
    QHBoxLayout *buttonLayout;
    QVBoxLayout *mainLayout;

    DictFrontend *fsm;
};

#endif // DICTSTARTPAGE_H
