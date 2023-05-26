cmake_minimum_required(VERSION 3.22)

# set project name
project(eyren)

# specify C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# find libs
find_package(Boost 1.74 COMPONENTS program_options REQUIRED)

find_package(PkgConfig)
pkg_check_modules(GTKMM gtkmm-3.0)

# set up executable
set(
    APP_SRC 
    src/main.cxx
    src/MainWindow.cxx
    src/ImageArea.cxx
)
add_executable(eyren ${APP_SRC})
target_link_libraries(eyren Boost::program_options ${GTKMM_LIBRARIES})

# include directories must come AFTER the executable's been added
include_directories(include ${Boost_INCLUDE_DIR} ${GTKMM_INCLUDE_DIRS})
