#include <stdio.h>
#include <stdlib.h>

void leerMatrizTxt(double**,int,int, FILE*);
void guardarMatrizTxt(double**,int,int);
double** definirMatriz(int, int);
void lecturaDatos(double**,int,int);
void imprimirMatriz(double**,int,int);
void eliminarColumna(double ** ,int,int,int,int);
void cambiarFilas(double** ,int,int,int);
int encontrarPivote(double**,int,int,int,int);
void escalonarMatriz(double**,int,int);

int main(int argc, char *argv[]) {
	
	double **p;
	int filas, columnas;
	
	FILE* fichero;
	fichero = fopen("input1.txt", "rt");
	fscanf(fichero, "%d %d", &filas, &columnas);
	columnas=(columnas+1);
	p = definirMatriz(filas, columnas);	
	leerMatrizTxt(p, filas, columnas, fichero);
	fclose(fichero);
	
	escalonarMatriz(p,filas,columnas);	
	guardarMatrizTxt(p,filas,columnas);
	free(p);
	printf("-----------+MATRIZ ESCALONADA COMPLETADA+-----------");
	return 0;
}

double** definirMatriz(int filas, int columnas){ 
	
	double** matriz;
	int i;
	matriz=(double**)malloc(filas*sizeof(double*));
	for(i=0;i<filas;i++)
	{
		matriz[i]=(double*)malloc((columnas)*sizeof(double));
	}
	return matriz;
}

void leerMatrizTxt(double** p, int filas, int columnas, FILE* fichero){
	int i,j;
	for(i=0; i<filas; i++){
		for(j=0; j<columnas; j++){
			fscanf(fichero,"%lf", &p[i][j]);
		}
	}
}

void eliminarColumna(double** p,int filas,int columnas,int filasPivote,int columnasPivote){
	double A,B,C;
	int i,j;
	double aux;
	A= p[filasPivote][columnasPivote];
	for(i=(filasPivote+1);i<filas;i++){
		B=p[i][columnasPivote];
		C=(-1)*(B/A);
		for(j=columnasPivote;j<columnas;j++){
			aux= (C* p[filasPivote][j])+p[i][j];
			p[i][j]= aux;
		}	
	}
}

void cambiarFilas( double** p,int columnas,int q,int r ){
	//q es el numero de la fila a cambiar
	//r es el numero de la segunda fila a cambiar
	double aux;
	int j;
	for (j=0;j<columnas;j++){
		aux=p[q][j];
		p[q][j]=p[r][j];
		p[r][j]=aux;
	} 
}

int encontrarPivote(double**p,int filas,int columnas, int q,int j){
	int i;
	int bandera=0;
	for (i=(q+1);i<filas;i++){
		if (p[i][j]!=0){
			cambiarFilas(p,columnas,q,i);
			bandera=1;
			break;
		}
	}
	return bandera;
}

void escalonarMatriz(double**p,int filas,int columnas){
	int i=0,j=0,bandera,contador=0;
	
	do{
		if(p[i][j]!=0){
			eliminarColumna(p,filas,columnas,i,j);
			j++;
		}
		else{
			bandera= encontrarPivote(p,filas,columnas,i,j);
			if (bandera==0){
				i=i-1;
				contador++;
				j=j+1;
			}
			else{
				eliminarColumna(p,filas,columnas,i,j);
				j++;
			}
		}
		i++;
	}while(i<(filas-1)&& j<columnas);
}

void guardarMatrizTxt(double** p, int filas, int columnas){
	int i,j;
	
	FILE* fichero2;
	fichero2 = fopen("output1.txt", "wt");
	for(i=0; i<filas; i++){
		for(j=0; j<columnas;j++){
			fprintf(fichero2,"%.2lf \t", p[i][j]);
		}
		fprintf(fichero2,"%s","\n");
	}
	fclose(fichero2);
}
