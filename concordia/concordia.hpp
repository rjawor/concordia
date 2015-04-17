#ifndef CONCORDIA_HDR
#define CONCORDIA_HDR

#include <string>
#include <vector>
#include <boost/shared_ptr.hpp>
#include <boost/filesystem.hpp>

#include "concordia/common/config.hpp"
#include "concordia/example.hpp"
#include "concordia/substring_occurence.hpp"
#include "concordia/concordia_config.hpp"
#include "concordia/concordia_index.hpp"
#include "concordia/index_searcher.hpp"
#include "concordia/concordia_search_result.hpp"
#include "concordia/anubis_search_result.hpp"
#include <divsufsort.h>


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

    void addExample(const Example & example) throw(ConcordiaException);

    void addAllExamples(const std::vector<Example> & examples)
                                                   throw(ConcordiaException);

    std::vector<SubstringOccurence> simpleSearch(const std::string & pattern)
                                                 throw(ConcordiaException);

    std::vector<AnubisSearchResult> anubisSearch(const std::string & pattern)
                                                 throw(ConcordiaException);

    boost::shared_ptr<ConcordiaSearchResult> concordiaSearch(
                                                 const std::string & pattern)
                                                 throw(ConcordiaException);

    void loadRAMIndexFromDisk() throw(ConcordiaException);

    void refreshSAfromRAM() throw(ConcordiaException);

private:
    void _initializeIndex() throw(ConcordiaException);

    static std::string _libraryVersion;

    boost::shared_ptr<ConcordiaConfig> _config;

    boost::shared_ptr<ConcordiaIndex> _index;

    boost::shared_ptr<IndexSearcher> _searcher;

    boost::shared_ptr<HashGenerator> _hashGenerator;

    boost::shared_ptr<std::vector<sauchar_t> > _T;

    boost::shared_ptr<std::vector<saidx_t> > _SA;

    boost::shared_ptr<std::vector<SUFFIX_MARKER_TYPE> > _markers;
};

#endif
