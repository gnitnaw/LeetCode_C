#include <stdio.h>
#include <stdlib.h>

#define NDATA16B    65536
typedef struct {
    int*    sort;
    int     num;
} chain16b;

unsigned short hash_32b_to_16b(const int);
void fillChain(chain16b*, int*, int);
int* twoSum(int*, int, int);
int* findSum(chain16b*, int, int*);
int findNum(chain16b*, int, int*);

int main(void) {
    int nums[] = {2, 7, 11, 15};
    int target = 17;
    int* result = twoSum(nums, sizeof(nums)/sizeof(int), target);
    if (result) printf("%d, %d\n", result[0], result[1]);
    free(result);
    return 0;
}

int* twoSum(int* nums, int numsSize, int target){
    chain16b* dataHash16b = (chain16b*) calloc(NDATA16B, sizeof(chain16b));
    fillChain(dataHash16b, nums, numsSize);

    int* result = findSum(dataHash16b, target, nums);
    for (int i=0; i<NDATA16B; ++i){
        free(dataHash16b[i].sort);
    }
    free(dataHash16b);

    return result;
}

int* findSum(chain16b* dataHash16b, int target, int* nums){
    int* result = malloc(2*sizeof(int));
    int a32;
    for (int i=0; i<NDATA16B; ++i){
        for (int j=0; j<dataHash16b[i].num; ++j) {
            result[0] = dataHash16b[i].sort[j];
            a32 = target - nums[dataHash16b[i].sort[j]];
            if ( (result[1] = findNum(dataHash16b, a32, nums)) >=0 && result[1] != result[0]) {
                return result;
            }
        }
    }
    free(result);
    return NULL;
}

int findNum(chain16b* dataHash16b, int a32, int* nums) {
    unsigned short a16 = hash_32b_to_16b(a32);
    for (int i=0; i<dataHash16b[a16].num; ++i) {
        if (nums[dataHash16b[a16].sort[i]] == a32) return dataHash16b[a16].sort[i];
    }
    return -1;
}

void fillChain(chain16b* dataHash16b, int* num, int numSize) {
    unsigned short uval16 = 0;
    for (int i=0; i<numSize; ++i) {
        uval16 = hash_32b_to_16b(num[i]);
        if (dataHash16b[uval16].num!=0) {
            dataHash16b[uval16].sort = realloc(dataHash16b[uval16].sort, sizeof(int)*(dataHash16b[uval16].num+1));
        } else {
            dataHash16b[uval16].sort = (int*) calloc(1000,sizeof(int));
        }
        dataHash16b[uval16].sort[dataHash16b[uval16].num++] = i;
    }
}

unsigned short hash_32b_to_16b(const int v) {
    int rightBits = v & 0xffff; // Left-most 16 bits
    int leftBits = v & 0xffff0000; // Right-most 16 bits
    leftBits = leftBits >> 16; // Shift the left-most 16 bits to a 16-bit value
    return (unsigned short)( 32768 + (unsigned short)(rightBits ^ leftBits)); // XOR the left-most and right-most bits
}

