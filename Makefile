CPP:=em++

ASSETSDIR:=assets
RELEASEDIR:=release



CPPSOURCEFILES:=$(wildcard ./*/*/*/*.cpp) $(wildcard ./*/*/*.cpp) $(wildcard */*.cpp) 

OBJFILES:=$(patsubst %.cpp,%.cpp.o,$(CPPSOURCEFILES)) 

TARGET:=main
FLAGS:=-std=c++17 
LINKERFLAGS:= -s EXPORTED_RUNTIME_METHODS=ccall,cwrap,getValue,setValue,stringToUTF8,UTF8ToString -s ERROR_ON_UNDEFINED_SYMBOLS=0 -s ALLOW_MEMORY_GROWTH=1 -s MAX_WEBGL_VERSION=2 -s MIN_WEBGL_VERSION=2 -s USE_LIBPNG=1

$(TARGET).html:$(OBJFILES)
	$(CPP) $^ -O1 -o $@ $(LINKERFLAGS) --preload-file ./assets $(FLAGS)

$(TARGET).js:$(OBJFILES)	
	$(CPP) $^ -O3 -o $@ $(LINKERFLAGS) --preload-file ./assets $(FLAGS)

run:$(TARGET).html
	emrun index.html --port 8080

debug:$(TARGET).html
	emrun $(TARGET).html --port 8080

%.cpp.o:%.cpp
	$(CPP) $^ -o $@ -c $(FLAGS)


.PHONY: clean, emsetup, release

release:
	rm -f $(RELEASEDIR)/$(TARGET).* ./$(TARGET).*
	make $(TARGET).js
	cp $(TARGET).* $(RELEASEDIR)/

clean:
	$(shell rm -f $(TARGET).* $(OBJFILES))

emsetup:
	$(CPP) src/main.cpp -o deleteme.wasm $(LINKERFLAGS) $(FLAGS)
	rm ./deleteme.wasm

