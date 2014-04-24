add_library(concordia-tests
  test_text_utils.cpp
  test_regex_replacement.cpp
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
  range_based_case_converter_tests.cpp
  simple_convert_tests.cpp
  special_casing_converter_tests.cpp
  )

target_link_libraries(concordia-tests concordia ${LIBCONFIG_LIB} concordia-tests-common utf8case)
