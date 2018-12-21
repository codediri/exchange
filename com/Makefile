LOCAL_COM = ../com
LOCAL_LIB = ../lib
LOCAL_SRC = ../src
LOCAL_BIN = ../bin

SYS_LIB = /usr/local/lib

SBAPP_COMPILE = g++ -c
SBAPP_LINK = g++ -g -o 

COMPILEFLAGS = -g -w -Wall -fpermissive -std=c++11
LINKLIBS = -L$(SYS_LIB)

SBAPP_BINARY = Exchange
SBAPP_LIBRARY = libExchange.la

#Compilation source files - all cc files from LOCAL_SRC
SOURCES=$(foreach LOC_SRC,$(LOCAL_SRC),$(wildcard $(LOC_SRC)/*.cc)) 

#Source compilation results
OBJECTS=$(SOURCES:.cc=.o) 
LIBOBJECTS=$(SOURCES:.cc=.o) 

#Compilation dependencies files
DFILES=$(SOURCES:.cc=.d)

all: $(SBAPP_BINARY) 

$(SBAPP_BINARY): $(OBJECTS) 
	$(SBAPP_LINK) $(LOCAL_LIB)/$(SBAPP_LIBRARY) $(LIBOBJECTS) $(LINKLIBS)
	$(SBAPP_LINK) $(LOCAL_BIN)/$(SBAPP_BINARY)_debug $(LIBOBJECTS) $(LINKLIBS)
	strip $(LOCAL_BIN)/$(SBAPP_BINARY)_debug -o $(LOCAL_BIN)/$(SBAPP_BINARY)
	rm -f $(LOCAL_SRC)/*.o rm -f $(LOCAL_SRC)/*.d

%.o: %.cc
	$(SBAPP_COMPILE) $< $(COMPILEFLAGS) -o $@
   
clean:
	rm -f $(LOCAL_BIN)/$(SBAPP_BINARY) $(LOCAL_BIN)/$(SBAPP_BINARY)_debug
	rm -f $(LOCAL_LIB)/$(SBAPP_LIBRARY)
	rm -rf $(LOCAL_SRC)/.libs $(LOCAL_LIB)/.libs
	rm -f $(LOCAL_SRC)/*.lo rm -f $(LOCAL_SRC)/*.o rm -f $(LOCAL_SRC)/*.d
    
cleanlocal:
	rm -f $(LOCAL_SRC)/*.lo rm -f $(LOCAL_SRC)/*.o rm -f $(LOCAL_SRC)/*.d
       
app:
	make clean
	make
	make cleanlocal

-include $(DFILES)


