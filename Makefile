.PHONY: all clean

all: prnt

prnt: main.cpp rp.cpp
	cl /nologo /std:c++17 /Od /EHsc /DUNICODE /D_UNICODE /Fe:prnt main.cpp rp.cpp

clean:
	del *.obj
	del *.exe
