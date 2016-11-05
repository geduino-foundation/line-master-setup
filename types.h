#ifndef TYPES_H
#define TYPES_H

struct Setup {
    unsigned short pid_proportional;
    unsigned short pid_integrative;
    unsigned short pid_derivative;
    unsigned short motors_max_speed;
    unsigned short ir_in_line_threshold;
    unsigned short ir_noise_threshold;
    unsigned short telemetry_enabled;
};

struct TelemetryData {
    unsigned int time;
    short error;
};

#endif // TYPES_H
