flags = -Wshadow -Winit-self -Wredundant-decls -Wcast-align -Wundef -Wfloat-equal -Winline -Wunreachable-code -Wmissing-declarations -Wmissing-include-dirs -Wswitch-enum -Wswitch-default -Weffc++ -Wmain -Wextra -Wall -g -pipe -fexceptions -Wcast-qual -Wconversion -Wctor-dtor-privacy -Wempty-body -Wformat-security -Wformat=2 -Wignored-qualifiers -Wlogical-op -Wno-missing-field-initializers -Wnon-virtual-dtor -Woverloaded-virtual -Wpointer-arith -Wsign-promo -Wstack-usage=8192 -Wstrict-aliasing -Wstrict-null-sentinel -Wtype-limits -Wwrite-strings -Werror=vla -D_DEBUG -D_EJUDGE_CLIENT_SIDE

list_cpp = ./src/main.cpp ./src/listFunctions.cpp ./src/listAccessFunctions.cpp ./src/classicListFunctions.cpp

list_all = ./include/listFunctions.h ./include/structsAndConsts.h ./include/listAccessFunctions.h ./include/classicListFunctions.h ./include/testFunctions.h $(list_cpp)

build:
	@echo -------------------------------------------------------------------------
	g++ ./src/main.cpp ./src/listFunctions.cpp ./src/listAccessFunctions.cpp ./src/classicListFunctions.cpp ./src/testFunctions.cpp $(flags) -o ./build/list.exe

run:
	./build/list.exe
