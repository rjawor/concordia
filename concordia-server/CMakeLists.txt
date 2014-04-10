add_library(concordia-server SHARED
  concordia_server.cpp
  )

add_subdirectory(t)
# =====================================

install(TARGETS concordia-server DESTINATION lib/)
install(FILES concordia_server.hpp DESTINATION include/concordia-server/)

target_link_libraries(concordia-server log4cpp)
target_link_libraries(concordia-server ${LIBSTEMMER_LIB})
target_link_libraries(concordia-server ${Boost_LIBRARIES})

if (WITH_RE2)
  target_link_libraries(concordia-server re2)
  if (WITH_PCRE)
    target_link_libraries(concordia-server pcrecpp)
  endif(WITH_PCRE)
else(WITH_RE2)
  if (WITH_PCRE)
    target_link_libraries(concordia-server pcrecpp)
  endif(WITH_PCRE)
endif(WITH_RE2)

