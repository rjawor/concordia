#include <boost/filesystem.hpp>
#include "tests/unit-tests/unit_tests_globals.hpp"
#include <string>
#include <sstream>

#include <boost/shared_ptr.hpp>
#include "concordia/common/config.hpp"
#include "concordia/sentence_anonymizer.hpp"
#include "tests/common/test_resources_manager.hpp"


using namespace std;

BOOST_AUTO_TEST_SUITE(sentence_anonymizer)

BOOST_AUTO_TEST_CASE( NETest )
{
    boost::shared_ptr<ConcordiaConfig> config(new ConcordiaConfig(TestResourcesManager::getTestConcordiaConfigFilePath("concordia.cfg")));
    SentenceAnonymizer anonymizer(config);
    
    
    string sentence = "Date: 12.04.2012, mail: test@example.com, number: 5.34";
    BOOST_CHECK_EQUAL(anonymizer.anonymize(sentence),"date  ne_date mail  ne_email number  ne_number");
}

BOOST_AUTO_TEST_CASE( HtmlTagsTest )
{
    boost::shared_ptr<ConcordiaConfig> config(new ConcordiaConfig(TestResourcesManager::getTestConcordiaConfigFilePath("concordia.cfg")));
    SentenceAnonymizer anonymizer(config);
    
    
    string sentence = "<a href='http://wp.pl'>link</a> and <b>bold</b> and newline <br/>";
    BOOST_CHECK_EQUAL(anonymizer.anonymize(sentence),"link and bold and newline ");
    
}

BOOST_AUTO_TEST_CASE( StopWordsTest )
{
    boost::shared_ptr<ConcordiaConfig> config(new ConcordiaConfig(TestResourcesManager::getTestConcordiaConfigFilePath("concordia.cfg")));
    SentenceAnonymizer anonymizer(config);
    
    
    string sentence = "Aczkolwiek nie wiem, czy to konieczne";
    BOOST_CHECK_EQUAL(anonymizer.anonymize(sentence),"  wiem   konieczne");
    
}

BOOST_AUTO_TEST_CASE( StopSymbolsTest )
{
    boost::shared_ptr<ConcordiaConfig> config(new ConcordiaConfig(TestResourcesManager::getTestConcordiaConfigFilePath("concordia.cfg")));
    SentenceAnonymizer anonymizer(config);
    
    
    string sentence = "xxx, . xxx  # xx $xx@ xx";
    BOOST_CHECK_EQUAL(anonymizer.anonymize(sentence),"xxx  xxx   xx xx xx");
    
}

BOOST_AUTO_TEST_CASE( SpaceSymbolsTest )
{
    boost::shared_ptr<ConcordiaConfig> config(new ConcordiaConfig(TestResourcesManager::getTestConcordiaConfigFilePath("concordia.cfg")));
    SentenceAnonymizer anonymizer(config);
    
    
    string sentence = "xxx-xxx xx|xx";
    BOOST_CHECK_EQUAL(anonymizer.anonymize(sentence),"xxx xxx xx xx");
    
}

BOOST_AUTO_TEST_CASE( WeirdSentenceTest )
{
    boost::shared_ptr<ConcordiaConfig> config(new ConcordiaConfig(TestResourcesManager::getTestConcordiaConfigFilePath("concordia.cfg")));
    SentenceAnonymizer anonymizer(config);
    
    string sentence = "Sony | DXC-M7PKDXC-M7PDXC-M7PHDXC-M7PK/1DXC-M7P/1DXC-M7PH/1DXC-327PKDXC-327PLDXC-327PHDXC-327APKDXC-327APLDXC-327AHDXC-537PKDXC-537PLDXC-537PHDXC-537APKDXC-537APLDXC-537APHEVW-537PKEVW-327PKDXC-637PDXC-637PKDXC-637PLDXC-637PHPVW-637PKPVW-637PLDXC-D30PFDXC-D30PKDXC-D30PLDXC-D30PHDSR-130PFDSR-130PKDSR-130PLPVW-D30PFPVW-D30PKPVW-D30PLDXC-327BPFDXC-327BPKDXC-327BPLDXC-327BPHDXC-D30WSPDXC-D35PHDXC-D35PLDXC-D35PKDXC-D35WSPLDSR-135PL | DXF-3000CEDXF-325CEDXF-501CEDXF-M3CEDXF-M7CEDXF-40CEDXF-40ACEDXF-50CEDXF-601CEDXF-40BCEDXF-50BCEDXF-701CEDXF-WSCEDXF-801CEHDVF-C30W | CCU-M3PCCU-M5PCCU-M7PCUU-M5AP | RM-M7GRM-M7E | — | CA-325PCA-325APCA-325BCA-327PCA-537PCA-511CA-512PCA-513VCT-U14 |";
    BOOST_CHECK_EQUAL(anonymizer.anonymize(sentence),"sony   dxc mne_numberpkdxc mne_numberpdxc mne_numberphdxc mne_numberpk ne_numberdxc mne_numberp ne_numberdxc mne_numberph ne_numberdxc ne_numberpkdxc ne_numberpldxc ne_numberphdxc ne_numberapkdxc ne_numberapldxc ne_numberahdxc ne_numberpkdxc ne_numberpldxc ne_numberphdxc ne_numberapkdxc ne_numberapldxc ne_numberaphevw ne_numberpkevw ne_numberpkdxc ne_numberpdxc ne_numberpkdxc ne_numberpldxc ne_numberphpvw ne_numberpkpvw ne_numberpldxc dne_numberpfdxc dne_numberpkdxc dne_numberpldxc dne_numberphdsr ne_numberpfdsr ne_numberpkdsr ne_numberplpvw dne_numberpfpvw dne_numberpkpvw dne_numberpldxc ne_numberbpfdxc ne_numberbpkdxc ne_numberbpldxc ne_numberbphdxc dne_numberwspdxc dne_numberphdxc dne_numberpldxc dne_numberpkdxc dne_numberwspldsr ne_numberpl   dxf ne_numbercedxf ne_numbercedxf ne_numbercedxf mne_numbercedxf mne_numbercedxf ne_numbercedxf ne_numberacedxf ne_numbercedxf ne_numbercedxf ne_numberbcedxf ne_numberbcedxf ne_numbercedxf wscedxf ne_numbercehdvf cne_numberw   ccu mne_numberpccu mne_numberpccu mne_numberpcuu mne_numberap   rm mne_numbergrm mne_numbere   —   ca ne_numberpca ne_numberapca ne_numberbca ne_numberpca ne_numberpca ne_numberca ne_numberpca ne_numbervct une_number  ");
    
}

BOOST_AUTO_TEST_SUITE_END()
