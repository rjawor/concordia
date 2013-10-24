#include <sstream>
#include "concordia/concordia_config.hpp"
#include "concordia/common/logging.hpp"

#define PUDDLE_TAGSET_PARAM "puddle_tagset_path"

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
