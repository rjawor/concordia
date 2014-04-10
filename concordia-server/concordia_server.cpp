#include "concordia-server/concordia_server.hpp"

#include <sstream>
#include <concordia/example.hpp>
#include <concordia/substring_occurence.hpp>
#include <boost/ptr_container/ptr_vector.hpp>
#include <boost/foreach.hpp>


ConcordiaServer::ConcordiaServer(const std::string & configFilePath)
                                         throw(ConcordiaException) {
    _concordia = boost::shared_ptr<Concordia> (
                            new Concordia(configFilePath));

}

ConcordiaServer::~ConcordiaServer() {
}

string ConcordiaServer::handleRequest(string & requestString) {
    stringstream ss;
    try {
        ss << "Content-type: text/html\r\n"
             << "\r\n"
             << "<html>\n"
             << "  <head>\n"
             << "    <title>Hello, World!</title>\n"
             << "  </head>\n"
             << "  <body>\n"
             << "    <h1>Hello, World!</h1>\n"
             << "    The concordia version is: "<< _concordia->getVersion() << "\n"
             << "    <h1>Input data:</h1>\n"
             << requestString;

        ss << "    <h1>Adding content as example:</h1>\n";

        Example example1(requestString, 0);
        Example example2("Ala ma kota", 1);
        Example example3("Marysia nie ma kota chyba", 2);
        _concordia->addExample(example1);
        _concordia->addExample(example2);
        _concordia->addExample(example3);

        _concordia->refreshSAfromRAM();

        ss << "    <h1>Searching ma kota:</h1>\n";
        boost::ptr_vector<SubstringOccurence> result =
                                 _concordia->simpleSearch("ma kota");
        BOOST_FOREACH(SubstringOccurence occurence, result) {
            ss << "\t\tfound match in sentence number: "
                      << occurence.getId() << "<br/><br/>";
        }                                 
        ss << "  </body>\n"
             << "</html>\n";
             
    } catch (ConcordiaException & e) {
        ss << "<h1> Concordia error:" << e.what() << "</h1>";
        
    }
    return ss.str();

}
