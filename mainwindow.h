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
#define MOTORS_MAX_SPEED_KEY                                    "motors.max.speed"
#define IR_NOISE_THRESHOLD_KEY                                  "ir.noise.threshold"
#define IR_IN_LINE_THRESHOLD_KEY                                "ir.in.line.threshold"

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

    void on_serial_port_refresh_clicked();

    void on_load_file_button_clicked();

    void on_save_file_button_clicked();

    void on_synch_button_clicked();

    void on_connect_button_clicked();

    void on_upload_button_clicked();

    void on_save_button_clicked();

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

    void loadFile();

    void saveFile();

    void log(const char * txt);

};

#endif // MAINWINDOW_H