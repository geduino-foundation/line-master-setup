#ifndef SERIALCLIENT_H
#define SERIALCLIENT_H

#include <serial/serial.h>

#define PROTOCOL_VERSION        0x00

#define GET_PROTOCOL_VERSION    0x00
#define GET_BATTERY_VOLTAGE     0x01
#define LOAD_FROM_EEPROM        0x02
#define SAVE_TO_EEPROM          0x03
#define DOWNLOAD                0x04
#define UPLOAD                  0x05

#define BAUDRATE                9600
#define TIMEOUT                 2500

struct Setup {
    unsigned short pid_proportional;
    unsigned short pid_integrative;
    unsigned short pid_derivative;
    unsigned short motors_max_speed;
    unsigned short ir_in_line_threshold;
    unsigned short ir_noise_threshold;
};

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

private:

    serial::Serial serial;

    void writeChar(const unsigned char data);

    void writeShort(const unsigned short data);

    void readChar(unsigned char * data);

    void readShort(unsigned short * data);

};

class NotYetConnected : public std::exception {

public:

    virtual const char* what() const throw() {
        return "Not yet connected";
    }

};

class SerialTimeout : public std::exception {

public:

    virtual const char* what() const throw() {
        return "Serial timeout expired";
    }

};

class ReadUnexpectedByteCount : public std::exception {

public:

    virtual const char* what() const throw() {
        return "Read unexpected byte count";
    }

};

class WriteUnexpectedByteCount : public std::exception {

public:

    virtual const char* what() const throw() {
        return "Write unexpected byte count";
    }

};

class ProtocolVersionException : public std::exception {

public:

    virtual const char* what() const throw() {
        return "Protocol version missmatch";
    }

};



#endif // SERIALCLIENT_H
