TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp \
    utility.cpp \
    line.cpp \
    program.cpp \
    scene.cpp \
    drawableobject.cpp \
    surface.cpp \
    rectangle.cpp \
    cube.cpp \
    model.cpp \
    wavefrontobjloader.cpp \
    light.cpp \
    Material/material.cpp

include(deployment.pri)
qtcAddDeployment()

CONFIG += c++11

QMAKE_CFLAGS += -mmacosx-version-min=10.7
QMAKE_CXXFLAGS += -mmacosx-version-min=10.7

INCLUDEPATH += /Users/jesterilianight/Documents/sources/gtest-1.7.0/include/ /opt/local/include

LIBS +=  -L/Applications/Xcode.app/Contents/Developer/Platforms/MacOSX.platform/Developer/SDKs/MacOSX10.9.sdk/System/Library/Frameworks/OpenGL.framework/Libraries -lGL \
         -L/opt/local/lib/ -lglfw

DISTFILES += \
    line.vs \
    ../shaders/dashed_line.vs \
    ../shaders/dashed_line.fs \
    ../models/compl_triangulate_normals.obj \
    ../models/cube.obj \
    ../models/cube_triangle.obj \
    ../models/foo.obj \
    ../models/foo_triangle.obj \
    ../models/head_triangulate_normals.obj \
    ../models/plane.obj \
    ../models/plane_triangle.obj \
    ../models/rectangle_triangulate_normals.obj \
    ../models/rectangle_triangulate_normals_smooth.obj \
    ../models/some.obj \
    ../models/sphere.obj \
    ../models/torus_triangulate_normals_flat.obj \
    ../models/torus_triangulate_normals_smooth.obj \
    ../models/cube_triangulate_normals_flat.obj \
    ../shaders/shaded.vs \
    ../shaders/shaded.fs \
    ../shaders/solid_color.fs \
    ../shaders/solid_color.vs

HEADERS += \
    utility.h \
    line.h \
    geometry.h \
    program.h \
    scene.h \
    drawableobject.h \
    surface.h \
    rectangle.h \
    cube.h \
    model.h \
    wavefrontobjloader.h \
    light.h \
    Material/material.h
