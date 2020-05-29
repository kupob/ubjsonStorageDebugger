cmake_minimum_required(VERSION 3.16)
project(ubjsonStorage)

set(CMAKE_CXX_STANDARD 17)

add_subdirectory(json)
add_subdirectory(UbjsonCpp)

find_package(EBML 1.3.9 REQUIRED)
find_package(Matroska CONFIG REQUIRED)

add_library(ubjsonStorage SHARED
        Storage.cpp
        Storage.h
        configReader/ConfigReader.cpp
        configReader/ConfigReader.h

        dataTypes/RawData.h
        dataTypes/stdSupport.h
        dataTypes/stdSupport.cpp
        dataTypes/TimeStamp.h
        dataTypes/FileInfo.h

        logger/log.h

        private/StoragePrivate.cpp
        private/StoragePrivate.h
        )

target_link_libraries(ubjsonStorage PUBLIC nlohmann_json::nlohmann_json)
target_link_libraries(ubjsonStorage PUBLIC EBML::ebml)
target_link_libraries(ubjsonStorage PRIVATE Matroska::matroska)
target_link_libraries(ubjsonStorage PUBLIC UbjsonCpp)
