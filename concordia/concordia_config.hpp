#ifndef CONCORDIA_CONFIG_HDR
#define CONCORDIA_CONFIG_HDR

#include <string>
#include <list>
#include <libconfig.h++>

#include "concordia/concordia_exception.hpp"

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
    explicit ConcordiaConfig(const std::string & configFilePath)
                                       throw(ConcordiaException);

    /*! Destructor.
    */
    virtual ~ConcordiaConfig();

    /*! Getter for the puddle file path parameter.
     \returns file path of the puddle tagset
    */
    std::string & getPuddleTagsetFilePath() {
        return _puddleTagsetFilePath;
    }

    std::string & getWordMapFilePath() {
        return _wordMapFilePath;
    }

    std::string & getHashedIndexFilePath() {
        return _hashedIndexFilePath;
    }

    std::string & getMarkersFilePath() {
        return _markersFilePath;
    }

    std::string & getSuffixArrayFilePath() {
        return _suffixArrayFilePath;
    }

    std::string & getHtmlTagsFilePath() {
        return _htmlTagsFilePath;
    }

    std::string & getSpaceSymbolsFilePath() {
        return _spaceSymbolsFilePath;
    }

    std::string & getStopWordsFilePath() {
        return _stopWordsFilePath;
    }

    std::string & getNamedEntitiesFilePath() {
        return _namedEntitiesFilePath;
    }

    std::string & getStopSymbolsFilePath() {
        return _stopSymbolsFilePath;
    }

    double getAnubisThreshold() {
        return _anubisThreshold;
    }

private:
    libconfig::Config _config;

    std::string _puddleTagsetFilePath;

    std::string _wordMapFilePath;

    std::string _hashedIndexFilePath;

    std::string _markersFilePath;

    std::string _suffixArrayFilePath;

    std::string _htmlTagsFilePath;

    std::string _spaceSymbolsFilePath;

    std::string _stopWordsFilePath;

    std::string _namedEntitiesFilePath;

    std::string _stopSymbolsFilePath;

    double _anubisThreshold;

    std::string _readConfigParameterStr(const std::string & name)
                                     throw(ConcordiaException);
};

#endif
