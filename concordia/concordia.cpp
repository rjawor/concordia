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
                        new ConcordiaIndex(_config->getHashedIndexFilePath()));
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
// SA is generated on command by different methods.
void Concordia::addSentence(const std::string & sentence)
                                 throw(ConcordiaException) {
    _index->addSentence(_hashGenerator, _T, sentence);
}

// Sentences are written to disk and added to T.
// SA is generated on command by different methods.
void Concordia::addAllSentences(
                boost::shared_ptr<std::vector<std::string> > sentences)
                                              throw(ConcordiaException) {
    _index->addAllSentences(_hashGenerator, _T, sentences);
}

void Concordia::loadRAMIndexFromDisk() throw(ConcordiaException) {
    if (boost::filesystem::exists(_config->getWordMapFilePath())
      && boost::filesystem::exists(_config->getHashedIndexFilePath())) {
        // reading index from files
        _T->clear();
        ifstream hashedIndexFile;
        hashedIndexFile.open(_config->getHashedIndexFilePath().c_str(), ios::in
                                                     | ios::ate | ios::binary);
        saidx_t fileSize = hashedIndexFile.tellg();
        if (fileSize > 0) {
            hashedIndexFile.seekg(0, ios::beg);

            while (!hashedIndexFile.eof()) {
                INDEX_CHARACTER_TYPE character =
                                 Utils::readIndexCharacter(hashedIndexFile);
                Utils::appendCharToSaucharVector(_T, character);
            }
            hashedIndexFile.close();

            // generating suffix array
            _SA = _index->generateSuffixArray(_hashGenerator, _T);
        } else {
            throw ConcordiaException("Index corrupt: empty hash index file");
        }
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

boost::shared_ptr<std::vector<saidx_t> > Concordia::simpleSearch(
                                          const string & pattern)
                                  throw(ConcordiaException) {
    if (_T->size() > 0) {
        return _searcher->simpleSearch(_hashGenerator, _T, _SA, pattern);
    } else {
        boost::shared_ptr<std::vector<saidx_t> > result =
            boost::shared_ptr<std::vector<saidx_t> >(new std::vector<saidx_t>);
        return result;
    }
}


