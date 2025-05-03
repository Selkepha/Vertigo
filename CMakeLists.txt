cmake_minimum_required(VERSION 3.10)

# set the project name
project(Vertigo VERSION 0.1)

# specify the C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_EXTENSIONS OFF) #ensures compiler uses same c++ standard
set(CMAKE_CXX_STANDARD_REQUIRED True)

# directories
SET(include_dir		"${CMAKE_SOURCE_DIR}/include")
SET(src_dir			"${CMAKE_SOURCE_DIR}/src")

# subdirectories
add_subdirectory(${src_dir})
add_subdirectory(./tests)