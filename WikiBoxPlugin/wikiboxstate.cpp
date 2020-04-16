#include "wikiboxstate.h"

WikiBoxState::WikiBoxState(QObject *parent, QObject *frontend, QObject *backend)
    : QObject(parent)
    , frontend{ frontend }
    , backend{ backend }
{

}
