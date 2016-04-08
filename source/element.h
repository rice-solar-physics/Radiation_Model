#ifndef ELEMENT_H
#define ELEMENT_H

#include "../../rsp_toolkit/source/xmlreader.h"

/* Element class for radiative emission model
 *
 * This class definition holds, sets, and gets all of the radiative emission
 * information associated with a particular element. A new instance of <CElement>
 * is instantiated for each element in the configuration file when <CRadiation>
 * is instantiated. (c) Dr. Stephen J. Bradshaw
 */
class CElement {

    private:

    // The atomic number of the element
    int Z;

    // The abundance of the element relative to hydrogen
    double fAbund;

    // The number of ions and their spectroscopic numbers
    int NumIons, *pSpecNum;
	
    // The temperature and density values in log_10 form
    int NumTemp, NumDen;
    double *pTemp, *pDen;
	
	// Configuration variables originally pulled from config.h
	bool density_dependent_rates;
	double minimum_collisional_coupling_time_scale, safety_atomic, cutoff_ion_fraction, epsilon_d, epsilon_r, max_optically_thin_density;
	
	// Parameter for skipping emissivity calculation
	bool do_emiss_calc;
		
    // Pointer to an array of pointers, each pointing to the emissivity
    // data for an individual ion held in a NumTemp * NumDen size array
    double **ppEmiss;
	
    // Pointers to two arrays of pointers.  One points to the total ionisation rate
    // and the other to the total recombination rate of each ion at a specified
    // temperature
    double **ppIonRate, **ppRecRate;
	
    // Pointer to an array of pointers, each pointing to the fractional
    // population of an individual ion at a specified temperature
    double **ppIonFrac;
	
    // Pointers to the factor phi( n, T ) for each ion and the total phi( n, T )
    // for the element
    double **ppPhi, *pTotalPhi;
	
    // Function to open and read the ranges data file
    void OpenRangesFile( char *szRangesFilename );

    // Function to open and read the abundances data file
    void OpenAbundanceFile( char *szAbundFilename );

    // Function to open and read the emissivity data file
    void OpenEmissivityFile( char *szEmissFilename );

    // Function to open and read the total ionisation and recombination rates file
    void OpenRatesFile( char *szRatesFilename );

    // Function to open and read the ionisation balance file
    void OpenIonFracFile( char *szIonFracFilename );

    // Functions to calculate the factor phi( n, T ), which is multiplied by n^2 to calculate the radiated energy
    void CalculatePhi( void );
    void CalculateTotalPhi( void );

    // Function to free all allocated memory
    void FreeAll( void );

    // Function to return the required emissivity values
    double GetIonEmissivity( int iIon, double flog_10T, double flog_10n );

    public:
	
    // Constructor
    CElement( int iZ, char *szRangesFilename, char *szAbundFilename, char *szEmissFilename, char *szRatesFilename, char *szIonFracFilename, bool doEmissCalc, tinyxml2::XMLElement * root );
	
    // Destructor
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