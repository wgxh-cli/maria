exec := main.out
out := out
sources := $(wildcard src/*.cc)
objects := $(sources:.cc=.o)
flags := -std=c++20

test.mra:
	./main /home/wgxh_cli/codes/maria/test.mra

$(exec): prebuild $(objects)
	clang++ $(flag) $(foreach obj,$(objects),$(out)/$(notdir $(obj))) -o $(exec)

%.o:
	clang++ $(flag) -c $(basename $@).cc -o ./$(out)/$(notdir $@)

prebuild:
	@mkdir -p out

clean:
	@rm -rf *.out
	@rm -rf out

