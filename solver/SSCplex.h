#ifndef SS_H
#define SS_H

/* ----------------------------------------------------------------
             A Smart Services Problem                                 
       Solved through the commercial LP code Cplex 
------------------------------------------------------------------- */

#include "mymemory.h"
#include "StdAfx.h"

// #define AV_THR 0.50

class SSCplex {

private:
	
	CPXENVptr env;     // the Cplex environment
	CPXLPptr  lp;      // the pointer to the LP solver

	int num_vm; // number of virtual machines
	int num_vf; // number of virtual function

	int h_len; // number of levels
	int lev_card; // number of nodes in each level

	int NNodes;
	int NArcs;

	double ** tempi_lat; //matrix containing latencies
	int * cap; // array containing node capacity
	int ** incom; // matrix containing the VM-Vf incompatibilities
	double ** proc_time; // matrix containing the VM-Vf processing time
	double * source_dist; // distance from source DC
	double * dest_dist; // distance from destination DC
	int first_z;

	double *Y;

	double objval;     // value of the objective function
	int    status;
	ofstream CPXout; 

public:
	/* Solve the problem. */
	void Solve( void );

        #if( MIP )
	 /* Set parameters  */
	 void SetParameters( void );
        #endif
  
	/* Return the objective function value */
	double GetObjVal( );

	/* Change a coefficient in the constraint matrix */
	void ChgBds(int z, double newval);

	/* Change problem type */
	void ChgPrType(int type);


/* AddExtraConstr adds to the problem NXC new linear constraints. IBeg, Indx
   and Vals must contain the description of the new constraints: each
   constraint is represented by the set of indices of variables with nonzero
   coefficient and the corresponding coefficients. The indices and
   coefficients of the i-th constraint, i = 0 .. NXC - 1, must be in Indx and
   Vals, respectively, in the positions between IBeg[ i ] (included) and
   IBeg[ i + 1 ] (excluded). The indices corresponding to each constraint,
   in Indx, must be ordered in increasing sense and without duplications.

   The indices of the variables are in the range [0,M-1] and are internally
   translated in [N,N+M-1].

   Note that IBeg, Indx and Vals are *not* pointers to const: this is done to
   allow the implementation to *overwrite* those vectors, should it find this
   useful. Furthermore, the implementation *need not* to restore the original
   containts of the vectors: no assumption should be done by the caller on the
   contents of IBeg, Indx and Vals after the call. The rationale for this is
   that these data structures may be "big", and that they should be of no use
   after the call, so by allowing the implementation to exploit that memory
   some serious memory problem may be avoided.

   XLr and XUr are, respectively, the lower and upper range of the extra
   constraints: if XLr[ i ] == - F_INF, then the row have sense <=, while if
   XUr[ i ] == F_INF, then the row have sense >=. XLr == NULL means "all
   equal to - F_INF", and XUr == NULL means "all equal to F_INF". It is an
   error if XLr[ i ] == - F_INF *and* XUr[ i ] == F_INF for some i (this is
   not a constraint), and therefore at least one between XLr and XUr must be
   non-NULL. */

	void AddExtraConstr( int NXC , 
			     int *IBeg , int *Indx , double *Vals ,
			     double *XLr = NULL , double *XUr = NULL );


	/* Constructor of the class: takes as parameters the data of the 
	   instance to be solved and constructs an instance of the problem. */
	SSCplex( string InstanceFile );
	    
	/* Destructor of the class. */
	~SSCplex();

};

#endif














