TARGET = program
#TARGET_PATH = #Compiled
SOURCE_PATHS = #Core Core\Class Core\UserInterface Core\Utilities
BUILD_PATH = Compiled\Build
INCLUDE_PATHS := \
	-I'$(CURDIR)' \
	-I'H:\My Stuff\Game Development\C\Libraries\glfw-3.3.bin.WIN64\include' \
	-I'C:\VulkanSDK\1.1.121.2\Include'
	#-I'H:\My Stuff\Game Development\C\Libraries\PDCurses-3.8'
LIBRARY_PATHS = \
	-L'H:\My Stuff\Game Development\C\Libraries\glfw-3.3.bin.WIN64\lib-mingw-w64' \
	-L'C:\VulkanSDK\1.1.121.2\Lib'
	#-L'H:\My Stuff\Game Development\C\Libraries\PDCurses-3.8\wincon'
LIBS = -lm -lglfw3 -lgdi32 -lvulkan-1
CC = x86_64-w64-mingw32-gcc
CFLAGS = -g3 -Og -std=c99 -pedantic -Wall -Wno-unused -fstrict-aliasing #-save-temps
BUILD_TYPE = -c

#SPICY STUFF THAT I DO NOT KNOW
subdirs = $(filter-out $1,$(sort $(dir $(wildcard $1*/))))
rfind = $(wildcard $1$2) $(foreach dir,$(call subdirs,$1),$(call rfind,$(dir),$2))

SUB_DIRS := $(call rfind,./,*/.)
SUB_DIRS := $(subst ./,,$(SUB_DIRS))
SUB_DIRS := $(subst /.,,$(SUB_DIRS))
ifdef DEBUGVERBOSE
$(info $(SUB_DIRS))
endif
VPATH := $(SUB_DIRS)

.PHONY: clean all default

default: $(TARGET)
all: default

SOURCEFILES = $(wildcard *.c)
SOURCEFILES += $(foreach path, $(SUB_DIRS), \
	$(wildcard $(path)/*.c))
SOURCEFILES_NOPATH = $(notdir $(SOURCEFILES))

HEADERFILES = $(wildcard *.h)
HEADERFILES += $(foreach path, $(SUB_DIRS), \
	$(wildcard $(path)/*.h))
HEADERFILES_NOPATH = $(notdir $(HEADERFILES))

OBJECTFILES_NOPATH = $(patsubst %.c, %.o, $(SOURCEFILES_NOPATH))
OBJECTFILES = $(addprefix $(BUILD_PATH)/,$(OBJECTFILES_NOPATH))

ifdef DEBUGVERBOSE
$(info _INCLUDEPATH: $(INCLUDE_PATHS))
$(info _LIBRARYPATH: $(LIBRARY_PATHS))
$(info _TARPATH: $(TARGET_PATH))
$(info _SRCPATH: $(SUB_DIRS))
$(info )
$(info _HDR: $(HEADERFILES_NOPATH))
$(info _SRC: $(SOURCEFILES_NOPATH))
$(info _OBJ: $(OBJECTFILES_NOPATH))
$(info )
$(info _SRC PATH: $(SOURCEFILES))
$(info _OBJ PATH: $(OBJECTFILES))
$(info _HDR PATH: $(HEADERFILES))
$(info )
endif

.PRECIOUS: $(SOURCEFILES) $(HEADERFILES) $(OBJECTFILES) $(SOURCEFILES_NOPATH) $(HEADERFILES_NOPATH) $(OBJECTFILES_NOPATH)

#STATIC PATTERN
$(OBJECTFILES): $(BUILD_PATH)/%.o: %.c $(HEADERFILES)
	@echo BUILDING $@ TO $(BUILD_PATH)
	$(CC) $(CFLAGS) $(INCLUDE_PATHS) $(BUILD_TYPE) $< -o $@

$(TARGET): $(OBJECTFILES)
	@echo COMPILING
	$(CC) $(OBJECTFILES) $(INCLUDE_PATHS) $(LIBRARY_PATHS) -Wall $(LIBS) -o $@.exe

run:
	$(TARGET) -Wall
clean:
	del /F $(TARGET).exe
	del /F $(BUILD_PATH)\\*.o
