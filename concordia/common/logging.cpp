#include "concordia/common/logging.hpp"

#include <log4cpp/FileAppender.hh>
#include <log4cpp/PatternLayout.hh>

ConcordiaLogger concordia_logger;

ConcordiaLogger::ConcordiaLogger() :
    logger_category(
        log4cpp::Category::getInstance("Category")) {
    initialize_logger_();
}

void ConcordiaLogger::initialize_logger_() {
    setDefaultLoggerAppender_();
    logger_category.setPriority(log4cpp::Priority::WARN);
}

void ConcordiaLogger::setDefaultLoggerAppender_() {
    log4cpp::Appender * default_logger_appender =
        new log4cpp::OstreamAppender(
            "OstreamAppender", &std::cerr);

    addDefaultLayoutToAppender_(default_logger_appender);

    setNewLoggerAppender_(default_logger_appender);
}

void ConcordiaLogger::addDefaultLayoutToAppender_(
                                       log4cpp::Appender * appender) {
    log4cpp::PatternLayout * layout =
        new log4cpp::PatternLayout();

    layout->setConversionPattern("%p %d{%Y-%m-%d %H:%M:%S,%l} : %m%n");

    appender->setLayout(layout);
}

ConcordiaLogger::~ConcordiaLogger() {
}

void ConcordiaLogger::setLoggingToFile(const std::string & filepath) {
    log4cpp::Appender * appender =
        new log4cpp::FileAppender("FileAppender", filepath.c_str());

    setNewLoggerAppender_(appender);
}

void ConcordiaLogger::setLoggingPriority(const std::string & priorityName) {
    try {
        log4cpp::Priority::Value newPriority =
            log4cpp::Priority::getPriorityValue(priorityName);
        logger_category.setPriority(newPriority);
    } catch(std::invalid_argument &) {
        ERROR("Unknown priority name: " << priorityName);
    }
}

log4cpp::Priority::Value ConcordiaLogger::getLoggingPriority() {
    return logger_category.getPriority();
}

void ConcordiaLogger::setNewLoggerAppender_(log4cpp::Appender * appender) {
    logger_category.removeAllAppenders();

    current_logger_appender = appender;
    logger_category.setAppender(current_logger_appender);
}

void ConcordiaLogger::flush(log4cpp::Priority::Value priorityLevel) {
    logger_category.log(priorityLevel, buffer.str());
    buffer.str("");
}

ConcordiaLogger & ConcordiaLogger::operator<< (const std::string & msg) {
    buffer << msg;
    return *this;
}

ConcordiaLogger & ConcordiaLogger::operator<< (const char * msg) {
    buffer << msg;
    return *this;
}

ConcordiaLogger & ConcordiaLogger::operator<< (unsigned long msg) {
    buffer << msg;
    return *this;
}

ConcordiaLogger & ConcordiaLogger::operator<< (signed long msg) {
    buffer << msg;
    return *this;
}

ConcordiaLogger & ConcordiaLogger::operator<< (unsigned int msg) {
    buffer << msg;
    return *this;
}

ConcordiaLogger & ConcordiaLogger::operator<< (signed int msg) {
    buffer << msg;
    return *this;
}

ConcordiaLogger & ConcordiaLogger::operator<< (unsigned short msg) {
    buffer << msg;
    return *this;
}

ConcordiaLogger & ConcordiaLogger::operator<< (signed short msg) {
    buffer << msg;
    return *this;
}

ConcordiaLogger & ConcordiaLogger::operator<< (float msg) {
    buffer << msg;
    return *this;
}

ConcordiaLogger & ConcordiaLogger::operator<< (double msg) {
    buffer << msg;
    return *this;
}

ConcordiaLogger & ConcordiaLogger::operator<< (bool msg) {
    buffer << msg;
    return *this;
}
