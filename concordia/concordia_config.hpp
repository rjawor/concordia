#ifndef CONCORDIA_CONFIG_HDR
#define CONCORDIA_CONFIG_HDR

#include <string>
#include <list>
#include <libconfig.h++>

#include "concordia/concordia_exception.hpp"

using namespace std;
using namespace libconfig;

/*!
Class representing the Concordia configuration.
*/
class ConcordiaConfig {
public:
    /*!
    Constructor.
     \param configFilePath path of the configuration file (see \ref running3 for file specification).
     \throws ConcordiaException
    */
    explicit ConcordiaConfig(const string & configFilePath)
                                            throw(ConcordiaException);

    /*! Destructor.
    */
    virtual ~ConcordiaConfig();

    /*! Getter for the puddle file path parameter.
     \returns file path of the puddle tagset
    */
    string & getPuddleTagsetFilePath() {
        return _puddleTagsetFilePath;
    }

    string & getWordMapFilePath() {
        return _wordMapFilePath;
    }

    string & getHashedIndexFilePath() {
        return _hashedIndexFilePath;
    }

    string & getSuffixArrayFilePath() {
        return _suffixArrayFilePath;
    }

private:
    Config _config;

    string _puddleTagsetFilePath;

    string _wordMapFilePath;

    string _hashedIndexFilePath;

    string _suffixArrayFilePath;

    string _readConfigParameterStr(const string & name)
                                     throw(ConcordiaException);
};

#endif
