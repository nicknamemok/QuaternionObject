#ifndef EXCEPTION_H
#define EXCEPTION_H

#include <string>

// Exception class
class exception
{
private:
    std::string m_error;
public:
    exception(std::string error);
    std::string getError();
};

#endif