#ifndef LAYERSTOCK_H
#define LAYERSTOCK_H

#include <QWidget>

#include "LayerChartBase.h"
#include <KDChartLegend>
#include <KDChartStockDiagram>
#include <KDChartThreeDBarAttributes>
#include <KDChartBackgroundAttributes>
#include <KDChartCartesianAxis>
#include <KDChartGridAttributes>
#include <KDChartFrameAttributes>
#include <KDChartLineDiagram>
#include "ModelStock.h"

#include <QTimerEvent>

namespace Ui {
class LayerStock;
}


class LayerStock : public LayerChartBase
{
    Q_OBJECT

public:
    explicit LayerStock(QWidget *parent = 0);
    ~LayerStock();

    ModelStock m_cModel;

    //K line
    StockDiagram m_diagram;

    CartesianAxis* m_rightAxis;
    CartesianAxis* m_bottomAxis;

    ThreeDBarAttributes m_threeDBarAttributes;

    void init3D();

private:

    void initUi();

    void initLegend();

    Legend *m_legendTop;

    Legend *m_legendBottom;

    Ui::LayerStock *ui;
};

#endif // LAYERSTOCK_H
