#include <sstream>

#include "concordia/concordia.hpp"
#include "concordia/common/config.hpp"
#include "concordia/common/utils.hpp"

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
                        new ConcordiaIndex(_config->getHashedIndexFilePath(),
                                           _config->getMarkersFilePath()));
    _searcher = boost::shared_ptr<IndexSearcher>(new IndexSearcher());
    _initializeIndex();
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

// Sentences are written to disk and added to T.
// SA is generated on command by other methods.
void Concordia::addExample(const Example & example)
                                 throw(ConcordiaException) {
    _index->addExample(_hashGenerator, _T, _markers, example);
}

// Sentences are written to disk and added to T.
// SA is generated on command by other methods.
void Concordia::addAllExamples(const boost::ptr_vector<Example > & examples)
                                              throw(ConcordiaException) {
    _index->addAllExamples(_hashGenerator, _T, _markers, examples);
}

void Concordia::loadRAMIndexFromDisk() throw(ConcordiaException) {
    if (boost::filesystem::exists(_config->getWordMapFilePath())
      && boost::filesystem::exists(_config->getHashedIndexFilePath())
      && boost::filesystem::exists(_config->getMarkersFilePath())) {
        // reading index from file
        _T->clear();
        ifstream hashedIndexFile;
        hashedIndexFile.open(_config->getHashedIndexFilePath().c_str(), ios::in
                                                     | ios::ate | ios::binary);
        saidx_t hiFileSize = hashedIndexFile.tellg();
        if (hiFileSize > 0) {
            hashedIndexFile.seekg(0, ios::beg);

            while (!hashedIndexFile.eof()) {
                INDEX_CHARACTER_TYPE character =
                                 Utils::readIndexCharacter(hashedIndexFile);
                Utils::appendCharToSaucharVector(_T, character);
            }
            hashedIndexFile.close();
        } else {
            hashedIndexFile.close();
            throw ConcordiaException("Index corrupt: empty hash index file");
        }

        // reading markers from file
        _markers->clear();
        ifstream markersFile;
        markersFile.open(_config->getMarkersFilePath().c_str(), ios::in
                                                     | ios::ate | ios::binary);
        saidx_t maFileSize = markersFile.tellg();
        if (maFileSize > 0) {
            markersFile.seekg(0, ios::beg);

            while (!markersFile.eof()) {
                SUFFIX_MARKER_TYPE marker =
                                 Utils::readMarker(markersFile);
                _markers->push_back(marker);
            }
            markersFile.close();
        } else {
            markersFile.close();
            throw ConcordiaException("Index corrupt: empty markers file");
        }
        // generating suffix array
        _SA = _index->generateSuffixArray(_hashGenerator, _T);
    } else {
        throw ConcordiaException("Index corrupt: missing files");
    }
}

void Concordia::refreshSAfromRAM() throw(ConcordiaException) {
    _SA = _index->generateSuffixArray(_hashGenerator, _T);
}


void Concordia::_initializeIndex() throw(ConcordiaException) {
    _hashGenerator = boost::shared_ptr<HashGenerator>(
                            new HashGenerator(_config->getWordMapFilePath()));
    _T = boost::shared_ptr<std::vector<sauchar_t> >(
                                                  new std::vector<sauchar_t>);
    _markers = boost::shared_ptr<std::vector<SUFFIX_MARKER_TYPE> >(
                                         new std::vector<SUFFIX_MARKER_TYPE>);
    if (boost::filesystem::exists(_config->getWordMapFilePath())
      && boost::filesystem::exists(_config->getHashedIndexFilePath())) {
        loadRAMIndexFromDisk();
    } else if (!boost::filesystem::exists(_config->getWordMapFilePath())
      && !boost::filesystem::exists(_config->getHashedIndexFilePath())) {
        // empty index
        _SA = boost::shared_ptr<std::vector<saidx_t> >(
                                                new std::vector<saidx_t>);
    } else {
        throw ConcordiaException("Index corrupt: missing files");
    }
}

boost::ptr_vector<SubstringOccurence> Concordia::simpleSearch(
                                          const string & pattern)
                                  throw(ConcordiaException) {
    if (_T->size() > 0) {
        return _searcher->simpleSearch(_hashGenerator, _T,
                                         _markers, _SA, pattern);
    } else {
        boost::ptr_vector<SubstringOccurence> result;
        return result;
    }
}

