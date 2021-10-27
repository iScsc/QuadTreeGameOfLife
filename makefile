_DEBUG = $(if $(DEBUG),-D DEBUG,)
_OPT = $(if $(OPT),-O3 -flto,)
CC = gcc
CFLAGS = -g -std=c99 -Wall $(_OPT) -I include/ $(_DEBUG)
CLIB = -lm -lSDL2main -lSDL2 #for libs
CEXEC = out/

.PHONY: clean clean-img doc check-syntax compile-all launch-tests video

# rule to generate the doxygen documentation
doc:
	doxygen conf/doxygen.conf

# rule to remove all .o files and all executables
clean:
	- make clean-img
	- rm -f *.o
	- find . -executable -type f -delete

# rule to clean images and video
clean-img:
	- rm out/*.ppm video.mp4

%.o: ./src/%.c
	$(CC) $(CFLAGS) -o $@ -c $^ $(CLIB)

%.o: ./tests/%.c
	$(CC) $(CFLAGS) -o $@ -c $^ $(CLIB)

#random C tests:
random-tests: random_tests.o
	$(CC) $(CFLAGS) -o $@ $^ $(CLIB)
# ---------

check-syntax: universe.o test-universe.o ppm_img.o graphic_interface.o

test-universe: test-universe.o universe.o ppm_img.o
	- mkdir $(CEXEC)
	- $(CC) $(CFLAGS) -o $(CEXEC)$@ $^ $(CLIB)
	- ./$(CEXEC)$@

test-ppm-img: test-ppm-img.o universe.o ppm_img.o
	- mkdir $(CEXEC)
	- $(CC) $(CFLAGS) -o $(CEXEC)$@ $^ $(CLIB)
	- ./$(CEXEC)$@

app: app.o universe.o graphic_interface.o
	- mkdir $(CEXEC)
	- $(CC) $(CFLAGS) -o $(CEXEC)$@ $^ $(CLIB)
	- ./$(CEXEC)$@

compile-all: \
	     	

ALL_TESTS = test-universe test-ppm-img

launch-tests: $(ALL_TESTS)
	for x in $(ALL_TESTS); do ./$(CEXEC)$$x --all; done

# misc
WIDTH=1024
HEIGHT=768

video: out
	mogrify -format png -resize $(WIDTH)X$(HEIGHT) -filter box -background white -extent $(WIDTH)X$(HEIGHT) -gravity center out/*.p*m
	ffmpeg -framerate 5 -i out/img-%03d.png -vcodec libx264 -vf format=yuv420p video.mp4
	rm -f out/*.png

valgrind: test-list-conway
	valgrind --leak-check=full ./$^