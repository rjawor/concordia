#ifndef CONCORDIA_HDR
#define CONCORDIA_HDR

#include <string>
#include <vector>
#include <boost/shared_ptr.hpp>

#include "concordia/concordia_config.hpp"
#include "concordia/concordia_index.hpp"
#include "concordia/index_searcher.hpp"
#include "build/libdivsufsort/include/divsufsort.h"


/*!
  The Concordia class is the main access point to the library.

*/

class Concordia {
public:
    /*! Constructor.
      \param configFilePath path to the Concordia configuration file
      \throws ConcordiaException
    */
    explicit Concordia(const std::string & configFilePath)
                                         throw(ConcordiaException);
    /*! Destructor.
    */
    virtual ~Concordia();

    /*! Getter for version.
      \returns version of the Concordia library.
    */
    std::string & getVersion();

    void addSentence(const std::string & sentence) throw(ConcordiaException);

    void addAllSentences(vector<std::string> & sentences)
                                                   throw(ConcordiaException);

    void generateIndex() throw(ConcordiaException);

    void loadIndex() throw(ConcordiaException);

    std::vector<saidx_t> simpleSearch(const std::string & pattern)
                                      throw(ConcordiaException);

private:
    static std::string _libraryVersion;

    boost::shared_ptr<ConcordiaConfig> _config;

    boost::shared_ptr<ConcordiaIndex> _index;

    boost::shared_ptr<IndexSearcher> _searcher;
};

#endif
