#ifndef DICTDATABASE_H
#define DICTDATABASE_H

#include <QObject>

class DictDatabase : public QObject
{
    Q_OBJECT
public:
    explicit DictDatabase(QObject *parent = nullptr);

signals:
    void onHistory();

public slots:
    void onRequestHistory();
};

#endif // DICTDATABASE_H
