#ifndef DICTRESULTPAGE_H
#define DICTRESULTPAGE_H

#include "dictfrontend.h"

#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QWidget>
#include <QUrl>

class DictResultPage : public QWidget
{
    Q_OBJECT
public:    
    explicit DictResultPage(QWidget *parent = nullptr);
    QSize sizeHint() const override;
    void setFSM(DictFrontend *fsm);

signals:
    void endSearch();

public slots:
    void onTurnPage(const char & pageNumber);
    void onResult(const QJsonObject & result,
                  const bool & isExpected,
                  const QUrl & nextURL);
private slots:
    void onExplore();


private:
    char pageNumber;
    QUrl nextURL;

    QLabel *title;
    QLabel *content;
    QPushButton *backButton;
    QPushButton *detailButton;
    QHBoxLayout *buttonLayout;
    QVBoxLayout *mainLayout;

    DictFrontend *fsm;
};

#endif // DICTRESULTPAGE_H
