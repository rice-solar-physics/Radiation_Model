#<cldoc:index>

Radiation Model

# Radiation Model 

The Radiation Model (RM) module provides routines for calculating radiative losses from a coronal plasma for an arbitrary number of elements and ions, including effects due to non-equilibrium ionization. The RM module is a central component of the HYDRAD and IonPopSolver codes and has been used in a number of published studies.

The RM module provides routines for reading and writing ion population fractions, both equilibrium and non-equilibrium and using these ion population fractions in the radiative loss function. The module requires the apolloDB database in order to read in the needed atomic data.