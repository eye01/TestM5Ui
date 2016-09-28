#include "LayerStock.h"
#include "ui_LayerStock.h"





LayerStock::LayerStock(QWidget *parent) :
    LayerChartBase(parent) , m_diagram( this ),
    ui(new Ui::LayerStock)
{
    ui->setupUi(this);

    initUi();

    initLegend();

    setDiagram(&m_diagram);

    m_diagram.setType( StockDiagram::Candlestick );

    m_diagram.setModel(&m_cModel );

    init3D();


}

LayerStock::~LayerStock()
{
    delete ui;
}

void LayerStock::init3D()
{
    //3D
    m_threeDBarAttributes = m_diagram.threeDBarAttributes();
    m_threeDBarAttributes.setDepth( 10.0 );
    //  m_threeDBarAttributes.setAngle(3);
    m_threeDBarAttributes.setUseShadowColors( true );

    m_diagram.setThreeDBarAttributes( m_threeDBarAttributes );
    m_threeDBarAttributes.setEnabled(false);
}

void LayerStock::initUi()
{
    //    KDChart::Legend *legend= new KDChart::Legend(&m_diagram, this );
    //    addLegend( legend );

    // Abscissa
    m_rightAxis = new CartesianAxis( &m_diagram );
    // Ordinate
    m_bottomAxis = new CartesianAxis( &m_diagram );

    m_rightAxis->setPosition( CartesianAxis::Right );
    RulerAttributes ruler = m_rightAxis->rulerAttributes();
    ruler.setTickMarkPen( QColor(Qt::black) ); //設定刻度顏色 黑色
    ruler.setShowRulerLine(true);
    m_rightAxis->setRulerAttributes( ruler );
    TextAttributes attributesR;
    attributesR=m_rightAxis->textAttributes();
    attributesR.setFontSize( Measure( 10.0, KDChartEnums::MeasureCalculationModeAbsolute ));
    m_rightAxis->setTextAttributes(attributesR);

    TextAttributes attributes = m_bottomAxis->textAttributes();

    attributes.setRotation( 90 );
    attributes.setFontSize( Measure( 10.0, KDChartEnums::MeasureCalculationModeAbsolute ) );
    m_bottomAxis->setTextAttributes( attributes );
    m_bottomAxis->setPosition( CartesianAxis::Bottom );
    m_diagram.addAxis( m_rightAxis );
    m_diagram.addAxis( m_bottomAxis );

    m_diagram.stockBarAttributes().setCandlestickWidth(0.7);

    //K線圖:背景設定
    BackgroundAttributes cLineBg = backgroundAttributes();
    //cLineBg.setBrush( Qt::white );
    cLineBg.setVisible( true );
    setBackgroundAttributes( cLineBg );

    //K線圖:網格設定
    GridAttributes cLineGrid = coordinatePlane()->globalGridAttributes();
    cLineGrid.setGridVisible( true );
    coordinatePlane()->setGlobalGridAttributes( cLineGrid );

    //K線圖:Bar設定
    m_diagram.setUpTrendCandlestickBrush( Qt::red );
    m_diagram.setDownTrendCandlestickBrush( Qt::darkGreen );
    m_diagram.setUpTrendCandlestickPen( QColor(Qt::black) );
    m_diagram.setDownTrendCandlestickPen( QColor(Qt::black) );

    //K線圖:刻度顏色設定

    RulerAttributes cLineR = m_rightAxis->rulerAttributes();
    cLineR.setTickMarkPen( QColor(Qt::black));
    m_rightAxis->setRulerAttributes( cLineR );
    RulerAttributes cLineB = m_bottomAxis->rulerAttributes();
    cLineB.setTickMarkPen( QColor(Qt::black) );
    m_bottomAxis->setRulerAttributes( cLineB );

    //    //K線圖:刻度文字顏色設定
    //    TextAttributes KLine_Text_R = KLineWidget->rightAxis->textAttributes();
    //    KLine_Text_R.setPen( textColor );
    //    KLineWidget->rightAxis->setTextAttributes( KLine_Text_R );
    //    TextAttributes KLine_Text_B = KLineWidget->bottomAxis->textAttributes();
    //    KLine_Text_B.setPen( textColor );
    //    KLineWidget->bottomAxis->setTextAttributes( KLine_Text_B );

    //    //K線圖:上標籤文字顏色設定
    //    KLineWidget->LegendTextPen.setColor( textColor );

    //    //K線圖:下標籤文字顏色設定
    //    TextAttributes Text_legend_B = KLineWidget->legend_B->textAttributes();
    //    Text_legend_B.setPen( textColor );
    //    KLineWidget->legend_B->setTextAttributes( Text_legend_B );



//    LineDiagram *m= new LineDiagram;
//    m->setCenterDataPoints( true );
//    m->setPen(QColor( Qt::red));
//    m->setModel(m_cModel);
//    this->coordinatePlane()->addDiagram( m);

}

void LayerStock::initLegend()
{
    m_legendTop = new Legend(& m_diagram, this );
    FrameAttributes frame;
    frame.setVisible( false );
    m_legendTop->setFrameAttributes( frame );

    MarkerAttributes marker( m_legendTop->markerAttributes(0) );
    marker.setMarkerStyle( MarkerAttributes::NoMarker );
    m_legendTop->setMarkerAttributes( 0, marker );

    RelativePosition relativePosition_T;
    relativePosition_T.setReferenceArea( this->coordinatePlane() );
    relativePosition_T.setReferencePosition( Position::North );
    relativePosition_T.setAlignment( Qt::AlignLeft );
    m_legendTop->setFloatingPosition( relativePosition_T );

    m_legendTop->setTitleText("");
    m_legendTop->setText( 0, "" );
    this->addLegend( m_legendTop );

    m_legendBottom = new Legend( &m_diagram, this );
    m_legendBottom->setFrameAttributes( frame );
    m_legendBottom->setMarkerAttributes( 0, marker );

    RelativePosition relativePosition_B;
    relativePosition_B.setReferenceArea( this->coordinatePlane() );
    relativePosition_B.setReferencePosition( Position::SouthWest );
    relativePosition_B.setAlignment( Qt::AlignLeft );
    relativePosition_B.setVerticalPadding( Measure(-28.0, KDChartEnums::MeasureCalculationModeAbsolute) );
    m_legendBottom->setFloatingPosition( relativePosition_B );

    m_legendBottom->setTitleText(" ");
    m_legendBottom->setText( 0, tr(" ") );
    this->addLegend(m_legendBottom);
}


