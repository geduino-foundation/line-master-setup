#ifndef TELEMETRYDIALOG_H
#define TELEMETRYDIALOG_H

#include <QDialog>

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

    void plot(TelemetryData * data, unsigned short count, Setup & setup);

private:

    Ui::TelemetryDialog * ui;

};

#endif // TELEMETRYDIALOG_H
