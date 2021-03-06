#include "tests/unit-tests/unit_tests_globals.hpp"

#include "concordia/concordia_config.hpp"
#include "tests/common/test_resources_manager.hpp"

#include <string>
#include <list>
#include <boost/algorithm/string/predicate.hpp>

BOOST_AUTO_TEST_SUITE(concordia_config)

BOOST_AUTO_TEST_CASE( ConfigParameters )
{
    ConcordiaConfig config(TestResourcesManager::getTestConcordiaConfigFilePath("concordia-mock.cfg"));
    BOOST_CHECK_EQUAL( config.getPuddleTagsetFilePath() , "puddle/tagset.txt" );
    BOOST_CHECK_EQUAL( config.getWordMapFilePath() , "/tmp/wm.bin" );
    BOOST_CHECK_EQUAL( config.getHashedIndexFilePath() , "/tmp/hi.bin" );
    BOOST_CHECK_EQUAL( config.getMarkersFilePath() , "/tmp/ma.bin" );
    BOOST_CHECK_EQUAL( config.getSuffixArrayFilePath() , "/tmp/sa.bin" );
    BOOST_CHECK_EQUAL( config.getHtmlTagsFilePath() , "/tmp/html_tags.txt" );
    BOOST_CHECK_EQUAL( config.getSpaceSymbolsFilePath() , "/tmp/space_symbols.txt" );
    BOOST_CHECK_EQUAL( config.getStopWordsFilePath() , "/tmp/stop_words.txt" );
    BOOST_CHECK_EQUAL( config.getNamedEntitiesFilePath() , "/tmp/named_entities.txt" );
    BOOST_CHECK_EQUAL( config.getStopSymbolsFilePath() , "/tmp/stop_symbols.txt" );
}

BOOST_AUTO_TEST_CASE( NonexistentConfigTest )
{
    bool exceptionThrown = false;
    std::string message = "";
    try {
        ConcordiaConfig config(TestResourcesManager::getTestConcordiaConfigFilePath("foo.cfg")); 
    } catch (ConcordiaException & e) {
        exceptionThrown = true;
        message = e.what();
    }    
    BOOST_CHECK_EQUAL(exceptionThrown, true);    
    BOOST_CHECK_EQUAL(boost::starts_with(message, "I/O error reading config file"), true);    
}


BOOST_AUTO_TEST_CASE( InvalidConfigTest )
{
    bool exceptionThrown = false;
    std::string message = "";
    try {
        ConcordiaConfig config(TestResourcesManager::getTestConcordiaConfigFilePath("invalid.cfg")); 
    } catch (ConcordiaException & e) {
        exceptionThrown = true;
        message = e.what();
    }    
    BOOST_CHECK_EQUAL(exceptionThrown, true);    
    BOOST_CHECK_EQUAL(boost::starts_with(message, "Error parsing config file"), true);    
}




BOOST_AUTO_TEST_SUITE_END()
