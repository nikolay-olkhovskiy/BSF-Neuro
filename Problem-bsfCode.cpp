/*==============================================================================
Project: Bulk Synchronous Farm (BSF)
Theme: BSF Skeleton
Module: Problem-bsfCode.cpp (Problem-dependent Code)
Prefix: PC
Author: Leonid B. Sokolinsky
This source code is a part of BSF Skeleton (https://github.com/leonid-sokolinsky/BSF-skeleton)
==============================================================================*/
#include <fdeep/fdeep.hpp>
#include "Problem-Data.h"			// Problem Types 
#include "Problem-Forwards.h"		// Problem Function Forwards
#include "Problem-bsfParameters.h"	// BSF-skeleton parameters
#include "BSF-SkeletonVariables.h"	// Skeleton Variables
using namespace std;

//----------------------- Predefined problem-dependent functions -----------------
void PC_bsf_Init(bool* success) {
	FILE* stream;
	PT_float buf;
	const char* lppFile;

	srand((unsigned)time(NULL) * (BSF_sv_mpiRank + 10));
	// ------------- Load LPP data -------------------

	PD_lppFile = PP_PATH;
	PD_lppFile += PP_LPP_FILE;
	lppFile = PD_lppFile.c_str();
	stream = fopen(lppFile, "r");
	if (stream == NULL) {
		if (BSF_sv_mpiRank == BSF_sv_mpiMaster)
			cout << "Failure of opening file '" << lppFile << "'.\n";
		*success = false;
		return;
	}

	if (fscanf(stream, "%d%d", &PD_m, &PD_n) == 0) {
		if (BSF_sv_mpiRank == BSF_sv_mpiMaster)
			cout << "Unexpected end of file" << endl;
		*success = false;
		return;
	}

	if (PD_m > PP_MAX_M || PD_n != PP_N) {
		if (BSF_sv_mpiRank == BSF_sv_mpiMaster) {
			cout << "Wrong problem parameters!" << endl;
			cout << "Number of inequalities: " << PD_m << " (max: " << PP_MAX_M << ")." << endl;
			cout << "Number of dimensions: " << PD_n << " (correct: " << PP_N << ")." << endl;
		}
		*success = false;
		return;
	}

	for (int i = 0; i < PD_m; i++) {
		for (int j = 0; j < PD_n; j++) {
			if (fscanf(stream, "%f", &buf) == 0) {
				if (BSF_sv_mpiRank == BSF_sv_mpiMaster)
					cout << "Unexpected end of file" << endl;
				*success = false;
				//				system("pause");
				return;
			}
			PD_A[i][j] = buf;
		}
		if (fscanf(stream, "%f", &buf) == 0) {
			if (BSF_sv_mpiRank == BSF_sv_mpiMaster)
				cout << "Unexpected end of file" << endl;
			*success = false;
			//			system("pause");
			return;
		}
		PD_b[i] = buf;
	}

	for (int j = 0; j < PD_n; j++) {
		if (fscanf(stream, "%f", &buf) == 0) {
			if (BSF_sv_mpiRank == BSF_sv_mpiMaster)
				cout << "Unexpected end of file" << endl;
			*success = false;
			//			system("pause");
			return;
		}
		PD_c[j] = buf;
		PD_z[j] = buf + 1.;
	}
	fclose(stream);
}

void PC_bsf_MasterInit(bool* success) {
	/*
	std::fill(PD_InputLayer.begin(), PD_InputLayer.end(), 1.);
	std::cout << PD_InputLayer.size() << std::endl;
	std::copy(PD_InputLayer.begin(), PD_InputLayer.end(), std::ostream_iterator<int>(std::cout, " "));
	std::cout << endl;

	PD_DNN = fdeep::load_model("fdeep_model.json");
	*/
}

void PC_bsf_SetListSize(int* listSize) {
	*listSize = 100;
}

void PC_bsf_CopyParameter(PT_bsf_parameter_T parameterIn, PT_bsf_parameter_T* parameterOutP) {

}

void PC_bsf_MapF(PT_bsf_mapElem_T* mapElem, PT_bsf_reduceElem_T* reduceElem, int* success) {	// For Job 0

}

void PC_bsf_MapF_1(PT_bsf_mapElem_T* mapElem, PT_bsf_reduceElem_T_1* reduceElem, int* success) {// For Job 1
	// Optional filling. Do not delete!
}

void PC_bsf_MapF_2(PT_bsf_mapElem_T* mapElem, PT_bsf_reduceElem_T_2* reduceElem, int* success) {// For Job 2
	// Optional filling. Do not delete!
}

void PC_bsf_MapF_3(PT_bsf_mapElem_T* mapElem, PT_bsf_reduceElem_T_3* reduceElem, int* success) {// For Job 3
	// Optional filling. Do not delete!
}

void PC_bsf_ReduceF(PT_bsf_reduceElem_T* x, PT_bsf_reduceElem_T* y, PT_bsf_reduceElem_T* z) {			// For Job 0
	// z = x (+) y
}

void PC_bsf_ReduceF_1(PT_bsf_reduceElem_T_1* x, PT_bsf_reduceElem_T_1* y, PT_bsf_reduceElem_T_1* z) {	// For Job 1
	// Optional filling. Do not delete!
}

void PC_bsf_ReduceF_2(PT_bsf_reduceElem_T_2* x, PT_bsf_reduceElem_T_2* y, PT_bsf_reduceElem_T_2* z) {	// For Job 2
	// Optional filling. Do not delete!
}

void PC_bsf_ReduceF_3(PT_bsf_reduceElem_T_3* x, PT_bsf_reduceElem_T_3* y, PT_bsf_reduceElem_T_3* z) {	// For Job 3
	// optional filling
}

void PC_bsf_ProcessResults(		// For Job 0
	PT_bsf_reduceElem_T* reduceResult,
	int reduceCounter, 
	PT_bsf_parameter_T* parameter, 
	int* nextJob,
	bool* exit 
) {
	*exit = true;
}

void PC_bsf_ProcessResults_1(	// For Job 1	
	PT_bsf_reduceElem_T_1* reduceResult,
	int reduceCounter, 
	PT_bsf_parameter_T* parameter, 
	int* nextJob,
	bool* exit 
) {
	// Optional filling. Do not delete!
}

void PC_bsf_ProcessResults_2(	// For Job 2
	PT_bsf_reduceElem_T_2* reduceResult,
	int reduceCounter, 
	PT_bsf_parameter_T* parameter, 
	int* nextJob,
	bool* exit 
	) {
	// Optional filling. Do not delete!
}

void PC_bsf_ProcessResults_3(	// For Job 3
	PT_bsf_reduceElem_T_3* reduceResult,
	int reduceCounter, 
	PT_bsf_parameter_T* parameter, 
	int* nextJob,
	bool* exit 
	) {
	// Optional filling. Do not delete!
}

void PC_bsf_JobDispatcher(
	PT_bsf_parameter_T* parameter, // Current Approximation
	int* job,
	bool* exit
) {
	// Optional filling. Do not delete!
}

void PC_bsf_ParametersOutput(PT_bsf_parameter_T parameter) {
	cout << "=================================================== Problem parameters ====================================================" << endl;
	cout << "Number of Workers: " << BSF_sv_numOfWorkers << endl;
	/*
	const auto result = PD_DNN->predict({
		fdeep::tensor(fdeep::tensor_shape(static_cast<std::size_t>(121)),
		std::vector<float>{PD_InputLayer})
	});
	std::cout << result.size() << std::endl;
	std::cout << result[0].depth() << std::endl;
	std::cout << result[0].rank() << std::endl;
	std::cout << result[0].height() << std::endl;
	std::cout << result[0].width() << std::endl;
	
	auto vec = result[0].to_vector();
	for (auto val : vec) std::cout << val << " ";
	cout << std::endl;
	*/
#ifdef PP_BSF_OMP
#ifdef PP_BSF_NUM_THREADS
	cout << "Number of Threads: " << PP_BSF_NUM_THREADS << endl;
#else
	cout << "Number of Threads: " << omp_get_num_procs() << endl;
#endif // PP_BSF_NUM_THREADS
#else
	cout << "OpenMP is turned off!" << endl;
#endif // PP_BSF_OMP
}

void PC_bsf_IterOutput(PT_bsf_reduceElem_T* reduceResult, int reduceCounter, PT_bsf_parameter_T parameter,
	double elapsedTime, int jobCase) {	// For Job 0
	cout << "------------------ " << BSF_sv_iterCounter << " ------------------" << endl;


}

void PC_bsf_IterOutput_1(PT_bsf_reduceElem_T_1* reduceResult, int reduceCounter, PT_bsf_parameter_T parameter,
	double elapsedTime, int jobCase) {	// For Job 1
	cout << "------------------ " << BSF_sv_iterCounter << " ------------------" << endl;
	// Optional filling. Do not delete!

}

void PC_bsf_IterOutput_2(PT_bsf_reduceElem_T_2* reduceResult, int reduceCounter, PT_bsf_parameter_T parameter,
	double elapsedTime, int jobCase) {	// For Job 2
	cout << "------------------ " << BSF_sv_iterCounter << " ------------------" << endl;
	// Optional filling. Do not delete!

}

void PC_bsf_IterOutput_3(PT_bsf_reduceElem_T_3* reduceResult, int reduceCounter, PT_bsf_parameter_T parameter,
	double elapsedTime, int jobCase) {	// For Job 3
	cout << "------------------ " << BSF_sv_iterCounter << " ------------------" << endl;
	// Optional filling. Do not delete!

}

void PC_bsf_ProblemOutput(PT_bsf_reduceElem_T* reduceResult, int reduceCounter, PT_bsf_parameter_T parameter,
	double t) {	// For Job 0

}

void PC_bsf_ProblemOutput_1(PT_bsf_reduceElem_T_1* reduceResult, int reduceCounter, PT_bsf_parameter_T parameter,
	double t) {	// For Job 1
	// Optional filling. Do not delete!
}

void PC_bsf_ProblemOutput_2(PT_bsf_reduceElem_T_2* reduceResult, int reduceCounter, PT_bsf_parameter_T parameter,
	double t) {	// For Job 2
	// Optional filling. Do not delete!
}

void PC_bsf_ProblemOutput_3(PT_bsf_reduceElem_T_3* reduceResult, int reduceCounter, PT_bsf_parameter_T parameter,
	double t) {	// For Job 3
	// Optional filling. Do not delete!
}

void PC_bsf_SetInitParameter(PT_bsf_parameter_T* parameter) {

}

void PC_bsf_SetMapListElem(PT_bsf_mapElem_T* elem, int i) {

}

//----------------------- Assigning Values to BSF-skeleton Variables (Do not modify!) -----------------------
void PC_bsfAssignAddressOffset(int value) { BSF_sv_addressOffset = value; }
void PC_bsfAssignIterCounter(int value) { BSF_sv_iterCounter = value; }
void PC_bsfAssignJobCase(int value) { BSF_sv_jobCase = value; }
void PC_bsfAssignMpiMaster(int value) { BSF_sv_mpiMaster = value; }
void PC_bsfAssignMpiRank(int value) { BSF_sv_mpiRank = value; }
void PC_bsfAssignNumberInSublist(int value) { BSF_sv_numberInSublist = value; }
void PC_bsfAssignNumOfWorkers(int value) { BSF_sv_numOfWorkers = value; }
void PC_bsfAssignParameter(PT_bsf_parameter_T parameter) { PC_bsf_CopyParameter(parameter, &BSF_sv_parameter); }
void PC_bsfAssignSublistLength(int value) { BSF_sv_sublistLength = value; }

//----------------------------- User functions -----------------------------
void DNN(PT_input_layer data, PT_vector direction) {
	direction[0] = 0.;
	direction[1] = 0.;
	direction[2] = 1.;
}