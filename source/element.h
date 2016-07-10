#ifndef ELEMENT_H
#define ELEMENT_H

#include "../../rsp_toolkit/source/xmlreader.h"

// Element class
//
// This class definition holds, sets, and gets all of the radiative emission
// information associated with a particular element. A new instance of <CElement>
// is instantiated for each element in the configuration file when <CRadiation>
// is instantiated.
//
class CElement {

  private:

    /* Atomic number of the element */
    int Z;

    /* Abundance of the element relative to hydrogen */
    double fAbund;

    /* Number of ions */
    int NumIons;

    /* Pointer to the spectroscopic numbers of the ions */
    int *pSpecNum;

    /* Number of temperature values */
    int NumTemp;

    /* Number of density values */
    int NumDen;

    /* Pointer to log base 10 of temperature values */
    double *pTemp;

    /* Pointer to log base 10 of density values */
    double *pDen;

    /* Option to use density dependent ionization rates */
    bool density_dependent_rates;

    /* Smallest possible time scale for electron/ion collisional coupling */
	  double minimum_collisional_coupling_time_scale;

    /* Solver safety factor */
    double safety_atomic;

    /* Value below which ion population fractions are set to zero */
    double cutoff_ion_fraction;

    /* Solver factor */
    double epsilon_d;

    /* Solver factor */
    double epsilon_r;

    /* Density above which optically thin treatment is not valid */
    double max_optically_thin_density;

  	/* Option for skipping emissivity calculation */
  	bool do_emiss_calc;

    /* Emissivity data for an individual ion held in a <NumTemp>*<NumDen> size array */
    double **ppEmiss;

    /* Total ionisation rate of each ion at a specified temperature */
    double **ppIonRate;

    /* Recombination rate of each ion at a specified temperature */
    double **ppRecRate;

    /* Fractional population of an individual ion at a specified temperature */
    double **ppIonFrac;

    /* Radiative loss function Phi at every temperature and density for each ion for the given element */
    double **ppPhi;

    /* Radiative loss function Phi summed over each ion at every temperature and density */
    double *pTotalPhi;

    // Open and read the ranges data file
    void OpenRangesFile( char *szRangesFilename );

    // Function to open and read the abundances data file
    void OpenAbundanceFile( char *szAbundFilename );

    // Function to open and read the emissivity data file
    void OpenEmissivityFile( char *szEmissFilename );

    // Function to open and read the total ionisation and recombination rates file
    void OpenRatesFile( char *szRatesFilename );

    // Function to open and read the ionisation balance file
    void OpenIonFracFile( char *szIonFracFilename );

    // Calculate radiative loss function Phi at every temperature and density for a given ion
    void CalculatePhi( void );

    // Sum radiative loss function Phi over all ions at every temperature and density
    void CalculateTotalPhi( void );

    // Function to free all allocated memory
    void FreeAll( void );

    // Function to return the required emissivity values
    double GetIonEmissivity( int iIon, double flog_10T, double flog_10n );

  public:

    // Default constructor
    // @iZ atomic number of element
    // @szRangesFilename temperature and density ranges data filename
    // @szAbundFilename element abundance data filename
    // @szEmissFilename element emissivity data filename
    // @szRatesFilename element ionization rates data filename
    // @szIonFracFilename element fractional ionization data filename
    // @doEmissCalc if True, do emissivity calculation; set to False in IonPopSolver
    // @root XML document tree root to radiation configuration file
    //
    //
    CElement( int iZ, char *szRangesFilename, char *szAbundFilename, char *szEmissFilename, char *szRatesFilename, char *szIonFracFilename, bool doEmissCalc, tinyxml2::XMLElement * root );

    /* Destructor */
    ~CElement( void );

    // Function to initialise the element object
    void Initialise( int iZ, char *szRangesFilename, char *szAbundFilename, char *szEmissFilename, char *szRatesFilename, char *szIonFracFilename, bool doEmissCalc );

	  // Function to set configuration variables
	  void SetConfigVars(tinyxml2::XMLElement * root);

    // Function to return the element abundance
    double GetAbundance( void );

    // Function to return the total ionisation and total recombination rate
    // for a particular ion at a specified temperature and density
    void GetRates( int iIon, double flog_10T, double *pfIonRate, double *pfRecRate );
    void GetRates( int iIon, double flog_10T, double flog_10n, double *pfIonRate, double *pfRecRate );

    // Function to return the fractional population of a particular ion at a
    // specified temperature and density in equilibrium
    double GetEquilIonFrac( int iIon, double flog_10T );
    double GetEquilIonFrac( int iIon, double flog_10T, double flog_10n );

    // Functions to calculate the emissivity in equilibrium (this number includes multiplication by the ion fraction)
    // Multiply by the number density squared to obtain the energy radiatied in units of erg cm^-3 s^-1
    double GetEmissivity( int iIon, double flog_10T, double flog_10n );
    double GetEmissivity( double flog_10T, double flog_10n );

    // Function to calculate the rate of change with respect to time of the fractional population of the ions and the characteristic time-scale
	// Overload for use with IonPopSolver code
    void Getdnibydt( double flog_10T, double flog_10n, double *pni0, double *pni1, double *pni2, double *pni3, double *pni4, double *s, double *s_pos, double *pv, double delta_s, double *pdnibydt, double *pTimeScale );
	void Getdnibydt( double flog_10T, double flog_10n, double *pni, double *pdnibydt, double *pTimeScale );

    // Functions to calculate the emissivity away from equilibrium (this number includes multiplication by the ion fraction)
    // Multiply by the number density squared to obtain the energy radiatied in units of erg cm^-3 s^-1
    double GetEmissivity( int iIon, double flog_10T, double flog_10n, double ni );
    double GetEmissivity( double flog_10T, double flog_10n, double *pni );

};

typedef CElement* PELEMENT;
typedef CElement** PPELEMENT;

#endif
