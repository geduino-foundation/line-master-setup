#ifndef TELEMETRYDIALOG_H
#define TELEMETRYDIALOG_H

#include <QDialog>

#include "types.h"

namespace Ui {
    class TelemetryDialog;
}

class TelemetryDialog : public QDialog {

    Q_OBJECT

public:

    explicit TelemetryDialog(QWidget * parent = 0);

    ~TelemetryDialog();

    void plot(TelemetryData * data, unsigned short count);

private:

    Ui::TelemetryDialog * ui;

};

#endif // TELEMETRYDIALOG_H
