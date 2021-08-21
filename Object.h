#ifndef QUATERNION_H
#define QUATERNION_H
#include "Quaternion.h"
#endif

static int ObjectID{1};

class Object
{

public:

    enum class ObjectType { generic, max_object_types };

private:

    int m_ObjectID{ObjectID};
    std::string m_name;
    ObjectType m_OType;
    Vector3D m_location;
    Quaternion m_orientation;

public:

    // Constructor, all-in-one
    Object(Vector3D location=Vector3D{}, Quaternion orientation=Quaternion{}, ObjectType OType=ObjectType::generic, std::string name="Generic")
        : m_name{ name }, m_OType{ OType }, m_location{ location }, m_orientation{ orientation } 
        {
            std::cout << "Object created..." << "\n";
            std::cout << "ID   :   " << getID() << "\n";
            std::cout << "Name :   " << getName() << "\n";
            ++ObjectID;
        }

    // Get functions template
    int getID() { return m_ObjectID; }
    std::string getName() {return m_name;}
    ObjectType getObjectType() {return m_OType;}
    Vector3D getLocation() {return m_location;}
    Quaternion getOrientation() {return m_orientation;}


    friend std::ostream& operator<< (std::ostream& out, Object object)
    {            
        out << "ID   :   " << getID() << "\n";
        out << "Name :   " << getName() << "\n"; 
        return out;
    }

};