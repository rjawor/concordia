#include "concordia/concordia.hpp"
#include "concordia/common/config.hpp"

#include <sstream>

// ===========================================

std::string _createLibraryVersion();

// ===========================================

std::string Concordia::_libraryVersion = _createLibraryVersion();

// ===========================================

Concordia::Concordia(const string & configFilePath) throw(ConcordiaException) {
    boost::shared_ptr<ConcordiaConfig> _config(
                                new ConcordiaConfig(configFilePath));
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

