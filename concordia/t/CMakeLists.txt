add_library(concordia-tests
  test_concordia.cpp
  test_concordia_config.cpp
  test_word_map.cpp
  test_hash_generator.cpp
  test_concordia_index.cpp
  )

target_link_libraries(concordia-tests concordia ${LIBCONFIG_LIB} concordia-tests-common)
