#include <iostream>  // Include the standard input-output stream library
#define signf(f) ((f>0.0f) * 2 - 1)


float clamp(float v) {
    return fabs(v) > 1.0f ? 1.0f * signf(v) : v;
}

float returnVoltage(float targetAngle, float currentAngle, unsigned int timeElapsed, float lastAngle, float p, float i , float d) {
    // targetAngle: angle trying to be reached
    // currentAngle: current angle
    // timeElapsed: time elapsed in milis
    // lastAngle: angle at end of last cycle
    float pchange = p * (targetAngle - currentAngle);
    float ichange = i * timeElapsed;
    float dchange = (currentAngle - lastAngle) * d;
    return clamp(p + i - d);
}

int main() {
    // Print a simple greeting message
    std::cout << "Hello, World!" << std::endl;
    float voltage = 0.0f;
    float pos = 0.0f;
    float targetPos = 100.0f;
    float lastPos = 0.0f;
    // loop
    unsigned int t = 0;
    while (1) {
        voltage = returnVoltage(targetPos, pos, t, lastPos, 0.01f, 0.0f, 0.0f);
        pos += voltage * 0.1f;
        std::cout << pos << std::endl;
        lastPos = pos;
        t++;
    }
    // Return 0 to indicate successful completion
    return 0;
}
