#ifndef TEST_RESOURCES_MANAGER_HDR
#define TEST_RESOURCES_MANAGER_HDR

#include <boost/shared_ptr.hpp>
#include <string>

#include "concordia/common/config.hpp"

using namespace std;

class TestResourcesManager {
public:
    static string getPuddleFilePath(const string & filename);

    static string getTestConcordiaConfigFilePath(const string & filename);

	static string getProdConcordiaConfigFilePath(const string & filename);

    static string getTestFilePath(const string & module, const string & filename);

};

#endif

