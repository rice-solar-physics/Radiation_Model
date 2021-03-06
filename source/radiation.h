#ifndef RADIATION_H
#define RADIATION_H

#include "element.h"

/* Radiative emission model class
 *
 * Class for handling radiative emission model functions and data. This class
 * includes functions for reading and writing equilibrium ionization fractions
 * as well as functions to calculate the amount of radiation in the nonequilibrium
 * case. This is the top-level class that should be called in a hydrodynamic model
 * to calculate the radiative loss. The <CElement> class is instantiated for the
 * specified number of elements by the constructor. (c) Dr. Stephen J. Bradshaw
 */
class CRadiation {

    private:

    // The number of elements for which ion fractional populations are available
    int NumElements;

	  // Config variables--originally set in config.h
	  double max_optically_thin_density; //log10 of maximum optically thin density value

    // Parameter for skipping emissivity calculation
	  bool do_emiss_calc;

    // Parameter for skipping unneeded frees in destructor
    bool freeMemory;

    // Pointer to an array of pointers of type PELEMENT
    PPELEMENT ppElements;

    // Pointer to an array containing each element's atomic number.  The offset
    // of the atomic number corresponds to the offset of the element object in
    // the ppElements array
    int *pZ;

    // The temperature and density values in log_10 form
    int NumTemp, NumDen;
    double *pTemp, *pDen;

    // Pointer to the factor total phi( n, T ) for all of the elements
    double *pTotalPhi;

    // Function to initialise the radiation object with a set of elements
    void Initialise( char *szFilename, bool doEmissCalc );

    // Function to open and read the ranges data file
    void OpenRangesFile( char *szRangesFilename );

    // Function to calculate the factor total phi( n, T ), which is multiplied by n^2 to calculate the radiated energy
    void CalculateTotalPhi( void );

    // Function to free all allocated memory
    void FreeAll( void );

    public:

	  // Constructor for full radiative loss model
	  // @szFilename path to configuration file
	  // @doEmissCalc if True, do the emissivity calculation; set to False if you just want to calculation ion population fractions
	  //
    CRadiation( char *szFilename, bool doEmissCalc );

    // Defualt constructor
    // Use if you only need the power-law radiative loss function
    //
    CRadiation( void );

    /* Destructor */
    ~CRadiation( void );

  	// Return atomic numbers
  	// @iNumElements Number of elements to use radiation calculation
  	//
  	// Return list of the atomic numbers of the elements comprising the radation
  	// model. Set the number of elements pointer in the <CRadiation> class
  	//
  	// @return pointer to list of atomic numbers
  	//
    int *pGetAtomicNumbers( int *iNumElements );

    // Return the abundance of a specified element
  	// @iZ atomic number of element
  	//
  	// Return the abundance of the element specified by <iZ>. Search through the
  	// list of atomic numbers to find the number that matches <iZ>.
  	//
  	// @return resulting abundance value from <CElement::GetAbundance>
    double GetAbundance( int iZ );

    // Function to return the ion fractional populations of a particular element at a
    // specified temperature and density in equilibrium
    void GetEquilIonFrac( int iZ, double *pni, double flog_10T );
    void GetEquilIonFrac( int iZ, double *pni, double flog_10T, double flog_10n );

    // Functions to write either a given set of ion fractional populations or all
    // fractional populations to a data file
    void WriteEquilIonFracToFile( void *pFile, int iZ, double flog_10T );
    void WriteEquilIonFracToFile( void *pFile, int iZ, double flog_10T, double flog_10n );
    void WriteEquilIonFracToFile( void *pFile, double flog_10T );
    void WriteEquilIonFracToFile( void *pFile, double flog_10T, double flog_10n );

    // Function to normalise the sum total of the ion fractional populations to 1
    void Normalise( int iZ, double *pni, double fTotal );

    // Functions to calculate the amount of energy radiated in equilibrium
    double GetRadiation( int iZ, int iIon, double flog_10T, double flog_10n );
    double GetRadiation( int iZ, double flog_10T, double flog_10n );
    double GetRadiation( double flog_10T, double flog_10n );

    // Functions to calculate the rate of change with respect to time of the fractional
    // populations of the ions and the characteristic time-scale
  	// Overload for use in IonPopSolver code
    void Getdnibydt( int iZ, double flog_10T, double flog_10n, double *pni0, double *pni1, double *pni2, double *pni3, double *pni4, double *s, double *s_pos, double *pv, double delta_s, double *pdnibydt, double *pTimeScale );
	  void Getdnibydt( int iZ, double flog_10T, double flog_10n, double *pni, double *pdnibydt, double *pTimeScale );
    void GetAlldnibydt( double flog_10T, double flog_10n, double **ppni0, double **ppni1, double **ppni2, double **ppni3, double **ppni4, double *s, double *s_pos, double *pv, double delta_s, double **ppdnibydt, double *pTimeScale );
    void GetAlldnibydt( double flog_10T, double flog_10n, double **ppni, double **ppdnibydt, double *pTimeScale );

    // Functions to calculate the amount of energy radiated in nonequilibrium
    double GetRadiation( int iZ, int iIon, double flog_10T, double flog_10n, double ni );
    double GetRadiation( int iZ, double flog_10T, double flog_10n, double *pni );
    double GetRadiation( double flog_10T, double flog_10n, double **ppni );

    // Functions to calculate energy radiated based upon power-laws
    double GetPowerLawRad( double flog_10T, double flog_10n );
    double GetPowerLawRad( double flog_10T );
    double GetFreeFreeRad( double flog_10T, double flog_10n );

  	// Atomic database filename
  	char atomicDBFilename[512];

};

typedef CRadiation* PRADIATION;

#endif
