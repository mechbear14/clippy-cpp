#ifndef DICTFRONTEND_H
#define DICTFRONTEND_H

#include <QObject>

class DictFrontend : public QObject
{
    Q_OBJECT
public:
    explicit DictFrontend(QObject *parent = nullptr);

signals:

public slots:
};

#endif // DICTFRONTEND_H
