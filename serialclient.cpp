#include "serialclient.h"

void SerialClient::connect(const std::string port) {

    if (!serial.isOpen()) {

        // Set port setting
        serial.setPort(port);
        serial.setBaudrate(BAUDRATE);
        serial.setTimeout(std::numeric_limits<uint32_t>::max(), TIMEOUT, 0, TIMEOUT, 0);

        // Open port
        serial.open();

    }

}

void SerialClient::disconnect() {

    if (serial.isOpen()) {

        // Close port
        serial.close();

    }

}

bool SerialClient::isConnected() {
    return serial.isOpen();
}

void SerialClient::checkProtocolVersion() {

    unsigned char protocolVersion;

    // Write cmd
    writeCmd(GET_PROTOCOL_VERSION, NULL, 0, & protocolVersion, 1);

    if (protocolVersion != PROTOCOL_VERSION) {

        // Throw exception
        throw ProtocolVersionException();

    }

}

void SerialClient::readBatteryVoltage(float * batteryVoltage) {

    unsigned short response;

    // Write cmd
    writeCmd(GET_BATTERY_VOLTAGE, NULL, 0, & response, 2);

    // Get battery voltage
    * batteryVoltage = (float) response / 1000;

}

void SerialClient::saveSetupToEEPROM() {

    // Write cmd
    writeCmd(SAVE_TO_EEPROM, NULL, 0, NULL, 0);

}

void SerialClient::uploadSetup(Setup * setup) {

    // Write cmd
    writeCmd(UPLOAD, setup, sizeof(Setup), NULL, 0);

}

void SerialClient::downloadSetup(Setup * setup) {

    // Write cmd
    writeCmd(DOWNLOAD, NULL, 0, setup, sizeof(Setup));

}

void SerialClient::downloadTelemetry(TelemetryData * data) {

    // Write cmd
    writeCmd(DOWNLOAD_TELEMETRY, NULL, 0, data, sizeof(TelemetryData) * TELEMETRY_BUFFER_SIZE);

}

void SerialClient::writeCmd(const unsigned char cmd, const void * request, size_t requestSize, void * response, size_t responseSize) {

    // Write command
    writeData(& cmd, 1);

    if (requestSize > 0) {

        // Write request
        writeData(request, requestSize);

    }

    if (responseSize > 0) {

        // Read response
        readData(response, responseSize);

    }

    // Check EOS
    checkEOS();

}

void SerialClient::writeData(const void * data, size_t size) {

    // Allocate a byte array for buffer
    uint8_t buffer[size];

    // Copy data into buffer
    std::memcpy(buffer, data, size);

    // Write data
    size_t count = serial.write(buffer, size);

    if (count != size) {

        // Throw exception
        throw WriteUnexpectedByteCount();

    }

}

void SerialClient::readData(void * data, size_t size) {

    // Wait for data available
    bool available = serial.waitReadable();

    if (available) {

        // Allocate a byte array for buffer
        uint8_t buffer[size];

        // Read data
        size_t count = serial.read(buffer, size);

        if (count == size) {

            // Copy buffer into data
            std::memcpy(data, buffer, size);

        } else {

            // Throw exception
            throw ReadUnexpectedByteCount();

        }

    } else {

        // Throw exception
        throw SerialTimeout();

    }

}

void SerialClient::checkEOS() {

    if (serial.available() > 0) {

        // Throw exception
        throw ReadUnexpectedByteCount();

    }

}
