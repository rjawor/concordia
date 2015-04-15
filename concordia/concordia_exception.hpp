#ifndef CONCORDIA_EXCEPTION_HDR
#define CONCORDIA_EXCEPTION_HDR

#include<exception>
#include<string>
#include<string.h>

/*!
Class representing an internal exception thrown in the Concordia library.
*/
class ConcordiaException : public std::exception {
public:
    /*! Constructor.
    */
    ConcordiaException() throw();

    /*! Constructor with a message.
     \param message message of the exception
    */
    explicit ConcordiaException(const std::string & message) throw();

    /*! Destructor.
    */
    ~ConcordiaException() throw();

    /*! Implementation of the virtual method which provides the exception message.
    */
    virtual const char* what() const throw();

private:
    std::string _message;
};

#endif
