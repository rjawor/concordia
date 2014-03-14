add_library(concordia-tests
  test_example.cpp
  test_tm_matches.cpp
  test_interval.cpp
  test_logging.cpp
  test_utils.cpp
  test_word_map.cpp
  test_hash_generator.cpp
  test_concordia_index.cpp
  test_concordia_config.cpp
  test_concordia.cpp
  )

target_link_libraries(concordia-tests concordia ${LIBCONFIG_LIB} concordia-tests-common)
