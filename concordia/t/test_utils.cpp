#include "tests/unit-tests/unit_tests_globals.hpp"
#include "concordia/common/utils.hpp"
#include "concordia/common/config.hpp"
#include "tests/common/test_resources_manager.hpp"
#include <boost/filesystem.hpp>

#include "divsufsort.h"

BOOST_AUTO_TEST_SUITE(utils)

BOOST_AUTO_TEST_CASE( WriteReadSingleCharacter )
{
    std::ofstream testFileOutput;
    testFileOutput.open(TestResourcesManager::getTestFilePath("temp","temp_file.bin").c_str(),
                                   std::ios::out|std::ios::binary);
    INDEX_CHARACTER_TYPE testCharacter = 123456789; //in hex: 75BCD15
    Utils::writeIndexCharacter(testFileOutput,testCharacter);
    testFileOutput.close();
    
    std::ifstream testFileInput;
    testFileInput.open(TestResourcesManager::getTestFilePath("temp","temp_file.bin").c_str(),std::ios::in|std::ios::binary);
    INDEX_CHARACTER_TYPE retrievedCharacter = Utils::readIndexCharacter(testFileInput);
    BOOST_CHECK_EQUAL(retrievedCharacter, testCharacter);
    testFileInput.close();
    
    boost::filesystem::remove(TestResourcesManager::getTestFilePath("temp","temp_file.bin"));     
}

BOOST_AUTO_TEST_CASE( IndexVectorToSaucharArray )
{
    std::vector<INDEX_CHARACTER_TYPE> hash;
    hash.push_back(123456789);         // in hex: 75BCD15
                                       // in memory:  15  cd  5b  07
                                       // in memory DEC:  21 205  91   7 

    hash.push_back(987654321);         // in hex: 3ADE68B1
                                       // in memory:  b1  68  de  3a
                                       // in memory DEC: 177 104 222  58         
    sauchar_t * dataArray = Utils::indexVectorToSaucharArray(hash);

    std::vector<INDEX_CHARACTER_TYPE> result;
    for (int i=0;i<8;i++) {
        INDEX_CHARACTER_TYPE a = dataArray[i];
        result.push_back(a);    
    }
    
    std::vector<INDEX_CHARACTER_TYPE> expected;
    expected.push_back(21);
    expected.push_back(205);
    expected.push_back(91);
    expected.push_back(7);
    expected.push_back(177);
    expected.push_back(104);
    expected.push_back(222);
    expected.push_back(58);

    BOOST_CHECK_EQUAL_COLLECTIONS(result.begin(), result.end(), expected.begin(), expected.end());      
}

BOOST_AUTO_TEST_CASE( IndexVectorToSaucharVector )
{
    std::vector<INDEX_CHARACTER_TYPE> hash;
    hash.push_back(123456789);         // in hex: 75BCD15
                                       // in memory:  15  cd  5b  07
                                       // in memory DEC:  21 205  91   7 

    hash.push_back(987654321);         // in hex: 3ADE68B1
                                       // in memory:  b1  68  de  3a
                                       // in memory DEC: 177 104 222  58         
    std::vector<sauchar_t> result = Utils::indexVectorToSaucharVector(hash);
    
    std::vector<sauchar_t> expected;
    expected.push_back(21);
    expected.push_back(205);
    expected.push_back(91);
    expected.push_back(7);
    expected.push_back(177);
    expected.push_back(104);
    expected.push_back(222);
    expected.push_back(58);

    BOOST_CHECK_EQUAL_COLLECTIONS(result.begin(), result.end(), expected.begin(), expected.end());      
}

BOOST_AUTO_TEST_CASE( MaxSentenceSize )
{
    BOOST_CHECK_EQUAL(Utils::maxSentenceSize, 65536);
}

//The below examples use the following marker:
//00000000|00000000|00000000|00000011|00000000|00000101|00000000|00000111

BOOST_AUTO_TEST_CASE( CreateMarker )
{
    BOOST_CHECK_EQUAL(Utils::createMarker(3,5,7), 12885229575);
}

BOOST_AUTO_TEST_CASE( GetIdFromMarker )
{
    BOOST_CHECK_EQUAL(Utils::getIdFromMarker(12885229575), 3);
}

BOOST_AUTO_TEST_CASE( GetOffsetFromMarker )
{
    BOOST_CHECK_EQUAL(Utils::getOffsetFromMarker(12885229575), 5);
}

BOOST_AUTO_TEST_CASE( GetLengthFromMarker )
{
    BOOST_CHECK_EQUAL(Utils::getLengthFromMarker(12885229575), 7);
}


BOOST_AUTO_TEST_SUITE_END()
