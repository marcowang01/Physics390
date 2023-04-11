CPP = g++
CPPFLAGS = -O2 -g -Iinclude


objs = pdfs.o pdfs2D.o sampling.o
objs := $(addprefix obj/, $(objs)) 

lib : $(objs)
	ar -r lib/libpdf.a $^ 

bin/test_% : test/test_%.cc lib
	$(CPP) $(CPPFLAGS) $(filter %.o %.cc, $^) -Llib -lpdf -o $@

bin/% : src/%.cc lib
	$(CPP) $(CPPFLAGS) $(filter %.o %.cc, $^) -Llib -lpdf -o $@

obj/%.o : src/%.cc 
	$(CPP) $(CPPFLAGS) -c $^ -o $@


test : bin/test_sample bin/test_exp_inversion bin/test_gaussian_inversion
all : lib



clean : 
	rm -f bin/*
	find  obj -name '*.o' -exec rm {} \;
	rm -f lib/*.a
	find ./ -name '*~' -exec rm {} \;
	find ./ -name '#*' -exec rm {} \;


