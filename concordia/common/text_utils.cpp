#include "concordia/common/text_utils.hpp"
#include <boost/algorithm/string.hpp>
#include <boost/algorithm/string/case_conv.hpp>
#include <boost/locale.hpp>


using namespace boost::locale;
 
string TextUtils::toLowerCase(const string & text) {
    generator gen;
    locale loc=gen("pl_PL.UTF-8"); 
    locale::global(loc); 
    cout.imbue(loc);
    
    string result = text;
    boost::locale::to_lower(result);
    return result;
}

string TextUtils::toUpperCase(const string & text) {
    generator gen;
    locale loc=gen("pl_PL.UTF-8"); 
    locale::global(loc); 
    cout.imbue(loc);

    string result = text;
    boost::locale::to_upper(result);
    return result;
}
