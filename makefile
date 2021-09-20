_DEBUG = $(if $(DEBUG),-D DEBUG,)
_OPT = $(if $(OPT),-O3 -flto,)
CC = gcc
CFLAGS = -g -std=c99 -Wall $(_OPT) -I./headers $(_DEBUG)
MFLAGS = -lm #for maths

.PHONY: clean clean-img doc check-syntax compile-all launch-tests video

# rule to generate the doxygen documentation
doc:
	doxygen conf/doxygen.conf

# rule to remove all .o files and all executables
clean:
	- rm -f *.o
	- find . -executable -type f -delete

# rule to clean images and video
clean-img:
	- rm out/*.ppm video.mp4

%.o: ./src/%.c
	$(CC) $(CFLAGS) -o $@ -c $^

%.o: ./tests/%.c
	$(CC) $(CFLAGS) -o $@ -c $^

#random C tests:
random-tests: random_tests.o
	$(CC) $(CFLAGS) -o $@ $^ $(MFLAGS)
# ---------

check-syntax: universe.o test-universe.o ppm_img.o

test-universe: test-universe.o universe.o ppm_img.o
	$(CC) $(CFLAGS) -o $@ $^ $(MFLAGS)

compile-all: \
	     	

ALL_TESTS = test-universe

launch-tests: $(ALL_TESTS)
	for x in $(ALL_TESTS); do ./$$x --all; done

# misc
WIDTH=1024
HEIGHT=768

video: out
	mogrify -format png -resize $(WIDTH)X$(HEIGHT) -filter box -background white -extent $(WIDTH)X$(HEIGHT) -gravity center out/*.p*m
	ffmpeg -framerate 5 -i out/img-%03d.png -vcodec libx264 -vf format=yuv420p video.mp4
	rm -f out/*.png

valgrind: test-list-conway
	valgrind --leak-check=full ./$^