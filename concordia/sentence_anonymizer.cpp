#include "concordia/sentence_anonymizer.hpp"

#include "concordia/common/text_utils.hpp"
#include <boost/foreach.hpp>
#include <fstream>
#include <sstream>
#include <iostream>
#include <boost/algorithm/string.hpp>

SentenceAnonymizer::SentenceAnonymizer(
                        boost::shared_ptr<ConcordiaConfig> config)
                                         throw(ConcordiaException) {
    _createNeRules(config->getNamedEntitiesFilePath());
    _createHtmlTagsRule(config->getHtmlTagsFilePath());
    _stopWords = _getMultipleReplacementRule(
                              config->getStopWordsFilePath(), "", true);
    _stopSymbols = _getMultipleReplacementRule(
                              config->getStopSymbolsFilePath(), "");
    _spaceSymbols = _getMultipleReplacementRule(
                              config->getSpaceSymbolsFilePath(), " ");
}

SentenceAnonymizer::~SentenceAnonymizer() {
}

string SentenceAnonymizer::anonymize(const string & sentence) {
    string result = sentence;

    result = _htmlTags->apply(result);

    BOOST_FOREACH(RegexReplacement & neRule, _namedEntities) {
        result = neRule.apply(result);
    }

    result = TextUtils::getInstance().toLowerCase(result);

    result = _stopWords->apply(result);
    result = _stopSymbols->apply(result);
    result = _spaceSymbols->apply(result);

    return result;
}

void SentenceAnonymizer::_createNeRules(string & namedEntitiesPath) {
    if (boost::filesystem::exists(namedEntitiesPath)) {
        string line;
        ifstream neFile(namedEntitiesPath.c_str());
        if (neFile.is_open()) {
            int lineCounter = 0;
            while (getline(neFile, line)) {
                lineCounter++;
                boost::shared_ptr<vector<string> >
                                 tokenTexts(new vector<string>());
                boost::split(*tokenTexts, line, boost::is_any_of(" "),
                             boost::token_compress_on);
                if (tokenTexts->size() != 2) {
                    stringstream ss;
                    ss << "Invalid line: " << lineCounter
                       << " in NE file: " << namedEntitiesPath;
                    throw ConcordiaException(ss.str());
                } else {
                    _namedEntities.push_back(new RegexReplacement(
                                tokenTexts->at(0), tokenTexts->at(1)));
                }
            }
            neFile.close();
        } else {
            throw ConcordiaException("Unable to read named entities file.");
        }
    } else {
        throw ConcordiaException("No named entities file.");
    }
}

void SentenceAnonymizer::_createHtmlTagsRule(string & htmlTagsPath) {
    string tagsExpression = "<\\/?(";
    if (boost::filesystem::exists(htmlTagsPath)) {
        string line;
        ifstream tagsFile(htmlTagsPath.c_str());
        if (tagsFile.is_open()) {
            while (getline(tagsFile, line)) {
                tagsExpression += "|";
            }
           tagsFile.close();
        } else {
            throw ConcordiaException("Unable to read html tags file.");
        }
    } else {
        throw ConcordiaException("No html tags file.");
    }
    tagsExpression = tagsExpression.substr(0, tagsExpression.size()-1);
    tagsExpression += "br).*?>";
    _htmlTags = boost::shared_ptr<RegexReplacement>(
                        new RegexReplacement(tagsExpression, "", false));
}

boost::shared_ptr<RegexReplacement>
            SentenceAnonymizer::_getMultipleReplacementRule(
                    string & filePath, string replacement, bool wholeWord) {
    string expression = "(";
    if (boost::filesystem::exists(filePath)) {
        string line;
        ifstream ruleFile(filePath.c_str());
        if (ruleFile.is_open()) {
            while (getline(ruleFile, line)) {
                if (wholeWord) {
                    expression += "\\b";
                }
                expression += line;
                if (wholeWord) {
                    expression += "\\b";
                }
                expression += "|";
            }
           ruleFile.close();
        } else {
            throw ConcordiaException("Unable to read file: "+filePath);
        }
    } else {
        throw ConcordiaException("No "+filePath+" file.");
    }
    expression = expression.substr(0, expression.size()-1);
    expression += ")";
    return boost::shared_ptr<RegexReplacement>(
                        new RegexReplacement(expression, replacement, false));
}

