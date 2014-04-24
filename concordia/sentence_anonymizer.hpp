#ifndef SENTENCE_ANONYMIZER_HDR
#define SENTENCE_ANONYMIZER_HDR

#include <string>
#include "concordia/common/config.hpp"
#include "concordia/regex_replacement.hpp"
#include "concordia/concordia_config.hpp"
#include "concordia/concordia_exception.hpp"
#include <boost/shared_ptr.hpp>
#include <boost/ptr_container/ptr_vector.hpp>


/*!
  Class for anonymizing sentence before adding to index.

*/

using namespace std;

class SentenceAnonymizer {
public:
    explicit SentenceAnonymizer(boost::shared_ptr<ConcordiaConfig> config)
                                                 throw(ConcordiaException);

    /*! Destructor.
    */
    virtual ~SentenceAnonymizer();
    
    string anonymize(const string & sentence);

private:

    boost::ptr_vector<RegexReplacement> _namedEntities;

    boost::shared_ptr<RegexReplacement> _stopWords;
    
    boost::shared_ptr<RegexReplacement> _stopSymbols;
    
    boost::shared_ptr<RegexReplacement> _spaceSymbols;    
};

#endif
