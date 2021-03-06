#ifndef REGEX_REPLACEMENT_HDR
#define REGEX_REPLACEMENT_HDR

#include <string>
#include "concordia/common/config.hpp"
#include "concordia/concordia_exception.hpp"
#include <boost/shared_ptr.hpp>
#include <boost/regex.hpp>
#include <boost/regex/icu.hpp>


/*!
  Class for replacing string occurences.

*/

typedef boost::error_info<struct my_tag, std::string> my_tag_error_info;

class RegexReplacement {
public:
    RegexReplacement(std::string patternString, std::string replacement,
                                              bool caseSensitive = true)
                                               throw(ConcordiaException);

    /*! Destructor.
    */
    virtual ~RegexReplacement();

    std::string apply(const std::string & text);

private:
    boost::u32regex _pattern;

    std::string _replacement;
};

#endif
