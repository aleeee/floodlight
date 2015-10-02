// stdafx.h : include file for standard system include files,
//  or project specific include files that are used frequently, but
//      are changed infrequently
//

#if !defined(AFX_STDAFX_H__62B87BDF_9578_4F69_A6E1_612D3F4C1F7E__INCLUDED_)
#define AFX_STDAFX_H__62B87BDF_9578_4F69_A6E1_612D3F4C1F7E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


// Insert your headers here
#define WIN32_LEAN_AND_MEAN		// Exclude rarely-used stuff from Windows headers

#define LINUX_TIMING 1 // if 1, use times() instead of clock() for the 
                       // total running time
#include <float.h>
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <string>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <cassert>    
#include <math.h>
#include <limits>
#include <assert.h>
#include <ctime>
#include <vector>
#include <list>
#include <iterator>
//#include <C:\ILOG\CPLEX90\include\ilcplex\cplex.h>
#include "/opt/ibm/ILOG/CPLEX_Studio_Community1262/cplex/include/ilcplex/cplex.h"

#if LINUX_TIMING
#include <unistd.h> //modifica 18/02/2008
#include <sys/times.h>
#endif

using namespace std;

#define MIP 1
#if( MIP )
#define MIPEMPH 1
#define NUMINTSOL 10000  // max number of integer solution generated
#define TIMELIMIT 1200  // maximum running time
#define CLOCKTYPE 1      // 0 for automatic, 1 for CPU time, 
                         //2 for wall clock time
#define NUMNODE   1000000 // maximum number of nodes in the B&B tree
#define NODESEL   0      // 0:depth-first, 1: best bound, 2: best estimate
#define VARSEL    0      // -1: min infeas, 0: automatic, 1: max infeas.,
                         // 2:pseudo cost, 3:strong branching, 4:reduced costs
#define BRDIR     0      // -1: down branch, 0: automatic, 1: up branch  
#define BACKTRACK 0.9   // [0,1]: low values increase backtracking (bestbound)
                         // high values decrease backtracking (depth-first)  
                         // Use values close to 1 with MIPEMPH = 0
#define STARTALG  1      // alg. used in the initial node: 1: primal,
                         // 2: dual, 3: network, 4: barrier ... 
#define SUBALG    2      // alg. used on subsequent node
#endif

#define PRINT 2
#define DEBUG 1
#define INFD DBL_MAX
#define RUNS 1
#define BILLAUT_INST 0
#define NICKEL_INST 0
#define JENSEN_INST 0
//#define uplim 0.0001
//#define lowlim -0.0001
//#define uplim 0.000001
#define uplim 0.001
//#define lowlim -0.000001
#define lowlim -0.001
#define epsilon 0.001
#define epsilon_sol 0.01

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_STDAFX_H__62B87BDF_9578_4F69_A6E1_612D3F4C1F7E__INCLUDED_)
