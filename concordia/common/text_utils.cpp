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

std::string TextUtils::toLowerCase(const std::string & text) {
    return simpleConvert(*_lowerConverter, text);
}

std::string TextUtils::toUpperCase(const std::string & text) {
    return simpleConvert(*_upperConverter, text);
}
