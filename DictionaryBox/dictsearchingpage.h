#ifndef DICTSEARCHINGPAGE_H
#define DICTSEARCHINGPAGE_H

#include "dictfrontend.h"

#include <QLabel>
#include <QPushButton>
#include <QVBoxLayout>
#include <QWidget>

class DictSearchingPage : public QWidget
{
    Q_OBJECT
public:
    explicit DictSearchingPage(QWidget *parent = nullptr);
    QSize sizeHint() const override;
    void setFSM(DictFrontend *fsm);

signals:
    void cancelSearch();

public slots:
    void onTurnPage(const char & pageNumber);

private slots:
    void onCancel();

private:
    char pageNumber;

    QLabel *text;
    QPushButton *cancelButton;
    QVBoxLayout *mainLayout;

    DictFrontend *fsm;
};

#endif // DICTSEARCHINGPAGE_H
