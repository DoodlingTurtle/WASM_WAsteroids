CC:=emcc
CPP:=em++

ASSETSDIR:=assets
RELEASEDIR:=release

################################################################################
#you need to edit anything after this
################################################################################

CCSOURCEFILES:=$(wildcard ./*/*/*/*.c) $(wildcard ./*/*/*.c) $(wildcard ./*/*.c)
CPPSOURCEFILES:=$(wildcard ./*/*/*/*.cpp) $(wildcard ./*/*/*.cpp) $(wildcard */*.cpp) 

OBJFILES:=$(patsubst %.c,%.c.o,$(CCSOURCEFILES)) $(patsubst %.cpp,%.cpp.o,$(CPPSOURCEFILES)) 

TARGET:=main
FLAGS:=-std=c++17 

$(TARGET).html:$(OBJFILES)
	$(CPP) $^ -O1 -o $@ -s EXPORTED_RUNTIME_METHODS=ccall,cwrap,getValue,setValue,stringToUTF8,UTF8ToString -s ERROR_ON_UNDEFINED_SYMBOLS=0 -s ALLOW_MEMORY_GROWTH=1 -s MAX_WEBGL_VERSION=2 -s MIN_WEBGL_VERSION=2 -s USE_LIBPNG=1 --preload-file ./assets $(FLAGS)

release:$(TARGET).html
	$(shell rm -f $(RELEASEDIR)/$(TARGET).wasm)
	$(shell rm -f $(RELEASEDIR)/$(TARGET).js)
	$(shell rm -f $(RELEASEDIR)/$(TARGET).data)
	$(shell cp $(TARGET).js $(RELEASEDIR)/) 
	$(shell cp $(TARGET).wasm $(RELEASEDIR)/) 
	$(shell cp $(TARGET).data $(RELEASEDIR)/) 

run:release
	emrun $(RELEASEDIR)/index.html --port 8080

debug:release
	emrun $(TARGET).html --port 8080

%.c.o:%.c
	$(CC) $^ -o $@ -c

%.cpp.o:%.cpp
	$(CPP) $^ -o $@ -c $(FLAGS)

.PHONY: clean
	
clean:
	$(shell rm -f $(TARGET).html)
	$(shell rm -f $(TARGET).js)
	$(shell rm -f $(TARGET).wasm)
	$(shell rm -f $(TARGET).data)
	$(shell rm -f $(OBJFILES))
