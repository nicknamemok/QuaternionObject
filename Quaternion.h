#ifndef VECTOR_H
#define VECTOR_H
#include <vector>
#endif

// Prerequisite 3-point vector class used for Quaternion class
class Vector3D
{

protected:

    double m_i{};
    double m_j{};
    double m_k{};

public:

    Vector3D(double i = 0.0, double j = 0.0, double k = 0.0)
        : m_i{ i }, m_j{ j }, m_k{ k } {}

    const double getI() { return m_i; }
    const double getJ() { return m_j; }
    const double getK() { return m_k; }

};


// Quaternion class
class Quaternion: public Vector3D
{

private:

    double m_real{};

public:

//** CONSTRUCTORS **//

    // vector with real, default
    Quaternion(Vector3D vector=Vector3D{}, double real=0.0)
        : Vector3D{ vector }, m_real{ real } {}

    // full manual
    Quaternion(double i, double j, double k, double real)
        : Vector3D{ i, j, k }, m_real{ real } {}



//** ARITHMETIC OVERLOADS **//

    friend Quaternion operator* (const Quaternion& q1, const Quaternion& q2)
    {

        return {{ q1.m_real*q2.m_i + q2.m_real*q1.m_i + q1.m_j*q2.m_k - q2.m_j*q1.m_k,
                  q1.m_real*q2.m_j + q2.m_real*q1.m_j + q1.m_k*q2.m_i - q2.m_k*q1.m_i,
                  q1.m_real*q2.m_k + q2.m_real*q1.m_k + q1.m_i*q2.m_j - q2.m_i*q1.m_j },
                  q1.m_real*q2.m_real - q1.m_i*q2.m_i - q1.m_j*q2.m_j - q1.m_k*q2.m_k };

    }

    friend Quaternion operator+ (Quaternion& q1, Quaternion& q2) {return {{q1.m_i+q2.m_i, q1.m_j+q2.m_j, q1.m_k+q2.m_k}, q1.m_real+q2.m_real};}
    friend Quaternion operator- (Quaternion& q1, Quaternion& q2) {return {{q1.m_i-q2.m_i, q1.m_j-q2.m_j, q1.m_k-q2.m_k}, q1.m_real-q2.m_real};}



//** TRANSFORMATIONS **//

    // Invert quaternion
    Quaternion invert() {return {-m_i, -m_j, -m_k, m_real};}

    // Rotate q by *this quaternion
    Quaternion transform(Quaternion& q) {return (*this)*q*(this->invert());}

    // Rotate v by *this quaternion
    Vector3D transform(Vector3D& v) {Quaternion q{v}; return transform(q);}

    // Rotate a vector of quaternions by *this
    std::vector<Quaternion> transform(std::vector<Quaternion> qVector)
    {
        std::vector<Quaternion> tempQ{qVector};
        for (int i{0}; i<qVector.size() ; ++i)
        {
            tempQ[i] = transform(qVector[i]);
        }
        return tempQ;
    }

    // Rotate a vector of Vector3D objects by *this
    std::vector<Vector3D> transform(std::vector<Vector3D> vVector)
    {
        std::vector<Vector3D> tempV{vVector};
        for (int i{0}; i<vVector.size() ; ++i)
        {
            tempV[i] = transform(vVector[i]);
        }
        return tempV;
    }



//** PRINT AND GET FUNCTIONS **//

    void print() {std::cout << getI() << " " << getJ() << " " << getK() << "\n";}
    const double getReal() {return m_real;}

};




