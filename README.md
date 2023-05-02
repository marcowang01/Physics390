# Physics390

# HW 2 Submission Usage

## Setup
```bash
$ cd cpp/basic_integration
$ make
```
## Running by hand
```bash
$ ./bin/test_pi_2D_Naive $RANDOM 1000 blah > ./data/sphere.dat
$ root -l ./root/plotVolumeNaive.C
```

## Running with the script
```bash
$ ./scripts/runSphereIntegrationNaive.sh
$  root -l root/plotSphereTrialsNaive.C
```