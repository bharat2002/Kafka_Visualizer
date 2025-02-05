cmake_minimum_required(VERSION 3.16)

project(Kafka-Visualizer VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Find Qt Widgets
find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)

# Include paths for librdkafka headers
include_directories("C:/Users/bpali/Downloads/librdkafka.redist.2.8.0/build/native/include/librdkafka")
# include_directories(D:/Projects/librdkafka/src)
# set(LIBRDKAFKA_INCLUDE_DIR "D:/Projects/vcpkg/installed/x64-windows/include/librdkafka")  # Path to librdkafka headers
# set(LIBRDKAFKA_LIB_DIR "D:/Projects/vcpkg/installed/x64-windows/debug/lib")  # Path to librdkafka libraries

# Link directories for librdkafka libraries (ensure they match the build type: Debug/Release)
# link_directories(D:/Projects/librdkafka/build/src/Debug)
# include_directories(${LIBRDKAFKA_INCLUDE_DIR})
# link_directories(${LIBRDKAFKA_LIB_DIR})

link_directories("C:/Users/bpali/Downloads/librdkafka.redist.2.8.0/build/native/lib/win/x64/win-x64-Release/v142")

# Define project sources
set(PROJECT_SOURCES
    main.cpp
    mainwindow.cpp
    mainwindow.h
    mainwindow.ui
    kakfaconsumer.cpp
    kakfaconsumer.h
)

# Add executable with manual finalization for Qt6
if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(Kafka-Visualizer
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
        kakfaconsumer.h kakfaconsumer.cpp
        inireader.h inireader.cpp
        config.ini
        Images.qrc
        ckafkainputdialog.h ckafkainputdialog.cpp
        ConsumerTab.h ConsumerTab.cpp
    )
else()
    add_executable(Kafka-Visualizer
        ${PROJECT_SOURCES}
    )
endif()

# Link the libraries: librdkafka (C API) and rdkafka++ (C++ API)
# Make sure the paths to the library files are correct.
target_link_libraries(Kafka-Visualizer PRIVATE
    Qt${QT_VERSION_MAJOR}::Widgets      # Link to the C API of librdkafka
   "C:/Users/bpali/Downloads/librdkafka.redist.2.8.0/build/native/lib/win/x64/win-x64-Release/v142/librdkafkacpp.lib"   # Link to the C++ API of librdkafka
)


# Set target properties (Bundle and executable settings for macOS and Windows)
set_target_properties(Kafka-Visualizer PROPERTIES
    WIN32_EXECUTABLE TRUE
)

# Install targets
include(GNUInstallDirs)
install(TARGETS Kafka-Visualizer
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

# Finalize executable for Qt6 (if using Qt6)
if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(Kafka-Visualizer)
endif()
