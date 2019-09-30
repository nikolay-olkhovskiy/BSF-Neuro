/*==============================================================================
Project: Bulk Synchronous Farm (BSF)
Theme: BSF Skeleton
Module: Problem-Implementation.cpp (Implementation of the Problem)
Prefix: PI
Author: Nadezhda A. Ezhova
Supervisor: Leonid B. Sokolinsky
This source code is a part of BSF Skeleton
==============================================================================*/

#include "Problem-Include.h"		// Problem "Include" Files
#include "Problem-bsfTypes.h"		// Predefined BSF Problem Types
#include "Problem-Types.h"			// Problem Types 
#include "Problem-Data.h"			// Problem Data 
#include "Problem-Forwards.h"		// Problem Function Forwards
#include "Problem-bsfParameters.h"	// BSF Skeleton Parameters
using namespace std;

void PI_bsf_Init(bool* success) { // success=false if initialization is unsuccessful
	cout << setprecision(PP_BSF_PRECISION);
	//...
}; 

void PI_bsf_AssignListSize(int* listSize) {

};

void PI_bsf_CopyData(PT_bsf_data_T* dataIn, PT_bsf_data_T* dataOut) {

};

void PI_bsf_MapF(PT_bsf_mapElem_T* mapElem, PT_bsf_reduceElem_T* reduceElem, int index, PT_bsf_data_T* data,
	int* success // 1 - reduceElem was produced successfully; 0 - otherwise
){

};

void PI_bsf_ReduceF(PT_bsf_reduceElem_T* x, PT_bsf_reduceElem_T* y, PT_bsf_reduceElem_T* z) { // z = x + y

};

void PI_bsf_ProcessResults(
	bool* exit, // "true" if Stopping Criterion is satisfied, and "false" otherwise
	PT_bsf_reduceElem_T* reduceResult,
	int count, // Number of successfully produced Elrments of Reduce List
	PT_bsf_data_T* data // Next Approximation
){

};

void PI_bsf_ParametersOutput(int numOfWorkers, PT_bsf_data_T data) {

};

void PI_bsf_IterOutput(PT_bsf_reduceElem_T* reduceResult, int count, PT_bsf_data_T data,
	int iterCount, double elapsedTime) {

//	static int counter = 0;	// Iteration Counter
//	counter++;
//	cout << "------------------ " << counter << " ------------------" << endl;

};

void PI_bsf_ProblemOutput(PT_bsf_reduceElem_T* reduceResult, int count, PT_bsf_data_T data,
	int iterCount, double t, double t_L, double t_s_L, double t_S, double t_r_L, double t_W,
	double t_A_w, double t_A_m, double t_p) {// Output Function

};

void PI_bsf_SetInitApproximation(PT_bsf_data_T* data) {

};

void PI_bsf_SetMapSubList(PT_bsf_mapElem_T* subList, int count, int offset, bool* success) {
	for (int j = 0; j < count; j++) {

	};
};

//----------------------------- User functions -----------------------------