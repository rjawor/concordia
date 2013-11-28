#include <sstream>
#include "concordia/concordia_config.hpp"
#include "concordia/common/logging.hpp"

#define PUDDLE_TAGSET_PARAM "puddle_tagset_path"
#define WORD_MAP_PARAM "word_map_path"
#define HASHED_INDEX_PARAM "hashed_index_path"
#define SUFFIX_ARRAY_PARAM "suffix_array_path"

ConcordiaConfig::ConcordiaConfig(const string & configFilePath)
                                     throw(ConcordiaException) {
    try {
        _config.readFile(configFilePath.c_str());
    } catch(ParseException & e) {
        throw ConcordiaException("Error parsing config file: "+configFilePath);
    } catch(FileIOException & e) {
        throw ConcordiaException("I/O error reading config file: "
                                                              +configFilePath);
    }

    _puddleTagsetFilePath =
          ConcordiaConfig::_readConfigParameterStr(PUDDLE_TAGSET_PARAM);
    _wordMapFilePath =
          ConcordiaConfig::_readConfigParameterStr(WORD_MAP_PARAM);
    _hashedIndexFilePath =
          ConcordiaConfig::_readConfigParameterStr(HASHED_INDEX_PARAM);
    _suffixArrayFilePath =
          ConcordiaConfig::_readConfigParameterStr(SUFFIX_ARRAY_PARAM);
}

ConcordiaConfig::~ConcordiaConfig() {
}

string ConcordiaConfig::_readConfigParameterStr(const string & name)
                                             throw(ConcordiaException) {
    if (!_config.exists(name)) {
        throw ConcordiaException("Config error: "+name+" setting not found");
    } else {
        return _config.lookup(name);
    }
}
