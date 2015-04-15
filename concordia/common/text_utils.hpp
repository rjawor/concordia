#ifndef TEXT_UTILS_HDR
#define TEXT_UTILS_HDR

#include <string>
#include <boost/shared_ptr.hpp>
#include "utf8case/simple_convert.hpp"
#include "utf8case/case_converter_factory.hpp"
#include "utf8case/string_case_converter_manager.hpp"

/*! Utility class for performing simple string operations.
*/
class TextUtils {
public:
    TextUtils();

    static TextUtils & getInstance() {
        static TextUtils instance;  // Guaranteed to be destroyed.
                                    // Instantiated on first use.
        return instance;
    }

    /*! A method for converting all string letters to lower case.
     \param text input string
     \returns lower case version of the input string.
    */
    std::string toLowerCase(const std::string & text);

    /*! A method for converting all string letters to upper case.
     \param text input string
     \returns upper case version of the input string.
    */
    std::string toUpperCase(const std::string & text);

private:
    explicit TextUtils(TextUtils const&);              // Don't Implement

    void operator=(TextUtils const&);                  // Don't implement

    boost::shared_ptr<StringGeneralCaseConverter> _lowerConverter;

    boost::shared_ptr<StringGeneralCaseConverter> _upperConverter;
};

#endif
