/*==============================================================================
Project: Bulk Synchronous Farm (BSF)
Theme: BSF Skeleton
Module: Problem-bsf-Forwards.h (Problem Function Forwards)
Author: Leonid B. Sokolinsky 
This source code is a part of BSF Skeleton (https://github.com/leonid-sokolinsky/BSF-skeleton)
==============================================================================*/
#include "Problem-bsfTypes.h"	// Predefined BSF types
#include "Problem-Types.h"		// Problem Types
//====================== Problem Functions ===========================
inline void DNN(PT_input_layer data, PT_vector direction);
inline void basis_Init();
inline void print_Vector(PT_vector x);
inline void add_Vector(PT_vector To, PT_vector From);
inline void subtract_Vector(PT_vector To, PT_vector From);
inline void copy_Vector(PT_vector To, PT_vector From);
inline void multiply_Vector(PT_vector To, PT_float C);
inline PT_float dotproduct_Vector(PT_vector x, PT_vector y);
inline void divide_Vector(PT_vector To, PT_float C);
inline void square_Vector(PT_vector To);
inline PT_float vector_Sum(PT_vector v, int start);
inline void basis_Print();

// Helper functions for MapF implementation
inline void G(PT_bsf_parameter_T parameter, PT_vector out);
inline bool isInnerPoint(PT_vector point);
inline void targetProjection(int i, PT_vector _In, PT_vector _Out);
inline PT_float objectiveDistance(PT_vector g);