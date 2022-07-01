/*==============================================================================
Project: Bulk Synchronous Farm (BSF)
Theme: BSF Skeleton
Module: Problem-Data.h (Problem Data)
Prefix: PD
Author: Leonid B. Sokolinsky
This source code is a part of BSF Skeleton (https://github.com/leonid-sokolinsky/BSF-skeleton)
==============================================================================*/
#include "Problem-Types.h"			// Problem Parameters 
#include <optional>
using namespace std;
//========================== Problem variables ====================================
static int						PD_n;			// Space dimension
static int						PD_m;			// Number of inequalities
static int						PD_t;			// Current step
static PT_input_layer			PD_I;			// Distances from retina points to objective projections
std::optional<fdeep::model>		PD_DNN;
static PT_vector				PD_base;		// Coordinate of base retina point
static PT_retina				PD_field;		// Coordinates of base retina points
static PT_retina				PD_retina;		// Coordinates of retina points

//========================== Problem data structures ==============================
static PT_matrix	PD_A;	// Matrix of the system Ax <= b
static PT_column	PD_b;	// Column of the constant terms of the system Ax <= b
static PT_vector	PD_c;	// Coefficients of the objective function <c,x>
static PT_matrix	PD_E;	// Matrix of vectors e(i) forming basis othogonal to objective function
static PT_vector	PD_g;	// Point of retina
static PT_vector	PD_z;	// Center of retina
//static PT_image		PD_I;	// Retina
static PT_vector	PD_v;	// Output vector predicted by neural network

//========================== Files ================================================
static string PD_lppFile; /* LPP file in the following format:
------------ begin of file -------------
m n
A_11 A_12 ... A_1n b_1
A_21 A_22 ... A_2n b_2
...
A_m1 A_m2 ... A_mn b_m
c_1 c_2 ... c_n
------------ end of file----------------*/
static string PD_outFile; /* OUT file in the following format:
------------ begin of file -------------
PD_n PP_K
z_1
z_2
...
z_n
I_1
I_2
...
I_k
v_1
v_2
...
v_n
------------ end of file----------------*/