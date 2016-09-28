#include "ModelStock.h"
#include <QDebug>
ModelStock::ModelStock(QObject *parent) : TableModel(parent)
{

    beginResetModel();

    QVector<QVariant> list;

    list.append(double(40));
    list.append(double(41));
    list.append(double(42));
    list.append(double(43));

    for(int i=0;i<NUMS;i++)
    {

    m_verticalHeaderData.append( " " );
    m_rows.append(list);
    }


    endResetModel();




}

void ModelStock::appendData(QString sHeadName, StockData data)
{
    beginResetModel();

    m_verticalHeaderData.append( sHeadName );
    m_verticalHeaderData.pop_front();
    m_rows.append(data);
    m_rows.pop_front();
     qDebug()<<"append OHLC : "<<data;
    endResetModel();
}

void ModelStock::reflash(QString sHeadName, StockData data)
{
    beginResetModel();
    if(m_rows.last().at(VALUE_OBJ_STOCK::_open)>0)
        data[VALUE_OBJ_STOCK::_open]=m_rows.last().at(VALUE_OBJ_STOCK::_open);
    m_verticalHeaderData.last()= sHeadName ;
    m_rows.last()= data;
    qDebug()<<"Re OHLC : "<<data;
    endResetModel();
}

void ModelStock::reflashAll(QStringList listHead, QList<StockData> listData)
{
    beginResetModel();





    endResetModel();
}
