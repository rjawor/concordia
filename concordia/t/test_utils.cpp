#include "tests/unit-tests/unit_tests_globals.hpp"
#include "concordia/common/utils.hpp"
#include "concordia/common/config.hpp"
#include "tests/common/test_resources_manager.hpp"
#include "build/libdivsufsort/include/divsufsort.h"
#include <boost/filesystem.hpp>

#include <string>

using namespace std;

BOOST_AUTO_TEST_SUITE(utils)

BOOST_AUTO_TEST_CASE( UtilsTest1 )
{
    ofstream testFileOutput;
    testFileOutput.open(TestResourcesManager::getTestFilePath("temp","temp_file.bin").c_str(),
                                   ios::out|ios::binary);
    INDEX_CHARACTER_TYPE testCharacter = 123456789; //in hex: 75BCD15
    Utils::writeIndexCharacter(testFileOutput,testCharacter);
    testFileOutput.close();
    
    ifstream testFileInput;
    testFileInput.open(TestResourcesManager::getTestFilePath("temp","temp_file.bin").c_str(),ios::in|ios::binary);
    INDEX_CHARACTER_TYPE retrievedCharacter = Utils::readIndexCharacter(testFileInput);
    BOOST_CHECK_EQUAL(retrievedCharacter, testCharacter);
    testFileInput.close();
    
    boost::filesystem::remove(TestResourcesManager::getTestFilePath("temp","temp_file.bin"));     
}

BOOST_AUTO_TEST_CASE( UtilsTest2 )
{
    ofstream testFileOutput;
    testFileOutput.open(TestResourcesManager::getTestFilePath("temp","temp_file.bin").c_str(),
                                   ios::out|ios::binary);
    Utils::writeIndexCharacter(testFileOutput,123456789); //in hex: 75BCD15
                                                          //in memory:  15  cd  5b  07
                                                          //   in DEC:  21 205  91   7 
                                                          
    Utils::writeIndexCharacter(testFileOutput,987654321); //in hex: 3ADE68B1
                                                          //in memory:  b1  68  de  3a
                                                          //   in DEC: 177 104 222  58 
    testFileOutput.close();
    
    sauchar_t * dataArray = new sauchar_t[8];
    ifstream testFileInput;
    testFileInput.open(TestResourcesManager::getTestFilePath("temp","temp_file.bin").c_str(),ios::in|ios::binary);
    
    INDEX_CHARACTER_TYPE retrievedCharacter1 = Utils::readIndexCharacter(testFileInput);
    BOOST_CHECK_EQUAL(retrievedCharacter1, 123456789);    
    Utils::insertCharToSaucharArray(dataArray, retrievedCharacter1, 0);

    INDEX_CHARACTER_TYPE retrievedCharacter2 = Utils::readIndexCharacter(testFileInput);
    BOOST_CHECK_EQUAL(retrievedCharacter2, 987654321);
    Utils::insertCharToSaucharArray(dataArray, retrievedCharacter2, 4);

    testFileInput.close();    

    vector<INDEX_CHARACTER_TYPE> expected;
    expected.push_back(21);
    expected.push_back(205);
    expected.push_back(91);
    expected.push_back(7);
    expected.push_back(177);
    expected.push_back(104);
    expected.push_back(222);
    expected.push_back(58);

    vector<INDEX_CHARACTER_TYPE> result;
    for (int i=0;i<8;i++) {
        INDEX_CHARACTER_TYPE a = dataArray[i];
        result.push_back(a);    
    }

    boost::filesystem::remove(TestResourcesManager::getTestFilePath("temp","temp_file.bin"));

    BOOST_CHECK_EQUAL_COLLECTIONS(result.begin(), result.end(), expected.begin(), expected.end());      
}

BOOST_AUTO_TEST_CASE( UtilsTest3 )
{
    vector<INDEX_CHARACTER_TYPE> hash;
    hash.push_back(123456789);
    hash.push_back(987654321);
        
    sauchar_t * dataArray = Utils::indexVectorToSaucharArray(hash);

    vector<INDEX_CHARACTER_TYPE> result;
    for (int i=0;i<8;i++) {
        INDEX_CHARACTER_TYPE a = dataArray[i];
        result.push_back(a);    
    }
    
    vector<INDEX_CHARACTER_TYPE> expected;
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

/*
BOOST_AUTO_TEST_CASE( UtilsTest4 )
{
    ofstream testFileOutput;
    testFileOutput.open(TestResourcesManager::getTestFilePath("temp","temp_file.bin").c_str(),
                                   ios::out|ios::binary);
    Utils::writeIndexCharacter(testFileOutput,123456789); //in hex: 75BCD15
                                                          //in memory:  15  cd  5b  07
                                                          //   in DEC:  21 205  91   7 
                                                          
    Utils::writeIndexCharacter(testFileOutput,987654321); //in hex: 3ADE68B1
                                                          //in memory:  b1  68  de  3a
                                                          //   in DEC: 177 104 222  58 
    testFileOutput.close();
    
    sauchar_t * dataArray = Utils::readIndexFromFile(
    ifstream testFileInput;
    testFileInput.open(TestResourcesManager::getTestFilePath("temp","temp_file.bin").c_str(),ios::in|ios::binary);
    
    INDEX_CHARACTER_TYPE retrievedCharacter1 = Utils::readIndexCharacter(testFileInput);
    BOOST_CHECK_EQUAL(retrievedCharacter1, 123456789);    
    Utils::insertCharToSaucharArray(dataArray, retrievedCharacter1, 0);

    INDEX_CHARACTER_TYPE retrievedCharacter2 = Utils::readIndexCharacter(testFileInput);
    BOOST_CHECK_EQUAL(retrievedCharacter2, 987654321);
    Utils::insertCharToSaucharArray(dataArray, retrievedCharacter2, 4);

    testFileInput.close();    

    vector<INDEX_CHARACTER_TYPE> expected;
    expected.push_back(21);
    expected.push_back(205);
    expected.push_back(91);
    expected.push_back(7);
    expected.push_back(177);
    expected.push_back(104);
    expected.push_back(222);
    expected.push_back(58);

    vector<INDEX_CHARACTER_TYPE> result;
    for (int i=0;i<8;i++) {
        INDEX_CHARACTER_TYPE a = dataArray[i];
        result.push_back(a);    
    }

    boost::filesystem::remove(TestResourcesManager::getTestFilePath("temp","temp_file.bin"));

    BOOST_CHECK_EQUAL_COLLECTIONS(result.begin(), result.end(), expected.begin(), expected.end());      
}
*/



BOOST_AUTO_TEST_SUITE_END()
