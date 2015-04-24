cmake_minimum_required(VERSION 2.8)

#Déclaration du projet
project(FractalProject)

find_package(OpenCV REQUIRED )

add_definitions(-std=c++11)

include_directories(${OpenCV_INCLUDE_DIRS})
#Déclaration de l'exécutable
add_executable(fractal	src/fractal.cpp)
target_link_libraries(fractal ${OpenCV_LIBS})


install(TARGETS fractal	RUNTIME DESTINATION bin)
