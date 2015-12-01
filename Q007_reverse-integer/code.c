#include <stdio.h>
#include <limits.h>

int reverse(int x) {
    int y = 0, max = INT_MAX/10+1, min = INT_MIN/10-1, z;
    while(x!=0) {
        if (y< max && y > min) y *= 10;
        else return 0;
        z = x%10;
        if ((z>=0 && y<INT_MAX-z) || (z<0 && y>INT_MIN-z)) y+=z;
        else return 0;
        x /=10;
    }
    return y;
}

int main(void) {
    int x = 1463847412;
    printf("%d", reverse(x));
    return 0;
}

