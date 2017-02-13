#Compiler and Linker
CROSS_COMPILE	:= 
CC          	:= g++

#The Target Binary Program
TARGET      := AutomationApp

#The Directories, Source, Includes, Objects, Binary and Resources
SRCDIR      := src
INCDIR      := inc
BUILDDIR    := obj
TARGETDIR   := bin
RESDIR      := res
SRCEXT      := cpp
SRCEXT++    := c
DEPEXT      := d
OBJEXT      := o

#Flags, Libraries and Includes
CFLAGS      := -std=c++0x -Wall -ggdb
LFLAGS 	    := -std=c++0x -O3 -ggdb
LIBPATH		:= -L/home/ariel/raspberry/interfone/projetos/libs/sqlite-raspberry
LIB         := -lsqlite3 -lpthread -ldl
INC         := -I$(INCDIR) -I/usr/local/include -I/home/ariel/raspberry/interfone/projetos/libs/sqlite
INCDEP      := -I$(INCDIR)

#---------------------------------------------------------------------------------
#DO NOT EDIT BELOW THIS LINE
#---------------------------------------------------------------------------------
SOURCES := $(shell find $(SRCDIR) -iname '*.'$(SRCEXT)) 
#OBJECTS := obj/main.o obj/Dht11.o
OBJECTS := $(patsubst $(SRCDIR)/%,$(BUILDDIR)/%,$(SOURCES:.$(SRCEXT)=.$(OBJEXT)))


all: directories $(TARGET)

#Make the Directories
directories:
	@mkdir -p $(TARGETDIR)
	@mkdir -p $(BUILDDIR)

$(TARGET): $(OBJECTS)
	$(CROSS_COMPILE)$(CC) $(LFLAGS) $(OBJECTS) -o $(TARGETDIR)/$@ $(SDL) $(LIBPATH) $(LIB)

$(BUILDDIR)/%.$(OBJEXT):$(SRCDIR)/%.$(SRCEXT)
	@mkdir -p $(dir $@)
	$(CROSS_COMPILE)$(CC) $(CFLAGS) $(INC) -c -o $@ $<
	@$(CROSS_COMPILE)$(CC) $(CFLAGS) $(INCDEP) -MM $(SRCDIR)/$*.$(SRCEXT) > $(BUILDDIR)/$*.$(DEPEXT)
	@cp -f $(BUILDDIR)/$*.$(DEPEXT) $(BUILDDIR)/$*.$(DEPEXT).tmp
	@sed -e 's|.*:|$(BUILDDIR)/$*.$(OBJEXT):|' < $(BUILDDIR)/$*.$(DEPEXT).tmp > $(BUILDDIR)/$*.$(DEPEXT)
	@sed -e 's/.*://' -e 's/\\$$//' < $(BUILDDIR)/$*.$(DEPEXT).tmp | fmt -1 | sed -e 's/^ *//' -e 's/$$/:/' >> $(BUILDDIR)/$*
	$(CROSS_COMPILE)$(CC) $(CFLAGS) -c $< -o $@ -I.

clean:
	@$(RM) -rf $(BUILDDIR)

#Non-File Targets
.PHONY: all clean
