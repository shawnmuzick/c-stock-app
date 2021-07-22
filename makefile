LIBS = `pkg-config --libs libcurl json-c gtk+-3.0 cairo` 
CFLAGS = `pkg-config --cflags gtk+-3.0 cairo`

all: main

main: objs
	gcc *.o $(LIBS) -lm -rdynamic -o ./builds/linux/main 
	mv *.o ./builds/linux
	cp main.glade ./builds/linux
objs:
	gcc *.c -c $(CFLAGS) 
clean_linux:
	rm -r ./builds/linux/*.o	
	rm -r ./builds/linux/main
	rm -r ./builds/linux/*.png
test_linux:
	./builds/linux/main
windows: 
	x86_64-w64-mingw32-gcc *.c $(CFLAGS) $(LIBS) -lm -o main.exe
