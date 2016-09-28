#ifndef MODELSTOCK_H
#define MODELSTOCK_H

#include <QObject>
#include "TableModel.h"
#define NUMS 60

typedef QVector<QVariant> StockData  ;



namespace VALUE_OBJ_STOCK
{
enum
{
    _open=0,
    _max=1,
    _min=2,
    _close=3
};
}


class ModelStock : public TableModel
{
    Q_OBJECT
public:
    explicit ModelStock(QObject *parent = 0);

    void appendData(QString sHeadName, StockData data);

    void reflash(QString sHeadName, StockData data);

    void reflashAll(QStringList listHead, QList<StockData> listData);
signals:

public slots:
};

#endif // MODELSTOCK_H
