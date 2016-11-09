/*
  mainwindow.h
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

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFileDialog>
#include <QSettings>
#include <serial/serial.h>

#include "serialclient.h"

#define PID_PROPORTIONAL_KEY                                    "pid.proportional"
#define PID_INTEGRATIVE_KEY                                     "pid.integrative"
#define PID_DERIVATIVE_KEY                                      "pid.derivative"
#define PID_MAX_PROPORTIONAL_KEY                                "pid.max.proportional"
#define PID_MAX_INTEGRATIVE_KEY                                 "pid.max.integrative"
#define PID_MAX_DERIVATIVE_KEY                                  "pid.max.derivative"
#define PID_MAX_CORRECTION_KEY                                  "pid.max.correction"
#define MOTORS_MAX_SPEED_KEY                                    "motors.max.speed"
#define IR_NOISE_THRESHOLD_KEY                                  "ir.noise.threshold"
#define IR_IN_LINE_THRESHOLD_KEY                                "ir.in.line.threshold"
#define TELEMETRY_ENABLED_KEY                                   "telemetry.enabled"

namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow {

    Q_OBJECT

public:

    explicit MainWindow(QWidget * parent = 0);

    ~MainWindow();

private slots:

    void on_pid_proportional_spin_valueChanged(int value);

    void on_pid_integrative_spin_valueChanged(int value);

    void on_pid_derivative_spin_valueChanged(int value);

    void on_motors_max_speed_spin_valueChanged(int value);

    void on_ir_noise_threshold_spin_valueChanged(int value);

    void on_ir_in_line_threshold_spin_valueChanged(int value);

    void on_telemetry_enabled_check_stateChanged(int value);

    void on_serial_port_refresh_clicked();

    void on_load_file_button_clicked();

    void on_save_file_button_clicked();

    void on_synch_button_clicked();

    void on_connect_button_clicked();

    void on_upload_button_clicked();

    void on_save_button_clicked();

    void on_download_telemetry_button_clicked();

    void on_pid_max_proportinal_spin_valueChanged(int value);

    void on_pid_max_integrative_spin_valueChanged(int value);

    void on_pid_max_derivative_spin_valueChanged(int value);

    void on_pid_max_correction_spin_valueChanged(int value);

private:

    Ui::MainWindow * ui;

    Setup setup;

    SerialClient serialClient;

    void update();

    void updateSerialPorts();

    void connect();

    void synch();

    void upload();

    void save();

    void dowloadTelemetry();

    void loadFile();

    void saveFile();

    void log(const char * txt);

};

#endif // MAINWINDOW_H
