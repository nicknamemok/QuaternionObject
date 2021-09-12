#include "EulerAngles.h"

// Test

constexpr double rad2degrees = 360 / (2*M_PI);
constexpr double degrees2rad = (2*M_PI) / 360;

EulerAngles::EulerAngles(double pitch, double roll, double yaw)
    : m_roll{ roll }, m_pitch{ pitch }, m_yaw{ yaw } {}

EulerAngles::EulerAngles(std::vector<double> v)
    : m_pitch{ v[0] }, m_roll{ v[1] }, m_yaw{ v[2] }
    { if (v.size() > 3) throw exception{"Invalid vector size."}; }

void EulerAngles::toAngle()
{
    if (m_unit == eulerAngleUnit::radians) { m_pitch *= rad2degrees; m_roll *= rad2degrees; m_yaw *= rad2degrees; m_unit = eulerAngleUnit::degrees; }
    else { throw exception{"Already in radians unit."}; }
};

void EulerAngles::toRadians()
{
    if (m_unit == eulerAngleUnit::degrees) { m_pitch *= degrees2rad; m_roll *= degrees2rad; m_yaw *= degrees2rad; m_unit = eulerAngleUnit::radians; }
    else { throw exception{"Already in degrees unit."}; }
};

Quaternion EulerAngles::toQuaternion()
{
    // Make sure to convert all angles to radians before conversion to Quaternion
    if (m_unit == eulerAngleUnit::radians) { (*this).toRadians(); }
    
    double real{ cos(m_roll/2)*cos(m_pitch/2)*cos(m_yaw/2) + sin(m_roll/2)*sin(m_pitch/2)*sin(m_yaw/2) };
    double i{ sin(m_roll/2)*cos(m_pitch/2)*cos(m_yaw/2) - cos(m_roll/2)*sin(m_pitch/2)*sin(m_yaw/2) };
    double j{ cos(m_roll/2)*sin(m_pitch/2)*cos(m_yaw/2) + sin(m_roll/2)*cos(m_pitch/2)*sin(m_yaw/2) };
    double k{ cos(m_roll/2)*cos(m_pitch/2)*sin(m_yaw/2) - sin(m_roll/2)*sin(m_pitch/2)*cos(m_yaw/2) };
    return Quaternion{ real,i,j,k };
};
