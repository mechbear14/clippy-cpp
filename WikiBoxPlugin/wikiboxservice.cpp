#include "wikiboxservice.h"

WikiBoxService::WikiBoxService(QObject *parent, QObject *backend)
    : QObject(parent)
    , backend{ backend }
{

}
