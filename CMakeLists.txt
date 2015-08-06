cmake_minimum_required(VERSION 2.8.11)
project( Client )
find_package( OpenCV REQUIRED )

find_package(Qt5Widgets)
find_package(Qt5Concurrent)
set(BOOST_ROOT C:/boost/boost_1_55_0/boost_1_55_0)
set(Boost_USE_STATIC_LIBS ON)


# Find includes in corresponding build directories
set(CMAKE_INCLUDE_CURRENT_DIR ON)
# Instruct CMake to run moc automatically when needed.
set(CMAKE_AUTOMOC ON)
#set(QT_UIC_EXECUTABLE C:/Qt/5.3/msvc2012_opengl/bin/uic.exe)
set(CMAKE_AUTOUIC ON)

find_package(Boost COMPONENTS system)
include_directories(C:/boost/boost_1_55_0/boost_1_55_0)
link_directories(${Boost_LIBRARY_DIRS})
add_executable( Client src/main.cpp src/mainwindow.cpp src/robotvision.cpp src/Source.cpp ${UI_HEADERS} )
#target_link_libraries( Client ${OpenCV_LIBS} opencv_core opencv_highgui ${Boost_LIBRARIES} )
target_link_libraries( Client C:/opencv/opencv/build/x86/vc11/lib/opencv_core249.lib /
							  C:/opencv/opencv/build/x86/vc11/lib/opencv_highgui249.lib /
							  C:/opencv/opencv/build/x86/vc11/lib/opencv_imgproc249.lib /
							  C:/opencv/opencv/build/x86/vc11/lib/opencv_video249.lib /
							  ${Boost_LIBRARIES} /
							  Qt5::Widgets /
							  Qt5::Concurrent
							  ${QT_QTNETWORK_LIBRARY})
