#include "concordia/word_map.hpp"
#include <climits>


WordMap::WordMap() throw(ConcordiaException) {
    _nextFree = 0;
}

WordMap::~WordMap() {
}

INDEX_CHARACTER_TYPE WordMap::getWordCode(const string & word)
                                    throw(ConcordiaException) {
    if (_map.find(word) == _map.end()) {
        if (_nextFree == INDEX_CHARACTER_TYPE_MAX_VALUE) {
             throw ConcordiaException("Word map capacity limit reached!");
        }
        INDEX_CHARACTER_TYPE newCode = _nextFree;
        _map[word] = newCode;
        _nextFree++;
        return newCode;
    } else {
        return _map[word];
    }
}


