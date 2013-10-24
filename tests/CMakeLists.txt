set(ALL_TESTS_METHODS_DIRS unit-tests common)

foreach(dir ${ALL_TESTS_METHODS_DIRS})
  add_subdirectory(${dir})
endforeach(dir)
