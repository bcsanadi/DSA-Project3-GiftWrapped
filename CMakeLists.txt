cmake_minimum_required(VERSION 3.29)
project(DSA_Project3_GiftWrapped LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)

include(FetchContent)
FetchContent_Declare(SFML
        GIT_REPOSITORY https://github.com/SFML/SFML.git
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

target_link_libraries(DSA_Project3_GiftWrapped
        sfml-graphics
        sfml-window
        sfml-system
        )

