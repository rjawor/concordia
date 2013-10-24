#include "concordia_exception.hpp"

ConcordiaException::ConcordiaException() throw():
    _message("Concordia exception") {
}

ConcordiaException::ConcordiaException(const string & message) throw():
    _message(message) {
}

ConcordiaException::~ConcordiaException() throw() {
}

const char* ConcordiaException::what() const throw() {
    char * m = new char[_message.size() + 1];
    m[_message.size()]=0;
    memcpy(m, _message.c_str(), _message.size());
    return m;
}
