#include "test_resources_manager.hpp"

#define PUDDLE_TEST_DIRECTORY "puddle"
#define CONCORDIA_TAGSET_DIRECTORY "concordia-tagset"
#define CONCORDIA_CONFIG_DIRECTORY "concordia-config"

std::string TestResourcesManager::getPuddleFilePath(const std::string & filename) {
    std::string result = std::string(TEST_RESOURCES_DIRECTORY);
    return result + "/" + PUDDLE_TEST_DIRECTORY +  "/" + filename;
}


std::string TestResourcesManager::getTestConcordiaConfigFilePath(const std::string & filename) {
    std::string result = std::string(TEST_RESOURCES_DIRECTORY);
    return result + "/" + CONCORDIA_CONFIG_DIRECTORY + "/" + filename;
}

std::string TestResourcesManager::getProdConcordiaConfigFilePath(const std::string & filename) {
    std::string result = std::string(PROD_RESOURCES_DIRECTORY);
    return result + "/" + CONCORDIA_CONFIG_DIRECTORY + "/" + filename;
}

std::string TestResourcesManager::getTestFilePath(const std::string & module, const std::string & filename) {
    std::string result = std::string(TEST_RESOURCES_DIRECTORY);
    return result + "/" + module + "/" + filename;
}

