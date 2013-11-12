#ifndef WORD_MAP_HDR
#define WORD_MAP_HDR

#include <string>
#include <map>
#include "concordia/concordia_exception.hpp"


/*!
  Class for generating a sentence hash.

*/

using namespace std;

class WordMap {
public:
    explicit WordMap() throw(ConcordiaException);
   
    /*! Destructor.
    */
    virtual ~WordMap();

    int getWordCode(const string & word);

private:
    
    map<string,int> _map;
    
    int _nextFree;

};

#endif
