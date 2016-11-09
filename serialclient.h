/*
  serialclient.h
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

#ifndef SERIALCLIENT_H
#define SERIALCLIENT_H

#include <serial/serial.h>
#include <stdlib.h>

#include "types.h"

#define PROTOCOL_VERSION        0x00

#define GET_PROTOCOL_VERSION    0x00
#define GET_BATTERY_VOLTAGE     0x01
#define LOAD_FROM_EEPROM        0x02
#define SAVE_TO_EEPROM          0x03
#define DOWNLOAD                0x04
#define UPLOAD                  0x05
#define DOWNLOAD_TELEMETRY      0x06

#define BAUDRATE                9600
#define TIMEOUT                 2500

#define TELEMETRY_BUFFER_SIZE   200

class SerialClient {

public:

    SerialClient() {
    }

    ~SerialClient() {

        if (serial.isOpen()) {

            // Close port
            serial.close();

        }

    }

    void connect(const std::string port);

    void disconnect();

    bool isConnected();

    void checkProtocolVersion();

    void readBatteryVoltage(float * batteryVoltage);

    void saveSetupToEEPROM();

    void uploadSetup(Setup * setup);

    void downloadSetup(Setup * setup);

    void downloadTelemetry(TelemetryData * data);

private:

    serial::Serial serial;

    void writeCmd(const unsigned char cmd, const void * request, size_t requestSize, void * response, size_t responseSize);

    void writeData(const void * data, size_t size);

    void readData(void * data, size_t size);

    void checkEOS();

};

class NotYetConnected : public std::exception {

public:

    virtual const char * what() const throw() {
        return "Not yet connected";
    }

};

class SerialTimeout : public std::exception {

public:

    virtual const char * what() const throw() {
        return "Serial timeout expired";
    }

};

class ReadUnexpectedByteCount : public std::exception {

public:

    virtual const char * what() const throw() {
        return "Read unexpected byte count";
    }

};

class WriteUnexpectedByteCount : public std::exception {

public:

    virtual const char * what() const throw() {
        return "Write unexpected byte count";
    }

};

class ProtocolVersionException : public std::exception {

public:

    virtual const char * what() const throw() {
        return "Protocol version missmatch";
    }

};



#endif // SERIALCLIENT_H
