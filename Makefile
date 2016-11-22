CC=g++

all: creator viewer

chas: chasiki

creator: bin PALib.o grap.o creator.o 
	$(CC) ./obj/creator.o ./obj/grap.o ./obj/PALib.o -o ./bin/creator

viewer: bin	PALib.o grap.o viewer.o 
	$(CC) ./obj/viewer.o ./obj/grap.o ./obj/PALib.o -o ./bin/viewer
	
grap.o: obj ./head/grap.cpp
	$(CC) -c ./head/grap.cpp -o ./obj/grap.o

PALib.o: obj ./head/PALib.cpp
	$(CC) -c ./head/PALib.cpp -o ./obj/PALib.o
	
creator.o: obj ./source/creator.cpp
	$(CC) -c ./source/creator.cpp -o ./obj/creator.o
	
viewer.o: obj ./source/viewer.cpp
	$(CC) -c ./source/viewer.cpp -o ./obj/viewer.o
	
obj: 
	mkdir .\obj

bin:
	mkdir .\bin
	
clean:
	del /Q .\obj\* .\bin\*