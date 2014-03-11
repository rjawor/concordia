set(ALL_DIRECTORIES common)

foreach(dir ${ALL_DIRECTORIES})
  link_directories("${concordia_BINARY_DIR}/${dir}")
  add_subdirectory(${dir})
endforeach(dir)

add_library(concordia SHARED
  interval.cpp
  tm_matches.cpp
  anubis_search_result.cpp
  substring_occurence.cpp
  example.cpp
  index_searcher.cpp
  concordia_index.cpp
  word_map.cpp
  hash_generator.cpp
  concordia.cpp
  concordia_config.cpp
  concordia_exception.cpp
  common/logging.cpp
  common/utils.cpp
  )

add_subdirectory(t)
# =====================================

install(TARGETS concordia DESTINATION lib/)
install(FILES 
          interval.hpp
          tm_matches.hpp
          anubis_search_result.hpp
          substring_occurence.hpp
          example.hpp
          index_searcher.hpp
          concordia_index.hpp
          word_map.hpp
          hash_generator.hpp
          concordia.hpp
          concordia_config.hpp
          concordia_exception.hpp
        DESTINATION include/concordia/)

install(FILES 
          common/config.hpp
          common/logging.hpp
          common/utils.hpp
        DESTINATION include/concordia/common/)

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

target_link_libraries(concordia log4cpp)
target_link_libraries(concordia ${LIBSTEMMER_LIB})
target_link_libraries(concordia ${Boost_LIBRARIES})
target_link_libraries(concordia divsufsort)

if (WITH_RE2)
  target_link_libraries(concordia re2)
  if (WITH_PCRE)
    target_link_libraries(concordia pcrecpp)
  endif(WITH_PCRE)
else(WITH_RE2)
  if (WITH_PCRE)
    target_link_libraries(concordia pcrecpp)
  endif(WITH_PCRE)
endif(WITH_RE2)

