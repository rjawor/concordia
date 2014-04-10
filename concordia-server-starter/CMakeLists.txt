
add_executable(concordia-server-starter concordia_server_starter.cpp)

target_link_libraries(concordia-server-starter concordia-server concordia ${Boost_LIBRARIES} ${FCGIPP_LIB} ${FCGI_LIB} ${LIBCONFIG_LIB})

if (WITH_RE2)
  target_link_libraries(concordia-server-starter re2)
  if (WITH_PCRE)
    target_link_libraries(concordia-server-starter pcrecpp)
  endif(WITH_PCRE)
else(WITH_RE2)
  if (WITH_PCRE)
    target_link_libraries(concordia-server-starter pcrecpp)
  endif(WITH_PCRE)
endif(WITH_RE2)

# =====================================

install(TARGETS concordia-server-starter DESTINATION bin/)

  
