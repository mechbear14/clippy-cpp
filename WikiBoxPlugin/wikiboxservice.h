#ifndef WIKIBOXSERVICE_H
#define WIKIBOXSERVICE_H

#include "wikiboxbackend.h"

#include <QObject>

class WikiBoxService : public QObject
{
    Q_OBJECT
public:
    explicit WikiBoxService(QObject *parent = nullptr, WikiBoxBackend *backend = nullptr);

signals:

public slots:
private:
    WikiBoxBackend *backend;
};

#endif // WIKIBOXSERVICE_H
