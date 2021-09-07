#include <vector>
#include <string>

#ifndef QUATERNION_H
#define QUATERNION_H

// Exception class
class QuaternionException
{
private:
    std::string m_error;
public:
    QuaternionException(std::string error) : m_error{ error } {}
    std::string getError() { return m_error; }
};


// Quaternion class
class Quaternion
{

private:

    double m_i{}, m_j{}, m_k{}, m_real{};

public:

// CONSTRUCTORS //

    // Vector, size 4
    Quaternion(std::vector<double> V)
        : m_i{ V[0] }, m_j{ V[1] }, m_k{ V[2] }, m_real{ V[3] }
        { if(V.size() > 4) throw QuaternionException{ "Invalid vector size." }; }

    // Vector, size 3, with real attached
    Quaternion(std::vector<double> V, double real)
        : m_i{ V[0] }, m_j{ V[1] }, m_k{ V[2] }, m_real{ real }
        { if(V.size() > 3) throw QuaternionException{ "Invalid vector size." }; }

    // Full manual
    Quaternion(double i, double j, double k, double real)
        : m_i{ i }, m_j{ j }, m_k{ k }, m_real{ real } {}



// ARITHMETIC OVERLOADS //

    // Multiplication
    friend Quaternion operator* (const Quaternion& q1, const Quaternion& q2)
    {

        return {{ q1.m_real*q2.m_i + q2.m_real*q1.m_i + q1.m_j*q2.m_k - q2.m_j*q1.m_k,
                  q1.m_real*q2.m_j + q2.m_real*q1.m_j + q1.m_k*q2.m_i - q2.m_k*q1.m_i,
                  q1.m_real*q2.m_k + q2.m_real*q1.m_k + q1.m_i*q2.m_j - q2.m_i*q1.m_j },
                  q1.m_real*q2.m_real - q1.m_i*q2.m_i - q1.m_j*q2.m_j - q1.m_k*q2.m_k };

    }

    // Addition an subtraction
    friend Quaternion operator+ (Quaternion& q1, Quaternion& q2) {return {{q1.m_i+q2.m_i, q1.m_j+q2.m_j, q1.m_k+q2.m_k}, q1.m_real+q2.m_real};}
    friend Quaternion operator- (Quaternion& q1, Quaternion& q2) {return {{q1.m_i-q2.m_i, q1.m_j-q2.m_j, q1.m_k-q2.m_k}, q1.m_real-q2.m_real};}


// TRANSFORMATIONS //

    // Invert quaternion
    Quaternion invert() {return {-m_i, -m_j, -m_k, m_real};}

/*
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



// PRINT AND GET FUNCTIONS //

    void print() {std::cout << getI() << " " << getJ() << " " << getK() << "\n";}
    const double getReal() {return m_real;}

*/

};


#endif

int main()
{
    std::vector<double> v{1,2,3,4,5};
    Quaternion q{v};
    return 0;
}