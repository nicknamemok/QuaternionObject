#ifndef QUATERNION_H
#define QUATERNION_H

#include <vector>
#include <string>
#include <iostream>
#include <cmath>
#include "EulerAngles.h"
#include "Exception.h"

class EulerAngles;

// Quaternion class
class Quaternion
{

private:

    double m_i{}, m_j{}, m_k{}, m_real{};

public:

    Quaternion(std::vector<double> V);
    Quaternion(std::vector<double> V, double real);
    Quaternion(double i, double j, double k, double real);

    friend Quaternion operator* (Quaternion& q1, Quaternion& q2);
    friend Quaternion operator+ (Quaternion& q1, Quaternion& q2);
    friend Quaternion operator- (Quaternion& q1, Quaternion& q2);

    void invert();
    void transform(Quaternion& q);
    void print();

    EulerAngles toEuler();

};

#endif