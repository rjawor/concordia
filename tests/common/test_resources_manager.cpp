#include "test_resources_manager.hpp"

#define PUDDLE_TEST_DIRECTORY "puddle"
#define CONCORDIA_TAGSET_DIRECTORY "concordia-tagset"
#define CONCORDIA_CONFIG_DIRECTORY "concordia-config"
#define CONCORDIA_INDEX_DIRECTORY "concordia-index"

string TestResourcesManager::getPuddleFilePath(const string & filename) {
    string result = string(TEST_RESOURCES_DIRECTORY);
    return result + "/" + PUDDLE_TEST_DIRECTORY +  "/" + filename;
}


string TestResourcesManager::getTestConcordiaConfigFilePath(const string & filename) {
    string result = string(TEST_RESOURCES_DIRECTORY);
    return result + "/" + CONCORDIA_CONFIG_DIRECTORY + "/" + filename;
}

string TestResourcesManager::getTestWordMapFilePath(const string & filename) {
    string result = string(TEST_RESOURCES_DIRECTORY);
    return result + "/" + CONCORDIA_INDEX_DIRECTORY + "/" + filename;
}

string TestResourcesManager::getTestHashIndexFilePath(const string & filename) {
    string result = string(TEST_RESOURCES_DIRECTORY);
    return result + "/" + CONCORDIA_INDEX_DIRECTORY + "/" + filename;
}

string TestResourcesManager::getTestSuffixArrayFilePath() {
    string result = string(TEST_RESOURCES_DIRECTORY);
    return result + "/" + CONCORDIA_INDEX_DIRECTORY + "/test_SA.bin";
}

string TestResourcesManager::getProdConcordiaConfigFilePath(const string & filename) {
    string result = string(PROD_RESOURCES_DIRECTORY);
    return result + "/" + CONCORDIA_CONFIG_DIRECTORY + "/" + filename;
}

