# Physics390

# HW 1 Usage
## setup
``` bash
$ cd cpp/probability
$ make
```
## Maxwell-Boltzmann Metropolis Sampling
### Sample PDF with a=5
```bash
$ ./bin/test_maxwell_boltzmann_metropolis $RANDOM 5 > maxwell_boltzmann.dat
$ root -l root/plotMaxwellBoltzmann.C
```
### Sample CDF with a=5
```bash
$ ./bin/test_maxwell_boltzmann_metropolis $RANDOM 5 1 > maxwell_boltzmann.dat
$ root -l root/plotMaxwellBoltzmann.C
```
## Maxwell-Boltzmann Rejection Sampling
### Sample PDF with a=5
```bash
$ ./bin/test_maxwell_boltzmann_rejection $RANDOM 5 > maxwell_boltzmann.dat
$ root -l root/plotMaxwellBoltzmann.C
```
### Sample CDF with a=5
```bash
$ ./bin/test_maxwell_boltzmann_rejection $RANDOM 5 1 > maxwell_boltzmann.dat
$ root -l root/plotMaxwellBoltzmann.C
```