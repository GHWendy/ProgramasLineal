#include <stdio.h>
#include <stdlib.h>

void leerMatrizTxt(double**,int,int, FILE*);
void guardarMatrizTxt(double**,int,int,int, FILE*);
double** definirMatriz(int , int);
void eliminarColumna(double ** ,int,int,int,int);
void cambiarFilas(double** ,int,int,int);
int encontrarPivote(double**,int,int,int,int);
void escalonarMatriz(double**,int,int);

int main(int argc, char *argv[]) {
	double **p;
	int nMatriz, filas, columnas,contador=1;
	
	FILE* fichero;
	FILE* fichero2;
	fichero = fopen("input2.txt", "rt");
	fichero2 = fopen("output2.txt", "wt");
	fscanf(fichero, "%d", &nMatriz);
	do{
		fscanf(fichero, "%d %d",&filas,&columnas);
		columnas=columnas+1;
		p=definirMatriz(filas,columnas);
		leerMatrizTxt(p, filas,columnas,fichero);
		escalonarMatriz(p,filas,columnas);
		guardarMatrizTxt(p,filas,columnas,contador,fichero2);
		
		for (int m=0; m<filas; m++)
			free (p[m]);
		free(p);
		
		contador++;
	} while(contador<=nMatriz);
	fclose(fichero);
	fclose(fichero2);
	
	printf("------+OPERACION GAUSS JORDAN COMPLETADA+------");
	return 0;
}

double** definirMatriz(int filas, int columnas){ 
	
	double** matriz;
	int i;
	matriz=(double**)malloc(filas*sizeof(double));
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


void eliminarColumna(double** p,int filas,int columnas,int filasPivote,int columnasPivote){
	double A,B;
	int i,j,k;
	double aux;
	A= p[filasPivote][columnasPivote];
	for(k=columnasPivote;k<columnas;k++){
		p[filasPivote][k]=(p[filasPivote][k]/A);
	}
	for (i=0;i<filas;i++){
		if(i!=filasPivote){
			B=(-1)*(p[i][columnasPivote]);
			for(j=columnasPivote;j<columnas;j++){
				aux= (B*p[filasPivote][j])+p[i][j];
				p[i][j]=aux;
			}
		}
	}
}

void escalonarMatriz(double**p,int filas,int columnas){
	int i=0,j=0,bandera;
	
	do{
		if(p[i][j]!=0){
			eliminarColumna(p,filas,columnas,i,j);
			j++;
		}
		else{
			bandera= encontrarPivote(p,filas,columnas,i,j);
			if (bandera==0){ 
				j++;			
			}
			else{
				eliminarColumna(p,filas,columnas,i,j);
				j++;
			}
		}
		i++;
	}while(i<(filas)&& j<columnas);
}

void guardarMatrizTxt(double** p, int filas, int columnas,int nMatriz, FILE* fichero2){
	int i,j;
	
	fprintf(fichero2,"%s %d\n","Matriz ",nMatriz);
	for(i=0; i<filas; i++){
		for(j=0; j<columnas;j++){
			fprintf(fichero2,"%.2lf \t", p[i][j]);
		}
		fprintf(fichero2,"%s","\n");
	}
	fprintf(fichero2,"%s","\n");
}
