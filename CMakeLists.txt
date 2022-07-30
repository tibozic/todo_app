cmake_minimum_required(VERSION 3.23.2)

project(todo_app C CXX)

add_subdirectory(src)

add_executable(${PROJECT_NAME}.out
  				src/main.cpp
  )

find_package(PkgConfig REQUIRED)
pkg_check_modules(GTK4 REQUIRED gtk4)

# target_include_directories(${PROJECT_NAME}.out PUBLIC src/libs/internal/Adder)
# target_link_directories(${PROJECT_NAME}.out PRIVATE src/libs/internal/Adder)

target_link_libraries(${PROJECT_NAME}.out
  						PRIVATE ${GTK4_LIBRARIES}
  )

target_compile_definitions(${PROJECT_NAME}.out
  							PRIVATE ${GTKMM_CFLAGS_OTHER}
  )

target_include_directories(${PROJECT_NAME}.out
  							PRIVATE ${GTK4_INCLUDE_DIRS}
  )

target_link_directories(${PROJECT_NAME}.out
  						PRIVATE ${GTK4_LIBRARY_DIRS}
  )
