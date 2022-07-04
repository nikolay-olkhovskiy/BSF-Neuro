/*==============================================================================
Project: Bulk Synchronous Farm (BSF)
Theme: BSF Skeleton
Module: Problem-Parameters.h (Problem Parameters)
Prefix: PP
Author: Leonid B. Sokolinsky

This source code is a part of BSF Skeleton (https://github.com/leonid-sokolinsky/BSF-skeleton)
==============================================================================*/

//=========================== Problem Parameters =========================
#define PP_N		3									// Number of dimensions
#define PP_ETA		15									// Rank of receptive field 		
#define PP_DELTA	0.5									// Density of receptive field
#define PP_K		961								// Number of points in receptive field
#define PP_MAX_M	25000								// Maximum number of inequalities

#define PP_PATH			"C:/Users/nikolay/source/repos/nikolay-olkhovskiy/BSF-Neuro/"	// Working directory of the application
//#define PP_PATH		"/home/olkhovskiina/input/"	// Working directory of the application
#define PP_LPP_FILE		"model_example.txt"
#define PP_MODEL_FILE	"fdeep_model.json"
#define PP_STEP_FILE	"step.txt"
#define PP_RETINA_BASE	"base.ret"

//-------------------------- Macroses ---------------------------
#define PF_MIN(x,y) (x<y?x:y)