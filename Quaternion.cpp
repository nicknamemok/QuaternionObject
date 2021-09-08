#include <vector>
#include <string>
#include <iostream>
#include <cmath>

#ifndef QUATERNION_H
#define QUATERNION_H

constexpr double rad2degrees = 360 / (2*M_PI);
constexpr double degrees2rad = (2*M_PI) / 360;

// Exception class
class exception
{
private:
    std::string m_error;
public:
    exception(std::string error) : m_error{ error } {}
    std::string getError() { return m_error; }
};


// Euler Angle class, default in Radians
class Quaternion;
class EulerAngles
{
private:

    enum class eulerAngleUnit { radians, degrees };
    double m_roll, m_pitch, m_yaw;
    eulerAngleUnit m_unit{ eulerAngleUnit::radians };

public:

    EulerAngles(double pitch, double roll, double yaw)
        : m_roll{ roll }, m_pitch{ pitch }, m_yaw{ yaw } {}

    EulerAngles(std::vector<double> v)
        : m_pitch{ v[0] }, m_roll{ v[1] }, m_yaw{ v[2] }
        { if (v.size() > 3) throw exception{"Invalid vector size."}; }

    void toAngle()
    {
        if (m_unit == eulerAngleUnit::radians) { m_pitch *= rad2degrees; m_roll *= rad2degrees; m_yaw *= rad2degrees; m_unit = eulerAngleUnit::degrees; }
        else { throw exception{"Already in radians unit."}; }
    }

    void toRadians()
    {
        if (m_unit == eulerAngleUnit::degrees) { m_pitch *= degrees2rad; m_roll *= degrees2rad; m_yaw *= degrees2rad; m_unit = eulerAngleUnit::radians; }
        else { throw exception{"Already in degrees unit."}; }
    }

    Quaternion toQuaternion();

};


// Quaternion class
class Quaternion
{

private:

    double m_i{}, m_j{}, m_k{}, m_real{};

public:

    Quaternion(std::vector<double> V)
        : m_i{ V[0] }, m_j{ V[1] }, m_k{ V[2] }, m_real{ V[3] }
        { if(V.size() > 4) throw exception{ "Invalid vector size." }; }

    Quaternion(std::vector<double> V, double real)
        : m_i{ V[0] }, m_j{ V[1] }, m_k{ V[2] }, m_real{ real }
        { if(V.size() > 3) throw exception{ "Invalid vector size." }; }

    Quaternion(double i, double j, double k, double real)
        : m_i{ i }, m_j{ j }, m_k{ k }, m_real{ real } {}


    friend Quaternion operator* (Quaternion& q1, Quaternion& q2)
    {

        return {{ q1.m_real*q2.m_i + q2.m_real*q1.m_i + q1.m_j*q2.m_k - q2.m_j*q1.m_k,
                  q1.m_real*q2.m_j + q2.m_real*q1.m_j + q1.m_k*q2.m_i - q2.m_k*q1.m_i,
                  q1.m_real*q2.m_k + q2.m_real*q1.m_k + q1.m_i*q2.m_j - q2.m_i*q1.m_j },
                  q1.m_real*q2.m_real - q1.m_i*q2.m_i - q1.m_j*q2.m_j - q1.m_k*q2.m_k };

    }

    friend Quaternion operator+ (Quaternion& q1, Quaternion& q2) {return {{q1.m_i+q2.m_i, q1.m_j+q2.m_j, q1.m_k+q2.m_k}, q1.m_real+q2.m_real};}
    friend Quaternion operator- (Quaternion& q1, Quaternion& q2) {return {{q1.m_i-q2.m_i, q1.m_j-q2.m_j, q1.m_k-q2.m_k}, q1.m_real-q2.m_real};}

    void invert() { m_i=-m_i; m_j=-m_j; m_k=-m_k; }
    void transform(Quaternion& q) { Quaternion qInvert{q}; qInvert.invert(); (*this) = q*(*this); (*this) = (*this)*qInvert;}
    void print() { std::cout << "(" << m_i << "i, " << m_j << "j, " << m_k << "k, " << m_real << "R)"; }

    EulerAngles toEuler()
    {
        double e1{ asin(2*(m_real*m_j - m_k*m_i)) };
        double e2{ atan((2*(m_real*m_i + m_j*m_k))/(1-2*(m_i*m_i+m_j*m_j))) };
        double e3{ atan((2*(m_real*m_k + m_i*m_j))/(1-2*(m_j*m_j+m_k*m_k))) };
        return EulerAngles{ e1,e2,e3 };
    }


};

Quaternion EulerAngles::toQuaternion()
{
    double real{ cos(m_roll/2)*cos(m_pitch/2)*cos(m_yaw/2) + sin(m_roll/2)*sin(m_pitch/2)*sin(m_yaw/2) };
    double i{ sin(m_roll/2)*cos(m_pitch/2)*cos(m_yaw/2) - cos(m_roll/2)*sin(m_pitch/2)*sin(m_yaw/2) };
    double j{ cos(m_roll/2)*sin(m_pitch/2)*cos(m_yaw/2) + sin(m_roll/2)*cos(m_pitch/2)*sin(m_yaw/2) };
    double k{ cos(m_roll/2)*cos(m_pitch/2)*sin(m_yaw/2) - sin(m_roll/2)*sin(m_pitch/2)*cos(m_yaw/2) };
    return Quaternion{ real,i,j,k };
}


#endif

int main()
{

    Quaternion q1{0,1,0,1}, q2{1,0,0,1};

    q1.print();
    q1.transform(q2);
    q1.print();

    return 0;
}