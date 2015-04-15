#ifndef TEST_RESOURCES_MANAGER_HDR
#define TEST_RESOURCES_MANAGER_HDR

#include <boost/shared_ptr.hpp>
#include <string>

#include "concordia/common/config.hpp"

class TestResourcesManager {
public:
    static std::string getPuddleFilePath(const std::string & filename);

    static std::string getTestConcordiaConfigFilePath(const std::string & filename);

	static std::string getProdConcordiaConfigFilePath(const std::string & filename);

    static std::string getTestFilePath(const std::string & module, const std::string & filename);

};

#endif

