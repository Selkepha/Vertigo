include_directories(../include/Vertigo)
include_directories(../include/Vertigo/Impact)
include_directories(./Impact)
include_directories(./)

add_subdirectory(./Impact)

add_library(Vertigo STATIC
			App.cpp
			Core.cpp 
			Logger.cpp
)

#link with SFML
find_package(SFML 3.0 REQUIRED COMPONENTS System Window Graphics Network Audio)
target_link_libraries(Vertigo PRIVATE SFML::Graphics SFML::Window SFML::System Impact)