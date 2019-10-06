#include "vex.h"

typedef struct gyroData{
    bool valid;
    float angle;
    float abs_angle;
} gyroData;

static gyroData theGyro = {false, 0.0, 0.0};

int GyroTask() {
    float gyro_value;
    float gyro_error = 0;
    float lastDriftGyro = 0;

    float angle;
    float old_angle = 0.0, delta_angle;

    long nSysTimeOffset;

    theGyro.valid = false;

    sleep(100);

    nSysTimeOffset = Brain.Timer.time();

    while (true) {
        gyro_value = Gyro.value(vex::analogUnits::mV);

        if (Brain.Timer.time() - nSysTimeOffset > 250) {
            if (fabs(gyro_value - lastDriftGyro) < 2) {
                gyro_error += (lastDriftGyro - gyro_value);
            }
            lastDriftGyro = gyro_value;
            nSysTimeOffset = Brain.Timer.time();
        }
        angle = (gyro_value + gyro_error)  / 10.0;

        // normalize into the range 0 - 360
        //if( angle < 0 ) angle += 360;

        theGyro.angle = angle;

        delta_angle = angle - old_angle;
        old_angle   = angle;

        if(delta_angle > 180) delta_angle -= 360;
        if(delta_angle < -180) delta_angle += 360;

        theGyro.abs_angle = theGyro.abs_angle + delta_angle;
        theGyro.valid = true;

        sleep(100);
    }
    return 0;
}

float GyroGetAngle() {
    return( theGyro.angle );
}

float GyroGetAbsAngle() {
    return( theGyro.abs_angle );
}

bool GyroGetValid() {
    return( theGyro.valid );
}