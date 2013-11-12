#ifndef CONCORDIA_HDR
#define CONCORDIA_HDR

#include <string>
#include <boost/shared_ptr.hpp>

#include "concordia/concordia_config.hpp"

/*!
  The Concordia class is the main access point to the library.

*/

class Concordia {
public:
    /*! Constructor.
      \param configFilePath path to the Concordia configuration file
      \throws ConcordiaException
    */
    explicit Concordia(const std::string & configFilePath)
                                         throw(ConcordiaException);
    /*! Destructor.
    */
    virtual ~Concordia();

    /*! Getter for version.
      \returns version of the Concordia library.
    */
    std::string & getVersion();

private:
    static std::string _libraryVersion;

    boost::shared_ptr<ConcordiaConfig> _config;
};

#endif
