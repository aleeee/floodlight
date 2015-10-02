#include "SSCplex.h"

int main (int argc, char *argv[])
{
 char* istanza=argv[1];

 long starttime, endtime; //starting and ending time 
 double oneruntime, runtime;
#if LINUX_TIMING
 clock_t t_u; 
 struct tms buff; 
#endif

 SSCplex *pg;
 
 runtime = 0;


 oneruntime = 0;
 starttime = clock();

#if LINUX_TIMING
	times(&buff);
	t_u = buff.tms_utime;
#endif
	pg = new SSCplex( istanza );

	pg->Solve( );
	
       double obj = pg->GetObjVal();
       cout << "Total latency time " << obj << endl;
#if LINUX_TIMING
	times(&buff);
#endif
	
	endtime = clock();
	
	oneruntime = ((double) (endtime - starttime)) / CLOCKS_PER_SEC;
	cout << "Total CPU time (I/0 + solver) " << oneruntime << endl;
	runtime += oneruntime;

	delete pg; 
	return 0;

}




