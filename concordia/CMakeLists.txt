set(ALL_DIRECTORIES common)

foreach(dir ${ALL_DIRECTORIES})
  link_directories("${concordia_BINARY_DIR}/${dir}")
  add_subdirectory(${dir})
endforeach(dir)

add_library(concordia SHARED
  concordia.cpp
  concordia_config.cpp
  concordia_exception.cpp
  common/logging.cpp
  )

add_subdirectory(t)
# =====================================

install(TARGETS concordia DESTINATION lib/)
install(FILES concordia.hpp DESTINATION include/concordia/)

target_link_libraries(concordia log4cpp)
target_link_libraries(concordia ${LIBSTEMMER_LIB})
target_link_libraries(concordia ${Boost_LIBRARIES})

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

