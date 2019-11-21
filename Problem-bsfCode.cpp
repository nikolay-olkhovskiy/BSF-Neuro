/*==============================================================================
Project: Bulk Synchronous Farm (BSF)
Theme: BSF Skeleton
Module: Problem-bsfCode.cpp (Problem-dependent Code)
Prefix: PI
Author: Leonid B. Sokolinsky

This source code is a part of BSF Skeleton
==============================================================================*/
#include "Problem-bsfParameters.h"	// Predefined Problem Parameters
#include "Problem-Data.h"			// Problem Types 
#include "Problem-Forwards.h"		// Problem Function Forwards
#include "Problem-Include.h"		// Problem "Include" Files
using namespace std;

//----------------------- Predefined problem-dependent functions -----------------
void PC_bsf_Init(bool* success) { // success=false if initialization is unsuccessful

}; 

void PC_bsf_AssignListSize(int* listSize) {

};

void PC_bsf_CopyData(PT_bsf_data_T* dataIn, PT_bsf_data_T* dataOut) {

};

void PC_bsf_MapF(PT_bsf_mapElem_T* mapElem, PT_bsf_reduceElem_T* reduceElem, PT_bsf_data_T* data, int numberInSublist, 
	int sublistLength, int offset, int* success // 1 - reduceElem was produced successfully; 0 - otherwise
){

};

void PC_bsf_ReduceF(PT_bsf_reduceElem_T* x, PT_bsf_reduceElem_T* y, PT_bsf_reduceElem_T* z) { // z = x + y

};

void PC_bsf_ProcessResults(
	bool* exit, // "true" if Stopping Criterion is satisfied, and "false" otherwise
	PT_bsf_reduceElem_T* reduceResult,
	int reduceCounter, // Number of successfully produced Elrments of Reduce List
	PT_bsf_data_T* data, // Current Approximation
	int iterCounter	// Iteration Counter
){

};

void PC_bsf_ParametersOutput(int numOfWorkers, PT_bsf_data_T data) {
	cout << "Number of Workers: " << numOfWorkers << endl;
#ifdef PP_BSF_OMP
#ifdef PP_BSF_NUM_THREADS
	cout << "Number of Threads: " << PP_BSF_NUM_THREADS << endl;
#else
	cout << "Number of Threads: " << omp_get_num_procs() << endl;
#endif // PP_BSF_NUM_THREADS
#else
	cout << "OpenMP is turned off!" << endl;
#endif // PP_BSF_OMP

};

void PC_bsf_IterOutput(PT_bsf_reduceElem_T* reduceResult, int reduceCounter, PT_bsf_data_T data,
	int iterCounter, double elapsedTime) {

//	cout << "------------------ " << iterCounter << " ------------------" << endl;

};

void PC_bsf_ProblemOutput(PT_bsf_reduceElem_T* reduceResult, int reduceCounter, PT_bsf_data_T data,
	int iterCounter, double t) {// Output Function

};

void PC_bsf_SetInitApproximation(PT_bsf_data_T* data) {

};

void PC_bsf_SetMapSubList(PT_bsf_mapElem_T* sublist, int sublistLength, int offset, bool* success) {
	for (int j = 0; j < sublistLength; j++) {

	};
};

//----------------------------- User functions -----------------------------