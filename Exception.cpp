#include "Exception.h"

exception::exception(std::string error) : m_error{ error } {}
std::string exception::getError() { return m_error; }
