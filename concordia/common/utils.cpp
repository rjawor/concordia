#include "concordia/common/utils.hpp"

Utils::Utils() {
}

Utils::~Utils() {
}

void Utils::writeIndexCharacter(ofstream & file,
                                      INDEX_CHARACTER_TYPE character) {
    file.write(reinterpret_cast<char *>(&character), sizeof(character));
}

INDEX_CHARACTER_TYPE Utils::readIndexCharacter(ifstream & file) {
    INDEX_CHARACTER_TYPE character;
    file.read(reinterpret_cast<char *>(&character), sizeof(character));
    return character;
}

sauchar_t * Utils::indexVectorToSaucharArray(
                     boost::shared_ptr<vector<INDEX_CHARACTER_TYPE> > input) {
    const int kArraySize = input->size()*sizeof(INDEX_CHARACTER_TYPE);
    sauchar_t * patternArray =
                    new sauchar_t[kArraySize];
    int pos = 0;
    for (vector<INDEX_CHARACTER_TYPE>::iterator it = input->begin();
                                          it != input->end(); ++it) {
        _insertCharToSaucharArray(patternArray, *it, pos);
        pos += sizeof(INDEX_CHARACTER_TYPE);
    }
    return patternArray;
}

void Utils::appendCharToSaucharVector(
                             boost::shared_ptr<std::vector<sauchar_t> > vector,
                             INDEX_CHARACTER_TYPE character) {
    sauchar_t * characterArray = reinterpret_cast<sauchar_t *>(&character);
    for (int i = 0; i < sizeof(character); i++) {
        vector->push_back(characterArray[i]);
    }
}

void Utils::_insertCharToSaucharArray(sauchar_t * array,
                                 INDEX_CHARACTER_TYPE character, int pos) {
    sauchar_t * characterArray = reinterpret_cast<sauchar_t *>(&character);
    for (int i = pos; i < pos+sizeof(character); i++) {
        array[i] = characterArray[i-pos];
    }
}

