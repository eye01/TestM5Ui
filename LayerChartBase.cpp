#include "LayerChartBase.h"

LayerChartBase::LayerChartBase(QWidget *parent) : Chart(parent)
{


}

void LayerChartBase::setDiagram(AbstractDiagram *diagram, AbstractDiagram *oldDiagram)
{

         this->coordinatePlane()->replaceDiagram(diagram,oldDiagram);

}
