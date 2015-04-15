#ifndef SENTENCE_ANONYMIZER_HDR
#define SENTENCE_ANONYMIZER_HDR

#include <string>
#include <vector>
#include "concordia/common/config.hpp"
#include "concordia/regex_replacement.hpp"
#include "concordia/concordia_config.hpp"
#include "concordia/concordia_exception.hpp"
#include <boost/shared_ptr.hpp>
#include <boost/filesystem.hpp>


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
    void _createNeRules(string & namedEntitiesPath);

    void _createHtmlTagsRule(string & htmlTagsPath);

    boost::shared_ptr<RegexReplacement> _getMultipleReplacementRule(
                                                string & filePath,
                                                string replacement,
                                                bool wholeWord = false);

    vector<RegexReplacement> _namedEntities;

    boost::shared_ptr<RegexReplacement> _htmlTags;

    boost::shared_ptr<RegexReplacement> _stopWords;

    boost::shared_ptr<RegexReplacement> _stopSymbols;

    boost::shared_ptr<RegexReplacement> _spaceSymbols;
};

#endif
