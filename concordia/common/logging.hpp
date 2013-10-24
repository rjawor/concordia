#ifndef LOGGING_HDR
#define LOGGING_HDR

#include <log4cpp/Category.hh>
#include <log4cpp/OstreamAppender.hh>
#include <log4cpp/SimpleLayout.hh>
#include <log4cpp/Priority.hh>

#include <iostream>
#include <sstream>

#include "concordia/common/config.hpp"

/*! Logging class based on the log4cpp library. The class comes from PSI-Toolkit.
*/ 

class ConcordiaLogger {
public:
    /*! Default constructor.
    */ 
    ConcordiaLogger();

    /*! Destructor.
    */ 
    ~ConcordiaLogger();

    /*! A method to initialize the log file.
     \param filepath the path of the log file
    */ 
    void setLoggingToFile(const std::string & filepath);

    /*! Setter for the logging priority.
     \param priorityName the log4cpp name of the logging priority
    */ 
    void setLoggingPriority(const std::string & priorityName);

    /*! Getter for the logging priority
     \returns the current logging priority.
    */ 
    log4cpp::Priority::Value getLoggingPriority();

    /*! Flush the current string buffer for given priorityLevel.
     \param priorityLevel the logging priority of the buffer to flush
    */ 
    void flush(log4cpp::Priority::Value priorityLevel);

    /*! Operator for direct logging.
     \param msg message to log
    */ 
    ConcordiaLogger & operator<< (const std::string & msg);

    /*! Operator for direct logging.
     \param msg message to log
    */ 
    ConcordiaLogger & operator<< (const char * msg);

    /*! Operator for direct logging.
     \param msg message to log
    */ 
    ConcordiaLogger & operator<< (unsigned long msg);

    /*! Operator for direct logging.
     \param msg message to log
    */ 
    ConcordiaLogger & operator<< (signed long msg);

    /*! Operator for direct logging.
     \param msg message to log
    */ 
    ConcordiaLogger & operator<< (unsigned int msg);

    /*! Operator for direct logging.
     \param msg message to log
    */ 
    ConcordiaLogger & operator<< (signed int msg);

    /*! Operator for direct logging.
     \param msg message to log
    */ 
    ConcordiaLogger & operator<< (unsigned short msg);

    /*! Operator for direct logging.
     \param msg message to log
    */ 
    ConcordiaLogger & operator<< (signed short msg);

    /*! Operator for direct logging.
     \param msg message to log
    */ 
    ConcordiaLogger & operator<< (float msg);

    /*! Operator for direct logging.
     \param msg message to log
    */ 
    ConcordiaLogger & operator<< (double msg);

    /*! Operator for direct logging.
     \param msg message to log
    */ 
    ConcordiaLogger & operator<< (bool msg);

private:
    void initialize_logger_();
    void setDefaultLoggerAppender_();
    void addDefaultLayoutToAppender_(log4cpp::Appender * appender);
    void setNewLoggerAppender_(log4cpp::Appender * appender);

    std::stringstream buffer;
    log4cpp::Category & logger_category;
    log4cpp::Appender * current_logger_appender;
};

extern ConcordiaLogger concordia_logger;

#define TRACE(M) \
    do { \
        concordia_logger << M;                        \
        concordia_logger.flush(log4cpp::Priority::DEBUG);  \
    } while (0)

#define DEBUG(M) \
    do { \
        concordia_logger << M;                        \
        concordia_logger.flush(log4cpp::Priority::DEBUG);                     \
    } while (0)

#define DEBUG_NOFLUSH(M) \
    do { \
        concordia_logger << M;                        \
    } while (0)

#define FLUSH \
    do { \
        concordia_logger.flush(log4cpp::Priority::DEBUG);                     \
    } while (0)

#define INFO(M) \
    do { \
        concordia_logger << M;                        \
        concordia_logger.flush(log4cpp::Priority::INFO);                     \
    } while (0)

#define WARN(M) \
    do { \
        concordia_logger << M;                        \
        concordia_logger.flush(log4cpp::Priority::WARN);                     \
    } while (0)

#define ERROR(M) \
    do { \
        concordia_logger << M;                        \
        concordia_logger.flush(log4cpp::Priority::ERROR);    \
    } while (0)

#define FATAL(M) \
    do { \
        concordia_logger << M;                        \
        concordia_logger.flush(log4cpp::Priority::FATAL);                     \
    } while (0)


#define SET_LOGGER_FILE(M) do { concordia_logger.setLoggingToFile(M); \
                           } while (0);
#define SET_LOGGING_LEVEL(M) \
    do { concordia_logger.setLoggingPriority(M); } while (0);
#endif
