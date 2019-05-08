// Contains code-gen definitions

#define STM_alloc double** A = (double **) malloc(sizeof(double *) * num_threads * 8); \
                  double** B = (double **) malloc(sizeof(double *) * num_threads * 8); \
                  double** C = (double **) malloc(sizeof(double *) * num_threads * 8);

#define STM_DS_alloc A[t_id * 8] = (double *) malloc(sizeof(double) * n); \
                     B[t_id * 8] = (double *) malloc(sizeof(double) * n); \
                     C[t_id * 8] = (double *) malloc(sizeof(double) * n);

#define A_map(j) A[t_id * 8][j]
#define B_map(j) B[t_id * 8][j]
#define C_map(j) C[t_id * 8][j]

#define STM_postrun()

#define scalar 3.0

#define STM_init(j) A_map(j) =  1.0, B_map(j) = 3.0, C_map(j) = 4.0;
#define STM_run(j) A_map(j) = B_map(j) + scalar * C_map(j);

#define STM_FUNC_calcn(wss,nThreads) (wss) / (3 * sizeof(double) * (nThreads));
#define STM_FUNC_calcActualWSS(n,nThreads) (n) * sizeof(double) * 3 * (nThreads);		       


bool validate_results(Configuration& configuration, Measurements& measurements, double *A){
  double a_val, b_val, c_val;
  double a_delta = 0, b_delta = 0, c_delta = 0;
  double a_err;
  double epsilon = 1.e-13;
  int k, j, flag_err = 0, i_err = 0;
  int wss = configuration.getInt("wss");
  int ntimes = configuration.getInt("ntimes");
  int num_threads = configuration.getInt("num_threads");
  int stream_array_size = STM_FUNC_calcn(wss,num_threads);
  a_val = 1.0;
  b_val = 3.0;
  c_val = 4.0;
  for(k = 0; k < ntimes; k++){
     a_val = b_val + scalar * c_val;
  }
  for(j = 0; j < stream_array_size; j++){
     a_delta += abs(A[j] - a_val);
  }
  a_err = a_delta/(float)stream_array_size;
  if(abs(a_err/a_val) > epsilon){
     flag_err++;
     i_err = 0;
     for(j = 0; j < stream_array_size; j++){
        if(abs(A[j]/a_val-1.0) > epsilon){
           i_err++;
        }   
     }   
     measurements.setField("NofErrors", i_err);
  }
  if(flag_err == 0){ 
     measurements.setField("V", "SUCCESS");
     return true;
  }
  measurements.setField("V", "FAILURE");
  return false;
}
