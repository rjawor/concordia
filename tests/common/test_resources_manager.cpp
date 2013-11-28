#include "test_resources_manager.hpp"

#define PUDDLE_TEST_DIRECTORY "puddle"
#define CONCORDIA_TAGSET_DIRECTORY "concordia-tagset"
#define CONCORDIA_CONFIG_DIRECTORY "concordia-config"

string TestResourcesManager::getPuddleFilePath(const string & filename) {
    string result = string(TEST_RESOURCES_DIRECTORY);
    return result + "/" + PUDDLE_TEST_DIRECTORY +  "/" + filename;
}


string TestResourcesManager::getTestConcordiaConfigFilePath(const string & filename) {
    string result = string(TEST_RESOURCES_DIRECTORY);
    return result + "/" + CONCORDIA_CONFIG_DIRECTORY + "/" + filename;
}

string TestResourcesManager::getProdConcordiaConfigFilePath(const string & filename) {
    string result = string(PROD_RESOURCES_DIRECTORY);
    return result + "/" + CONCORDIA_CONFIG_DIRECTORY + "/" + filename;
}

string TestResourcesManager::getTestFilePath(const string & module, const string & filename) {
    string result = string(TEST_RESOURCES_DIRECTORY);
    return result + "/" + module + "/" + filename;
}

