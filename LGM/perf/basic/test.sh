g++ -c -pipe -g -Wall -W -D_REENTRANT -DQT_GUI_LIB -DQT_CORE_LIB -I/usr/lib/qt4/mkspecs/linux-g++ -Inbproject -I/usr/include/QtCore -I/usr/include/QtGui -I/usr/include -I. -Inbproject -I. -o build/Debug/GNU-Linux-x86/FrameCounter.o FrameCounter.cpp
g++ -c -pipe -g -Wall -W -D_REENTRANT -DQT_GUI_LIB -DQT_CORE_LIB -I/usr/lib/qt4/mkspecs/linux-g++ -Inbproject -I/usr/include/QtCore -I/usr/include/QtGui -I/usr/include -I. -Inbproject -I. -o build/Debug/GNU-Linux-x86/MyThread.o MyThread.cpp
g++ -c -pipe -g -Wall -W -D_REENTRANT -DQT_GUI_LIB -DQT_CORE_LIB -I/usr/lib/qt4/mkspecs/linux-g++ -Inbproject -I/usr/include/QtCore -I/usr/include/QtGui -I/usr/include -I. -Inbproject -I. -o build/Debug/GNU-Linux-x86/MyWidget.o MyWidget.cpp

g++ -c -pipe -g -Wall -W -D_REENTRANT -DQT_GUI_LIB -DQT_CORE_LIB -I/usr/lib/qt4/mkspecs/linux-g++ -Inbproject -I/usr/include/QtCore -I/usr/include/QtGui -I/usr/include -I. -Inbproject -I. -o build/Debug/GNU-Linux-x86/main.o main.cpp
g++  -o dist/Debug/GNU-Linux-x86/basic build/Debug/GNU-Linux-x86/FrameCounter.o build/Debug/GNU-Linux-x86/MyThread.o build/Debug/GNU-Linux-x86/MyWidget.o  build/Debug/GNU-Linux-x86/main.o     -lQtGui -lQtCore -lpthread 
