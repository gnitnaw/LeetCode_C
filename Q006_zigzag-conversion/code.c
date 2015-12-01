#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* convert(char* s, int numRows) {
    int i, j, k=0, l=0;
    size_t len = strlen(s);
    char *a = (char*) malloc((len+1)*sizeof(char));

    if (numRows >= len || numRows==1) {
	strcpy(a, s);
	return a;
    }    

    for (i=0; i<numRows; ++i) {
	j = i;
	l = 0;
	while (j<len) {
	    a[k++] = s[j];
	    if (i==0 || i == numRows-1) j += 2*(numRows-1);
	    else {
		if (!(l&1)) j+= 2*(numRows-1-i);
		else j+= 2*i;
	    }
	    l++;
	}
    }
    a[len] = '\0';
    return a;
}

int main(void) {
    char s[] = "PAYPALISHIRING";
    printf("%s\n", convert(s, 3));
    return 0;
}

