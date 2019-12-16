#include<stdio.h>
#include<stdlib.h>
typedef int *bits;
bits quantifier(int composante_rouge,int composante_vert,int composante_bleue,int n);

bits quantifier(int composante_rouge,int composante_vert,int composante_bleue,int n){
	int dim = n*3;
	bits b = malloc(dim*sizeof(int));
	if(b == NULL)exit(1);
	b[dim] =(int){0};
	int rouge[8],vert[8],bleue[8];
	int i=0;
	while(composante_rouge > 0 || composante_vert > 0 || composante_bleue > 0){
		rouge[i] = composante_rouge%2;
		composante_rouge = composante_rouge/2;
		vert[i] = composante_vert%2;
		composante_vert = composante_vert/2;
		bleue[i] = composante_bleue%2;
		composante_bleue = composante_bleue/2;
		i++;}
	if(dim == 6){
		b[0] = rouge[7];
		b[1] = rouge[6];
		b[2] = vert[7];
		b[3] = vert[6];
		b[4] = bleue[7];
		b[5] = bleue[6];
		}
	else if(dim == 9){
			/*for(i=0;i<9;i++){
				if(i<3)b[i] = rouge[7-i];
				else if(i<5)for(int j=7;j>4;j--)b[i] = vert[j];
				else for(int j=7;j>4;j--)b[3] = vert[7];
			*/	
		b[0] = rouge[7];
		b[1] = rouge[6];
		b[2] = rouge[5];
		b[3] = vert[7];
		b[4] = vert[6];
		b[5] = vert[5];
		b[6] = bleue[7];
		b[7] = bleue[6];
		b[8] = bleue[5];
		}
	return b;
}

int main(void){
	/*int n,cr,cv,cb;
	
	printf("sasir le nombre de bits sur quoi quantifier\n");
	scanf("%d",&n);
	
	printf("saisir les composantes\n");
	scanf("%d%d%d",&cr,&cb,&cv);
	
	bits b = malloc(n*3*sizeof(int));
	if(b == NULL)exit(EXIT_FAILURE);
	b = quantifier(cr,cb,cv,n);
	for(int i=0;i<n*3;i++)printf("%d ",b[i]);
	printf("\n");
	*/
	int Longueur,Hauteur,NombreComposantes,Dimension,i=3;
	char nomfichier[10];
	
	printf("saisir le nom du fichier\n");
	scanf("%10s",nomfichier);
	
	FILE *entree;
	entree = fopen(nomfichier,"r");	
	
	fscanf(entree,"%d%d%d",&Longueur,&Hauteur,&NombreComposantes);
	
	int *ComposantesRouges,*ComposantesVertes,*ComposantesBleues;
	ComposantesRouges = malloc(Longueur*sizeof(int));
	ComposantesVertes = malloc(Longueur*sizeof(int));
	ComposantesBleues = malloc(Longueur*sizeof(int));
	if(ComposantesRouges == NULL || ComposantesVertes == NULL || ComposantesBleues == NULL)exit(EXIT_FAILURE));
	Dimension = Longueur * Hauteur;
	while(feof(entree) == 0){
		if(i<=Dimension)fscanf(entree,"%d",&ComposantesRouges[i]);
		else if(i<=2*Dimension)fscanf(entree,"%d",&ComposantesVertes[i]);
		else fscanf(entree,"%d",&ComposantesBleues[i]);
		i++;
	}
	fclose(entree);
	printf("%d %d %d\n",Longueur,Hauteur,NombreComposantes);
	
	printf("%d %d %d \n",ComposantesRouges[0],ComposantesVertes[0],ComposantesBleues[0]);
	return 0;
}








	
