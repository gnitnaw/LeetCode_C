#include <stdio.h>
#include <stdlib.h>
void swap(int* str, int i, int j) {
    int temp = str[i];
    str[i] = str[j];
    str[j] = temp;
}

void rotate(int* nums, int numsSize, int k) {
    int i;
    k %= numsSize;
    if (k==0) return;
    int *vec = (int*) malloc(sizeof(int)*k);
    for (i=1; i<=k; ++i){
	vec[k-i] = nums[numsSize-i];
    }
    for (i=numsSize-1; i>=k; --i) {
	nums[i] = nums[i-k];
    }
    for (i=k-1; i>=0; --i) {
	nums[i] = vec[i];
    }

    free(vec);
}
int main(void) {
    int a[] = {1,2,3,4,5,6,7}, i;
    rotate(a, 7, 3);
    for (i=0; i<(sizeof(a)/sizeof(int)); ++i) {
	printf("%d, ", a[i]);
    }
    return 0;
}
