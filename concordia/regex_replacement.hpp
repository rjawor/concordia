#ifndef REGEX_REPLACEMENT_HDR
#define REGEX_REPLACEMENT_HDR

#include <string>
#include "concordia/common/config.hpp"
#include "concordia/concordia_exception.hpp"
#include <boost/shared_ptr.hpp>
#include <boost/regex.hpp>


/*!
  Class for replacing string occurences.

*/

using namespace std;

typedef boost::error_info<struct my_tag,std::string> my_tag_error_info;

class RegexReplacement {
public:
    explicit RegexReplacement(string patternString, string replacement)
                                              throw(ConcordiaException);

    /*! Destructor.
    */
    virtual ~RegexReplacement();
    
    string apply(const string & text);

private:
    boost::regex _pattern;
    
    string _replacement;    
};

#endif
