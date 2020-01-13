cmake_minimum_required(VERSION 3.4)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project(MKO_methods)


add_library(types STATIC
        ${CMAKE_CURRENT_SOURCE_DIR}/sources/types.cpp
)
add_library(major-criterion STATIC
        ${CMAKE_CURRENT_SOURCE_DIR}/sources/major_criterion_method.cpp
)
add_library(pareto-set STATIC
        ${CMAKE_CURRENT_SOURCE_DIR}/sources/pareto_set_method.cpp
)
add_library(union-weighting STATIC
        ${CMAKE_CURRENT_SOURCE_DIR}/sources/criteria_union_weighting_method.cpp
)
add_library(hierarchy-analysis STATIC
        ${CMAKE_CURRENT_SOURCE_DIR}/sources/hierarchy_analysis_method.cpp
)
add_executable(MKO-methods
        ${CMAKE_CURRENT_SOURCE_DIR}/sources/MKO_methods.cpp
)



target_include_directories(types
        PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include
)
target_include_directories(major-criterion
        PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include
)
target_include_directories(pareto-set
        PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include
)
target_include_directories(union-weighting
        PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include
)
target_include_directories(hierarchy-analysis
        PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include
)
target_include_directories(MKO-methods
        PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include
)



target_link_libraries(major-criterion
        PUBLIC types
)
target_link_libraries(pareto-set
        PUBLIC types
)
target_link_libraries(union-weighting
        PUBLIC types
)
target_link_libraries(hierarchy-analysis
        PUBLIC types
)
target_link_libraries(MKO-methods
        PUBLIC major-criterion
        PUBLIC pareto-set
        PUBLIC union-weighting
        PUBLIC hierarchy-analysis
)


