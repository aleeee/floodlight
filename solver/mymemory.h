#ifndef __MYMEMORY
#define __MYMEMORY


#include "StdAfx.h"
//#include "OPTvect.h"

//using namespace OPTtypes_di_unipi_it;

#ifdef UNIX
#define CALLOC(ptr, nr, type) if( (ptr = (type *) calloc((size_t)(nr), sizeof(type))) == 0){fprintf(stderr, "calloc failed on line %d of file %s\n", __LINE__, __FILE__); exit(0);}
#endif


typedef int *intptr;
typedef intptr *int2ptr;
typedef double *doubleptr;
typedef doubleptr *double2ptr;


inline void stop(char* string, int code){
	cout<<string<<'\n';
	exit(code);
};

inline bool *arraybool(int up)
 {
  bool *tmp;
  int  i;

  #ifdef UNIX
  CALLOC(tmp, up, bool);
  for(i=0;i<up;i++) tmp[i] = false;
  #else 
  tmp = new bool[up];
  for(i=0;i<up;i++) tmp[i] = false;
  #endif
  
  return(tmp);
 }


inline void free_arraybool(bool *a)
 {

  #ifdef UNIX
	if (a) free(a);  
  #else	
	if (a) delete [] a;  
  #endif

 }

inline int *arrayint(int up)
 {
  int *tmp;
  int i;

  #ifdef UNIX
  CALLOC(tmp, up, int);
  for(i=0;i<up;i++) tmp[i] = 0;
  #else 
  tmp = new int[up];
  for(i=0;i<up;i++) tmp[i] = 0;
  #endif
  
  return(tmp);
 }

inline int *arrayint_defaultvalue(int up, int value)
 {
  int *tmp;
  int i;

  #ifdef UNIX
  CALLOC(tmp, up, int);
  for(i=0;i<up;i++) tmp[i] = value;
  #else 
  tmp = new int[up];
  for(i=0;i<up;i++) tmp[i] = value;
  #endif
  
  return(tmp);
 }

inline void free_arrayint(int *a)
 {

  #ifdef UNIX
	if (a) free(a);  
  #else	
	if (a) delete [] a;  
  #endif

 }


inline double *array(int up)
 {
  double *tmp;
  int i;

  #ifdef UNIX
  CALLOC(tmp, up, double);
  for(i=0;i<up;i++) tmp[i] = 0;
  #else 
  tmp = new double[up];
  for(i=0;i<up;i++) tmp[i] = 0;
  #endif

  return(tmp);
 }

inline double *arrayinf(int up)
 {
  double *tmp;
  int i;

  #ifdef UNIX
  CALLOC(tmp, up, double);
  for(i=0;i<up;i++) tmp[i] = INFD;
  #else 
  tmp = new double[up];
  for(i=0;i<up;i++) tmp[i] = INFD;
  #endif

  return(tmp);
 }

inline void free_array(double *a)
 {
  #ifdef UNIX
	if (a) free(a);  
  #else	
	if (a) delete [] a;  
  #endif
 }



inline char *arraychar(int up)
 {
  char *tmp;
  int i;

  #ifdef UNIX
  CALLOC(tmp, up, char);
  for(i=0;i<up;i++) tmp[i] = 0;
  #else 
  tmp = new char[up];
  for(i=0;i<up;i++) tmp[i] = 0;
  #endif

  return(tmp);
 }



inline void free_arraychar(char *a)
 {
  #ifdef UNIX
	if (a) free(a);  
  #else	
	if (a) delete [] a;  
  #endif
 }



inline int **matrix2int(int up1, int up2)
 {
  int    i,j;
  int **tmp;

  #ifdef UNIX
  CALLOC (tmp,up1,int*);
  for (i=0; i< up1; i++) 
  {
   CALLOC (tmp[i],up2,int);
   for(j=0;j<up2;j++) tmp[i][j] = 0;
  }
  #else
  tmp = new intptr[up1];
  for (i=0; i< up1; i++) 
  {
   tmp[i] = new int[up2];
   for(j=0;j<up2;j++) tmp[i][j] = 0;
  }
  #endif
  return(tmp);
 }



inline void free_matrix2int(int **a,int up1)
 {
  int   i;

  #ifdef UNIX
  if (!a) return;
  for (i=0; i< up1; i++) free(a[i]);
  free(a);
  #else	
  if (!a) return;
  for (i=0; i< up1; i++) delete [] a[i];
  delete [] a;
  #endif

 }


inline double **matrix2(int up1, int up2)
 {
  int    i,j;
  double **tmp;

  #ifdef UNIX
  CALLOC (tmp,up1,double*);
  for (i=0; i< up1; i++) 
  {
   CALLOC (tmp[i],up2,double);
   for(j=0;j<up2;j++) tmp[i][j] = 0;
  }
  #else
  tmp = new doubleptr[up1];
  for (i=0; i< up1; i++)  
  {
   tmp[i] = new double[up2];
   for(j=0;j<up2;j++) tmp[i][j] = 0;
  } 
  #endif

  return(tmp);
 }



inline void free_matrix2(double **a,int up1)
 {
  int   i;

  #ifdef UNIX
  if (!a) return;
  for (i=0; i< up1; i++) free(a[i]);
  free(a);
  #else	
  if (!a) return;
  for (i=0; i< up1; i++) delete [] a[i];
  delete [] a;
  #endif
 }



inline double ***matrix3(int up1, int up2, int up3)
 {
  int    i, j,k;
  double ***tmp;


  #ifdef UNIX
  CALLOC (tmp,up1,double**);  
  for (i=0; i< up1; i++)
   {
    CALLOC (tmp[i],up2,double*);
    for (j=0; j< up2; j++)
	{		 
     CALLOC (tmp[i][j],up3,double);
     for(k=0;k<up3;k++) tmp[i][j][k] = 0;
	}
   }
  #else  
  tmp = new double2ptr[up1];
  for (i=0; i< up1; i++)
   {
	tmp[i] = new doubleptr[up2];
    for (j=0; j< up2; j++)
	{		 
	 tmp[i][j] = new double[up3];
     for(k=0;k<up3;k++) tmp[i][j][k] = 0;
	}
   }
  #endif

  return(tmp);
 }



inline void free_matrix3(double ***a,int up1,int up2)
 {
  int   i, j;

  #ifdef UNIX
  if (!a) return;
  for (i=0; i<up1; i++)
   {
    for (j=0; j<up2; j++) free(a[i][j]);
    free(a[i]);
   }
  free(a);
  #else	
  if (!a) return;
  for (i=0; i<up1; i++)
   {
    for (j=0; j<up2; j++) delete [] a[i][j];
    delete [] a[i];
   }
  delete [] a;
  #endif  
 }



inline int ***matrix3int(int up1, int up2, int up3)
 {
  int    i, j,k;
  int ***tmp;

  #ifdef UNIX
  CALLOC (tmp,up1,int**);  
  for (i=0; i< up1; i++)
   {
    CALLOC (tmp[i],up2,int*);
    for (j=0; j< up2; j++)
	{		 
     CALLOC (tmp[i][j],up3,int);
     for(k=0;k<up3;k++) tmp[i][j][k] = 0;
	}
   }
  #else  
  tmp = new int2ptr[up1];
  for (i=0; i< up1; i++)
  {
	tmp[i] = new intptr[up2];
    for (j=0; j< up2; j++)
	{	
     tmp[i][j] = new int[up3];
     for(k=0;k<up3;k++) tmp[i][j][k] = 0;
	}
  }
  #endif

  return(tmp);
 }



inline void free_matrix3int(int ***a,int up1,int up2)
 {
  int   i, j;
  #ifdef UNIX
  if (!a) return;
  for (i=0; i<up1; i++)
   {
    for (j=0; j<up2; j++) free(a[i][j]);
    free(a[i]);
   }
  free(a);
  #else	
  if (!a) return;
  for (i=0; i<up1; i++)
   {
    for (j=0; j<up2; j++) delete [] a[i][j];
    delete [] a[i];
   }
  delete [] a;
  #endif  
 }

inline double cint(double x){

  double intpart;
  if (modf(x,&intpart)>=.5)
    return ceil(x);
  else
    return(floor(x));
}

inline double round(double r,unsigned places){
	double off=pow(10,places);
	return cint(r*off)/off;
}

#endif






