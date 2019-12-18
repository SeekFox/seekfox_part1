#include<stdio.h>
#include<stdlib.h>
typedef int *bits;
typedef int **matrice;

int quantifier(int composante_rouge,int composante_vert,int composante_bleue,int n);

int quantifier(int composante_rouge,int composante_vert,int composante_bleue,int n){
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
		
	return ;
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
	int NbLignes,NbColonnes,NombreComposantes;
	char nomfichier[10];
	
	printf("saisir le nom du fichier\n");
	scanf("%10s",nomfichier);
	
	FILE *entree;
	entree = fopen(nomfichier,"r");	
	
	fscanf(entree,"%d%d%d",&NbLignes,&NbColonnes,&NombreComposantes);
	
	matrice Rouge,Vert,Bleue;
	
	Rouge = malloc(NbLignes*sizeof(int));
	Verte = malloc(NbLignes*sizeof(int));
	Bleue = malloc(NbLignes*sizeof(int));
	if(Rouge == NULL || Verte == NULL || Bleue == NULL)exit(EXIT_FAILURE));
	
	for(int i=0;i<NbLignes;i++){
		Rouge[i] = malloc(NbColonnes*sizeof(int));
		Verte[i] = malloc(NbColonnes*sizeof(int));
		Blueue[i] = malloc(NbColonnes*sizeof(int));
		if(Rouge[i] == NULL || Verte[i] == NULL || Bleue[i] == NULL)exit(EXIT_FAILURE));
		}
		
	for(int i=0;i<NbLignes;i++){
		for(int j=0;j<NbColonnes;j++){
			fscanf(entree,"%d",&Rouges[i][j]); 		
		}
	}
		
	for(int i=0;i<NbLignes;i++){
		for(int j=0;j<NbColonnes;j++){
			fscanf(entree,"%d",&Verte[i][j]); 		
		}
	}
		
	for(int i=0;i<NbLignes;i++){
		for(int j=0;j<NbColonnes;j++){
			fscanf(entree,"%d",&Bleue[i][j]); 		
		}
	}
	
	for(int i=0;i<Nblignes;i++){
		for(int j=0;j<NbColonnes;j++){
			
		}
	}
	int Histogramme[64]={0};
	
	fclose(entree);
	
	printf("%d %d %d\n",NbLignes,NbColonnes,NombreComposantes);
	
	printf("%d %d %d \n",ComposantesRouges[0],ComposantesVertes[0],ComposantesBleues[0]);
	return 0;
}








	
