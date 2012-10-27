
PREFIX=/usr

ARCH=$(shell uname -m)

PROJECT=TurionPowerControl
PROJ_CXXFLAGS=-O2 $(CXXFLAGS) $(shell getconf LFS_CFLAGS)
PROJ_LDFLAGS=$(LDFLAGS)
PROJ_LIBS=$(LIBS) -lrt

OBJROOT=obj
OBJDIR=$(OBJROOT)/$(ARCH)

SOURCES=TurionPowerControl.cpp \
	config.cpp \
	cpuPrimitives.cpp \
	Griffin.cpp \
	K10Processor.cpp \
	Brazos.cpp \
	Llano.cpp \
	Interlagos.cpp \
	MSRObject.cpp \
	MSVC_Round.cpp \
	PCIRegObject.cpp \
	PerformanceCounter.cpp \
	Processor.cpp \
	K10PerformanceCounters.cpp \
	scaler.cpp \
	Signal.cpp

OBJECTS=$(SOURCES:%.cpp=$(OBJDIR)/%.o)
DEPS=$(SOURCES:%.cpp=$(OBJDIR)/.%.d)

all: $(OBJDIR) $(PROJECT)

version.h:
	${shell BRANCH=$$(svn info | sed -nr '/URL:/{s=(.*/)([^/]*$$)=\2=;p}') ; REV=$$(svnversion) ; [ "$$BRANCH" != "" -a "$$REV" != "" ] && A=\"$$BRANCH-r$$REV\" || A=\"export\" ;  if [ "$$A" != "$$(cat version.h 2> /dev/null | cut -f 3 -d \ )" ]; then echo \#define _SOURCE_VERSION $$A > version.h ; fi}
	@true

i386:
	$(MAKE) CXXFLAGS="-m32 -D_FILE_OFFSET_BITS=64" LDFLAGS="-m32" ARCH=i386

install:
	install -ps $(PROJECT) $(PREFIX)/bin

uninstall:
	$(RM) $(PREFIX)/bin/$(PROJECT)

$(PROJECT): $(OBJECTS)
	$(CXX) $(PROJ_LDFLAGS) -o $@ $(OBJECTS) $(PROJ_LIBS)

$(OBJDIR)/%.o: %.cpp
	$(CXX) $(PROJ_CXXFLAGS) -MMD -MF $(<:%.cpp=$(OBJDIR)/.%.d) -MT $(<:%.cpp=$(OBJDIR)/%.o) -c -o $@ $<

$(OBJDIR):
	mkdir -p $(OBJDIR)

clean:
	$(RM) $(OBJECTS) $(PROJECT)
	
distclean: clean
	$(RM) -r $(OBJROOT)
	$(RM) core core.[0-9]
	$(RM) *~ DEADJOE *.orig *.rej *.i *.r[0-9]* *.mine

.PHONY: clean distclean all install uninstall i386 version.h

-include $(DEPS)
