# Cengiz Başaran
# Ingenico.TR
# 2015/11/26

.SILENT:

CPPC=g++
CC=gcc
LD=g++

BASE_DIR=../..
OUT_DIR_X64=$(BASE_DIR)/DLL/Linux/x64
OUT_DIR_X86=$(BASE_DIR)/DLL/Linux/x86
OUT_DIR_DEBUG_X64=$(BASE_DIR)/DLL_DEBUG/Linux/x64
OUT_DIR_DEBUG_X86=$(BASE_DIR)/DLL_DEBUG/Linux/x86
ifdef DEBIAN
	OUT_DIR_X64=$(BASE_DIR)/DLL/Linux/x64_DEBIAN
	OUT_DIR_DEBUG_X64=$(BASE_DIR)/DLL_DEBUG/Linux/x64_DEBIAN
endif

OBJ_DIR_X64=$(OUT_DIR_X64)/ConsoleAppObj
OBJ_DIR_X86=$(OUT_DIR_X86)/ConsoleAppObj
OBJ_DIR_DEBUG_X64=$(OUT_DIR_DEBUG_X64)/ConsoleAppObj
OBJ_DIR_DEBUG_X86=$(OUT_DIR_DEBUG_X86)/ConsoleAppObj

C_APP_FILE_X64=$(OUT_DIR_X64)/ConsoleApp
C_APP_FILE_X86=$(OUT_DIR_X86)/ConsoleApp
C_APP_FILE_DEBUG_X64=$(OUT_DIR_DEBUG_X64)/ConsoleApp
C_APP_FILE_DEBUG_X86=$(OUT_DIR_DEBUG_X86)/ConsoleApp

CPP_APP_FILE_X64=$(OUT_DIR_X64)/CppConsoleApp
CPP_APP_FILE_X86=$(OUT_DIR_X86)/CppConsoleApp
CPP_APP_FILE_DEBUG_X64=$(OUT_DIR_DEBUG_X64)/CppConsoleApp
CPP_APP_FILE_DEBUG_X86=$(OUT_DIR_DEBUG_X86)/CppConsoleApp

INC_DIR=$(BASE_DIR)/Inc
LINUX_CLASS_DIR=$(BASE_DIR)/LinuxClass

SRC_DIR=$(BASE_DIR)/Simulator/Console

HEADER_FILES  = $(INC_DIR)/GMPSmartDLL.h
HEADER_FILES += $(LINUX_CLASS_DIR)/IngGMPSmartDLL.h

C_SOURCE_FILES  = main.c

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
LFLAGS = -ldl

CFLAGS_X64= -m64 -fPIC -fpack-struct=8 -DING_LINUX_64
CPPFLAGS_X64= -m64 -fPIC -fpack-struct=8 -DING_LINUX_64
LFLAGS_X64= -m64

CFLAGS_X86= -m32 -fpack-struct=8 -DING_LINUX_32
CPPFLAGS_X86= -m32 -fpack-struct=8 -DING_LINUX_32
LFLAGS_X86= -m32 -L/usr/lib32/

CFLAGS_NON_DEBUG = -Werror
CPPFLAGS_NON_DEBUG = -Werror
CFLAGS_DEBUG = -g3 -D_DEBUG
CPPFLAGS_DEBUG = -g3 -D_DEBUG

DEPENDANCY_FILES=makefile $(HEADER_FILES)

# ------------------------------    x64    ---------------------------------------
$(OBJ_DIR_X64)/%.o: $(SRC_DIR)/%.c $(DEPENDANCY_FILES)
	echo compiling x64 : $(notdir $<) - $(notdir $@)
	mkdir -p $(@D)
	$(CC) $(INCLUDE_DIRS) $(DEFINITIONS) $(CFLAGS) $(CFLAGS_X64) $(CFLAGS_NON_DEBUG) -c $< -o $@ 

$(OBJ_DIR_X64)/%.o: $(SRC_DIR)/%.cpp $(DEPENDANCY_FILES)
	echo compiling x64 : $(notdir $<) - $(notdir $@)
	mkdir -p $(@D)
	$(CPPC) $(INCLUDE_DIRS) $(DEFINITIONS) $(CPPFLAGS) $(CPPFLAGS_X64) $(CPPFLAGS_NON_DEBUG) -c $< -o $@

$(OBJ_DIR_X64)/%.o: $(LINUX_CLASS_DIR)/%.cpp $(DEPENDANCY_FILES)
	echo compiling x64 : $(notdir $<) - $(notdir $@)
	mkdir -p $(@D)
	$(CPPC) $(INCLUDE_DIRS) $(DEFINITIONS) $(CPPFLAGS) $(CPPFLAGS_X64) $(CPPFLAGS_NON_DEBUG) -c $< -o $@

$(C_APP_FILE_X64): $(addprefix $(OBJ_DIR_X64)/,$(C_OBJS))
	echo Linking x64 ConsoleApp ...
	$(LD) $(LFLAGS_X64) $(addprefix $(OBJ_DIR_X64)/,$(C_OBJS)) $(LIBS) -o $@ $(LFLAGS)
	echo --------------- $(C_APP_FILE_X64) Created. ---------------

$(CPP_APP_FILE_X64): $(addprefix $(OBJ_DIR_X64)/,$(CPP_OBJS))
	echo Linking x64 CppConsoleApp ...
	$(LD) $(LFLAGS_X64) $(addprefix $(OBJ_DIR_X64)/,$(CPP_OBJS)) $(LIBS) -o $@ $(LFLAGS)
	echo --------------- $(CPP_APP_FILE_X64) Created. ---------------
# ------------------------------    x64    ---------------------------------------

# ------------------------------    x86    ---------------------------------------
$(OBJ_DIR_X86)/%.o: $(SRC_DIR)/%.c $(DEPENDANCY_FILES)
	echo compiling x86 : $(notdir $<) - $(notdir $@)
	mkdir -p $(@D)
	$(CC) $(INCLUDE_DIRS) $(DEFINITIONS) $(CFLAGS) $(CFLAGS_X86) $(CFLAGS_NON_DEBUG) -c $< -o $@

$(OBJ_DIR_X86)/%.o: $(SRC_DIR)/%.cpp $(DEPENDANCY_FILES)
	echo compiling x86 : $(notdir $<) - $(notdir $@)
	mkdir -p $(@D)
	$(CPPC) $(INCLUDE_DIRS) $(DEFINITIONS) $(CPPFLAGS) $(CPPFLAGS_X86) $(CPPFLAGS_NON_DEBUG) -c $< -o $@

$(OBJ_DIR_X86)/%.o: $(LINUX_CLASS_DIR)/%.cpp $(DEPENDANCY_FILES)
	echo compiling x86 : $(notdir $<) - $(notdir $@)
	mkdir -p $(@D)
	$(CPPC) $(INCLUDE_DIRS) $(DEFINITIONS) $(CPPFLAGS) $(CPPFLAGS_X86) $(CPPFLAGS_NON_DEBUG) -c $< -o $@

$(C_APP_FILE_X86): $(addprefix $(OBJ_DIR_X86)/,$(C_OBJS))
	echo Linking x86 ConsoleApp ...
	$(LD) $(LFLAGS_X86) $(addprefix $(OBJ_DIR_X86)/,$(C_OBJS)) $(LIBS) -o $@ $(LFLAGS) 
	echo --------------- $(C_APP_FILE_X86) Created. ---------------

$(CPP_APP_FILE_X86): $(addprefix $(OBJ_DIR_X86)/,$(CPP_OBJS))
	echo Linking x86 CppConsoleApp ...
	$(LD) $(LFLAGS_X86) $(addprefix $(OBJ_DIR_X86)/,$(CPP_OBJS)) $(LIBS) -o $@ $(LFLAGS) 
	echo --------------- $(CPP_APP_FILE_X86) Created. ---------------
# ------------------------------    x86    ---------------------------------------

# ------------------------------ DEBUG x64 ---------------------------------------
$(OBJ_DIR_DEBUG_X64)/%.o: $(SRC_DIR)/%.c $(DEPENDANCY_FILES)
	echo compiling DEBUG x64 : $(notdir $<) - $(notdir $@)
	mkdir -p $(@D)
	$(CC) $(INCLUDE_DIRS) $(DEFINITIONS) $(CFLAGS) $(CFLAGS_X64) $(CFLAGS_DEBUG) -c $< -o $@

$(OBJ_DIR_DEBUG_X64)/%.o: $(SRC_DIR)/%.cpp $(DEPENDANCY_FILES)
	echo compiling DEBUG x64 : $(notdir $<) - $(notdir $@)
	mkdir -p $(@D)
	$(CPPC) $(INCLUDE_DIRS) $(DEFINITIONS) $(CPPFLAGS) $(CPPFLAGS_X64) $(CPPFLAGS_DEBUG) -c $< -o $@

$(OBJ_DIR_DEBUG_X64)/%.o: $(LINUX_CLASS_DIR)/%.cpp $(DEPENDANCY_FILES)
	echo compiling DEBUG x64 : $(notdir $<) - $(notdir $@)
	mkdir -p $(@D)
	$(CPPC) $(INCLUDE_DIRS) $(DEFINITIONS) $(CPPFLAGS) $(CPPFLAGS_X64) $(CPPFLAGS_DEBUG) -c $< -o $@

$(C_APP_FILE_DEBUG_X64): $(addprefix $(OBJ_DIR_DEBUG_X64)/,$(C_OBJS))
	echo Linking DEBUG x64 ConsoleApp ...
	$(LD) $(LFLAGS_X64) $(addprefix $(OBJ_DIR_DEBUG_X64)/,$(C_OBJS)) $(LIBS) -o $@ $(LFLAGS) 
	echo --------------- $(C_APP_FILE_DEBUG_X64) Created. ---------------

$(CPP_APP_FILE_DEBUG_X64): $(addprefix $(OBJ_DIR_DEBUG_X64)/,$(CPP_OBJS))
	echo Linking DEBUG x64 CppConsoleApp ...
	$(LD) $(LFLAGS_X64) $(addprefix $(OBJ_DIR_DEBUG_X64)/,$(CPP_OBJS)) $(LIBS) -o $@ $(LFLAGS) 
	echo --------------- $(CPP_APP_FILE_DEBUG_X64) Created. ---------------
# ------------------------------ DEBUG x64 ---------------------------------------

# ------------------------------ DEBUG x86 ---------------------------------------
$(OBJ_DIR_DEBUG_X86)/%.o: $(SRC_DIR)/%.c $(DEPENDANCY_FILES)
	echo compiling DEBUG x86 : $(notdir $<) - $(notdir $@)
	mkdir -p $(@D)
	$(CC) $(INCLUDE_DIRS) $(DEFINITIONS) $(CFLAGS) $(CFLAGS_X86) $(CFLAGS_DEBUG) -c $< -o $@ 

$(OBJ_DIR_DEBUG_X86)/%.o: $(SRC_DIR)/%.cpp $(DEPENDANCY_FILES)
	echo compiling DEBUG x86 : $(notdir $<) - $(notdir $@)
	mkdir -p $(@D)
	$(CPPC) $(INCLUDE_DIRS) $(DEFINITIONS) $(CPPFLAGS) $(CPPFLAGS_X86) $(CPPFLAGS_DEBUG) -c $< -o $@

$(OBJ_DIR_DEBUG_X86)/%.o: $(LINUX_CLASS_DIR)/%.cpp $(DEPENDANCY_FILES)
	echo compiling DEBUG x86 : $(notdir $<) - $(notdir $@)
	mkdir -p $(@D)
	$(CPPC) $(INCLUDE_DIRS) $(DEFINITIONS) $(CPPFLAGS) $(CPPFLAGS_X86) $(CPPFLAGS_DEBUG) -c $< -o $@

$(C_APP_FILE_DEBUG_X86): $(addprefix $(OBJ_DIR_DEBUG_X86)/,$(C_OBJS))
	echo Linking DEBUG x86 ConsoleApp ...
	$(LD) $(LFLAGS_X86) $(addprefix $(OBJ_DIR_DEBUG_X86)/,$(C_OBJS)) $(LIBS) -o $@ $(LFLAGS) 
	echo --------------- $(C_APP_FILE_DEBUG_X86) Created. ---------------

$(CPP_APP_FILE_DEBUG_X86): $(addprefix $(OBJ_DIR_DEBUG_X86)/,$(CPP_OBJS))
	echo Linking DEBUG x86 CppConsoleApp ...
	$(LD) $(LFLAGS_X86) $(addprefix $(OBJ_DIR_DEBUG_X86)/,$(CPP_OBJS)) $(LIBS) -o $@ $(LFLAGS) 
	echo --------------- $(C_APP_FILE_DEBUG_X86) Created. ---------------
# ------------------------------ DEBUG x86 ---------------------------------------

NEEDED=$(C_APP_FILE_X64) $(C_APP_FILE_X86) $(C_APP_FILE_DEBUG_X64) $(C_APP_FILE_DEBUG_X86) $(CPP_APP_FILE_X64) $(CPP_APP_FILE_X86) $(CPP_APP_FILE_DEBUG_X64) $(CPP_APP_FILE_DEBUG_X86)
ifdef DEBIAN
NEEDED=$(C_APP_FILE_X64) $(C_APP_FILE_DEBUG_X64) $(CPP_APP_FILE_X64) $(CPP_APP_FILE_DEBUG_X64)
endif

.PHONY: X64
X64: $(C_APP_FILE_X64)

.PHONY: X86
X86: $(C_APP_FILE_X86)

.PHONY: DX64
DX64: $(C_APP_FILE_DEBUG_X64)

.PHONY: DX86
DX86: $(C_APP_FILE_DEBUG_X86)

.PHONY: CPPX64
CPPX64: $(CPP_APP_FILE_X64)

.PHONY: CPPX86
CPPX86: $(CPP_APP_FILE_X86)

.PHONY: CPPDX64
CPPDX64: $(CPP_APP_FILE_DEBUG_X64)

.PHONY: CPPDX86
CPPDX86: $(CPP_APP_FILE_DEBUG_X86)

.PHONY: all
all: $(NEEDED)
	echo Compile and link done..
	echo ======================== T H E = E N D ========================

.PHONY: clean
clean:
	rm -f $(OBJ_DIR_X64)/*.o
	rm -f $(OBJ_DIR_X86)/*.o
	rm -f $(OBJ_DIR_DEBUG_X64)/*.o
	rm -f $(OBJ_DIR_DEBUG_X86)/*.o
	rm -f $(C_APP_FILE_X64)
	rm -f $(C_APP_FILE_X86)
	rm -f $(C_APP_FILE_DEBUG_X64)
	rm -f $(C_APP_FILE_DEBUG_X86)
	rm -f $(CPP_APP_FILE_X64)
	rm -f $(CPP_APP_FILE_X86)
	rm -f $(CPP_APP_FILE_DEBUG_X64)
	rm -f $(CPP_APP_FILE_DEBUG_X86)
	#rmdir $(OBJ_DIR_X64)
	#rmdir $(OBJ_DIR_X86)
	#rmdir $(OBJ_DIR_DEBUG_X64)
	#rmdir $(OBJ_DIR_DEBUG_X86)

