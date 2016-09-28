#ifndef LAYERCHARTBASE_H
#define LAYERCHARTBASE_H

#include <QWidget>
#include <KDChartChart>
#include <KDChartAbstractCoordinatePlane>
#include <KDChartBackgroundAttributes>
#include <KDChartCartesianAxis>

using namespace KDChart;

class LayerChartBase : public Chart
{
    Q_OBJECT
public:
    explicit LayerChartBase(QWidget *parent = 0);

    void setDiagram( AbstractDiagram* diagram, AbstractDiagram* oldDiagram = 0);

signals:

public slots:
};

#endif // LAYERCHARTBASE_H
