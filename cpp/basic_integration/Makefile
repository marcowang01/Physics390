CPP = g++
CPPFLAGS = -O2 -g -Iinclude -I../probability/include
LDFLAGS = -L../probability/lib -Llib  -lprobability -lintegration

all : lib test

objs = integration_Naive.o integration_MeanVariance.o
objs := $(addprefix obj/, $(objs)) 

lib : $(objs)
	ar -r lib/libintegration.a $^ 

bin/test_% : test/test_%.cc lib
	$(CPP) $(CPPFLAGS) $(filter %.o %.cc, $^) $(LDFLAGS) -o $@

bin/% : src/%.cc lib
	$(CPP) $(CPPFLAGS) $(filter %.o %.cc, $^) $(LDFLAGS) -o $@

obj/%.o : src/%.cc 
	$(CPP) $(CPPFLAGS) -c $^ -o $@


test : bin/test_pi_1D_Naive bin/test_pi_1D_MeanVariance  bin/test_pi_1D_MeanVariance bin/test_importance 
#bin/test_pi_2D_Naive bin/test_maxwell_boltzmann_MeanVariance

clean : 
	rm -f bin/*
	find  obj -name '*.o' -exec rm {} \;
	rm -f lib/*.a
	find ./ -name '*~' -exec rm {} \;
	find ./ -name '#*' -exec rm {} \;

realclean : clean
	rm -f bin/*.dat

