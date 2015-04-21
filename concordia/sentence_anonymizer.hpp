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

class SentenceAnonymizer {
public:
    explicit SentenceAnonymizer(boost::shared_ptr<ConcordiaConfig> config)
                                                 throw(ConcordiaException);

    /*! Destructor.
    */
    virtual ~SentenceAnonymizer();

    std::string anonymize(const std::string & sentence);

private:
    void _createNeRules(std::string & namedEntitiesPath);

    void _createHtmlTagsRule(std::string & htmlTagsPath);

    boost::shared_ptr<RegexReplacement> _getMultipleReplacementRule(
                                             std::string & filePath,
                                             std::string replacement,
                                             bool wholeWord = false);

    std::vector<RegexReplacement> _namedEntities;

    boost::shared_ptr<RegexReplacement> _htmlTags;

    bool _stopWordsEnabled;

    boost::shared_ptr<RegexReplacement> _stopWords;

    boost::shared_ptr<RegexReplacement> _stopSymbols;

    boost::shared_ptr<RegexReplacement> _spaceSymbols;
};

#endif
