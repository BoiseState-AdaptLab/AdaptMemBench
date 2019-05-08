// Contains code-gen definitions
#define STM_alloc double** A = (double **) malloc(sizeof(double *) * num_threads * 8); \
                  double** B = (double **) malloc(sizeof(double *) * num_threads * 8);

#define STM_DS_alloc A[t_id * 8] = (double *) malloc(sizeof(double) * (n+2)); \
                     B[t_id * 8] = (double *) malloc(sizeof(double) * (n+2));


#define A_map(j) A[t_id * 8][j]
#define B_map(j) B[t_id * 8][j]

#define EPS 1e-13

#define STM_init(j) A_map(j) = j * 1.0, B_map(j) = j * 1.2;
#define STM_run(j) A_map(j) = (B_map(j-1) + B_map(j) + B_map(j+1)) * 0.3333;
#define STM_postrun() double* tmp = A[t_id * 8];A[t_id * 8]=B[t_id * 8];B[t_id * 8]=tmp;
#define STM_val(j) flag_err = abs(A_map(j) - ((j-1+1)*1.2 + \
                                   (j+1)*1.2 + \
                                    (j+1+1)*1.2) \
                       ) <= EPS && !flag_err ? 1 : flag_err;
		      

#define STM_FUNC_calcn(wss,nThreads) (wss)/(2*sizeof(double) * (nThreads));
#define STM_FUNC_calcActualWSS(n, nThreads) (n)*sizeof(double) * 2 * (nThreads);



bool verify_results(Configuration& configuration, Measurements& measurements, double **A, double **B){
  int wss = configuration.getInt("wss");
  int ntimes = configuration.getInt("ntimes");
  int num_threads = configuration.getInt("num_threads");
  int nv = wss/(2 * sizeof(double) * num_threads);
  int i, j;
  int err = 0;
  double** exp_A = (double **) malloc(sizeof(double *) * num_threads * 8);
  double** exp_B = (double **) malloc(sizeof(double *) * num_threads * 8);
  for (int t_id = 0; t_id < num_threads; t_id++) {
     exp_A[t_id] = (double *) malloc(sizeof(double) * (nv+2));
     exp_B[t_id] = (double *) malloc(sizeof(double) * (nv+2));
     for (int i = 0; i < nv+2; i++) {
         exp_A[t_id * 8][i] = i * 1.0;
         exp_B[t_id * 8][i] = i * 1.2;
     }
  }
  for (int k = 0; k < ntimes; k++) {
     for (int t_id = 0; t_id < num_threads; t_id++) {
        double *exp_dataptr_A = exp_A[t_id];
        double *exp_dataptr_B = exp_B[t_id];
        for (j = 1; j <= nv; j++) {
           exp_A[t_id * 8][j] = (exp_B[t_id * 8][j-1] + exp_B[t_id * 8][j] + exp_B[t_id * 8][j+1])*0.3333;
        }
        double* temp = exp_A[t_id * 8]; exp_A[t_id * 8] = exp_B[t_id * 8]; exp_B[t_id * 8]= temp;
     }
  }
 for (int t_id = 0; t_id < num_threads; t_id++) {
     for (i = 0; i <= nv+1; i++) {
        double *exp_dataptr_A = exp_A[t_id];
        double *exp_dataptr_B = exp_B[t_id];
        double *dataptr_A = A[t_id];
        double *dataptr_B = B[t_id];
        if (ntimes % 2 == 0){
          if ( abs(exp_A[t_id * 8][i] - A[t_id * 8][i]) >= EPS ) {
              err++;
           }
        }
        else {
          if ( abs(exp_B[t_id * 8][i] - B[t_id * 8][i]) >= EPS ) {
             err++;
          }
       }
    }
  }
  if (err > 0) {
     measurements.setField("NofErrors", err);
     measurements.setField("Verification", "FAILURE");
     return false;
  }
  measurements.setField("Verification", "SUCCESS");
  return true;
}

