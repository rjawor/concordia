add_library(concordia-server-tests
  test_concordia.cpp
  test_concordia_config.cpp
  )

target_link_libraries(concordia-server-tests concordia ${LIBCONFIG_LIB} concordia-tests-common)
