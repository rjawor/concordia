add_library(utf8case SHARED
    case_tables.cpp
    range_based_case_converter.cpp
    regular_contextual_case_converter.cpp
    simple_convert.cpp
    special_casing_converter.cpp
    string_case_converter_manager.cpp
    turkish_and_azeri_lower_contextual_case_converter.cpp
    turkish_and_azeri_upper_contextual_case_converter.cpp
)

install(TARGETS utf8case DESTINATION lib/)
install(FILES 
        case_converter_factory.hpp
        general_case_converter.hpp
        simple_convert.hpp
        turkish_and_azeri_lower_contextual_case_converter.hpp
        case_tables.hpp
        range_based_case_converter.hpp
        special_casing_converter.hpp
        turkish_and_azeri_upper_contextual_case_converter.hpp
        contextual_case_converter.hpp
        regular_contextual_case_converter.hpp
        string_case_converter_manager.hpp

DESTINATION include/utf8case/)
