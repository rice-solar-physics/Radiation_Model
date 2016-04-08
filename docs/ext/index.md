#<cldoc:index>

Radiation Model

# Radiation Model 

The Radiation Model (RM) module provides routines for calculating radiative losses from a coronal plasma for an arbitrary number of elements and ions, including effects due to non-equilibrium ionization. The RM module is a central component of the HYDRAD and [IonPopSolver](https://github.com/rice-solar-physics/IonPopSolver) codes and has been used in a number of published studies.

The RM module provides routines for reading and writing ion population fractions, both equilibrium and non-equilibrium and using these ion population fractions in the radiative loss function. The module requires the apolloDB database in order to read in the needed atomic data.

You can find the source code on [GitHub](https://github.com/rice-solar-physics/Radiation_Model). If you find any bugs or issues, please report them using [the issue tracker on GitHub](https://github.com/rice-solar-physics/Radiation_Model/issues).

## Dependencies
To build RM, you will need to install [`rsp_toolkit`](https://github.com/rice-solar-physics/rsp_toolkit), a collection of file I/O and fitting routines:
```bash
git clone --recursive https://github.com/rice-solar-physics/rsp_toolkit.git
```
The [`tinyxml2`](https://github.com/leethomason/tinyxml2) library for parsing XML files also comes bundled with this package. `rsp_toolkit` should be cloned into the same directory that you've installed the RM module.

In order to run the RM module as part of your code, you will need to install [`apolloDB`](https://github.com/rice-solar-physics/apolloDB), the database containing all the atomic data needed for the calculations done in the RM module:
```bash
git clone https://github.com/rice-solar-physics/apolloDB.git
```

## Installation

## Configuration

## Using RM in Your Code

## Examples