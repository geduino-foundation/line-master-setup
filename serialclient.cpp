#include "serialclient.h"

#include <ostream>
#include <istream>
#include <iostream>
#include <math.h>

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

    // Send command
    writeChar(GET_PROTOCOL_VERSION);

    // Read response
    unsigned char protocolVersion;
    readChar(& protocolVersion);

    if (protocolVersion != PROTOCOL_VERSION) {

        // Throw exception
        throw ProtocolVersionException();

    }

}

void SerialClient::readBatteryVoltage(float * batteryVoltage) {

    // Send command
    writeChar(GET_BATTERY_VOLTAGE);

    // Read response
    unsigned short response;
    readShort(& response);

    // Get battery voltage
    * batteryVoltage = (float) response / 1000;

}

void SerialClient::saveSetupToEEPROM() {

    // Send command
    writeChar(SAVE_TO_EEPROM);

}

void SerialClient::uploadSetup(Setup * setup) {

    // Send command
    writeChar(UPLOAD);

    // Read setup
    writeShort(setup->pid_proportional);
    writeShort(setup->pid_integrative);
    writeShort(setup->pid_derivative);
    writeShort(setup->motors_max_speed);
    writeShort(setup->ir_in_line_threshold);
    writeShort(setup->ir_noise_threshold);
    writeShort(setup->telemetry_enabled);

}

void SerialClient::downloadSetup(Setup * setup) {

    // Send command
    writeChar(DOWNLOAD);

    // Read setup
    readShort(& setup->pid_proportional);
    readShort(& setup->pid_integrative);
    readShort(& setup->pid_derivative);
    readShort(& setup->motors_max_speed);
    readShort(& setup->ir_in_line_threshold);
    readShort(& setup->ir_noise_threshold);
    readShort(& setup->telemetry_enabled);

}

void SerialClient::downloadTelemetry(TelemetryData * data) {

    // Send command
    writeChar(DOWNLOAD_TELEMETRY);

    for (unsigned int index = 0; index < TELEMETRY_BUFFER_SIZE; index++) {

        // Read data
        readInt(& data[index].time);
        readShort(& data[index].error);

    }

}

void SerialClient::readChar(unsigned char * data) {

    // Wait for data available
    bool available = serial.waitReadable();

    if (available) {

        // Read data
        size_t count = serial.read(data, 1);

        if (count != 1) {

            // Throw exception
            throw ReadUnexpectedByteCount();

        }

    } else {

        // Throw exception
        throw SerialTimeout();

    }

}

void SerialClient::readShort(unsigned short * data) {

    // Wait for data available
    bool available = serial.waitReadable();

    if (available) {

        uint8_t buffer[2];

        // Read data
        size_t count = serial.read(buffer, 2);

        if (count != 2) {

            // Throw exception
            throw ReadUnexpectedByteCount();

        } else {

            // Copy buffer into data
            * data = buffer[0];
            * data <<= 8;
            * data += buffer[1];

        }

    } else {

        // Throw exception
        throw SerialTimeout();

    }

}

void SerialClient::readShort(short * data) {

    // Wait for data available
    bool available = serial.waitReadable();

    if (available) {

        uint8_t buffer[2];

        // Read data
        size_t count = serial.read(buffer, 2);

        if (count != 2) {

            // Throw exception
            throw ReadUnexpectedByteCount();

        } else {

            // Copy buffer into data
            * data = buffer[0];
            * data <<= 8;
            * data += buffer[1];

        }

    } else {

        // Throw exception
        throw SerialTimeout();

    }

}

void SerialClient::readInt(unsigned int * data) {

    // Wait for data available
    bool available = serial.waitReadable();

    if (available) {

        uint8_t buffer[4];

        // Read data
        size_t count = serial.read(buffer, 4);

        if (count != 4) {

            // Throw exception
            throw ReadUnexpectedByteCount();

        } else {

            // Copy buffer into data
            * data = buffer[0];
            * data <<= 8;
            * data += buffer[1];
            * data <<= 8;
            * data += buffer[2];
            * data <<= 8;
            * data += buffer[3];

        }

    } else {

        // Throw exception
        throw SerialTimeout();

    }

}

void SerialClient::writeChar(const unsigned char data) {

    // Write data
    size_t count = serial.write(& data, 1);

    if (count != 1) {

        // Throw exception
        throw WriteUnexpectedByteCount();

    }

}

void SerialClient::writeShort(const unsigned short data) {

    uint8_t buffer[2];

    // Copy data into buffer
    buffer[0] = data >> 8;
    buffer[1] = data;

    // Write data
    size_t count = serial.write(buffer, 2);

    if (count != 2) {

        // Throw exception
        throw WriteUnexpectedByteCount();

    }

}
