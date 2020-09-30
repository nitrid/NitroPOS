# Cengiz Başaran
# Ingenico.TR
# 2015/11/26

.SILENT:
COMPILER_DIR=$(HOME)/raspberrypi/tools/arm-bcm2708/arm-linux-gnueabihf/bin
CPPC=$(COMPILER_DIR)/arm-linux-gnueabihf-g++
CC=$(COMPILER_DIR)/arm-linux-gnueabihf-gcc
LD=$(COMPILER_DIR)/arm-linux-gnueabihf-g++

BASE_DIR=../..
OUT_DIR=$(BASE_DIR)/DLL/RaspberryPI/PI_3_ModelB
OUT_DIR_DEBUG=$(BASE_DIR)/DLL_DEBUG/RaspberryPI/PI_3_ModelB

OBJ_DIR=$(OUT_DIR)/ConsoleAppObj
OBJ_DIR_DEBUG=$(OUT_DIR_DEBUG)/ConsoleAppObj

C_APP_FILE=$(OUT_DIR)/ConsoleApp
C_APP_FILE_DEBUG=$(OUT_DIR_DEBUG)/ConsoleApp

CPP_APP_FILE=$(OUT_DIR)/CppConsoleApp
CPP_APP_FILE_DEBUG=$(OUT_DIR_DEBUG)/CppConsoleApp

INC_DIR=$(BASE_DIR)/Inc
LINUX_CLASS_DIR=$(BASE_DIR)/LinuxClass

SRC_DIR=$(BASE_DIR)/Simulator/Console_RPI

HEADER_FILES  = $(INC_DIR)/GMPSmartDLL.h
HEADER_FILES += $(LINUX_CLASS_DIR)/IngGMPSmartDLL.h

C_SOURCE_FILES = main.c

CPP_SOURCE_FILES  = CppConsoleApp.cpp
CPP_SOURCE_FILES += IngGMPSmartDLL.cpp

C_OBJS=$(sort $(patsubst %.cpp,%.o,$(patsubst %.c,%.o,$(C_SOURCE_FILES))))
CPP_OBJS=$(sort $(patsubst %.cpp,%.o,$(patsubst %.c,%.o,$(CPP_SOURCE_FILES))))

INCLUDE_DIRS=-I$(INC_DIR) -I$(LINUX_CLASS_DIR)

DEFINITIONS = -DLINUX
ifdef DEBIAN
DEFINITIONS += -DDEBIAN_VERSION
endif

LIBS = 

CFLAGS =  -Wall -W -Wdeclaration-after-statement -O2 -DLINUX
CPPFLAGS = -Wall -W -O2 -DLINUX
#LFLAGS = -Wl,--no-as-needed -ldl
LFLAGS = -ldl

CFLAGS_RPI= -fpack-struct=8 -DING_RASPBERRY_PI
CPPFLAGS_RPI= -fpack-struct=8 -DING_RASPBERRY_PI
LFLAGS_RPI= -L/home/swrd/raspberrypi/rootfs/usr/lib32/

CFLAGS_NON_DEBUG = -Werror
CPPFLAGS_NON_DEBUG = -Werror
CFLAGS_DEBUG = -g3 -D_DEBUG
CPPFLAGS_DEBUG = -g3 -D_DEBUG

DEPENDANCY_FILES=makefile $(HEADER_FILES)

# ------------------------------       ---------------------------------------
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c $(DEPENDANCY_FILES)
	echo compiling : $(notdir $<) - $(notdir $@)
	if [ ! -d "$(dir $@)" ]; then mkdir $(dir $@); fi
	$(CC) $(INCLUDE_DIRS) $(DEFINITIONS) $(CFLAGS) $(CFLAGS_RPI) $(CFLAGS_NON_DEBUG) -c $< -o $@

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp $(DEPENDANCY_FILES)
	echo compiling : $(notdir $<) - $(notdir $@)
	if [ ! -d "$(dir $@)" ]; then mkdir $(dir $@); fi
	$(CPPC) $(INCLUDE_DIRS) $(DEFINITIONS) $(CPPFLAGS) $(CPPFLAGS_RPI) $(CPPFLAGS_NON_DEBUG) -c $< -o $@

$(OBJ_DIR)/%.o: $(LINUX_CLASS_DIR)/%.cpp $(DEPENDANCY_FILES)
	echo compiling : $(notdir $<) - $(notdir $@)
	if [ ! -d "$(dir $@)" ]; then mkdir $(dir $@); fi
	$(CPPC) $(INCLUDE_DIRS) $(DEFINITIONS) $(CPPFLAGS) $(CPPFLAGS_RPI) $(CPPFLAGS_NON_DEBUG) -c $< -o $@

$(C_APP_FILE): $(addprefix $(OBJ_DIR)/,$(C_OBJS))
	echo Linking ConsoleApp ...
	$(LD) $(LFLAGS) $(addprefix $(OBJ_DIR)/,$(C_OBJS)) $(LIBS) -o $@ $(LFLAGS_RPI) 
	echo --------------- $(C_APP_FILE) Created. ---------------

$(CPP_APP_FILE): $(addprefix $(OBJ_DIR)/,$(CPP_OBJS))
	echo Linking CppConsoleApp ...
	$(LD) $(LFLAGS) $(addprefix $(OBJ_DIR)/,$(CPP_OBJS)) $(LIBS) -o $@ $(LFLAGS_RPI) 
	echo --------------- $(CPP_APP_FILE) Created. ---------------
# ------------------------------       ---------------------------------------

# ------------------------------ DEBUG ---------------------------------------
$(OBJ_DIR_DEBUG)/%.o: $(SRC_DIR)/%.c $(DEPENDANCY_FILES)
	echo compiling DEBUG : $(notdir $<) - $(notdir $@)
	if [ ! -d "$(dir $@)" ]; then mkdir $(dir $@); fi
	$(CC) $(INCLUDE_DIRS) $(DEFINITIONS) $(CFLAGS) $(CFLAGS_RPI) $(CFLAGS_DEBUG) -c $< -o $@ 

$(OBJ_DIR_DEBUG)/%.o: $(SRC_DIR)/%.cpp $(DEPENDANCY_FILES)
	echo compiling DEBUG : $(notdir $<) - $(notdir $@)
	if [ ! -d "$(dir $@)" ]; then mkdir $(dir $@); fi
	$(CPPC) $(INCLUDE_DIRS) $(DEFINITIONS) $(CPPFLAGS) $(CPPFLAGS_RPI) $(CPPFLAGS_DEBUG) -c $< -o $@

$(OBJ_DIR_DEBUG)/%.o: $(LINUX_CLASS_DIR)/%.cpp $(DEPENDANCY_FILES)
	echo compiling DEBUG : $(notdir $<) - $(notdir $@)
	if [ ! -d "$(dir $@)" ]; then mkdir $(dir $@); fi
	$(CPPC) $(INCLUDE_DIRS) $(DEFINITIONS) $(CPPFLAGS) $(CPPFLAGS_RPI) $(CPPFLAGS_DEBUG) -c $< -o $@

$(C_APP_FILE_DEBUG): $(addprefix $(OBJ_DIR_DEBUG)/,$(C_OBJS))
	echo Linking DEBUG ConsoleApp ...
	$(LD) $(LFLAGS) $(addprefix $(OBJ_DIR_DEBUG)/,$(C_OBJS)) $(LIBS) -o $@ $(LFLAGS_RPI) 
	echo --------------- $(C_APP_FILE_DEBUG) Created. ---------------

$(CPP_APP_FILE_DEBUG): $(addprefix $(OBJ_DIR_DEBUG)/,$(CPP_OBJS))
	echo Linking DEBUG CppConsoleApp ...
	$(LD) $(LFLAGS) $(addprefix $(OBJ_DIR_DEBUG)/,$(CPP_OBJS)) $(LIBS) -o $@ $(LFLAGS_RPI) 
	echo --------------- $(C_APP_FILE_DEBUG) Created. ---------------
# ------------------------------ DEBUG  ---------------------------------------

NEEDED=$(C_APP_FILE) $(C_APP_FILE_DEBUG) $(CPP_APP_FILE) $(CPP_APP_FILE_DEBUG)

.PHONY: all
all: $(NEEDED)
	echo Compile and link done..
	echo ======================== T H E = E N D ========================

.PHONY: clean
clean:
	rm -f $(OBJ_DIR)/*.o
	rm -f $(OBJ_DIR_DEBUG)/*.o
	rm -f $(C_APP_FILE)
	rm -f $(C_APP_FILE_DEBUG)
	rm -f $(CPP_APP_FILE)
	rm -f $(CPP_APP_FILE_DEBUG)
	#rmdir $(OBJ_DIR)
	#rmdir $(OBJ_DIR_DEBUG)
