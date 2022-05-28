cmake_minimum_required(VERSION 3.16)

project(Qwt
  VERSION 6.2.0
  DESCRIPTION "Qt Widgets for Technical Applications"
  HOMEPAGE_URL "https://qwt.sourceforge.io"
  LANGUAGES CXX
)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)
set(CMAKE_CXX_EXTENSIONS OFF)

if(MSVC)
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /W4 /permissive-")
else()
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Wpedantic -Wcast-qual \
    -Wcast-align -Wredundant-decls -Wformat -Wshadow -Woverloaded-virtual \
    -fno-math-errno -funsafe-math-optimizations")
  if(CMAKE_COMPILER_ID STREQUAL "GNU")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wlogical-op")
  endif()
  add_compile_definitions(QT_STRICT_ITERATORS)
endif()

include(CheckPIESupported)
check_pie_supported(OUTPUT_VARIABLE PIE_MESSAGE LANGUAGES CXX)
if(CMAKE_CXX_LINK_PIE_SUPPORTED)
  set(CMAKE_POSITION_INDEPENDENT_CODE TRUE)
endif()

include(GNUInstallDirs)

option(QWT_DLL "Build shared library" ON)
if(QWT_DLL)
  set(BUILD_SHARED_LIBS ON)
else()
  set(BUILD_SHARED_LIBS OFF)
endif()

option(QWT_STATIC "Build static library" OFF)
if(QWT_STATIC)
  set(BUILD_STATIC_LIBS ON)
else()
  set(BUILD_STATIC_LIBS OFF)
endif()

if(NOT QWT_DLL AND NOT QWT_STATIC)
  message(FATAL_ERROR "Building shared and static library are both disabled!")
endif()

option(QWT_PLOT "Enable QwtPlot widget" ON)

option(QWT_POLAR "Enable QwtPolar classes" ON)

option(QWT_WIDGETS "Enables other widgets (sliders, dials, ...), beside QwtPlot" ON)

option(QWT_SVG "Enable SVG Support (Displaying & Exporting)" ON)

option(QWT_OPENGL "Enable OpenGL Plot Canvas" ON)

option(QWT_DESIGNER "Build Qwt Designer plugin" ON)

if(WIN32)
  option(QWT_DESIGNER_SELF_CONTAINED "Build a self-contained designer plugin" ON)
endif()

if(APPLE)
  option(QWT_FRAMEWORK "Build Qwt as a framework" ON)
endif()

option(QWT_BUILD_PLAYGROUND "Build the applications in playground" OFF)

option(QWT_BUILD_TESTS "Build Tests" OFF)

option(QWT_BUILD_EXAMPLES "Build Examples" OFF)

find_package(Qt6 COMPONENTS Core QUIET)
if(Qt6_FOUND)
  set(QT_VERSION_MAJOR 6)
else()
  find_package(Qt5 COMPONENTS Core REQUIRED)
  set(QT_VERSION_MAJOR 5)
endif()

find_package(Qt${QT_VERSION_MAJOR} COMPONENTS PrintSupport Concurrent Widgets REQUIRED)

if(QWT_OPENGL)
  find_package(Qt${QT_VERSION_MAJOR} COMPONENTS OpenGL REQUIRED)
  if(QT_VERSION_MAJOR VERSION_GREATER_EQUAL 6)
    find_package(Qt${QT_VERSION_MAJOR} COMPONENTS OpenGLWidgets REQUIRED)
  endif()
endif()

if(QWT_SVG)
  find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Svg REQUIRED)
endif()

add_subdirectory(src)

if(QWT_DESIGNER)
  find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Designer)
  add_subdirectory(designer)
endif()

if(QWT_BUILD_PLAYGROUND)
  add_subdirectory(playground)
endif()

if(QWT_BUILD_TESTS)
  add_subdirectory(tests)
endif()

if(QWT_BUILD_EXAMPLES)
  add_subdirectory(examples)
endif()
