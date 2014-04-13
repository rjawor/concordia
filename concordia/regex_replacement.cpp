#include "concordia/regex_replacement.hpp"
#include <sstream>
#include <boost/exception/all.hpp>
#include <boost/throw_exception.hpp>

RegexReplacement::RegexReplacement(string patternString, string replacement)
                                         throw(ConcordiaException):
                                         _replacement(replacement) {
    try {
        _pattern = boost::regex(patternString);
    } catch ( const std::exception & e ) {
        stringstream ss;
        
        ss << "Bad regex pattern: " << patternString <<
             " Detailed info: " << e.what();
             
        if ( std::string const * extra  = boost::get_error_info<my_tag_error_info>(e) ) {
            ss << *extra;
        }
        throw ConcordiaException(ss.str());
    }
}

RegexReplacement::~RegexReplacement() {
}

string RegexReplacement::apply(const string & text) {
    return boost::regex_replace(text, _pattern, _replacement,
                    boost::match_default | boost::format_all);
}

