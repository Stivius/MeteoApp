#pragma once

#include <QtCore/QObject>
#include <QtCharts/QChartView>

QT_CHARTS_USE_NAMESPACE

class ChartSource : public QObject
{
    Q_OBJECT

public:
    explicit ChartSource(QObject* parent = nullptr);

public slots:
    void update(QChartView* chartView, const QList<int>& data, int min, int max);

};
