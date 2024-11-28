cmake_minimum_required(VERSION 3.16)
project(QtProject VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

# Set Qt6 path
set(CMAKE_PREFIX_PATH "C:/Qt/6.8.0/msvc2022_64")

# Find required Qt packages
find_package(Qt6 COMPONENTS Core Widgets OpenGL OpenGLWidgets REQUIRED)

# OpenCascade configuration
set(OpenCASCADE_INCLUDE_DIR "C:/Users/kutay/Downloads/occt-vc143-64/occt-vc143-64/inc")
set(OpenCASCADE_LIBRARY_DIR "C:/Users/kutay/Downloads/occt-vc143-64/occt-vc143-64/win64/vc14/lib")
set(OpenCASCADE_BINARY_DIR "C:/Users/kutay/Downloads/occt-vc143-64/occt-vc143-64/win64/vc14/bin")

include_directories(${OpenCASCADE_INCLUDE_DIR})
link_directories(${OpenCASCADE_LIBRARY_DIR})

add_executable(QtProject
    main.cpp
    mainwindow.cpp
    mainwindow.h
    occview.cpp
    occview.h
)

target_include_directories(QtProject PRIVATE 
    ${OpenCASCADE_INCLUDE_DIR}
)

target_link_libraries(QtProject PRIVATE
    Qt6::Core
    Qt6::Widgets
    Qt6::OpenGL
    Qt6::OpenGLWidgets
    # OpenCascade Libraries
    "${OpenCASCADE_LIBRARY_DIR}/TKernel.lib"
    "${OpenCASCADE_LIBRARY_DIR}/TKMath.lib"
    "${OpenCASCADE_LIBRARY_DIR}/TKService.lib"
    "${OpenCASCADE_LIBRARY_DIR}/TKV3d.lib"
    "${OpenCASCADE_LIBRARY_DIR}/TKOpenGl.lib"
    "${OpenCASCADE_LIBRARY_DIR}/TKBRep.lib"
    "${OpenCASCADE_LIBRARY_DIR}/TKDEIGES.lib"
    "${OpenCASCADE_LIBRARY_DIR}/TKDESTL.lib"
    "${OpenCASCADE_LIBRARY_DIR}/TKDEVRML.lib"
    "${OpenCASCADE_LIBRARY_DIR}/TKDESTEP.lib"
    "${OpenCASCADE_LIBRARY_DIR}/TKXSBase.lib"
    "${OpenCASCADE_LIBRARY_DIR}/TKShHealing.lib"
    "${OpenCASCADE_LIBRARY_DIR}/TKHLR.lib"
    "${OpenCASCADE_LIBRARY_DIR}/TKTopAlgo.lib"
    "${OpenCASCADE_LIBRARY_DIR}/TKMesh.lib"
    "${OpenCASCADE_LIBRARY_DIR}/TKPrim.lib"
    "${OpenCASCADE_LIBRARY_DIR}/TKCDF.lib"
    "${OpenCASCADE_LIBRARY_DIR}/TKBool.lib"
    "${OpenCASCADE_LIBRARY_DIR}/TKBO.lib"
    "${OpenCASCADE_LIBRARY_DIR}/TKFillet.lib"
    "${OpenCASCADE_LIBRARY_DIR}/TKOffset.lib"
    "${OpenCASCADE_LIBRARY_DIR}/TKFeat.lib"
    "${OpenCASCADE_LIBRARY_DIR}/TKG2d.lib"
    "${OpenCASCADE_LIBRARY_DIR}/TKG3d.lib"
    "${OpenCASCADE_LIBRARY_DIR}/TKGeomBase.lib"
    "${OpenCASCADE_LIBRARY_DIR}/TKGeomAlgo.lib"
)

# Copy OpenCascade DLLs to output directory
add_custom_command(TARGET QtProject POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    "${OpenCASCADE_BINARY_DIR}"
    "$<TARGET_FILE_DIR:QtProject>"
)
