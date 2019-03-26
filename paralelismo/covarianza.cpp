/**
   Implementación con openmp de la covarianza
   La fórmula que se procede a implementar es 
cov(X,Y)= 1/n (sum_{i=1}^n x_iy_i ) - x_media y_media

En el main puede encontrar un caso de prueba, introduzca por argumentos el tamaño de los vectores a los que calcular la covarianza.

Recordatorio: 
- Para compilar código g++ -O2 -fopenmp -o covarianza.out covarianza.cpp
- Número de hilos (desde el shell):
- export OMP_NUM_THREADS="numero"
ejemplo: OMP_NUM_THREADS=4

Blanca Cano Camarero
Granada 26/III/19 
 */

#include <iostream>
#include <omp.h>

//generar números aleatorios
#include <stdlib.h>
#include <time.h>

using namespace std;

//--------- funciones auxiliares --------

//media de los elementos de un vector
double media ( int* v, int len);

/**
   Cálculo de la covarianaza: 
cov(X,Y)= 1/len (sum_{i=1}^len v_iu_i ) - v_media u_media
 */
double covarianza ( int* v, int*u, int len);

 


//Ejemplo de uso 
int main(int argc, char*argv[])
{

  // --- inicialización vectores --- 
  //tamaño de los vectores a los que calcularles la covarianza
  int len; 
  if ( argc > 1 )
    len = atoi( argv[1]);
  else
    return 1; 
        
  // creación de los vectores
  int *X = new int [len];
  int *Y = new int [len];

  //completamos los vectores, en este caso de manera aletoria
  srand(time(NULL)); 
  for( int i=0; i< len; i++)
    {
      X[i] = rand()%len;
      Y[i] = rand()%len;
    }
  
  //---- covarianza ---
  cout << "La covarianza es: " << covarianza(X,Y,len) <<endl; 
 
  
  //liberamos memoria
  delete [] X;
  delete [] Y; 
}

double media ( int * v, int len)
{
  double media=0;

  #pragma omp parallel for
  for ( int i=0; i<len; i++)
    media += v[i];

  return media/len; 
}


double covarianza ( int* v, int*u, int len)
{
   double sum=0;

  #pragma omp parallel for
  for ( int i=0; i<len; i++)
    {
      sum += v[i]*u[i];
    }
  
  return sum/len - media (v,len)*media(u,len); 
}
