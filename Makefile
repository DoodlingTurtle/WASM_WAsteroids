CPP:=em++
RELEASEDIR:=release

TARGET:=main
COMMON_FLAGS:=-std=c++17 
LINKERFLAGS:= --preload-file ./assets -s EXPORTED_RUNTIME_METHODS=ccall,cwrap,getValue,setValue,stringToUTF8,UTF8ToString -s ERROR_ON_UNDEFINED_SYMBOLS=0 -s ALLOW_MEMORY_GROWTH=1 -s MAX_WEBGL_VERSION=2 -s MIN_WEBGL_VERSION=2 -s USE_OGG=1 -s USE_SDL_MIXER=1 -s USE_LIBPNG=1DEBUG_FLAGS:= $(FLAGS) -DDEBUG_BUILD -s ASSERTIONS=2 -s SAFE_HEAP=1 -s STACK_OVERFLOW_CHECK

RELEASE_FLAGS:= $(COMMON_FLAGS) -O3
DEBUG_FLAGS  := $(COMMON_FLAGS) -DDEBUG_BUILD --emrun

FLAGS:=$(DEBUG_FLAGS)
CPPSOURCEFILES:=$(wildcard ./*/*/*/*.cpp) $(wildcard ./*/*/*.cpp) $(wildcard */*.cpp) 
OBJFILES:=$(patsubst %.cpp,%.cpp.o,$(CPPSOURCEFILES)) 


$(TARGET).html:$(OBJFILES)
	$(CPP) $^ -g -o $@ $(LINKERFLAGS) $(FLAGS)

run: $(TARGET).html
	emrun index.html

release: FLAGS:=$(RELEASE_FLAGS)
release: clean $(TARGET).js
	cp $(TARGET).* $(RELEASEDIR)/
	$(shell make clean)

$(TARGET).js:$(OBJFILES)	
	$(CPP) $^ -o $@ $(LINKERFLAGS) $(FLAGS)
	
%.cpp.o:%.cpp
	$(CPP) $^ -o $@ -c $(FLAGS)  


.PHONY: emsetup, clean
	
clean: 
	$(shell rm -f $(TARGET).* $(OBJFILES))

emsetup:
	$(CPP) src/main.cpp -o deleteme.* $(LINKERFLAGS) $(DEBUG_FLAGS)
	rm ./deleteme.wasm

