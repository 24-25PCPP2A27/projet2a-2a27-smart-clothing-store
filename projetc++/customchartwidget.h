#ifndef CUSTOMCHARTWIDGET_H
#define CUSTOMCHARTWIDGET_H

#include <QWidget>
#include <QMap>
#include <QString>

class CustomChartWidget : public QWidget {
    Q_OBJECT

public:
    explicit CustomChartWidget(QWidget *parent = nullptr);
    void setData(const QMap<QString, int> &data);  // To pass data for the chart

protected:
    void paintEvent(QPaintEvent *event) override; // Override paintEvent to draw the chart

private:
    QMap<QString, int> chartData;  // Data for the chart
};

#endif // CUSTOMCHARTWIDGET_H
