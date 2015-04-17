#include <sstream>
#include <stdlib.h>
#include "concordia/concordia_config.hpp"
#include "concordia/common/logging.hpp"

#define PUDDLE_TAGSET_PARAM "puddle_tagset_path"
#define WORD_MAP_PARAM "word_map_path"
#define HASHED_INDEX_PARAM "hashed_index_path"
#define MARKERS_PARAM "markers_path"
#define SUFFIX_ARRAY_PARAM "suffix_array_path"
#define HTML_TAGS_PARAM "html_tags_path"
#define SPACE_SYMBOLS_PARAM "space_symbols_path"
#define STOP_WORDS_PARAM "stop_words_path"
#define NAMED_ENTITIES_PARAM "named_entities_path"
#define STOP_SYMBOLS_PARAM "stop_symbols_path"
#define ANUBIS_THRESHOLD_PARAM "anubis_threshold"

ConcordiaConfig::ConcordiaConfig(const std::string & configFilePath)
                                     throw(ConcordiaException) {
    try {
        _config.readFile(configFilePath.c_str());
    } catch(libconfig::ParseException & e) {
        throw ConcordiaException("Error parsing config file: "+configFilePath);
    } catch(libconfig::FileIOException & e) {
        throw ConcordiaException("I/O error reading config file: "
                                                              +configFilePath);
    }

    _puddleTagsetFilePath =
          ConcordiaConfig::_readConfigParameterStr(PUDDLE_TAGSET_PARAM);
    _wordMapFilePath =
          ConcordiaConfig::_readConfigParameterStr(WORD_MAP_PARAM);
    _hashedIndexFilePath =
          ConcordiaConfig::_readConfigParameterStr(HASHED_INDEX_PARAM);
    _markersFilePath =
          ConcordiaConfig::_readConfigParameterStr(MARKERS_PARAM);
    _suffixArrayFilePath =
          ConcordiaConfig::_readConfigParameterStr(SUFFIX_ARRAY_PARAM);
    _htmlTagsFilePath =
          ConcordiaConfig::_readConfigParameterStr(HTML_TAGS_PARAM);
    _spaceSymbolsFilePath =
          ConcordiaConfig::_readConfigParameterStr(SPACE_SYMBOLS_PARAM);
    _stopWordsFilePath =
          ConcordiaConfig::_readConfigParameterStr(STOP_WORDS_PARAM);
    _namedEntitiesFilePath =
          ConcordiaConfig::_readConfigParameterStr(NAMED_ENTITIES_PARAM);
    _stopSymbolsFilePath =
          ConcordiaConfig::_readConfigParameterStr(STOP_SYMBOLS_PARAM);
    _anubisThreshold = atof(ConcordiaConfig::_readConfigParameterStr(
                                            ANUBIS_THRESHOLD_PARAM).c_str());
}

ConcordiaConfig::~ConcordiaConfig() {
}

std::string ConcordiaConfig::_readConfigParameterStr(const std::string & name)
                                             throw(ConcordiaException) {
    if (!_config.exists(name)) {
        throw ConcordiaException("Config error: "+name+" setting not found");
    } else {
        return _config.lookup(name);
    }
}
