#include"../gmp-6.0.0/gmp.h"
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
		
	int limit = 1000 * (*(int *)arg + 1);
	int i = (*(int *)arg) * 1000;
	mpz_t rop;
	mpz_realloc2(rop, 1000);
	while(1) {
		while(i <= limit) {
			
			mpz_powm_ui(rop, g, i, p);
			
			if ( !mpz_cmp(A, rop) ) {
				printf("------ Result = %d ------\n", i);
				mpz_clears(g, p, A);
				exit(0);
			}
			i++;
		}
		limit = limit + 4000;
	}
	pthread_exit(NULL);
}

int main(int argc, char** argv) { 
 	
    mpz_init_set_str (g, argv[1], 10);
    mpz_init_set_str (p, argv[2], 10);
    mpz_init_set_str (A, argv[3], 10);
	
    int i, n;
    n = 4; 
    pthread_t pthreads[n];
    for (i = 0; i < n; ++i ) {
    	
    	pthread_create(pthreads + i, NULL, &module, &i);
    }
    void* value;
    for (i = 0; i < n; i++) {
   		pthread_join(pthreads[i] , value);
  	}
		
	return 0;
}
