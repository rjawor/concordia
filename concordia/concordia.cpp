#include <sstream>

#include "concordia/concordia.hpp"
#include "concordia/common/config.hpp"

// ===========================================

std::string _createLibraryVersion();

// ===========================================

std::string Concordia::_libraryVersion = _createLibraryVersion();

// ===========================================

Concordia::Concordia(const std::string & configFilePath)
                                         throw(ConcordiaException) {
    _config = boost::shared_ptr<ConcordiaConfig> (
                                new ConcordiaConfig(configFilePath));
    _index = boost::shared_ptr<ConcordiaIndex>(
                        new ConcordiaIndex(_config->getWordMapFilePath(),
                                           _config->getHashedIndexFilePath(),
                                           _config->getSuffixArrayFilePath()));
    _searcher = boost::shared_ptr<IndexSearcher>(new IndexSearcher());
}

Concordia::~Concordia() {
}

std::string & Concordia::getVersion() {
    return _libraryVersion;
}

std::string _createLibraryVersion() {
    std::stringstream version;

    version << CONCORDIA_VERSION_MAJOR
            << "."
            << CONCORDIA_VERSION_MINOR;

    return version.str();
}

void Concordia::addSentence(const std::string & sentence)
                                 throw(ConcordiaException) {
    _index->addSentence(sentence);
}

void Concordia::generateIndex() throw(ConcordiaException) {
    _index->generateSuffixArray();
    _index->serializeWordMap();
    _searcher->loadIndex(_config->getWordMapFilePath(),
                         _config->getHashedIndexFilePath(),
                         _config->getSuffixArrayFilePath());
}

std::vector<saidx_t> Concordia::simpleSearch(const std::string & pattern)
                                  throw(ConcordiaException) {
    return _searcher->simpleSearch(pattern);
}


