/*==============================================================================
Project: Bulk Synchronous Farm (BSF)
Theme: BSF Skeleton
Module: BSF-Types.h (BSF Types)
Prefix: BT
Author: Nadezhda A. Ezhova 
Supervisor: Leonid B. Sokolinsky
This source code is a part of BSF Skeleton
==============================================================================*/

//=========================== BSF Types ===============================
struct BT_order_T {  
	char exit;		// true, if worker must stop
	PT_bsf_data_T data;
};

struct BT_extendedReduceElem_T { // Extended element type of reduce list
	PT_bsf_reduceElem_T elem;	// Element of reduce list
	int counter;			// Counter
	double t_W;
	double t_A_w;
};
