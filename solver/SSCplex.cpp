/* ----------------------------------------------------------------
             A Smart Services Problem                                 
       Solved through the commercial LP code Cplex 
------------------------------------------------------------------- */

#include "SSCplex.h"


SSCplex::SSCplex( string InstanceFile )
{
 num_vm = 0; // number of virtual machines
 num_vf = 0; // number of virtual function
 int offset;
 
 ifstream in;
 in.open(InstanceFile.c_str());
 if( !in.is_open() )
 {
  cout<<"Cannot open instance file.\n";
  exit(1);
 }
	
 //leggo da file il numero di macchine e di funzioni virtuali
 in >> num_vm;
 in >> num_vf;

 cout << "Num VM " << num_vm << " Num VF " << num_vf << endl;

 lev_card = num_vm; // the number of nodes in each level
 h_len = num_vf;

 int lev_card_arcs = lev_card*lev_card;

 //number of nodes and arcs 
 NNodes = lev_card * h_len + 2;
 NArcs = lev_card * lev_card * (h_len-1) + 2*lev_card;
 
 // array used to store the solution
 Y = array(NArcs);

 tempi_lat = new double *[num_vm];

 for (int i=0; i<num_vm; i++)
   tempi_lat[i] = new double[num_vm];

 cap = new int[ num_vm ];
 
 // fill the distance matrix 
 for (int i=0; i<num_vm; i++)
  for (int j=0; j<num_vm; j++)
    //   if( j >= i )
    in >> tempi_lat[i][j];
 //   else  (in input is supposed to be symmetric)
 //    tempi_lat[i][j] = tempi_lat[j][i];

 // fill the capacity array
 for (int i=0; i<num_vm; i++)
  in >> cap[ i ];

 incom = new int *[num_vf];
 for (int i=0; i<num_vf; i++)
  incom[i] = new int[num_vm+1];

 proc_time = new double *[num_vf];
 for (int i=0; i<num_vf; i++)
  proc_time[i] = new double[num_vm];

 for( int i = 0; i < num_vf; i++ )
 {
   string dummy;
   int cnt;
   in >> dummy >> incom[i][0];
   cnt = incom[i][0];
   for( int j = 1; j <= cnt; j++ )
     in >> incom[i][j];

   for( int j = 0; j < num_vm; j++ )
     in >> proc_time[i][j];
 }

 source_dist = new double[ num_vm ];
 dest_dist = new double[ num_vm ];

 for( int j = 0; j < num_vm; j++ )
   in >> source_dist[j];
 for( int j = 0; j < num_vm; j++ )
   in >> dest_dist[j];


 in.close();

 /* Initialize the CPLEX environment */
 env = CPXopenCPLEX (&status);
 if ( env == NULL ) {
   stop("Could not open CPLEX environment.\n", status);
 }

 /* Create the problem */
 lp = CPXcreateprob( env , &status , "HCP" );
 if ( lp == NULL ) {
   stop("Failed to create LP.\n", status);
 }
 if( DEBUG ) {
   CPXout.open("DEBUG.txt", ios::out); 	
 }

 // Turn on debugging routines
 status = CPXsetintparam (env, CPX_PARAM_DATACHECK, CPX_ON);
 if ( status ) {
    stop("Failure to turn on debugging, error %d.\n", status);
 }
  
 // Turn on output to the screen     
 status = CPXsetintparam (env, CPX_PARAM_SCRIND, CPX_ON);
 if ( status ) {
   stop("Failure to turn on screen indicator, error %d.\n", status);
 }

  double  *obj = NULL;
  double  *ub = NULL;
  double  *lb = NULL;
  char	*ctype = NULL;
	
  int nzcnt;
  double *rhs = NULL;
  char *sense = NULL;
  int *matbeg;
  int *matind;
  double *matval;

  // variable counters
  int y_var = NArcs; // flow variables

  // creating variables
  ub = array(y_var);
  lb = array(y_var);

  for( int k = 0; k < y_var; k++ ){
    lb[k] = 0.0;
    ub[ k ] = 1.0;
  }
#if( MIP )
  ctype = arraychar(y_var);	
  for( int h = 0; h < y_var; h++)
    ctype[h] = 'B';
#endif

  obj = array(NArcs);
  for(int i = 0; i < lev_card; i++ )
    obj[i] = proc_time[0][i] + source_dist[i];

  offset = lev_card * lev_card * (h_len-1) + lev_card;
  for(int i = 0; i < lev_card; i++ )
    obj[offset+i] = dest_dist[i];

  offset = lev_card;
  for( int h = 0; h < h_len - 1; h++ )
   for( int i = 0; i < lev_card; i++ )
    for( int j = 0; j < lev_card; j++ )
    {
     int k = offset + h * (lev_card * lev_card) + i * lev_card + j;
     obj[k] = tempi_lat[i][j] + proc_time[h+1][j];
    }

  status = CPXnewcols(env, lp, y_var, obj, lb, ub, ctype, NULL);
  if ( status )
    stop("Failure to create y cols.", status);

  nzcnt = NArcs;
  matind = arrayint(nzcnt);
  matval = array(nzcnt);
  matbeg = arrayint(2);
  
  rhs = array(1);       // at most one constraint is loaded 
  sense = arraychar(1); // in one shot

  matbeg[0] = 0;
  
  // flow conservation constraint relative to source node
  rhs[0] = 1.0;
  sense[0] = 'E';

  for( int h = 0; h < lev_card; h++ )
  {
   matind[h] = h;
   matval[h] = 1.0;
  }

  matbeg[1] = lev_card;
  status = CPXaddrows(env, lp, 0, 1, lev_card, rhs, sense, 
		      matbeg, matind, matval, NULL, NULL);

  if ( status ) {
    stop("Failed to insert cons.\n", status);	
  }

  offset = lev_card + (h_len - 1) * (lev_card * lev_card);
    // flow conservation constraint relative to destination node
  for( int h = 0; h < lev_card; h++ )
  {
   matind[h] = offset + h;
   matval[h] = 1.0;
  }

  matbeg[1] = lev_card;
  status = CPXaddrows(env, lp, 0, 1, lev_card, rhs, sense, 
		      matbeg, matind, matval, NULL, NULL);
  if ( status ) {
    stop("Failed to insert cons.\n", status);	
  }
  
  // flow conservation constraints relative to intermediate nodes
  rhs[0] = 0.0;
  for( int h = 0; h < h_len; h++ )
  {
   for( int i = 0; i < lev_card; i++ )
   {
    int k = 0; // insert a constraint for each intermediate node
    // incoming flow
    if( h == 0 )
    {
     matind[k] = i;
     matval[k] = -1.0;
     k++;
    }
    else
    {
     offset = lev_card + lev_card*lev_card*(h-1);
     for( int j = 0; j < lev_card; j++ )
     {
      matind[k] = offset + j * lev_card + i;
      matval[k] = -1.0;
      k++;
     } 
    }
    // outcoming flow
    if( h == h_len - 1)
    {
     offset = lev_card + lev_card*lev_card*h;
     matind[k] = offset +  i;
     matval[k] = 1.0;
     k++;
    }
    else
    {
     offset = lev_card + lev_card*lev_card*h;
     for( int j = 0; j < lev_card; j++ )
     {
      matind[k] = offset + i*lev_card + j;
      matval[k] = 1.0;
      k++;
     } 

    }
    
    matbeg[1] = k;
    assert( k <= nzcnt );
    status = CPXaddrows(env, lp, 0, 1, k, rhs, sense, 
			matbeg, matind, matval, NULL, NULL);
    if ( status ) {
      stop("Failed to insert cons.\n", status);	
    }
   }
  }

  // VM capacity constraints 
  sense[0] = 'L';
  for( int i = 0; i < lev_card; i++ )
  {
   int k = 0; // insert a constraint for each VM
   rhs[0] = cap[i];

   for( int h = 0; h < h_len - 1; h++ )
   {
    offset = lev_card + lev_card*lev_card*h;
    for( int j = 0; j < lev_card; j++ )
    {
     matind[k] = offset + i*lev_card + j;
     matval[k] = 1.0;
     k++;
    }
   }
   offset = lev_card + lev_card*lev_card*(h_len-1);
   matind[k] = offset +  i;
   matval[k] = 1.0;
   k++;

   matbeg[1] = k;
   assert( k <= nzcnt );
   status = CPXaddrows(env, lp, 0, 1, k, rhs, sense, 
		       matbeg, matind, matval, NULL, NULL);
   if ( status ) {
     stop("Failed to insert cons.\n", status);	
   }
  }

  // incompatibilities management
  // vf_0
  int cnt = incom[0][0];
  for( int j = 0; j < cnt; j++ )
  {
   int arc_index = incom[0][j+1];
   ChgBds(arc_index, 0.0);
  }
  // other vf_h
  for( int h = 1; h < num_vf; h++ )
  {
   int cnt = incom[h][0];
   int offset = lev_card + (h-1) * (lev_card*lev_card);
   for( int j = 0; j < cnt; j++ )
    for( int i = 0; i < lev_card; i++ )
    {
     int arc_index = offset + i * lev_card + incom[h][j+1];
     ChgBds(arc_index, 0.0);
    }
  }

#if DEBUG
	status = CPXwriteprob(env, lp, "SS.lp", "LP");
	if ( status ) stop("Failed to write LP to disk.", status);
#endif

/* Set limit to emphasize feasibility */    
 status = CPXsetintparam (env, CPX_PARAM_MIPEMPHASIS, MIPEMPH);
 if ( status ) 
   stop("Failure to set parameter emphasizing feasibility.\n", status);


// Turn on output to the screen     
 status = CPXsetintparam (env, CPX_PARAM_SCRIND, CPX_ON);
 if ( status ) {
   stop("Failure to turn on screen indicator, error %d.\n", status);
 }

 status = CPXsetdblparam (env, CPX_PARAM_TILIM, TIMELIMIT);

 free_arraychar(sense);
 free_array(rhs);
 free_arrayint(matbeg);
 free_array(matval);
 free_arrayint(matind);
 free_array(obj);
#if( MIP )
 free_arraychar(ctype);
#endif
 free_array(lb);
 free_array(ub);
} //END SSCplex
  



#if( MIP )
/* Set Cplex parameter */
void SSCplex::SetParameters( void ){

	/* Set limit to emphasize feasibility */    
	status = CPXsetintparam (env, CPX_PARAM_MIPEMPHASIS, MIPEMPH);
	if ( status ) 
	    stop("Failure to set parameter emphasizing feasibility.\n", status);
    
	/* Set limit on number of integer solutions */    
	 status = CPXsetintparam (env, CPX_PARAM_INTSOLLIM, NUMINTSOL);
	if ( status ) 
	    stop("Failure to set limit on number of integer solutions.\n", status);
	
	/* Set time to CPU time */
	status = CPXsetintparam (env, CPX_PARAM_CLOCKTYPE, CLOCKTYPE);
	if ( status ) 
		stop("Failure to set clock type.\n", status);

	/* Set limit on time */    
	status = CPXsetdblparam (env, CPX_PARAM_TILIM, TIMELIMIT);
	if ( status ) 
		stop("Failure to set limit on time.\n", status);
  
	/* Set limit on number of nodes */    
	status = CPXsetintparam (env, CPX_PARAM_NODELIM, NUMNODE);
	if ( status ) 
	    stop("Failure to set limit on number of nodes.\n", status);
 
	/* Set MIP node selection strategy */    
	status = CPXsetintparam (env, CPX_PARAM_NODESEL, NODESEL);
	if ( status ) 
		stop("Failure to set node selection strategy.\n", status);
  
	/* Set MIP variable selection strategy */    
	status = CPXsetintparam (env, CPX_PARAM_VARSEL, VARSEL);
	if ( status ) 
		stop("Failure to set variable selection strategy.\n", status);

	/* Set MIP branching direction */    
	status = CPXsetintparam (env, CPX_PARAM_BRDIR, BRDIR);
	if ( status ) 
		stop("Failure to set branching direction.\n", status);
  
	/* Set backtracking tolerance */    
	status = CPXsetdblparam (env, CPX_PARAM_BTTOL, BACKTRACK);
	if ( status ) 
		stop("Failure to set backtracking tolerance.\n", status);


	/* Set algorithm to be used on the initial node */    
	status = CPXsetintparam (env, CPX_PARAM_STARTALG, STARTALG);
	if ( status ) 
	    stop("Failure to set the start-algorithm.\n", status);

	/* Set algorithm to be used on subsequent nodes */    
	status = CPXsetintparam (env, CPX_PARAM_SUBALG, SUBALG);
	if ( status ) 
	    stop("Failure to set the start-algorithm.\n", status);
  
}
#endif
  
double SSCplex::GetObjVal( ){
	return objval;
}


void SSCplex::Solve( void )
{
 // the solver 
#if( MIP )
 status = CPXmipopt (env, lp);
 if ( status ) {
   stop("Failed to optimize MIP.\n", status);
 }
 int solstat = CPXgetstat (env, lp);
 cout << "Solstat " << solstat << endl;
 status = CPXgetmipobjval (env, lp, &objval);
 if ( status ) 
   stop("No MIP objective value available.  Exiting...\n", status);


 // get the best solution
 int begin = 0;
 int end = begin + NArcs;
 
 status = CPXgetmipx (env, lp, Y, begin, end-1);

 int k = 0;
 bool found = false;
 while( !found && ( k < lev_card ))
  if( Y[k] )
  {
   found = true;
   cout << "vf 0 on VM " << k << endl;
  }
  else
   k++;

 for( int h = 0; h < h_len - 1; h++ )
 {
  found = false;
  int i = 0;
  while( !found && ( i < lev_card ))
  {
   int j = 0;
   int offset = lev_card +  h * (lev_card * lev_card) + i * lev_card;
   while( !found && ( j < lev_card ))
   {
    if( Y[offset + j] )
    {
     found = true;
     cout << "vf " << h+1 << " on VM " << j << endl;
    }
    else
     j++;
   }
   i++;
  }
 }
#endif
}//END SolveMIP
  
void SSCplex::ChgBds(int z, double newval ){
        
	int j;
	int status;
	char lu;
	double bd;
	
	assert( newval == 0.0);

	j = z;	
	bd = newval;
	lu = 'U';	
	status = CPXchgbds(env, lp, 1, &j, &lu, &bd);
	
	if ( status ) {
		stop("Failed to change bounds.\n", status);
	}
};
        



void SSCplex::ChgPrType(int type)
{
  //  int status = CPXchgprobtype(env,lp,type);
  //  int status = CPXchgprobtype(env,lp,CPXPROB_RELAXED);
  int status = CPXchgprobtype(env,lp,2);
  if(!status) cout << "Error while solving problem type" << endl;
}

void SSCplex::AddExtraConstr( int NXC , int *IBeg , int *Indx ,
			      double *Vals , double *XLr , double *XUr )
{
  
#if DEBUG
	status = CPXwriteprob(env, lp, "SPIC.txt", "LP");
	if ( status ) stop("Failed to write LP to disk.", status);
#endif

 }  // end( SSCplex::AddExtraConstr )


SSCplex::~SSCplex(){
  /* Free up the class data member arrays */

  delete[] dest_dist;
  delete[] source_dist;

  for( int i = 0; i < num_vf; i++ )
   delete proc_time[i];
  delete[] proc_time;

  for( int i = 0; i < num_vf; i++ )
   delete incom[i];
  delete[] incom;

  delete[] cap;
  
  for( int i = 0; i < num_vm; i++ )
    delete tempi_lat[i];
  delete[] tempi_lat;

 free_array(Y);
}
;









