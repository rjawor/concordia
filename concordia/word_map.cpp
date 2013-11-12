#include "concordia/word_map.hpp"


WordMap::WordMap() throw(ConcordiaException) {
    _nextFree = 0;
}

WordMap::~WordMap() {
}

int WordMap::getWordCode(const string & word) {
    
    if (_map.find(word) == _map.end() ) {
        int newCode = _nextFree;
        _map[word] = newCode;
        _nextFree++;
        return newCode;
    } else {
        return _map[word];      
    }

}


