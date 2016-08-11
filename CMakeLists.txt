cmake_minimum_required (VERSION 2.8)
file(GLOB SOURCE_FILES "src/*")
add_executable (hexapod ${SOURCE_FILES})

find_package(OpenGL REQUIRED)
find_package(GLUT REQUIRED)
include_directories( ${OPENGL_INCLUDE_DIRS}  ${GLUT_INCLUDE_DIRS} )
target_link_libraries(hexapod ${OPENGL_LIBRARIES} ${GLUT_LIBRARY} )

