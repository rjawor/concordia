#include "concordia/common/text_utils.hpp"
#include <boost/algorithm/string.hpp>
#include <boost/algorithm/string/case_conv.hpp>
#include <boost/locale.hpp>

TextUtils::TextUtils() {
    _lowerConverter =
        StringCaseConverterManager::getInstance().getLowerCaseConverter("pl");
    _upperConverter =
        StringCaseConverterManager::getInstance().getUpperCaseConverter("pl");
}
 
string TextUtils::toLowerCase(const string & text) {
    return simpleConvert(*_lowerConverter, text);
}

string TextUtils::toUpperCase(const string & text) {
    return simpleConvert(*_upperConverter, text);
}
