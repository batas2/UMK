#############################################################################
# Makefile for building: /06_FloodFillB
# Generated by qmake (2.01a) (Qt 4.6.2) on: ?r. mar 24 16:46:33 2010
# Project:  nbproject/qt-Debug.pro
# Template: app
# Command: /usr/bin/qmake-qt4 -unix VPATH=. -o qttmp-Debug.mk nbproject/qt-Debug.pro
#############################################################################

####### Compiler, tools and options

CC            = gcc
CXX           = g++
DEFINES       = -DQT_GUI_LIB -DQT_CORE_LIB
CFLAGS        = -pipe -g -Wall -W -D_REENTRANT $(DEFINES)
CXXFLAGS      = -pipe -g -Wall -W -D_REENTRANT $(DEFINES)
INCPATH       = -I/usr/lib/qt4/mkspecs/linux-g++ -Inbproject -I/usr/include/QtCore -I/usr/include/QtGui -I/usr/include -I. -Inbproject -I.
LINK          = g++
LFLAGS        = 
LIBS          = $(SUBLIBS)   -lQtGui -lQtCore -lpthread 
AR            = ar cqs
RANLIB        = 
QMAKE         = /usr/bin/qmake-qt4
TAR           = tar -cf
COMPRESS      = gzip -9f
COPY          = cp -f
SED           = sed
COPY_FILE     = $(COPY)
COPY_DIR      = $(COPY) -r
STRIP         = 
INSTALL_FILE  = install -m 644 -p
INSTALL_DIR   = $(COPY_DIR)
INSTALL_PROGRAM = install -m 755 -p
DEL_FILE      = rm -f
SYMLINK       = ln -f -s
DEL_DIR       = rmdir
MOVE          = mv -f
CHK_DIR_EXISTS= test -d
MKDIR         = mkdir -p

####### Output directory

OBJECTS_DIR   = build/Debug/GNU-Linux-x86/

####### Files

SOURCES       = main.cpp 
OBJECTS       = build/Debug/GNU-Linux-x86/main.o
DIST          = /usr/lib/qt4/mkspecs/common/g++-multilib.conf \
		/usr/lib/qt4/mkspecs/common/unix.conf \
		/usr/lib/qt4/mkspecs/common/linux.conf \
		/usr/lib/qt4/mkspecs/qconfig.pri \
		/usr/lib/qt4/mkspecs/features/qt_functions.prf \
		/usr/lib/qt4/mkspecs/features/qt_config.prf \
		/usr/lib/qt4/mkspecs/features/exclusive_builds.prf \
		/usr/lib/qt4/mkspecs/features/default_pre.prf \
		/usr/lib/qt4/mkspecs/features/debug.prf \
		/usr/lib/qt4/mkspecs/features/default_post.prf \
		/usr/lib/qt4/mkspecs/features/warn_on.prf \
		/usr/lib/qt4/mkspecs/features/qt.prf \
		/usr/lib/qt4/mkspecs/features/unix/thread.prf \
		/usr/lib/qt4/mkspecs/features/moc.prf \
		/usr/lib/qt4/mkspecs/features/resources.prf \
		/usr/lib/qt4/mkspecs/features/uic.prf \
		/usr/lib/qt4/mkspecs/features/yacc.prf \
		/usr/lib/qt4/mkspecs/features/lex.prf \
		/usr/lib/qt4/mkspecs/features/include_source_dir.prf \
		nbproject/qt-Debug.pro
QMAKE_TARGET  = 06_FloodFillB
DESTDIR       = /
TARGET        = /06_FloodFillB

first: all
####### Implicit rules

.SUFFIXES: .o .c .cpp .cc .cxx .C

.cpp.o:
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o "$@" "$<"

.cc.o:
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o "$@" "$<"

.cxx.o:
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o "$@" "$<"

.C.o:
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o "$@" "$<"

.c.o:
	$(CC) -c $(CFLAGS) $(INCPATH) -o "$@" "$<"

####### Build rules

all: qttmp-Debug.mk $(TARGET)

$(TARGET):  $(OBJECTS)  
	@$(CHK_DIR_EXISTS) / || $(MKDIR) / 
	$(LINK) $(LFLAGS) -o $(TARGET) $(OBJECTS) $(OBJCOMP) $(LIBS)

qttmp-Debug.mk: nbproject/qt-Debug.pro  /usr/lib/qt4/mkspecs/linux-g++/qmake.conf /usr/lib/qt4/mkspecs/common/g++-multilib.conf \
		/usr/lib/qt4/mkspecs/common/unix.conf \
		/usr/lib/qt4/mkspecs/common/linux.conf \
		/usr/lib/qt4/mkspecs/qconfig.pri \
		/usr/lib/qt4/mkspecs/features/qt_functions.prf \
		/usr/lib/qt4/mkspecs/features/qt_config.prf \
		/usr/lib/qt4/mkspecs/features/exclusive_builds.prf \
		/usr/lib/qt4/mkspecs/features/default_pre.prf \
		/usr/lib/qt4/mkspecs/features/debug.prf \
		/usr/lib/qt4/mkspecs/features/default_post.prf \
		/usr/lib/qt4/mkspecs/features/warn_on.prf \
		/usr/lib/qt4/mkspecs/features/qt.prf \
		/usr/lib/qt4/mkspecs/features/unix/thread.prf \
		/usr/lib/qt4/mkspecs/features/moc.prf \
		/usr/lib/qt4/mkspecs/features/resources.prf \
		/usr/lib/qt4/mkspecs/features/uic.prf \
		/usr/lib/qt4/mkspecs/features/yacc.prf \
		/usr/lib/qt4/mkspecs/features/lex.prf \
		/usr/lib/qt4/mkspecs/features/include_source_dir.prf
	$(QMAKE) -unix VPATH=. -o qttmp-Debug.mk nbproject/qt-Debug.pro
/usr/lib/qt4/mkspecs/common/g++-multilib.conf:
/usr/lib/qt4/mkspecs/common/unix.conf:
/usr/lib/qt4/mkspecs/common/linux.conf:
/usr/lib/qt4/mkspecs/qconfig.pri:
/usr/lib/qt4/mkspecs/features/qt_functions.prf:
/usr/lib/qt4/mkspecs/features/qt_config.prf:
/usr/lib/qt4/mkspecs/features/exclusive_builds.prf:
/usr/lib/qt4/mkspecs/features/default_pre.prf:
/usr/lib/qt4/mkspecs/features/debug.prf:
/usr/lib/qt4/mkspecs/features/default_post.prf:
/usr/lib/qt4/mkspecs/features/warn_on.prf:
/usr/lib/qt4/mkspecs/features/qt.prf:
/usr/lib/qt4/mkspecs/features/unix/thread.prf:
/usr/lib/qt4/mkspecs/features/moc.prf:
/usr/lib/qt4/mkspecs/features/resources.prf:
/usr/lib/qt4/mkspecs/features/uic.prf:
/usr/lib/qt4/mkspecs/features/yacc.prf:
/usr/lib/qt4/mkspecs/features/lex.prf:
/usr/lib/qt4/mkspecs/features/include_source_dir.prf:
qmake:  FORCE
	@$(QMAKE) -unix VPATH=. -o qttmp-Debug.mk nbproject/qt-Debug.pro

dist: 
	@$(CHK_DIR_EXISTS) nbproject/build/Debug/GNU-Linux-x86/06_FloodFillB1.0.0 || $(MKDIR) nbproject/build/Debug/GNU-Linux-x86/06_FloodFillB1.0.0 
	$(COPY_FILE) --parents $(SOURCES) $(DIST) nbproject/build/Debug/GNU-Linux-x86/06_FloodFillB1.0.0/ && $(COPY_FILE) --parents main.cpp nbproject/build/Debug/GNU-Linux-x86/06_FloodFillB1.0.0/ && (cd `dirname nbproject/build/Debug/GNU-Linux-x86/06_FloodFillB1.0.0` && $(TAR) 06_FloodFillB1.0.0.tar 06_FloodFillB1.0.0 && $(COMPRESS) 06_FloodFillB1.0.0.tar) && $(MOVE) `dirname nbproject/build/Debug/GNU-Linux-x86/06_FloodFillB1.0.0`/06_FloodFillB1.0.0.tar.gz . && $(DEL_FILE) -r nbproject/build/Debug/GNU-Linux-x86/06_FloodFillB1.0.0


clean:compiler_clean 
	-$(DEL_FILE) $(OBJECTS)
	-$(DEL_FILE) *~ core *.core


####### Sub-libraries

distclean: clean
	-$(DEL_FILE) $(TARGET) 
	-$(DEL_FILE) qttmp-Debug.mk


mocclean: compiler_moc_header_clean compiler_moc_source_clean

mocables: compiler_moc_header_make_all compiler_moc_source_make_all

compiler_moc_header_make_all:
compiler_moc_header_clean:
compiler_rcc_make_all:
compiler_rcc_clean:
compiler_image_collection_make_all: qmake_image_collection.cpp
compiler_image_collection_clean:
	-$(DEL_FILE) qmake_image_collection.cpp
compiler_moc_source_make_all:
compiler_moc_source_clean:
compiler_uic_make_all:
compiler_uic_clean:
compiler_yacc_decl_make_all:
compiler_yacc_decl_clean:
compiler_yacc_impl_make_all:
compiler_yacc_impl_clean:
compiler_lex_make_all:
compiler_lex_clean:
compiler_clean: 

####### Compile

build/Debug/GNU-Linux-x86/main.o: main.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o build/Debug/GNU-Linux-x86/main.o main.cpp

####### Install

install:   FORCE

uninstall:   FORCE

FORCE:

