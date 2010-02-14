#
# Generated Makefile - do not edit!
#
# Edit the Makefile in the project folder instead (../Makefile). Each target
# has a -pre and a -post target defined where you can add customized code.
#
# This makefile implements configuration specific macros and targets.


# Environment
MKDIR=mkdir
CP=cp
CCADMIN=CCadmin
RANLIB=ranlib
CC=gcc
CCC=g++
CXX=g++
FC=
AS=

# Macros
CND_PLATFORM=GNU-Linux-x86
CND_CONF=Debug
CND_DISTDIR=dist

# Include project Makefile
include Makefile

# Object Directory
OBJECTDIR=build/${CND_CONF}/${CND_PLATFORM}

# Object Files
OBJECTFILES= \
	${OBJECTDIR}/src/lib/net/connection.o \
	${OBJECTDIR}/src/lib/network.o \
	${OBJECTDIR}/src/lib/client.o \
	${OBJECTDIR}/main.o \
	${OBJECTDIR}/src/lib/MainThread.o \
	${OBJECTDIR}/src/lib/net/tcpv4.o

# C Compiler Flags
CFLAGS=

# CC Compiler Flags
CCFLAGS=-lpthread
CXXFLAGS=-lpthread

# Fortran Compiler Flags
FFLAGS=

# Assembler Flags
ASFLAGS=

# Link Libraries and Options
LDLIBSOPTIONS=/home/batas2/Pobrane/boost_1_41_0/stage/lib/libboost_thread.a

# Build Targets
.build-conf: ${BUILD_SUBPROJECTS}
	${MAKE}  -f nbproject/Makefile-Debug.mk dist/Debug/GNU-Linux-x86/threadserwer

dist/Debug/GNU-Linux-x86/threadserwer: /home/batas2/Pobrane/boost_1_41_0/stage/lib/libboost_thread.a

dist/Debug/GNU-Linux-x86/threadserwer: ${OBJECTFILES}
	${MKDIR} -p dist/Debug/GNU-Linux-x86
	${LINK.cc} -o ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/threadserwer ${OBJECTFILES} ${LDLIBSOPTIONS} 

${OBJECTDIR}/src/lib/net/connection.o: nbproject/Makefile-${CND_CONF}.mk src/lib/net/connection.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/lib/net
	${RM} $@.d
	$(COMPILE.cc) -g -Wall -I/home/batas2/Pobrane/boost_1_41_0 -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/lib/net/connection.o src/lib/net/connection.cpp

${OBJECTDIR}/src/lib/network.o: nbproject/Makefile-${CND_CONF}.mk src/lib/network.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/lib
	${RM} $@.d
	$(COMPILE.cc) -g -Wall -I/home/batas2/Pobrane/boost_1_41_0 -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/lib/network.o src/lib/network.cpp

${OBJECTDIR}/src/lib/client.o: nbproject/Makefile-${CND_CONF}.mk src/lib/client.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/lib
	${RM} $@.d
	$(COMPILE.cc) -g -Wall -I/home/batas2/Pobrane/boost_1_41_0 -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/lib/client.o src/lib/client.cpp

${OBJECTDIR}/main.o: nbproject/Makefile-${CND_CONF}.mk main.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -g -Wall -I/home/batas2/Pobrane/boost_1_41_0 -MMD -MP -MF $@.d -o ${OBJECTDIR}/main.o main.cpp

${OBJECTDIR}/src/lib/MainThread.o: nbproject/Makefile-${CND_CONF}.mk src/lib/MainThread.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/lib
	${RM} $@.d
	$(COMPILE.cc) -g -Wall -I/home/batas2/Pobrane/boost_1_41_0 -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/lib/MainThread.o src/lib/MainThread.cpp

${OBJECTDIR}/src/lib/net/tcpv4.o: nbproject/Makefile-${CND_CONF}.mk src/lib/net/tcpv4.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/lib/net
	${RM} $@.d
	$(COMPILE.cc) -g -Wall -I/home/batas2/Pobrane/boost_1_41_0 -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/lib/net/tcpv4.o src/lib/net/tcpv4.cpp

# Subprojects
.build-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r build/Debug
	${RM} dist/Debug/GNU-Linux-x86/threadserwer

# Subprojects
.clean-subprojects:

# Enable dependency checking
.dep.inc: .depcheck-impl

include .dep.inc
