#include<gmp.h>
#include<stdio.h>
#include<pthread.h>
#include<fcntl.h>
#include<signal.h>
#include<unistd.h>
#include<stdlib.h>


mpz_t g;
mpz_t p;
mpz_t A;

void* module(void *arg) {
		
	mpz_t limit; 
	mpz_t rop;
	mpz_t i;
	
	mpz_init_set_ui(limit, 1000 * (*(int *)arg + 1));
	
	mpz_init_set_ui(i, (*(int *)arg) * 1000);
	
	while(1) {
		while( mpz_cmp(limit, i) ) {
		
			mpz_add_ui(i, i, 1);
			mpz_powm(rop, g, i, p);
			
			if ( !mpz_cmp(A, rop) ) {
				printf("------ Result =  ");
				mpz_out_str(stdout, 10, i);
				printf("\n");
				exit(0);
			}
		
		}
		mpz_add_ui(i, i, 4000);
	}
	pthread_exit(NULL);
}

int main(int argc, char** argv) { 
 	
    mpz_set_str (g, argv[1], 10);
    mpz_set_str (p, argv[2], 10);
    mpz_set_str (A, argv[3], 10);
	
    int i, n;
    n = 4; 
    pthread_t pthreads[n];
    for (i = 0; i < n; ++i ) {
    	
    	pthread_create(i + pthreads, NULL, &module, &i);
    }
 	void* res   ;
    for (i = 0; i < n; i++) {
   		pthread_join(pthreads[i], res);
  	}
	mpz_clears(g, p, A);
	return 0;
}
