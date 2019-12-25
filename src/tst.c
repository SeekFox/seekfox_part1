#include<stdio.h>
#include<stdlib.h>
#include<math.h>
typedef int **matrice;
typedef int *bits;


int main(void){
	for(int i=0;i<10;i++){
		if(i%2 == 0)continue;
		else printf("%d",i);

	}
return 0;
}