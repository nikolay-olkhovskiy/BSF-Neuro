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
	}
	fclose(stream);
	basis_Init();

	PD_z[0] = 200.;
	PD_z[1] = 200.;
	PD_z[2] = 0.;

	PD_t = 0;

	if (BSF_sv_mpiRank == BSF_sv_mpiMaster) {
	/*
		std::fill(PD_InputLayer.begin(), PD_InputLayer.end(), 1.);
		std::cout << PD_InputLayer.size() << std::endl;
		std::copy(PD_InputLayer.begin(), PD_InputLayer.end(), std::ostream_iterator<int>(std::cout, " "));
		std::cout << endl;

		PD_DNN = fdeep::load_model("fdeep_model.json");
	*/
	}
}

void PC_bsf_SetListSize(int* listSize) {
	*listSize = PD_m;
}

void PC_bsf_CopyParameter(PT_bsf_parameter_T parameterIn, PT_bsf_parameter_T* parameterOutP) {
	parameterOutP->k = parameterIn.k;
	for (int i = 0; i < PD_n; i++) parameterOutP->z[i] = parameterIn.z[i];
}

void PC_bsf_MapF(PT_bsf_mapElem_T* mapElem, PT_bsf_reduceElem_T* reduceElem, int* success) {	// For Job 0
	PT_vector target;
	int i = mapElem->inequalityNo;
	G(BSF_sv_parameter, PD_g, PD_base);
	targetProjection(i, PD_g, target);
	for (int j = 0; j < PP_N; j++) reduceElem->g[j] = PD_g[j];
	for (int j = 0; j < PP_N; j++) reduceElem->base[j] = PD_base[j];
	if (dotproduct_Vector(PD_A[i], PD_c) > 0 && isInnerPoint(target)) {
		reduceElem->objectiveDistance = objectiveDistance(target);
	}
	else
		reduceElem->objectiveDistance = FLT_MAX;
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
	if (isfinite(x->objectiveDistance) && isfinite(y->objectiveDistance))
		z->objectiveDistance = PF_MIN(x->objectiveDistance, y->objectiveDistance);
	else if (isfinite(x->objectiveDistance))
		z->objectiveDistance = x->objectiveDistance;
	else if (isfinite(y->objectiveDistance))
		z->objectiveDistance = y->objectiveDistance;
	else
		z->objectiveDistance = FLT_MAX;
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
	FILE* stream;
	const char* fileName;

	PD_I[parameter->k] = reduceResult->objectiveDistance;
	copy_Vector(PD_retina[parameter->k], reduceResult->g);
	copy_Vector(PD_field[parameter->k], reduceResult->base);
	parameter->k += 1;

	if (parameter->k >= PP_K) {
		DNN(PD_I, PD_v);

		//--------------- Output step results -----------------//
		PD_outFile = PP_PATH;
		PD_outFile += "step" + to_string(PD_t) + ".txt";
		fileName = PD_outFile.c_str();
		cout << "-----------------------------------" << endl;
		stream = fopen(fileName, "w");
		if (stream == NULL) {
			cout << "Failure of opening file " << fileName << "!\n";
			return;
		}
		fprintf(stream, "%d %d\n", PD_n, PP_K);
		for (PT_integer i = 0; i < PD_n; i++) {
			fprintf(stream, "%.4f\n", PD_z[i]);
		}
		for (PT_integer i = 0; i < PP_K; i++) {
			for (PT_integer j = 0; j < PD_n; j++) {
				fprintf(stream, "%.4f ", PD_retina[i][j]);
			}
			fprintf(stream, "%.4f\n", PD_I[i]);
		}
		for (PT_integer i = 0; i < PD_n; i++) {
			fprintf(stream, "%.4f\n", PD_v[i]);
		}
		fclose(stream);
		cout << "Precedent is saved into file '" << fileName << "'." << endl;
		cout << "-----------------------------------" << endl;
		//--------------- End of step output -----------------//
		
		add_Vector(PD_z, PD_v);
		parameter->k = 0;
		copy_Vector(parameter->z, PD_z);
		PD_t++;
	}

	*exit = (PD_t > 10); // Possible overfilling!!! Needed type for superlong integers.
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
	cout << "Dimensions: " << PD_n << ", max = " << log(PP_K) / log(2 * PP_ETA + 1) << endl;
	cout << "Number of inequalities: " << PD_m << endl;
	cout << "Receptive field rank: " << PP_ETA << endl;
	cout << "Receptive field density: " << PP_DELTA << endl;
	cout << "Maximum number of points: " << PP_K << endl;
	cout << "Receptive field coordinates: " << endl;
	for (int i = 0; i < PD_n; i++) {
		cout << PD_z[i] << " ";
	}
	cout << endl;
	cout << "Objective function coordinates: " << endl;
	for (int i = 0; i < PD_n; i++) {
		cout << PD_c[i] << " ";
	}
	cout << endl;
	basis_Print();
	cout << "Matrix of inequalities: " << endl;
	for (int i = 0; i < PD_m; i++) {
		print_Vector(PD_A[i]); cout << endl;
	}
}

void PC_bsf_IterOutput(PT_bsf_reduceElem_T* reduceResult, int reduceCounter, PT_bsf_parameter_T parameter,
	double elapsedTime, int jobCase) {	// For Job 0
	cout << "------------------ " << BSF_sv_iterCounter << " ------------------" << endl;
	cout << "Time:\t" << elapsedTime << endl;
	cout << "Point number:\t" << parameter.k << endl;
	cout << "Z coordinates:\t";
	print_Vector(parameter.z);
	cout << endl;
	cout << "Receptive field rank:\t" << PP_ETA * PP_DELTA << endl;
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
	FILE* stream;
	const char* fileName;
	
	cout << "=============================================" << endl;
	cout << "Time: " << t << endl;
	cout << "Iterations: " << BSF_sv_iterCounter << endl;

	DNN(PD_I, PD_v);

	//--------------- Output results -----------------//
	PD_outFile = PP_PATH;
	PD_outFile += PP_STEP_FILE;
	fileName = PD_outFile.c_str();
	cout << "-----------------------------------" << endl;
	stream = fopen(fileName, "w");
	if (stream == NULL) {
		cout << "Failure of opening file " << fileName << "!\n";
		return;
	}
	fprintf(stream, "%d %d\n", PD_n, PP_K);
	for (PT_integer i = 0; i < PD_n; i++) {
		fprintf(stream, "%.4f\n", PD_z[i]);
	}
	for (PT_integer i = 0; i < PP_K; i++) {
		fprintf(stream, "%.4f\n", PD_I[i]);
	}
	for (PT_integer i = 0; i < PD_n; i++) {
		fprintf(stream, "%.4f\n", PD_v[i]);
	}
	fclose(stream);
	cout << "Image is saved into file '" << fileName << "'." << endl;
	cout << "-----------------------------------" << endl;

#ifdef PP_RETINA_BASE
	//--------------- Base retina output -----------------//
	PD_outFile = PP_PATH;
	PD_outFile += PP_RETINA_BASE;
	fileName = PD_outFile.c_str();
	cout << "-----------------------------------" << endl;
	stream = fopen(fileName, "w");
	if (stream == NULL) {
		cout << "Failure of opening file " << fileName << "!\n";
		return;
	}
	fprintf(stream, "%d %d\n", PD_n - 1, PP_K);
	for (PT_integer i = 0; i < PP_K; i++) {
		for (PT_integer j = 0; j < PD_n - 1; j++) {
			fprintf(stream, "%.4f ", PD_field[i][j]);
		}
		fprintf(stream, "\n");
	}
	fclose(stream);
	cout << "Base retina is saved into file '" << fileName << "'." << endl;
	cout << "-----------------------------------" << endl;
#endif

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
	parameter->k = 0;
	for (int i = 0; i < PD_n; i++) parameter->z[i] = PD_z[i];
}

void PC_bsf_SetMapListElem(PT_bsf_mapElem_T* elem, int i) {
	elem->inequalityNo = i;
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
	direction[2] = 10.;
}
inline void basis_Init() {
	//PD_c
	int j;
	PT_float length;
	PT_float tailSum;
	PT_vector PD_c2;

	//cout << "Basis initialization: " << endl;

	copy_Vector(PD_c2, PD_c);
	square_Vector(PD_c2);

	copy_Vector(PD_E[0], PD_c);
	for (int i = 1; i < PD_n; i++) {
		for (j = 0; j < i; j++)	PD_E[i][j] = 0;
		tailSum = vector_Sum(PD_c2, i);
		if (tailSum == 0) {
			PD_E[i][i - 1] = 0;
			PD_E[i][i] = 1;
			j++;
			for (; j < PD_n; j++) { PD_E[i][j] = 0; }
		}
		else if (PD_c[i - 1] == 0.) {
			PD_E[i][i - 1] = 1.;
			for (; j < PD_n; j++) { PD_E[i][j] = 0; }
		}
		else {
			PD_E[i][i - 1] = (PT_float)((-1. * tailSum) / PD_c[i - 1]);
			for (; j < PD_n; j++) { PD_E[i][j] = PD_c[j]; }
		}
		length = sqrt(dotproduct_Vector(PD_E[i], PD_E[i]));
		divide_Vector(PD_E[i], length);

	//	print_Vector(PD_E[i]);
	//	cout << endl;
	}
}
inline void print_Vector(PT_vector x) {
	for (int i = 0; i < PD_n; i++)
		cout << x[i] << " ";
}
inline void add_Vector(PT_vector To, PT_vector From) {
	for (int i = 0; i < PD_n; i++)
		To[i] += From[i];
}
inline void subtract_Vector(PT_vector To, PT_vector From) {
	for (int i = 0; i < PD_n; i++)
		To[i] -= From[i];
}
inline void copy_Vector(PT_vector To, PT_vector From) {
	for (int i = 0; i < PD_n; i++)
		To[i] = From[i];
}
inline void multiply_Vector(PT_vector To, PT_float C) {
	for (int i = 0; i < PD_n; i++)
		To[i] *= C;
}
inline PT_float dotproduct_Vector(PT_vector x, PT_vector y) {
	PT_float result = 0.0f;
	for (int i = 0; i < PD_n; i++) {
		result += x[i] * y[i];
	}
	return result;
}
inline void divide_Vector(PT_vector To, PT_float C) {
	for (int i = 0; i < PD_n; i++)
		To[i] /= C;
}
inline void square_Vector(PT_vector To) {
	for (int i = 0; i < PD_n; i++)
		To[i] *= To[i];
}
inline PT_float vector_Sum(PT_vector v, int start) {
	PT_float result = 0.0f;
	for (int i = start; i < PD_n; i++) {
		result += v[i];
	}
	return result;
}
inline void basis_Print() {
	for (int i = 1; i < PD_n; i++) {
		print_Vector(PD_E[i]);
		cout << endl;
	}
}

inline void G(PT_bsf_parameter_T parameter, PT_vector out, PT_vector base) {
	PT_vector tempPoint;
	PT_vector coordinate;
	PT_integer dimensionPointsNumber;
	int i[PP_N];
	PT_integer pointNo = parameter.k;

	for (int j = PD_n - 1; j > 0; j--) {
		dimensionPointsNumber = (PT_integer)powf(2 * PP_ETA + 1, (PT_float)j - 1); //Possible overfilling!
		i[j - 1] = (int)(pointNo / dimensionPointsNumber);
		pointNo = pointNo % dimensionPointsNumber;
	}
	//copy_Vector(tempPoint, PD_z);
	copy_Vector(tempPoint, parameter.z);
	for (int j = 1; j < PD_n; j++) {
		copy_Vector(coordinate, PD_E[j]);
		multiply_Vector(coordinate, (PT_float)(i[j - 1] * PP_DELTA - PP_ETA * PP_DELTA));
		base[j - 1] = (PT_float)(i[j - 1] * PP_DELTA - PP_ETA * PP_DELTA);
		add_Vector(tempPoint, coordinate);
	}
	for (int i = 0; i < PD_n; i++)
		out[i] = tempPoint[i];
};

inline bool isInnerPoint(PT_vector point) {
	bool result = true;
	for (int i = 0; i < PD_m; i++) {
		if (dotproduct_Vector(PD_A[i], point) > PD_b[i])
			result = false;
	}
	return result;
}

inline void targetProjection(int i, PT_vector _In, PT_vector _Out) {
	PT_vector projection;
	PT_vector temp;

	//------------ Computing target projection gamma_i ----------//
	copy_Vector(temp, PD_c);
	multiply_Vector(temp, (PT_float)((dotproduct_Vector(PD_A[i], _In) - PD_b[i]) / dotproduct_Vector(PD_A[i], PD_c)));
	copy_Vector(projection, _In);
	subtract_Vector(projection, temp);
	copy_Vector(_Out, projection);
}

inline PT_float objectiveDistance(PT_vector x) {
	PT_vector temp;

	//------------ Computing target distance rho_c -------------//
	copy_Vector(temp, PD_z);
	subtract_Vector(temp, x);

	return (PT_float)(dotproduct_Vector(PD_c, temp) / sqrt(dotproduct_Vector(PD_c, PD_c)));
}
