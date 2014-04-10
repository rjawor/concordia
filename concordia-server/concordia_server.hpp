#ifndef CONCORDIA_SERVER_HDR
#define CONCORDIA_SERVER_HDR

#include <string>
#include <concordia/concordia_exception.hpp>
#include <boost/shared_ptr.hpp>
#include <concordia/concordia.hpp>


using namespace std;

class ConcordiaServer {
public:
    /*! Constructor.
      \param configFilePath path to the Concordia configuration file
      \throws ConcordiaException
    */
    explicit ConcordiaServer(const std::string & configFilePath)
                                         throw(ConcordiaException);
    /*! Destructor.
    */
    virtual ~ConcordiaServer();

    string handleRequest(string & requestString);

private:
    boost::shared_ptr<Concordia> _concordia;
};

#endif
