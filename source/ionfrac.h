
#include "radiation.h"

// Ionization fraction class
//
// Class for handling ionization fraction information. Methods include writing, reading,
// and setting ionization fractions for all ions of a given element. The rates of change
// for the ionization fractions from the time-dependent ionization equations are also
// handled here.
//
class CIonFrac {

  private:

  	/* Pointer to a radiation object*/
    PRADIATION pRadiation;

  	/*- Threshold below which ion populations are set to zero. Set in radation configuration file.*/
  	double cutoff_ion_fraction;

    /*- Pointer to an array of pointers containing the fractional populations of the ions for each element at the current temperature */
    double **ppIonFrac;


  	/*- Pointer to an array of pointers containing the rate of change with respect to time of the fractional population of the ions for each element at the current temperature */
    double **ppdnibydt;

    /*- Initialize object */
    void Initialise( CIonFrac *pIonFrac, char *szFilename, PRADIATION pRadiationObj );

    /*- Free all memory allocated by object */
    void FreeAll( void );

  public:

  	// Default constructor
    // @pIonFrac instance of <CIonFrac> class
  	// @szFilename radiation configuration filename
    // @pRadiationObj instance of <PRADIATION>
    //
  	//
    CIonFrac( CIonFrac *pIonFrac, char *szFilename, PRADIATION pRadiationObj );

    /* Destructor */
    ~CIonFrac( void );

    /* Number of elements for which ion population fractions are available */
    int NumElements;

	  /* Pointer to an array containing each element's atomic number.*/
    int *pZ;

    // Return pointer to arrays of all ion population fractions
	  //
    // This function returns a pointer to an array of pointers containing
    // the ion population fractions
    //
    // @return pointer to array of pointers of ion population fractions
	  //
	  double** ppGetIonFrac( void );

    // Return ion population fractions for element <iZ>
  	// @iZ atomic number of element
  	//
  	// This function returns a pointer to the ion population fractions
  	// for a particular element <iZ>.
   	//
   	// @return pointer to array of pointers of ion population fractions
    //
    double* pGetIonFrac( int iZ );

    // Write all ion fractions to file
    // @pFile file stream object for writing ion fractions
	  //
    // This function writes ion population fractions for all elements
    // using the filestream <pFile>.
    //
    void WriteAllIonFracToFile( void *pFile );

   	// Write ion population fractions to file
    // @pFile filestream object for writing ion population fractions
  	// @iZ atomic number of element
  	//
  	// This function writes ion population fractions for element <iZ> using
  	// the filestream <pFile>.
  	//
    void WriteIonFracToFile( void *pFile, int iZ );

  	// Read all ion population fractions
  	// @pFile filestream object for reading ion population fractions
  	//
  	// This function reads the ion population fractions for all elements
  	// using the filestream <pFile>.
  	//
    void ReadAllIonFracFromFile( void *pFile );

  	// Read <iZ> ion population fractions
  	// @pFile filestream object for reading ion population fractions
  	// @iZ atomic number of element
  	//
  	// This function reads the ion population fractions for element <iZ>
  	// using the filestream <pFile>.
  	//
  	void ReadIonFracFromFile( void *pFile, int iZ );

	  // Ion population fraction rate of change for all elements
	  //
	  // This function gets the pointer to an array of pointers containing the
	  // rate of change of the ion population fractions for all elements at the
	  // current temperature.
	  //
	  // @return pointer to array of pointers containing ion population fraction rates of change
	  //
    double** ppGetdnibydt( void );

  	// Ion population fraction rate of change for element <iZ>
  	// @iZ atomic number of element
  	//
  	// This function gets the pointer to an array of pointers containing the
  	// rate of change of the ion population fractions for element <iZ> at the
  	// current temperature.
  	//
  	// @return pointer to array of pointers containing ion population fraction rates of change
	  //
    double* pGetdnibydt( int iZ );

  	// Integrate ion fraction rates of change for all elements
  	// @delta_t current time step
  	//
  	// This function integrates the dnibydt term at the current timestep,
  	// and sums over all ions for all elements. The sum of the ion
  	// fractions are then normalized to one.
  	//
  	//
    void IntegrateAllIonFrac( double delta_t );

  	// Integrate ion fraction rates of change for element <iZ>.
   	// @iZ atomic number of element
  	// @delta_t current time step
  	//
  	// Integrates the dnibydt term at the current timestep
  	// and sum over all ions of element <iZ>. Normalize
  	// ion population fractions to one.
  	//
    void IntegrateIonFrac( int iZ, double delta_t );

  	// Return pointer to array of atomic numbers <pZ>
  	// @pNumElements pointer to number of elements
  	//
  	// Function to return the number of elements for which
  	// ion population fractions data is stored and the
  	// atomic numbers of the elements.
  	//
  	// @return pointer to atomic number of elements
  	//
    int* pGetElementInfo( int *pNumElements );

  	// Overwrite ion population fractions for all elements
    // @pIonFrac pointer to instance of <CIonFrac> class
  	//
    // Copy the ion population fractions from <pIonFrac> to the
    // new instance of <CIonFrac> for all elements.
  	//
    void CopyAllIonFrac( CIonFrac *pIonFrac );

  	// Overwrite ion population fractions element <iZ>
  	// @iZ atomic number of element
  	// @pIonFrac pointer to instance of <CIonFrac> class
  	//
  	// Copy the ion population fractions from <pIonFrac> to the
  	// new instance of <CIonFrac> for element <iZ>.
  	//
    void CopyIonFrac( int iZ, CIonFrac *pIonFrac );

  	// Overwrite rate of change for all elements
  	// @pIonFrac pointer to instance of <CIonFrac> class
  	//
  	// Copy rate of change terms for ion population
  	// fractions for all elements from <pIonFrac> to
  	// new instance of <CIonFrac>.
  	//
  	//
    void CopyAlldnibydt( CIonFrac *pIonFrac );

  	// Overwrite rate of change for all elements
  	// @iZ atomic number of element
  	// @pIonFrac pointer to instance of <CIonFrac> class
  	//
  	// Copy rate of change terms for ion population
  	// fractions for element <iZ> from <pIonFrac> to new
  	// instance of <CIonFrac>.
  	//
  	//
  	void Copydnibydt( int iZ, CIonFrac *pIonFrac );

  	// Interpolate ion population fractions for all elements
  	// @x coordinates at wich ion population fractions are evaluated
  	// @pppIonFrac pointer to array of ion population fractions
  	// @iPoints number of points to perform interpolation over
  	// @s coordinates to interpolate over
  	//
  	// Interpolate the ion population fractions over <s> for all
  	// elements using a given number of points <iPoints> from the
  	// coordinates <x>.
  	//
    void InterpolateAllIonFrac( double *x, double ***pppIonFrac, int iPoints, double s );

  	// Interpolate ion population fractions for element <iZ>
  	// @iZ atomic number of element
  	// @x coordinates at wich ion population fractions are evaluated
  	// @pppIonFrac pointer to array of ion population fractions
  	// @iPoints number of points to perform interpolation over
  	// @s coordinates to interpolate over
  	//
  	// Interpolate the ion population fractions over <s> for a given
  	// element <iZ> using a given number of points <iPoints> from the
  	// coordinates <x>.
  	//
    void InterpolateIonFrac( int iZ, double *x, double ***pppIonFrac, int iPoints, double s );

    // Reset fractional population of element <iZ>
    // @iZ atomic number of element
    // @flog_10T log base 10 of temperature (in K)
    //
    // Reset fractional population of element <iZ> to its equilibrium
    // value for a given temperature <flog_10T>.
    //
    void ResetIonFrac( int iZ, double flog_10T );

    // Reset fractional population of element <iZ> for given density
    // @iZ atomic number of element
    // @flog_10T log base 10 of temperature (in K)
    // @flog_10n log base 10 of density (in cm^-3)
    //
    // Reset fractional population of element <iZ> to its equilibrium
    // value for a given temperature <flog_10T> and density <flog_10n>.
    //
    void ResetIonFrac( int iZ, double flog_10T, double flog_10n );

    // Reset fractional population of all elements
    // @flog_10T log base 10 of temperature (in K)
    //
    // Reset fractional population of all elements to their equilibrium
    // values for a given temperature <flog_10T>.
    //
    void ResetAllIonFrac( double flog_10T );

    // Reset fractional population of all elements for given density.
    // @flog_10T log base 10 of temperature (in K)
    // @flog_10n log base 10 of density (in cm^-3)
    //
    // Reset fractional population of all elements to their equilibrium
    // values for a given temperature <flog_10T> and density <flog_10n>.
    //
    void ResetAllIonFrac( double flog_10T, double flog_10n );

};

typedef CIonFrac* PIONFRAC;
