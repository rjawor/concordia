add_library(concordia-tests
  test_concordia.cpp
  test_concordia_config.cpp
  test_word_map.cpp
  )

target_link_libraries(concordia-tests concordia ${LIBCONFIG_LIB} concordia-tests-common)
