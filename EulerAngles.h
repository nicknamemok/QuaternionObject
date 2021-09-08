#ifndef EULERANGLES_H
#define EULERANGLES_H

#include <cmath>
#include "Quaternion.h"
#include "Exception.h"

class Quaternion;

// Euler Angle class, default in Radians
class EulerAngles
{
private:

    enum class eulerAngleUnit { radians, degrees };
    double m_roll, m_pitch, m_yaw;
    eulerAngleUnit m_unit{ eulerAngleUnit::radians };

public:

    EulerAngles(double pitch, double roll, double yaw);
    EulerAngles(std::vector<double> v);

    void toAngle();
    void toRadians();

    Quaternion toQuaternion();

};

#endif