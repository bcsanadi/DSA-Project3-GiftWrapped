cmake_minimum_required(VERSION 3.29)
project(DSA_Project3_GiftWrapped)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)


include(FetchContent)
FetchContent_Declare(SFML
        GIT_REPOSITORY https://github.com/SFML/SFML.git
        GIT_TAG 3.0.x
        GIT_SHALLOW ON
        EXCLUDE_FROM_ALL
        SYSTEM)
FetchContent_MakeAvailable(SFML)


add_executable(DSA_Project3_GiftWrapped
    Graph.cpp
    Graph.h
    main.cpp
        Product.h
        ProductParsing.cpp
        )

cmake_minimum_required(VERSION 3.28)
project(CMakeSFMLProject LANGUAGES CXX)



