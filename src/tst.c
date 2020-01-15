#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<string.h>



int main(void){
int j= 0,i=0;
for(i=0;i<5;i++){
	for(j=0;j<5;j++){
		printf("is ok \n");
		if(j == 3)break;
	}
	if(j==3)break;
	printf("%d\n",i);
}
printf("test reussi\n");
	return 0;
}