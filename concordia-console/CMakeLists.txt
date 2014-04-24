
add_executable(concordia-console concordia-console.cpp)

target_link_libraries(concordia-console concordia utf8case ${Boost_LIBRARIES} ${LIBCONFIG_LIB} ${LIBSTEMMER_LIB})

if (WITH_RE2)
  target_link_libraries(concordia-console re2)
  if (WITH_PCRE)
    target_link_libraries(concordia-console pcrecpp)
  endif(WITH_PCRE)
else(WITH_RE2)
  if (WITH_PCRE)
    target_link_libraries(concordia-console pcrecpp)
  endif(WITH_PCRE)
endif(WITH_RE2)

# =====================================

install(TARGETS concordia-console DESTINATION bin/)

  
