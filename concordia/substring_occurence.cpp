#include "concordia/substring_occurence.hpp"
#include "concordia/common/utils.hpp"

SubstringOccurence::SubstringOccurence() {
}

SubstringOccurence::SubstringOccurence(const SUFFIX_MARKER_TYPE & marker) {
    _id = Utils::getIdFromMarker(marker);
    _offset = Utils::getOffsetFromMarker(marker);
    _exampleLength = Utils::getLengthFromMarker(marker);    
}

void SubstringOccurence::enterDataFromMarker(const SUFFIX_MARKER_TYPE & marker) {
    _id = Utils::getIdFromMarker(marker);
    _offset = Utils::getOffsetFromMarker(marker);
    _exampleLength = Utils::getLengthFromMarker(marker);
}


SubstringOccurence::SubstringOccurence(
                                   const SUFFIX_MARKER_TYPE & id,
                                   const SUFFIX_MARKER_TYPE & offset,
                                   const SUFFIX_MARKER_TYPE & exampleLength):
                                   _id(id),
                                   _offset(offset),
                                   _exampleLength(exampleLength) {
}

SubstringOccurence::~SubstringOccurence() {
}

