CPP = g++
CPPFLAGS = -O2 -g -Iinclude

all : lib test

objs = pdfs.o cdfs.o pdfs2D.o sampling.o
objs := $(addprefix obj/, $(objs)) 

lib : $(objs)
	ar -r lib/libpdf.a $^ 

bin/test_% : test/test_%.cc lib
	$(CPP) $(CPPFLAGS) $(filter %.o %.cc, $^) -Llib -lpdf -o $@

bin/% : src/%.cc lib
	$(CPP) $(CPPFLAGS) $(filter %.o %.cc, $^) -Llib -lpdf -o $@

obj/%.o : src/%.cc 
	$(CPP) $(CPPFLAGS) -c $^ -o $@


test : bin/test_uniform_rejection bin/test_gaussian_rejection bin/test_exp_inversion bin/test_gaussian_inversion bin/test_compare_sampling 


clean : 
	rm -f bin/*
	find  obj -name '*.o' -exec rm {} \;
	rm -f lib/*.a
	find ./ -name '*~' -exec rm {} \;
	find ./ -name '#*' -exec rm {} \;



