// Contains code-gen definitions
// ADAPT_OP_PTS=schedule(static),schedule(dynamic)
#define STM_alloc double* A = (double *) malloc(sizeof(double) * (n + 2)); \
                  double* B = (double *) malloc(sizeof(double) * (n + 2));


#define A_map(j) A[j]
#define B_map(j) B[j]

#define EPS 1e-13

#define STM_init(j) A_map(j) = j * 1.0, B_map(j) = j * 1.2;
#define STM_run(j) A_map(j) = B_map(j-1) + B_map(j) + B_map(j+1);
#define STM_postrun() double* tmp = A;A=B;B=tmp;
#define STM_val(j) flag_err = abs(A_map(j) - ((j-1+1)*1.2 + \
                                   (j+1)*1.2 + \
                                    (j+1+1)*1.2) \
                       ) <= EPS && !flag_err ? 1 : flag_err;
		      

#define STM_FUNC_calcn(wss) (wss)/(2*sizeof(double));
#define STM_FUNC_calcActualWSS(n) (n)*sizeof(double) * 2;




bool validate_results(Configuration& configuration, Measurements& measurements, double *A, double *B){
  int wss = configuration.getInt("wss");
  int ntimes = configuration.getInt("ntimes");
  int nv = STM_FUNC_calcn(wss);
  int i, j;
  int err = 0;
  double *exp_A = (double *) malloc(sizeof(double) * (nv + 2));
  double *exp_B = (double *) malloc(sizeof(double) * (nv + 2));
  for (i = 0; i <= nv+1; i++){
     exp_A[i] = i * 1.0;
     exp_B[i] = i * 1.2; 
  }
  for (int k = 0; k < ntimes; k++) {
     for (j = 1; j <= nv; j++) {
        exp_A[j] = exp_B[j-1] + exp_B[j] + exp_B[j+1];
     }
     double* temp = exp_A; exp_A = exp_B; exp_B = temp;
  }
  
  for (i = 0; i <= nv+1; i++) {
     /*printf("A[%d]=%lf, ", i, A[i]);
     printf("B[%d]=%lf,   ", i, B[i]);
     printf("exp_A[%d]=%lf, ", i, exp_A[i]);
     printf("exp_B[%d]=%lf ", i, exp_B[i]);
     printf("\n");*/
     if (ntimes % 2 == 0){
        if ( abs(exp_A[i] - A[i]) > EPS ) {
            err++;
            printf("ERROR %d --   ", err);
            printf("A[%d]=%lf, ", i, A[i]);
            printf("B[%d]=%lf,   ", i, B[i]);
            printf("exp_A[%d]=%lf, ", i, exp_A[i]);
            printf("exp_B[%d]=%lf ", i, exp_B[i]);
            printf("\n"); 
        }
     }
     else {
        if ( abs(exp_B[i] - B[i]) >= EPS ) {
            err++;
            printf("ERROR %d --  ", err);
            printf("A[%d]=%lf, ", i, A[i]);
            printf("B[%d]=%lf,   ", i, B[i]);
            printf("exp_A[%d]=%lf, ", i, exp_A[i]);
            printf("exp_B[%d]=%lf ", i, exp_B[i]);
            printf("\n"); 
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
