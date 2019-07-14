#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <math.h>
#include <pthread.h>
#include "pth_msort.h"
pthread_t handles_sort[4] , handles_merge[4], handles_merge_level1[2];
#define REP 1 //
struct dataType{
	int* A ;
	int* B ;
};

typedef struct dataType dT ;

//input array
//int* values2;
unsigned int N1;
unsigned int my_index;

//sorted array
//int* sorted1;


void* last_merge_right0(void* rank){
  dT *tData = ( dT *)rank;

	unsigned int end1 = (0)?0: (N1/4 + 1);
	unsigned int end2 = (0)?N1/2: (my_index+1);
	unsigned int pnt_final = (0)?(my_index + 2 - N1/4): N1; 
	unsigned int pnt1 = (0)?N1/4: (N1/2 - 1);
	unsigned int pnt2 = (0)?(my_index): (N1 - 1);
	unsigned int len = (0)?(my_index + 2 - N1/4)/2: (5*N1/4 - my_index - 2)/2;
	unsigned int i;
	for(i = 0; i < len; i++){
		pnt_final--;
		if(pnt1 != end1 && pnt2 != end2){
			if(tData->A[pnt1] > tData->A[pnt2])
				tData->B[pnt_final] = tData->A[pnt1--];
			else
				tData->B[pnt_final] = tData->A[pnt2--];
		}	
		else if(pnt1 == end1)
			tData->B[pnt_final] = tData->A[pnt2--];
		else 
			tData->B[pnt_final] = tData->A[pnt1--];
	}

	
	return NULL;
}
void* last_merge_right1(void* rank){
  dT *tData = ( dT *)rank;

	unsigned int end1 = (1)?0: (N1/4 + 1);
	unsigned int end2 = (1)?N1/2: (my_index+1);
	unsigned int pnt_final = (1)?(my_index + 2 - N1/4): N1; 
	unsigned int pnt1 = (1)?N1/4: (N1/2 - 1);
	unsigned int pnt2 = (1)?(my_index): (N1 - 1);
	unsigned int len = (1)?(my_index + 2 - N1/4)/2: (5*N1/4 - my_index - 2)/2;
	unsigned int i;
	for(i = 0; i < len; i++){
		pnt_final--;
		if(pnt1 != end1 && pnt2 != end2){
			if(tData->A[pnt1] > tData->A[pnt2])
				tData->B[pnt_final] = tData->A[pnt1--];
			else
				tData->B[pnt_final] = tData->A[pnt2--];
		}	
		else if(pnt1 == end1)
			tData->B[pnt_final] = tData->A[pnt2--];
		else 
			tData->B[pnt_final] = tData->A[pnt1--];
	}
	
	return NULL;
}

void* last_merge_left0 (void* rank){
 dT *tData = ( dT *)rank;

	unsigned int end1 = (0)?(N1/4): (N1/2-1);
	unsigned int end2 = (0)?my_index: (N1-1);
	unsigned int pnt_final = (0)?0 :(my_index + 2 - N1/4); 
	unsigned int pnt1 = (0)?0: N1/4+1;
	unsigned int pnt2 = (0)?N1/2: (my_index+1);
	unsigned int len = (0)?(my_index + 2 - N1/4 - (my_index + 2 - N1/4)/2): (5*N1/4 - my_index - 2 - (5*N1/4 - my_index - 2)/2); 
	
	unsigned int i;
	for(i = 0; i < len; i++){
		if(pnt1 != end1 && pnt2 != end2){
			if(tData->A[pnt1] > tData->A[pnt2])
				tData->B[pnt_final] = tData->A[pnt2++];
			else
				tData->B[pnt_final] = tData->A[pnt1++];
		}	
		else if(pnt1 == end1)
			tData->B[pnt_final] = tData->A[pnt2++];
		else 
			tData->B[pnt_final] = tData->A[pnt1++];
		pnt_final++;
	}
	return NULL;
}
void* last_merge_left1 (void* rank){
 dT *tData = ( dT *)rank;

	unsigned int end1 = (1)?(N1/4): (N1/2-1);
	unsigned int end2 = (1)?my_index: (N1-1);
	unsigned int pnt_final = (1)?0 :(my_index + 2 - N1/4); 
	unsigned int pnt1 = (1)?0: N1/4+1;
	unsigned int pnt2 = (1)?N1/2: (my_index+1);
	unsigned int len = (1)?(my_index + 2 - N1/4 - (my_index + 2 - N1/4)/2): (5*N1/4 - my_index - 2 - (5*N1/4 - my_index - 2)/2); 
	
	unsigned int i;
	for(i = 0; i < len; i++){
		if(pnt1 != end1 && pnt2 != end2){
			if(tData->A[pnt1] > tData->A[pnt2])
				tData->B[pnt_final] = tData->A[pnt2++];
			else
				tData->B[pnt_final] = tData->A[pnt1++];
		}	
		else if(pnt1 == end1)
			tData->B[pnt_final] = tData->A[pnt2++];
		else 
			tData->B[pnt_final] = tData->A[pnt1++];
		pnt_final++;
	}
	return NULL;
}

unsigned int binary_search(int goal, unsigned int first, unsigned int last ,const int* values1){
		unsigned int mid = (first + last)/2;
		if(values1[mid] == goal || (last - first) == 1)
			return mid;
		else if(values1[mid] > goal)
			return binary_search(goal, first, mid,values1);
		else
			return binary_search(goal, mid , last,values1);
		
}


void* first_sort0 (void* rank){
 dT *tData = ( dT *)rank;

	
	unsigned int first = (unsigned int)((N1/4)*0);
	unsigned int last = (unsigned int)(N1/4)*(0+1);
	
	mergesort(first, last,tData->A);

	return NULL;
}
void* first_sort1 (void* rank){
 dT *tData = ( dT *)rank;

	
	unsigned int first = (unsigned int)((N1/4)*1);
	unsigned int last = (unsigned int)(N1/4)*(1+1);
	
	mergesort(first, last,tData->A);

	return NULL;
}void* first_sort2 (void* rank){
 dT *tData = ( dT *)rank;

	
	unsigned int first = (unsigned int)((N1/4)*2);
	unsigned int last = (unsigned int)(N1/4)*(2+1);
	
	mergesort(first, last,tData->A);

	return NULL;
}
void* first_sort3 (void* rank){
 dT *tData = ( dT *)rank;

	
	unsigned int first = (unsigned int)((N1/4)*3);
	unsigned int last = (unsigned int)(N1/4)*(3+1);
	
	mergesort(first, last,tData->A);

	return NULL;
}

void* secound_Merge0 (void* rank){
 dT *tData = ( dT *)rank;

	
	unsigned int first = (unsigned int)((N1/2)*0);
	unsigned int last = (unsigned int)(N1/2)*(0+1);
	
	merge(first, last,tData->A);
	
	return NULL;
}
void* secound_Merge1 (void* rank){
 dT *tData = ( dT *)rank;

	
	unsigned int first = (unsigned int)((N1/2)*1);
	unsigned int last = (unsigned int)(N1/2)*(1+1);
	
	merge(first, last,tData->A);
	
	return NULL;
}

void mergesort (unsigned int first, unsigned int last , int* values1){
	unsigned int len = last - first;
	if ( len == 1)
		return;
 	else if (len ==2 ){
		if(values1[first] > values1[first+1] ){
			int temp = values1[first+1];
			values1[first + 1] = values1[first];
			values1[first] = temp;
		}
		else{
			return;
		}
	}
	else{
		mergesort(first, first + len/2,values1);
		mergesort (first +(len/2), last,values1);
		merge (first, last,values1);
	}
	return;
}

void merge (unsigned int first, unsigned int last , int* values1){
        unsigned int my_index1 =0, my_index2 =0;
        unsigned int len = last - first;
        int* part1 = (int*) malloc(len/2*sizeof(int));
        int* part2 = (int*) malloc((len/2+1)*sizeof(int));
        unsigned int i;
        for (i =first; i< first + len/2; i++)
                part1 [i - first] = values1[i];
        for (i =first + len/2; i< last; i++)
                part2 [i - first - len/2] = values1[i];
        for (i = first; i<last; i++){
                if( my_index1 < len/2 & my_index2< (len-len/2)){
                if((part1[my_index1] > part2[my_index2]))
                        values1[i] = part2[my_index2++];
                else
                        values1[i] = part1[my_index1++];
                }
                else if( my_index1 ==len/2)
                        values1[i] = part2[my_index2++];
                else
                        values1[i] = part1[my_index1++];
        }
	free(part1);
free(part2);
        return;
}
void mergeSortParallel (const int* values, unsigned int N, int* sorted) {


	dT* tData=(dT*)malloc(sizeof(dT)) ;
	
//
		// values2 = (int*) malloc ( sizeof(int) * N );
//		 sorted1 = (int*) malloc ( sizeof(int) * N );
		N1=N;
		//for (int i=0 ; i<N ; i++)
		//	values2[i] = values[i];
tData->A = &values[0];
tData->B = &sorted[0];


//free(values);




	
		pthread_create( &handles_sort[0], NULL, first_sort0, (void*)(tData) ); 
		pthread_create( &handles_sort[1], NULL, first_sort1, (void*)(tData) ); 
		pthread_create( &handles_sort[2], NULL, first_sort2, (void*)(tData) ); 
		pthread_create( &handles_sort[3], NULL, first_sort3, (void*)(tData) ); 
		
		pthread_join( handles_sort[0], NULL); 
		pthread_join( handles_sort[1], NULL); 
		pthread_join( handles_sort[2], NULL); 
		pthread_join( handles_sort[3], NULL); 
	

		pthread_create( &handles_merge_level1[0], NULL, secound_Merge0, (void*)(tData)); 
		pthread_create( &handles_merge_level1[1], NULL, secound_Merge1, (void*)(tData)); 
		
		pthread_join( handles_merge_level1[0], NULL); 
		pthread_join( handles_merge_level1[1], NULL);
		
		my_index = binary_search(values[N/4], N/2, N,values);
		//printf("%d\n", my_index);
		
		pthread_create( &handles_merge[1], NULL, last_merge_right0 , (void*)(tData) ); 
		pthread_create( &handles_merge[1], NULL, last_merge_left0 , (void*)(tData) ); 

		pthread_create( &handles_merge[2], NULL, last_merge_right1 , (void*)(tData) ); 
		pthread_create( &handles_merge[3], NULL, last_merge_left1 , (void*)(tData) ); 
		
		pthread_join( handles_merge[0], NULL);
		pthread_join( handles_merge[1], NULL);
		pthread_join( handles_merge[2], NULL);
		pthread_join( handles_merge[3], NULL);
//for (int i=0 ; i<N ; i++)
//			sorted[i] = sorted1[i];


}




