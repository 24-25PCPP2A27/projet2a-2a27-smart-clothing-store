#include "customchartwidget.h"
#include <QPainter>
#include <QPaintEvent>
#include <QFontMetrics>

CustomChartWidget::CustomChartWidget(QWidget *parent)
    : QWidget(parent) {}

void CustomChartWidget::setData(const QMap<QString, int> &data) {
    chartData = data;  // Store the data
    update();          // Trigger a repaint
}

void CustomChartWidget::paintEvent(QPaintEvent *event) {
    Q_UNUSED(event);

    if (chartData.isEmpty())
        return;

    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

    // Define margins
    int margin = 20;
    int chartWidth = width() - 2 * margin;
    int chartHeight = height() - 2 * margin;

    // Calculate bar width and scaling factor
    int barWidth = chartWidth / chartData.size();
    int maxCount = 0;
    for (int value : chartData) {
        maxCount = qMax(maxCount, value);
    }
    double scaleFactor = (maxCount > 0) ? (double)chartHeight / maxCount : 1.0;

    // Draw bars and labels
    int x = margin;
    painter.setBrush(Qt::blue);
    painter.setPen(Qt::black);

    for (auto it = chartData.begin(); it != chartData.end(); ++it) {
        int barHeight = static_cast<int>(it.value() * scaleFactor);
        QRect barRect(x, chartHeight + margin - barHeight, barWidth - 10, barHeight);
        painter.drawRect(barRect);

        // Draw label
        painter.drawText(x, chartHeight + margin + 15, barWidth, 20, Qt::AlignCenter, it.key());

        x += barWidth;
    }

    // Draw axes
    painter.drawLine(margin, chartHeight + margin, width() - margin, chartHeight + margin); // X-axis
    painter.drawLine(margin, margin, margin, chartHeight + margin); // Y-axis
}
