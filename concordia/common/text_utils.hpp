#ifndef TEXT_UTILS_HDR
#define TEXT_UTILS_HDR

#include <string>


using namespace std;

/*! Utility class for performing simple string operations.
*/
class TextUtils {
public:

    /*! A method for converting all string letters to lower case.
     \param text input string
     \returns lower case version of the input string.
    */
    static string toLowerCase(const string & text);

    /*! A method for converting all string letters to upper case.
     \param text input string
     \returns upper case version of the input string.
    */
    static string toUpperCase(const string & text);

private:

};

#endif
