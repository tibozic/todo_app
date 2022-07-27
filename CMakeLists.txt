cmake_minimum_required(VERSION 3.23.2)

project(todo_app)

add_executable(${PROJECT_NAME}.out src/main.cpp)

add_subdirectory(src)

# target_include_directories(${PROJECT_NAME}.out PUBLIC src/libs/internal/Adder)
# target_link_directories(${PROJECT_NAME}.out PRIVATE src/libs/internal/Adder)

target_link_libraries(${PROJECT_NAME}.out)
