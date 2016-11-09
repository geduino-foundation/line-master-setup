/*
  telemetrydialog.cpp
  Copyright (C) 2016 Alessandro Francescon

  This program is free software: you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation, either version 3 of the License.

  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include "telemetrydialog.h"
#include "ui_telemetrydialog.h"

TelemetryDialog::TelemetryDialog(QWidget * parent) :
    QDialog(parent), ui(new Ui::TelemetryDialog) {

    ui->setupUi(this);

}

TelemetryDialog::~TelemetryDialog() {

    delete ui;

}

void TelemetryDialog::plot(TelemetryData * data, unsigned short count, Setup setup) {

    // Add graph for error
    ui->telemetry_plot->addGraph();
    ui->telemetry_plot->graph(0)->setPen(QPen(Qt::red));
    ui->telemetry_plot->graph(0)->setName("Error");

    // Add graph for correction
    ui->telemetry_plot->addGraph(ui->telemetry_plot->xAxis, ui->telemetry_plot->yAxis2);
    ui->telemetry_plot->graph(1)->setPen(QPen(Qt::blue));
    ui->telemetry_plot->graph(1)->setName("Correction");

    // Setup second axis
    ui->telemetry_plot->xAxis2->setVisible(true);
    ui->telemetry_plot->xAxis2->setTickLabels(false);
    ui->telemetry_plot->yAxis2->setVisible(true);
    ui->telemetry_plot->yAxis2->setTickLabels(true);

    // Connect x axes
    connect(ui->telemetry_plot->xAxis, SIGNAL(rangeChanged(QCPRange)), ui->telemetry_plot->xAxis2, SLOT(setRange(QCPRange)));
    connect(ui->telemetry_plot->yAxis, SIGNAL(rangeChanged(QCPRange, QCPRange)), this, SLOT(on_primary_axis_range_changed(QCPRange, QCPRange)));

    // Show legend
    ui->telemetry_plot->legend->setVisible(true);

    QVector<double> time(count), error(count), correction(count);

    // Create and setup PID for simulation
    PID pid;
    pid.setup(setup);

    // Prepare data
    for (unsigned short index = 0; index < count; index++) {

        // Simulate correction
        short simulated_correction;
        pid.update(data[index].error, & simulated_correction);

        // Set time, error and correction
        time[index] = (double) (data[index].time - data[0].time);
        error[index] = (double) data[index].error;
        correction[index] = (double) simulated_correction;

    }

    // Set data
    ui->telemetry_plot->graph(0)->setData(time, error);
    ui->telemetry_plot->graph(1)->setData(time, correction);

    // Rescale axes
    ui->telemetry_plot->graph(0)->rescaleAxes();
    ui->telemetry_plot->graph(1)->rescaleAxes(true);

    // Set interaction
    ui->telemetry_plot->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom);

}

void TelemetryDialog::on_primary_axis_range_changed(QCPRange newRange, QCPRange oldRange) {

    // Get y axis 2 range
    QCPRange range = ui->telemetry_plot->yAxis2->range();

    double upper, lower;

    // Calculate new upper and lower for second y axis
    upper = range.upper / oldRange.upper * newRange.upper;
    lower = range.lower / oldRange.lower * newRange.lower;

    // Set new range in y axis
    QCPRange newRange(upper, lower);
    ui->telemetry_plot->yAxis2->setRange(newRange);

}
