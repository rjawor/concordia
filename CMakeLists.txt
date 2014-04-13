# Tutorial: http://www.cmake.org/cmake/help/cmake_tutorial.html

cmake_minimum_required(VERSION 2.6)
project(concordia C CXX)

set (CONCORDIA_VERSION_MAJOR 0)
set (CONCORDIA_VERSION_MINOR 1)

# Type of the characters in SA

set (INDEX_CHARACTER_TYPE "unsigned int")
set (INDEX_CHARACTER_TYPE_MAX_VALUE 4294967295)
# The above allows for (roughly) 2^32 = 4 294 967 295 words in corpus.

# Suffix markers
set (SUFFIX_MARKER_TYPE "unsigned int")
set (SUFFIX_MARKER_TYPE_MAX_VALUE 4294967295)
set (SUFFIX_MARKER_DIVISOR 256)
# The above settings assign 3 bytes to sentence id and 1 byte for suffix offset.
# This allows to store 2^24 = 16 777 216 sentences no longer than 256 words.

# ============================== #
# Production paths
# ============================== #

set (PROD_RESOURCES_DIRECTORY "${concordia_SOURCE_DIR}/prod/resources")

set (PROD_PUDDLE_TAGSET_PATH "${PROD_RESOURCES_DIRECTORY}/puddle/tagset.txt")

# ============================== #
# Testing paths
# ============================== #

set (TEST_RESOURCES_DIRECTORY "${concordia_SOURCE_DIR}/tests/resources")
set (TEST_PUDDLE_TAGSET_PATH "${TEST_RESOURCES_DIRECTORY}/puddle/basic-tagset.txt")
set (TEMP_WORD_MAP "temp_word_map.bin")
set (TEMP_HASHED_INDEX "temp_hashed_index.bin")
set (TEMP_MARKERS "temp_markers.bin")
set (TEMP_SUFFIX_ARRAY "temp_suffix_array.bin")

file(MAKE_DIRECTORY ${TEST_RESOURCES_DIRECTORY}/temp)
file(MAKE_DIRECTORY ${PROD_RESOURCES_DIRECTORY}/temp)

SET(CMAKE_INSTALL_RPATH "${CMAKE_INSTALL_PREFIX}/lib")

set(BASE_TARGETS concordia)


                
# ================================================
# Third-party libraries
# ================================================

# ----------------------------------------------------
# Regular expression libraries
# ----------------------------------------------------
option(WITH_RE2 "Using RE2 regular expression library" OFF)
message(STATUS "Using RE2 regular expression library ${WITH_RE2}")

if(WITH_RE2)
    set(HAVE_RE2 1)
endif(WITH_RE2)

option(WITH_PCRE "Using PCRE regular expression library" ON)
message(STATUS "Using PCRE regular expression library ${WITH_PCRE}")

if(WITH_PCRE)
  set(HAVE_PCRE 1)
endif(WITH_PCRE)

# ----------------------------------------------------
# Boost
# ----------------------------------------------------
set(Boost_USE_STATIC_LIBS OFF)
set(Boost_USE_STATIC_RUNTIME OFF)
find_package(Boost COMPONENTS 
      serialization unit_test_framework system filesystem program_options iostreams regex REQUIRED)

# ----------------------------------------------------
# libconfig
# ----------------------------------------------------
find_library(LIBCONFIG_LIB NAMES config++ REQUIRED)
find_path(LIBCONFIG_INCLUDE libconfig.h++)

if(EXISTS ${LIBCONFIG_LIB} AND EXISTS ${LIBCONFIG_INCLUDE})
  message(STATUS "Found Libconfig")
  include_directories(${LIBCONFIG_INCLUDE})
  link_directories(${LIBCONFIG_LIB})
endif(EXISTS ${LIBCONFIG_LIB} AND EXISTS ${LIBCONFIG_INCLUDE})

# ----------------------------------------------------
# Snowball stemmer
# ----------------------------------------------------
find_library(LIBSTEMMER_LIB NAMES stemmer REQUIRED)
find_path(LIBSTEMMER_INCLUDE libstemmer.h)

if(EXISTS ${LIBSTEMMER_LIB} AND EXISTS ${LIBSTEMMER_INCLUDE})
  message(STATUS "Found libstemmer")
  include_directories(${LIBSTEMMER_INCLUDE})
  link_directories(${LIBSTEMMER_LIB})
endif(EXISTS ${LIBSTEMMER_LIB} AND EXISTS ${LIBSTEMMER_INCLUDE})

# ----------------------------------------------------
# Logging
# ----------------------------------------------------
find_library(LOG4CPP_LIB NAMES log4cpp REQUIRED)
find_path(LOG4CPP_INCLUDE log4cpp/Appender.hh)

if(EXISTS ${LOG4CPP_LIB} AND EXISTS ${LOG4CPP_INCLUDE})
  message(STATUS "Found Log4cpp")
  include_directories(${LOG4CPP_INCLUDE})
  link_directories(${LOG4CPP_LIB})
endif(EXISTS ${LOG4CPP_LIB} AND EXISTS ${LOG4CPP_INCLUDE})

# ================================================
# Concordia: Configuration
# ================================================

configure_file (
  "${concordia_SOURCE_DIR}/concordia/common/config.hpp.in"
  "${concordia_SOURCE_DIR}/concordia/common/config.hpp"
  )

configure_file (
  "${concordia_SOURCE_DIR}/tests/resources/concordia-config/concordia.cfg.in"
  "${concordia_SOURCE_DIR}/tests/resources/concordia-config/concordia.cfg"
  )

configure_file (
  "${concordia_SOURCE_DIR}/prod/resources/concordia-config/concordia.cfg.in"
  "${concordia_SOURCE_DIR}/prod/resources/concordia-config/concordia.cfg"
  )

# ================================================
# Concordia: sub-projects
# ================================================

set(ALL_DIRECTORIES concordia concordia-console libdivsufsort)

include_directories("${concordia_SOURCE_DIR}")

foreach(dir ${ALL_DIRECTORIES})
  link_directories("${concordia_BINARY_DIR}/${dir}")
  add_subdirectory(${dir})
endforeach(dir)


    
# ================================================
# Tests
# ================================================

set(TESTS_TARGETS concordia-tests)

add_subdirectory(tests)

ENABLE_TESTING()
ADD_TEST(FullTest ${CMAKE_CURRENT_BINARY_DIR}/tests/unit-tests/test_runner)

# Doxygen
find_package(Doxygen)
if(DOXYGEN_FOUND)
    FIND_PROGRAM(DOT_TOOL dot DOC "Dot tool from graphviz")
    SET(DOXYFILE_LATEX ON)
    SET(DOXYGEN_HAVE_DOT NO)
    SET(DOXYGEN_QUIET YES)
        
    SET(INPUT_FILES)
    SET(INPUT_FILES "${INPUT_FILES} ${CMAKE_CURRENT_SOURCE_DIR}")

    if(DOT_TOOL)
        SET(DOXYGEN_HAVE_DOT YES)
        message(STATUS "Graphviz found")
    else(DOT_TOOL)
        message(STATUS "Consider installing Graphviz for call and caller graphs in the documentation")
    endif(DOT_TOOL)
    configure_file(${CMAKE_CURRENT_SOURCE_DIR}/Doxyfile.in ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile @ONLY)
    add_custom_target(doc ALL ${DOXYGEN_EXECUTABLE} ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile
    WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
    COMMENT "Generating API documentation with Doxygen" VERBATIM)
    
endif(DOXYGEN_FOUND)


