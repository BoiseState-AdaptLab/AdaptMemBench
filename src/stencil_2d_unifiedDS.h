// Contains code-gen definitions
// ADAPT_OPTS=schedule(static),schedule(dynamic),collapse(2)

#define STM_alloc double* A = (double *)malloc(sizeof(double)*(n+2)*(n+2));\
                      double* B = (double *)malloc(sizeof(double)*(n+2)*(n+2));

#define A_map(j,i) A[(j)*(n+2)+(i)]
#define B_map(j,i) B[(j)*(n+2)+(i)]

#define EPS 1e-13

#define STM_2DS_init(j,i) A_map((j),(i)) = (j) * 1.0, B_map((j),(i)) = (j) * 1.2;
#define STM_2DS_run(j,i) A_map((j),(i)) = B_map((j)-1,(i))+B_map((j)-1,(i)-1)+B_map((j)-1,(i)+1)\
                                  + B_map((j),(i))  +B_map((j),(i)-1)  +B_map((j),(i)+1)\
                                  + B_map((j)+1,(i))+B_map((j)+1,(i)-1)+B_map((j)+1,(i)+1);
#define STM_postrun() double* tmp = A;A=B;B=tmp;
#define STM_2DS_val(j) flag_err = abs(A_map(j) - ((j-1+1)*1.2 + \
                                   (j+1)*1.2 + \
                                    (j+1+1)*1.2) \
                       ) <= EPS && !flag_err ? 1 : flag_err;

#define STM_FUNC_calcn(wss) (long) sqrt((wss)/(2*sizeof(double)));
#define STM_FUNC_calcActualWSS(n) (n)*(n)*sizeof(double)*2;

bool validate_results(Configuration& configuration, Measurements& measurements, double *A, double *B){
  int wss = configuration.getInt("wss");
  int ntimes = configuration.getInt("ntimes");
  int nv = STM_FUNC_calcn(wss);
  int i, j;
  int err = 0;
  //Allocation
  double *exp_A = (double *) malloc(sizeof(double) * (nv + 2) * (nv + 2));
  double *exp_B = (double *) malloc(sizeof(double) * (nv + 2) * (nv + 2));
  //Initialization
  for (i = 0; i <= nv+1; i++){
     for (j = 0; j <= nv+1; j++){
        exp_A[i*(nv+2)+j] = i * 1.0;
        exp_B[i*(nv+2)+j] = i * 1.2;
     }
  }
  //Execution
  for (int k = 0; k < ntimes; k++) {
     for (i = 1; i <= nv; i++) {
        for (j = 1; j <= nv; j++) {
           exp_A[i*(nv+2)+j] = exp_B[(i-1)*(nv+2) +j] + exp_B[(i-1)*(nv+2)+(j-1)] + exp_B[(i-1)*(nv+2)+(j+1)] \
                         + exp_B[i*(nv+2)+j] + exp_B[i*(nv+2) + (j-1)] + exp_B[i*(nv+2) + (j+1)] \
 	                 + exp_B[(i+1)*(nv+2)+j] + exp_B[(i+1)*(nv+2)+(j-1)] + exp_B[(i+1)*(nv+2)+(j+1)];
        }
     }
     double* temp = exp_A; exp_A = exp_B; exp_B = temp;
  }
  //Validation
  for (i = 0; i <= nv+1; i++) {
    for (j = 0; j <= nv+1; j++) {
      /* printf("A[%d,%d]=%lf, ", i, j, A[i*(nv+2)+j]);
       printf("B[%d,%d]=%lf,   ", i, j, B[i*(nv+2)+j]);
       printf("exp_A[%d,%d]=%lf, ", i, j, exp_A[i*(nv+2)+j]);
       printf("exp_B[%d,%d]=%lf ", i, j, exp_B[i*(nv+2)+j]);
       printf("\n");*/
       if (ntimes % 2 == 0) {
          if ( abs(exp_A[i*(nv+2)+j] - A[i*(nv+2)+j]) >= EPS ) {
             err++;
          }
       }
       else{
          if ( abs(exp_B[i*(nv+2)+j] - B[i*(nv+2)+j]) >= EPS ) {
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

