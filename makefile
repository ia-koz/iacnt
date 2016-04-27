#
# Compiler
#
compiler = g++


#
# Comliler options
#
flags = -Wall -std=c++11 -pthread
libraries =


#
# Terminal commands
#
rm = rm
rm_r = rm -r
rm_f = rm -f
rm_rf = rm -rf
mkdir = mkdir
mkdir_p = mkdir -p

#
# Main target
#
target_name = iacnt
target_rule = $(binaries_dir)/$(target_name)

#
# Directories
#
sources_dir = src
objects_dir = obj
binaries_dir = bin


#
# Target rule
#
all : createnv $(target_rule)

$(target_rule) : $(objects_dir)/main.o $(objects_dir)/option.o $(objects_dir)/readopts.o
	$(compiler) $(flags) $^ $(libraries) -o $@


#
# Dependency rule
#
main_dep = $(sources_dir)/main.c++ $(sources_dir)/typedefs.h++ $(sources_dir)/option.h++ $(sources_dir)/readopts.h++
$(objects_dir)/main.o : $(main_dep)
	$(compiler) -c $(flags) $< -o $@

option_dep = $(sources_dir)/option.c++ $(sources_dir)/option.h++ $(sources_dir)/typedefs.h++
$(objects_dir)/option.o : $(option_dep)
	$(compiler) -c $(flags) $< -o $@

readopts_dep = $(sources_dir)/readopts.c++ $(sources_dir)/readopts.h++ $(sources_dir)/typedefs.h++ $(sources_dir)/option.h++
$(objects_dir)/readopts.o : $(readopts_dep)
	$(compiler) -c $(flags) $< -o $@


#
# Template rule
#
$(objects_dir)/%.o : $(sources_dir)/%.c++
	$(compiler) -c $(flags) $< -o $@


#
# Support rule
#
clean :
	$(rm_r) $(objects_dir)/*
	$(rm_r) $(binaries_dir)/*

forceclean :
	$(rm_rf) $(objects_dir)/*
	$(rm_rf) $(binaries_dir)/*

cleanall :
	$(rm_rf) $(objects_dir)/
	$(rm_rf) $(binaries_dir)/

createnv :
	$(mkdir_p) $(objects_dir) $(binaries_dir)


.PHONY : clean forceclean cleanall createnv
