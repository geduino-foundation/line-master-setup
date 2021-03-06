/*
  telemetrydialog.h
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

#ifndef TELEMETRYDIALOG_H
#define TELEMETRYDIALOG_H

#include <QDialog>

#include "qcustomplot.h"
#include "types.h"
#include "pid.h"

namespace Ui {
    class TelemetryDialog;
}

class TelemetryDialog : public QDialog {

    Q_OBJECT

public:

    explicit TelemetryDialog(QWidget * parent = 0);

    ~TelemetryDialog();

    void plot(TelemetryData * data, unsigned short count, Setup setup);

private slots:

    void on_primary_axis_range_changed(QCPRange newRange, QCPRange oldRange);

private:

    Ui::TelemetryDialog * ui;

};

#endif // TELEMETRYDIALOG_H
