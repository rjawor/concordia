add_library(utf8case-tests
   range_based_case_converter_tests.cpp
   simple_convert_tests.cpp
   special_casing_converter_tests.cpp
)

target_link_libraries(utf8case-tests utf8case)
