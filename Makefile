exec := main.out
out := out
sources := $(wildcard src/*.cc)
objects := $(sources:.cc=.o)

build: $(exec)
	@echo "---------"
	@./main.out

$(exec): prebuild $(objects)
	clang++ $(foreach obj,$(objects),$(out)/$(notdir $(obj))) -o $(exec)

%.o:
	clang++ -c $(basename $@).cc -o ./$(out)/$(notdir $@)

prebuild:
	@mkdir -p out

clean:
	@rm -rf *.out
	@rm -rf out

