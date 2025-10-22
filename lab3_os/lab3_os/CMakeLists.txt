# CMakeList.txt: проект CMake для lab3_os; включите исходный код и определения,
# укажите здесь логику для конкретного проекта.
#

# Добавьте источник в исполняемый файл этого проекта.
add_executable(lab3_os
    src/lab3_os.cpp
    src/marker_thread.cpp
    src/sync.cpp
    src/lab3_os.h
    src/marker_thread.h
    src/sync.h
)
if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET lab3_os PROPERTY CXX_STANDARD 20)
endif()

# TODO: Добавьте тесты и целевые объекты, если это необходимо.
