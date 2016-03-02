# Radiation Model

Because so much data has to be read in for the radiation model, maybe it's best to create another variable that can point to the top (root) of a directory tree that can serve as the atomic database for the code. In this case, it would point to `Radiation_Model/atomic_data`. Generalizing the location allows for more flexibility and in the future could allow for easier updates to the database with CHIANTI.

Instead of using `Radiation_Model/source/config.h` and defining radaiation parameters both here and in `Initial_Conditions/source/config.h`, would be better to instead switch to a `radiation.cfg` file that specifies all of the parameters in `Radiation_Model/source/config.h`, gives the root of the atomic database, `Atomic_DB_Root`, and gives the path to the elements files, `elements_{eq,neq}.cfg`. This will help to consolidate all of the inputs to the radiation model and will reduce repetition across the configuration files for both the HYDRAD and Initial Conditions codes.

Outline for how radiation model parameters are read in and generated by GUI
## `Radiation_Model/config/elements_eq.cfg`
This configuration file, which specifies all of the information for calculating the radiative loss function, is read in when `CRadiation.Initialise(<elements_config_file.cfg>)` is called. 

 Variable Target | Type | Description |
|:---------------:|:---- |:-----------|
| `szRangesFilename` | `char` array | Filename of _T_ and _n_ range database |
| `buffer2` | `char` array | Top level directory for emissivity information |
| `buffer3` | `char` array | Top level directory for abundance information |
| `buffer4` | `char` array | Top level directory for rates and balances information |
| `NumElements` | int | Number of elements to be read from the file |
| `buffer1` | `char` array | Atomic symbol for the _i_<sup>th</sup> element; used to construct emissivities, rates, and balances filenames |
| `pZ[i]` | int | Atomic number of the _i_<sup>th</sup> element; used in instantiation of `CElement` class for each element _i_. |

The last two rows are repeated `NumElements` times in the configuration file (i.e. atomic symbol and number for each element listed). The relevant input files are all fed into an instance of the `CElement` class. 

## `Radiation_Model/config/elements_neq.cfg`
TODO: List all of variable mappings as they are read into the radiation model code.

| Variable | Type | Description | File Target(s) |
|:--------:|:-----|:----------- |:-------------- |


## `Radiation_Model/source/config.h`
TODO: Here, list all of the `#ifdef` vars that get defined. May have to look at GUI source to sort this out.

### Physics

| Variable | Type | Description | File Target(s) |
|:--------:|:-----|:----------- |:-------------- |
| `DENSITY_DEPENDENT_RATES` | boolean | Radiation; | `Radiation_Model/source/element.cpp`; part of the `CElement` class|
| `MINIMUM_COLLISIONAL_COUPLING_TIME_SCALE` | float | Collisions; | `Radiation_Model/source/element.cpp`,`HYDRAD/source/eqns.cpp` |
 

### Solver

| Variable | Type | Description | File Target(s) |
|:--------:|:-----|:----------- |:-------------- |
| `MAX_OPTICALLY_THIN_DENSITY` | float | log_10 of the max optically thin density | `Radiation_Model/source/radiation.cpp`; part of the `CRadiation` class |
| `SAFETY_ATOMIC` | float | | `Radiation_Model/source/element.cpp` |
| `CUTOFF_ION_FRACTION` | float |  | `Radiation_Model/source/element.cpp`,`Radiation_Model/source/ionfrac.cpp` |
| `EPSILON_D` | float | | `Radiation_Model/source/element.cpp` |
| `EPSILON_R` | float | | `Radiation_Model/source/element.cpp` |
