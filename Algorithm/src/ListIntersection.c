#include "ListIntersection.h"
static int* data1;
static int* data2;

#define DISP_STAT \
	printf("Duplicate count %d\n", duplicateCount);														\
	printf("Start Time %d\n", startTime.tv_usec);															\
	printf("End Time %d\n", endTime.tv_usec);																	\
	printf("Elapsed Time %f \n", (float)(endTime.tv_sec - startTime.tv_sec + 	\
				(endTime.tv_usec - startTime.tv_usec)/1000))

void swap(int* source, int a, int b) {
	int temp = source[a];
	source[a] = source[b];
	source[b] = temp;
}

void knuthShuffle(int* inArray, int length) {
	int i;
	int current;
	for (i = length; i > 0;) {
		current = rand()%i;
		swap(inArray, current, --i);
	}
}

void threeWayQuickSort(int* inArray, int left, int right) {
	if (left >= right) return;
	int i = left, j = left, k = right;
	int pivot = inArray[left + rand()%(right - left + 1)];
	while (i <= k) {
		if (inArray[i] < pivot) { 
			swap(inArray, i, j);
			i++; j++;
		}
		else if (inArray[i] > pivot) {
			swap(inArray, i, k);
			k--;
		}
		else i++;
	}
	threeWayQuickSort(inArray, left, j - 1);
	threeWayQuickSort(inArray, k + 1, right);
}

void initData() {
	int i;
	data1 = (int*) malloc(THOUSAND*sizeof(int));
	data2 = (int*) malloc(MILLION*sizeof(int));
	for (i = 0; i < THOUSAND; i++) {
		data1[i] = i;
	}
	knuthShuffle(data1, THOUSAND);
	for (i = 0; i < MILLION; i++) {
		data2[i] = i;
	}
	knuthShuffle(data2, MILLION);
}

void intersectionAlgoOne() {
}

void intersectionAlgoTwo() {
	int i, duplicateCount = 0;
	struct timeval startTime, endTime;
	gettimeofday(&startTime, NULL);
	int* data3 = (int*) malloc((MILLION + THOUSAND)*sizeof(int));
	for (i = 0; i < THOUSAND; i++) {
		data3[i] = data1[i];
	}
	for (; i < MILLION + THOUSAND; i++) {
		data3[i] = data2[i - THOUSAND];
	}
	threeWayQuickSort(data3, 0, MILLION + THOUSAND - 1);

	for (i = 0; i < (MILLION + THOUSAND) - 1; i++)
		if (data3[i] == data3[i+1]) duplicateCount++; i++;

	gettimeofday(&endTime, NULL);
	DISP_STAT;
}

int main() {
	srand(time(NULL));
	initData();
	intersectionAlgoOne();
	intersectionAlgoTwo();
	return 0;
}
