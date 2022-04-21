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
//========================== Problem variables ====================================
std::vector<float>				PD_InputLayer(121);
std::optional<fdeep::model>		PD_DNN;

//========================== Problem data structures ==============================
