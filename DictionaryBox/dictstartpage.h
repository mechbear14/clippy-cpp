#ifndef DICTSTARTPAGE_H
#define DICTSTARTPAGE_H

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
    void setFrontend(QObject * frontend);

signals:

public slots:

private:
    QLabel *title;
    QLabel *prompt;
    QLineEdit *input;
    QLabel *message;
    QPushButton *backButton;
    QPushButton *searchButton;
    QHBoxLayout *buttonLayout;
    QVBoxLayout *mainLayout;
    QObject *frontend;
};

#endif // DICTSTARTPAGE_H
