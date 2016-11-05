#include "telemetrydialog.h"
#include "ui_telemetrydialog.h"

#include <ostream>
#include <istream>
#include <iostream>
#include <math.h>

TelemetryDialog::TelemetryDialog(QWidget * parent) :
    QDialog(parent), ui(new Ui::TelemetryDialog) {

    ui->setupUi(this);

}

TelemetryDialog::~TelemetryDialog() {

    delete ui;

}

void TelemetryDialog::plot(TelemetryData * data, unsigned short count) {

    // Add graph
    ui->telemetry_plot->addGraph();

    // Set pen
    ui->telemetry_plot->graph(0)->setPen(QPen(Qt::blue));

    // Setup second axis
    ui->telemetry_plot->xAxis2->setVisible(true);
    ui->telemetry_plot->xAxis2->setTickLabels(false);
    ui->telemetry_plot->yAxis2->setVisible(true);
    ui->telemetry_plot->yAxis2->setTickLabels(false);

    // Connect two axes
    connect(ui->telemetry_plot->xAxis, SIGNAL(rangeChanged(QCPRange)), ui->telemetry_plot->xAxis2, SLOT(setRange(QCPRange)));
    connect(ui->telemetry_plot->yAxis, SIGNAL(rangeChanged(QCPRange)), ui->telemetry_plot->yAxis2, SLOT(setRange(QCPRange)));

    QVector<double> x(count), y(count);

    // Prepare data
    for (unsigned short index = 0; index < count; index++) {

        // Set x and y
        x[index] = (double) (data[index].time - data[0].time);
        y[index] = (double) data[index].error;

    }

    // Set data
    ui->telemetry_plot->graph(0)->setData(x, y);

    // Rescale axes
    ui->telemetry_plot->graph(0)->rescaleAxes();

    // Set interaction
    ui->telemetry_plot->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom);

}
