#ifndef WIKIBOXBACKEND_H
#define WIKIBOXBACKEND_H

#include <QObject>

class WikiBoxBackend : public QObject
{
    Q_OBJECT
public:
    explicit WikiBoxBackend(QObject *parent = nullptr);

signals:

public slots:
};

#endif // WIKIBOXBACKEND_H
