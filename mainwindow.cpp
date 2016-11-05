#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "telemetrydialog.h"

MainWindow::MainWindow(QWidget * parent) :
    QMainWindow(parent), ui(new Ui::MainWindow) {

    // Setup UI
    ui->setupUi(this);

    // Fill setup with zeroes
    memset(& setup, 0, sizeof(setup));

    // Update setup
    update();

    // Update serial ports
    updateSerialPorts();

}

MainWindow::~MainWindow() {

    // Delete UI
    delete ui;

}

void MainWindow::update() {

    // Update widget with model values
    ui->pid_proportional_spin->setValue(setup.pid_proportional);
    ui->pid_integrative_spin->setValue(setup.pid_integrative);
    ui->pid_derivative_spin->setValue(setup.pid_derivative);
    ui->motors_max_speed_spin->setValue(setup.motors_max_speed);
    ui->ir_in_line_threshold_spin->setValue(setup.ir_in_line_threshold);
    ui->ir_noise_threshold_spin->setValue(setup.ir_noise_threshold);
    ui->telemetry_enabled_check->setChecked(setup.telemetry_enabled);

}

void MainWindow::updateSerialPorts() {

    // Log
    log("Updating serial ports");

    // Remove all items
    ui->serial_port_combo->clear();

    // Get serial ports
    std::vector<serial::PortInfo> serialPorts = serial::list_ports();

    for (std::vector<serial::PortInfo>::iterator it = serialPorts.begin(); it != serialPorts.end(); it++) {

        // Get actual serial port
        serial::PortInfo portInfo = * it;

        // Add serial port to combo
        ui->serial_port_combo->addItem(QString::fromStdString(portInfo.port));

    }

    // Log
    log("Done");

}

void MainWindow::connect() {

    // Get serial port
    std::string serialPort = ui->serial_port_combo->currentText().toStdString();

    try {

        if (serialClient.isConnected()) {

            // Log
            log("Disconnecting serial client");

            // Disconnecting first
            serialClient.disconnect();

        }

        // Log
        log("Connecting serial client");

        // Connect
        serialClient.connect(serialPort);

        // Log
        log("Done");

    } catch (serial::SerialException & ex) {

        // Log
        log("Error:");
        log(ex.what());

    } catch (serial::IOException & ex) {

        // Log
        log("Error:");
        log(ex.what());

    } catch (serial::PortNotOpenedException & ex) {

        // Log
        log("Error:");
        log(ex.what());

    }

}

void MainWindow::synch() {

    try {

        // Log
        log("Checking protocol version");

        // Check protocol version
        serialClient.checkProtocolVersion();

        // Log
        log("Retrieving battery voltage");

        // Read battery voltage
        float batteryVoltage;
        serialClient.readBatteryVoltage(& batteryVoltage);

        // Refresh ui
        ui->battery_lcd->display(QString::number(batteryVoltage));

        // Log
        log("Downloading setup");

        // Download setup
        serialClient.downloadSetup(& setup);

        // Update e=setup
        update();

        // Log
        log("Done");

    } catch (std::exception & ex) {

        // Log
        log("Error:");
        log(ex.what());

    }

}

void MainWindow::upload() {

    try {

        // Log
        log("Checking protocol version");

        // Check protocol version
        serialClient.checkProtocolVersion();

        // Log
        log("Uploading setup");

        // Download setup
        serialClient.uploadSetup(& setup);

        // Log
        log("Done");

    } catch (std::exception & ex) {

        // Log
        log("Error:");
        log(ex.what());

    }

}

void MainWindow::save() {

    try {

        // Log
        log("Checking protocol version");

        // Check protocol version
        serialClient.checkProtocolVersion();

        // Log
        log("Saving to EEPROM");

        // Download setup
        serialClient.saveSetupToEEPROM();

        // Log
        log("Done");

    } catch (std::exception & ex) {

        // Log
        log("Error:");
        log(ex.what());

    }

}

void MainWindow::dowloadTelemetry() {

    try {

        // Log
        log("Checking protocol version");

        // Check protocol version
        serialClient.checkProtocolVersion();

        // Log
        log("Downloading telemetry");

        TelemetryData data[TELEMETRY_BUFFER_SIZE];

        // Download telemetry
        serialClient.downloadTelemetry(data);

        // Create telemetry dialog
        TelemetryDialog * telemetryDialog = new TelemetryDialog(this);
        telemetryDialog->show();

        // Plot data
        telemetryDialog->plot(data, TELEMETRY_BUFFER_SIZE);

        // Log
        log("Done");

    } catch (std::exception & ex) {

        // Log
        log("Error:");
        log(ex.what());

    }

}

void MainWindow::loadFile() {

    // Request file name
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open Setup File"), "./", tr("Setup file (*.set)"));

    // Load setup
    QSettings settingsSetup(fileName, QSettings::NativeFormat);
    setup.pid_proportional = settingsSetup.value(PID_PROPORTIONAL_KEY, 0).toInt();
    setup.pid_integrative = settingsSetup.value(PID_INTEGRATIVE_KEY, 0).toInt();
    setup.pid_derivative = settingsSetup.value(PID_DERIVATIVE_KEY, 0).toInt();
    setup.motors_max_speed = settingsSetup.value(MOTORS_MAX_SPEED_KEY, 0).toInt();
    setup.ir_noise_threshold = settingsSetup.value(IR_NOISE_THRESHOLD_KEY, 0).toInt();
    setup.ir_in_line_threshold = settingsSetup.value(IR_IN_LINE_THRESHOLD_KEY, 0).toInt();
    setup.telemetry_enabled = settingsSetup.value(TELEMETRY_ENABLED_KEY, 0).toInt();

    // Update
    update();

    // Log
    log("Setup loaded");

}

void MainWindow::saveFile() {

    // Request file name
    QString fileName = QFileDialog::getSaveFileName(this, tr("Save Setup File"), "./", tr("Setup file (*.set)"));

    // Save setup
    QSettings settingsSetup(fileName, QSettings::NativeFormat);
    settingsSetup.setValue(PID_PROPORTIONAL_KEY, setup.pid_proportional);
    settingsSetup.setValue(PID_INTEGRATIVE_KEY, setup.pid_integrative);
    settingsSetup.setValue(PID_DERIVATIVE_KEY, setup.pid_derivative);
    settingsSetup.setValue(MOTORS_MAX_SPEED_KEY, setup.motors_max_speed);
    settingsSetup.setValue(IR_NOISE_THRESHOLD_KEY, setup.ir_noise_threshold);
    settingsSetup.setValue(IR_IN_LINE_THRESHOLD_KEY, setup.ir_in_line_threshold);
    settingsSetup.setValue(TELEMETRY_ENABLED_KEY, setup.telemetry_enabled);

    // Log
    log("Setup saved");

}

void MainWindow::log(const char * txt) {

    // Append txt
    ui->output_text->append(txt);

}

void MainWindow::on_pid_proportional_spin_valueChanged(int value) {

    // Set value
    setup.pid_proportional = value;

}

void MainWindow::on_pid_integrative_spin_valueChanged(int value) {

    // Set value
    setup.pid_integrative = value;

}

void MainWindow::on_pid_derivative_spin_valueChanged(int value) {

    // Set value
    setup.pid_derivative = value;

}

void MainWindow::on_motors_max_speed_spin_valueChanged(int value) {

    // Set value
    setup.motors_max_speed = value;

}

void MainWindow::on_ir_noise_threshold_spin_valueChanged(int value) {

    // Set value
    setup.ir_noise_threshold = value;

}

void MainWindow::on_ir_in_line_threshold_spin_valueChanged(int value) {

    // Set value
    setup.ir_in_line_threshold = value;

}

void MainWindow::on_telemetry_enabled_check_stateChanged(int value) {

    // Set value
    setup.telemetry_enabled = value;

}

void MainWindow::on_serial_port_refresh_clicked() {

    // Update serial ports
    updateSerialPorts();

}

void MainWindow::on_load_file_button_clicked() {

    // Load file
    loadFile();

}

void MainWindow::on_save_file_button_clicked() {

    // Save file
    saveFile();

}

void MainWindow::on_connect_button_clicked() {

    // Connect
    connect();

}

void MainWindow::on_synch_button_clicked() {

    // Synch
    synch();

}

void MainWindow::on_upload_button_clicked() {

    // Upload
    upload();

}

void MainWindow::on_save_button_clicked() {

    // Save
    save();

}

void MainWindow::on_download_telemetry_button_clicked() {

    // Download telemetry
    dowloadTelemetry();

}
