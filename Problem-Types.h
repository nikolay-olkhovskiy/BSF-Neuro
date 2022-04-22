/*==============================================================================
Project: Bulk Synchronous Farm (BSF)
Theme: BSF Skeleton
Module: Problem-Types.h (Problem Types)
Prefix: PT
Author: Leonid B. Sokolinsky

This source code is a part of BSF Skeleton (https://github.com/leonid-sokolinsky/BSF-skeleton)
==============================================================================*/
#pragma once
#include "Problem-Include.h"		// Problem "Include" Files
#include "Problem-Parameters.h"		// Problem Parameters 
//=========================== Problem Types =========================
typedef float					PT_float;
typedef int						PT_integer;
typedef PT_float				PT_input_layer[PP_K];
typedef PT_float				PT_vector[PP_N];
typedef PT_vector				PT_matrix[PP_MAX_M];
typedef PT_float				PT_column[PP_MAX_M];
typedef PT_float				PT_image[PP_K];
