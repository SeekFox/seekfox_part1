#ifndef ELEMENT_H
#define ELEMENT_H
typedef struct ELEMENT{
	double val;
}ELEMENT;

void affiche_ELEMENT(ELEMENT display);
ELEMENT saisir_ELEMENT();
ELEMENT affect_ELEMENT(double value);
int compare_ELEMENT(ELEMENT a, ELEMENT b);

#endif
