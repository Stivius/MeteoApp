#include "ChartSource.hpp"

#include <QtCharts/QLineSeries>
#include <QtCharts/QValueAxis>
#include <QtQuick/QQuickView>
#include <QtQuick/QQuickItem>

QT_CHARTS_USE_NAMESPACE

Q_DECLARE_METATYPE(QChartView*)
Q_DECLARE_METATYPE(QAbstractSeries*)
Q_DECLARE_METATYPE(QAbstractAxis*)

ChartSource::ChartSource(QObject* parent) :
    QObject(parent)
{
    qRegisterMetaType<QChartView*>();
    qRegisterMetaType<QAbstractSeries*>();
    qRegisterMetaType<QAbstractAxis*>();
}

void ChartSource::update(QChartView* chartView, const QList<int>& data, int min, int max)
{
    if(!chartView || data.empty())
        return;

    QLineSeries* series = new QLineSeries;
    series->setName("temperature");

    chartView->chart()->removeAllSeries();
    chartView->chart()->addSeries(series);

    auto xAxis = new QValueAxis;
    auto yAxis = new QValueAxis;

    xAxis->setRange(0.0, static_cast<qreal>(data.size()));
    yAxis->setRange(static_cast<qreal>(min), static_cast<qreal>(max));

    chartView->chart()->axes(Qt::Horizontal, series).append(xAxis);
    chartView->chart()->axes(Qt::Vertical, series).append(yAxis);

    for(int i = 0; i < data.size(); ++i)
        series->append({static_cast<qreal>(i), static_cast<qreal>(data[i])});
}
