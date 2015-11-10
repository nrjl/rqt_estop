cmake_minimum_required(VERSION 2.8.3)
project(rqt_estop)

## Find catkin macros and libraries
find_package(catkin REQUIRED COMPONENTS 
    roscpp
    rqt_gui
    rqt_gui_cpp
    geometry_msgs
)

find_package(Qt4 REQUIRED COMPONENTS QtCore QtGui)

include(${QT_USE_FILE})

set(rqt_estop_SRCS
  src/estop_gui.cpp
)

set(rqt_estop_HDRS
  src/estop_gui.h
)

set(rqt_estop_UIS
  src/estop_gui.ui
)

set(rqt_estop_INCLUDE_DIRECTORIES
  include
  ${CMAKE_CURRENT_BINARY_DIR}
)

catkin_package(
	INCLUDE_DIRS ${rqt_estop_INCLUDE_DIRECTORIES}
	LIBRARIES ${PROJECT_NAME} 
    CATKIN_DEPENDS roscpp rqt_gui rqt_gui_cpp geometry_msgs
)
catkin_python_setup()

qt4_wrap_cpp(rqt_estop_MOCS ${rqt_estop_HDRS})
qt4_wrap_ui(rqt_estop_UIS_H ${rqt_estop_UIS})

include_directories(${rqt_estop_INCLUDE_DIRECTORIES} ${catkin_INCLUDE_DIRS})
add_library(${PROJECT_NAME} ${rqt_estop_SRCS} ${rqt_estop_MOCS} ${rqt_estop_UIS_H})
target_link_libraries(${PROJECT_NAME} ${catkin_LIBRARIES} ${QT_QTCORE_LIBRARY} ${QT_QTGUI_LIBRARY})

find_package(class_loader)
class_loader_hide_library_symbols(${PROJECT_NAME})

add_dependencies(rqt_estop ${catkin_EXPORTED_TARGETS})

install(FILES plugin.xml
  DESTINATION ${CATKIN_PACKAGE_SHARE_DESTINATION}
)

install(TARGETS ${PROJECT_NAME}
  ARCHIVE DESTINATION ${CATKIN_PACKAGE_LIB_DESTINATION}
  LIBRARY DESTINATION ${CATKIN_PACKAGE_LIB_DESTINATION})

install(PROGRAMS scripts/rqt_estop
  DESTINATION ${CATKIN_PACKAGE_BIN_DESTINATION}
)

install(DIRECTORY include/${PROJECT_NAME}/
  DESTINATION ${CATKIN_PACKAGE_INCLUDE_DESTINATION}
)
