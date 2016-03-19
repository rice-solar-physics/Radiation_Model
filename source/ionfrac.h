// ****
// *
// * Ionisation Fraction Class Definition for Radiative Emission Model
// *
// * (c) Dr. Stephen J. Bradshaw
// *
// * Date last modified: 10/29/2015
// *
// ****

#include "radiation.h"

/*Ionization fraction class
 *
 * Class for handling ionization fraction information. Methods include writing, reading, 
 * and setting ionization fractions for all ions of a given element. The rates of change for
 * the ionization fractions from the time-dependent ionization equations are also handled here.
 */
class CIonFrac {

    private:

    // Pointer to a radiation object
    PRADIATION pRadiation;

	//Additional parameters
	double cutoff_ion_fraction;

    /* Double pointer array of ion population fractions
	 * 
	 * Pointer to an array of pointers containing the fractional populations of the
     * ions for each element at the current temperature
	 */
    double **ppIonFrac;

    /* Double pointer array of dnibydt terms
	 *
	 * Pointer to an array of pointers containing the rate of change with respect
     * to time of the fractional population of the ions for each element at the
     * current temperature
	 */
    double **ppdnibydt;

    // Initialize object
    void Initialise( CIonFrac *pIonFrac, char *szFilename, PRADIATION pRadiationObj );

    // Free all memory allocated by object
    void FreeAll( void );
	
    public:

    // Default constructor
    CIonFrac( CIonFrac *pIonFrac, char *szFilename, PRADIATION pRadiationObj );
	
    // Destructor
    ~CIonFrac( void );
	
    // Number of elements for which ion fractional populations are available
    int NumElements;
	
    /* Pointer to array of atomic numbers
	 * 
	 * Pointer to an array containing each element's atomic number. The offset
     * of the atomic number corresponds to the offset of the ionisation fraction
     * object in the ppIonFrac array
	 */
    int *pZ;

    // Return double pointer to fractional populations of elements
    double** ppGetIonFrac( void );
	// Return pointer to fractional populations of iZ at current temperature
    double* pGetIonFrac( int iZ );

    // Write all ion fractions to file
    void WriteAllIonFracToFile( void *pFile );
	//Write all
    void WriteIonFracToFile( void *pFile, int iZ );

    // Functions to read either all of the ion fractional populations or a particular set of
    // fractional populations from a data file
    void ReadAllIonFracFromFile( void *pFile );
    void ReadIonFracFromFile( void *pFile, int iZ );

    // Functions to return a pointer to the rate of change with respect to time
    // of the fractional populations of the ions at the current temperature
    double** ppGetdnibydt( void );
    double* pGetdnibydt( int iZ );

    // Functions to integrate the fractional populations of the ions
    void IntegrateAllIonFrac( double delta_t );
	
	/* Integrate single ion fractions
 	 * @iZ atomic number of element
	 * @delta_t current time step
	 *
	 * IntegrateIonFrac finds the given element, integrates the dnibydt term at 
	 * the current timestep, and sums over all ions of the element. The sum of the
	 * ion fractions are then normalized to one.
 	 */
    void IntegrateIonFrac( int iZ, double delta_t );

    // Function to return the number of elements for which ion fractional population
    // data is stored and the atomic numbers of the elements
    int* pGetElementInfo( int *pNumElements );

    // Functions to overwrite fractional populations in the current object
    void CopyAllIonFrac( CIonFrac *pIonFrac ); 
    void CopyIonFrac( int iZ, CIonFrac *pIonFrac );

    // Functions to overwrite dnibydt's in the current object
    void CopyAlldnibydt( CIonFrac *pIonFrac );
    void Copydnibydt( int iZ, CIonFrac *pIonFrac );

    // Functions to interpolate the fractional populations in the current object from
    // the adjacent fractional populations
    void InterpolateAllIonFrac( double *x, double ***pppIonFrac, int iPoints, double s );
    void InterpolateIonFrac( int iZ, double *x, double ***pppIonFrac, int iPoints, double s );

    // Functions to reset the fractional populations to their equilibrium values at the
    // specified temperature and density
    void ResetIonFrac( int iZ, double flog_10T );
    void ResetIonFrac( int iZ, double flog_10T, double flog_10n );
    void ResetAllIonFrac( double flog_10T );
    void ResetAllIonFrac( double flog_10T, double flog_10n );

};

typedef CIonFrac* PIONFRAC;
