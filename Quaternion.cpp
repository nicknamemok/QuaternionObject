#include "Quaternion.h"


Quaternion::Quaternion(std::vector<double> V)
    : m_i{ V[0] }, m_j{ V[1] }, m_k{ V[2] }, m_real{ V[3] }
    { if(V.size() > 4) throw exception{ "Invalid vector size." }; }

Quaternion::Quaternion(std::vector<double> V, double real)
    : m_i{ V[0] }, m_j{ V[1] }, m_k{ V[2] }, m_real{ real }
    { if(V.size() > 3) throw exception{ "Invalid vector size." }; }

Quaternion::Quaternion(double i, double j, double k, double real)
    : m_i{ i }, m_j{ j }, m_k{ k }, m_real{ real } {}


Quaternion operator* (Quaternion& q1, Quaternion& q2)
{
    return Quaternion{ q1.m_real*q2.m_i + q2.m_real*q1.m_i + q1.m_j*q2.m_k - q2.m_j*q1.m_k,
                q1.m_real*q2.m_j + q2.m_real*q1.m_j + q1.m_k*q2.m_i - q2.m_k*q1.m_i,
                q1.m_real*q2.m_k + q2.m_real*q1.m_k + q1.m_i*q2.m_j - q2.m_i*q1.m_j,
                q1.m_real*q2.m_real - q1.m_i*q2.m_i - q1.m_j*q2.m_j - q1.m_k*q2.m_k };
}

Quaternion operator+ (Quaternion& q1, Quaternion& q2) {return Quaternion{q1.m_i+q2.m_i, q1.m_j+q2.m_j, q1.m_k+q2.m_k, q1.m_real+q2.m_real};}
Quaternion operator- (Quaternion& q1, Quaternion& q2) {return Quaternion{q1.m_i-q2.m_i, q1.m_j-q2.m_j, q1.m_k-q2.m_k, q1.m_real-q2.m_real};}

void Quaternion::invert() { m_i=-m_i; m_j=-m_j; m_k=-m_k; }
void Quaternion::transform(Quaternion& q) { Quaternion qInvert{q}; qInvert.invert(); (*this) = q*(*this); (*this) = (*this)*qInvert;}
void Quaternion::print() { std::cout << "(" << m_i << "i, " << m_j << "j, " << m_k << "k, " << m_real << "R)"; }

EulerAngles Quaternion::toEuler()
{
    double e1{ asin(2*(m_real*m_j - m_k*m_i)) };
    double e2{ atan((2*(m_real*m_i + m_j*m_k))/(1-2*(m_i*m_i+m_j*m_j))) };
    double e3{ atan((2*(m_real*m_k + m_i*m_j))/(1-2*(m_j*m_j+m_k*m_k))) };
    return EulerAngles{ e1,e2,e3 };
};

