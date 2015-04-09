#include "concordia/common/utils.hpp"
#include <math.h>

Utils::Utils() {
}

Utils::~Utils() {
}

void Utils::writeIndexCharacter(ofstream & file,
                                      INDEX_CHARACTER_TYPE character) {
    file.write(reinterpret_cast<char *>(&character), sizeof(character));
}

void Utils::writeMarker(ofstream & file,
                                      SUFFIX_MARKER_TYPE marker) {
    file.write(reinterpret_cast<char *>(&marker), sizeof(marker));
}

INDEX_CHARACTER_TYPE Utils::readIndexCharacter(ifstream & file) {
    INDEX_CHARACTER_TYPE character;
    file.read(reinterpret_cast<char *>(&character), sizeof(character));
    return character;
}

SUFFIX_MARKER_TYPE Utils::readMarker(ifstream & file) {
    SUFFIX_MARKER_TYPE marker;
    file.read(reinterpret_cast<char *>(&marker), sizeof(marker));
    return marker;
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

boost::shared_ptr<std::vector<sauchar_t> > Utils::indexVectorToSaucharVector(
                     boost::shared_ptr<vector<INDEX_CHARACTER_TYPE> > input) {
    boost::shared_ptr<std::vector<sauchar_t> > result =
        boost::shared_ptr<std::vector<sauchar_t> >(new std::vector<sauchar_t>);

    for (vector<INDEX_CHARACTER_TYPE>::iterator it = input->begin();
                                          it != input->end(); ++it) {
        appendCharToSaucharVector(result, *it);
    }
    return result;
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

SUFFIX_MARKER_TYPE Utils::getIdFromMarker(SUFFIX_MARKER_TYPE marker) {
    // shift right to erase offset and length
    return marker >> SUFFIX_MARKER_SENTENCE_BYTES * 16;
}

SUFFIX_MARKER_TYPE Utils::getOffsetFromMarker(SUFFIX_MARKER_TYPE marker) {
    // shift left to erase id
    SUFFIX_MARKER_TYPE result = marker << _idBytes * 8;
    // shift back right and go further to erase length
    result = result >> (_idBytes * 8 + SUFFIX_MARKER_SENTENCE_BYTES * 8);
    return result;
}

SUFFIX_MARKER_TYPE Utils::getLengthFromMarker(SUFFIX_MARKER_TYPE marker) {
    // shift left to erase id and offset
    SUFFIX_MARKER_TYPE result = marker <<
                        (_idBytes * 8 + SUFFIX_MARKER_SENTENCE_BYTES * 8);
    // shift back
    return result >> (_idBytes * 8 + SUFFIX_MARKER_SENTENCE_BYTES * 8);
}

SUFFIX_MARKER_TYPE Utils::createMarker(SUFFIX_MARKER_TYPE id,
                                              SUFFIX_MARKER_TYPE offset,
                                              SUFFIX_MARKER_TYPE length) {
    // shift twice by SUFFIX_MARKER_SENTENCE_BYTES
    SUFFIX_MARKER_TYPE result = id << SUFFIX_MARKER_SENTENCE_BYTES * 16;
    // shift once by SUFFIX_MARKER_SENTENCE_BYTES
    result += offset << SUFFIX_MARKER_SENTENCE_BYTES * 8;
    // no shift at all
    result += length;

    return result;
}

SUFFIX_MARKER_TYPE Utils::maxSentenceSize =
                     pow(2, SUFFIX_MARKER_SENTENCE_BYTES*8);

int Utils::_idBytes = sizeof(SUFFIX_MARKER_TYPE) -
                       2 * SUFFIX_MARKER_SENTENCE_BYTES;

