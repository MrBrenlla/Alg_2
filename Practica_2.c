#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <time.h>
#include <math.h>

#define MAX_ITER 32001
#define MIN_ITER 250
#define K 1000


void ord_ins(int v[], int n );
void ord_shell(int v[],int n);
void inicializar_semilla();
void aleatorio(int v [], int n);
void ascendente(int v [], int n);
void descendente(int v [], int n);
int comOrd(int v[],int n);
void ej1(int n);
void tempos(int n, void (*fun)(int v [], int n),void (*ord)(int v[], int n),
int cotainf, int cotaax, int cotasup);
void ordShell();
void ordIns();

/*
--------------------------------------------------------------------------------
*/
double microsegundos() { /* obtiene la hora del sistema en microsegundos */
struct timeval t;
if (gettimeofday(&t, NULL) < 0 )
return 0.0;
return (t.tv_usec + t.tv_sec * 1000000.0);
}
/*
--------------------------------------------------------------------------------
*/
void ord_ins(int v[], int n ){
  int x , j , i;
  for(i = 0 ;i<n; i++){
    x = v[i] ;
    j = i-1 ;
    while( j > -1 && v[j] > x ){
      v[j+1] = v[j] ;
      j = j-1;
    }
    v[j+1] = x;
  }
}
/*
--------------------------------------------------------------------------------
*/
void ord_shell(int v[],int n){
  int incremento = n , seguir, tmp , j, i;
  do{
    incremento = incremento / 2;
    for(i = incremento; i<n;i++){
      tmp = v[i];
      j = i;
      seguir = 1;
      while (j-incremento > -1 && seguir==1){
        if (tmp < v[j-incremento]){
          v[j] = v[j-incremento];
          j = j-incremento;
        }
        else seguir = 0;
    }
    v[j] = tmp;
  }
}while( incremento > 1);
}
/*
--------------------------------------------------------------------------------
*/
void inicializar_semilla() {
  srand(time(NULL));
}
/*
--------------------------------------------------------------------------------
*/
void aleatorio(int v [], int n) {
  /* se generan nomeros pseudoaleatorio entre -n y +n */
  int i, m=2*n+1;
  for (i=0; i < n; i++)
  v[i] = (rand() % m) - n;
}
/*
--------------------------------------------------------------------------------
*/
void ascendente(int v [], int n) {
  int i;
  for (i=0; i < n; i++)
  v[i] = i;
}
/*
--------------------------------------------------------------------------------
*/
void descendente(int v [], int n) {
  int i;
  for (i=0; i < n; i++)
  v[i] = n-i;
}
/*
--------------------------------------------------------------------------------
*/
int comOrd(int v[],int n){
  int i;
  for(i = 1 ; i<n ; i++) if(v[i]<v[i-1]) return 0;
  return 1;
}
/*
--------------------------------------------------------------------------------
*/
void ej1(int n){
  int i;
  int v[n];
  aleatorio(v,n);
  printf("Inicializacion aleatoria\n");
  for(i = 0; i<n;i++) printf("%d ",v[i] );
  printf("\n");
  printf("ordenado? %d\n",comOrd(v,n));
  printf("Ordenacion por Insercion\n");
  ord_ins(v,n);
  for(i = 0; i<n;i++) printf("%d ",v[i] );
  printf("\n");
  printf("ordenado? %d\n",comOrd(v,n));
  aleatorio(v,n);
  printf("Inicializacion aleatoria\n");
  for(i = 0; i<n;i++) printf("%d ",v[i] );
  printf("\n");
  printf("ordenado? %d\n",comOrd(v,n));
    printf("Ordenacion por Shell\n");
  ord_shell(v,n);
  for(i = 0; i<n;i++) printf("%d ",v[i] );
  printf("\n");
  printf("ordenado? %d\n",comOrd(v,n));
}
/*
--------------------------------------------------------------------------------
*/
void tempos(int n, void (*fun)(int v [], int n),void (*ord)(int v[], int n),
int cotainf, int cotaax, int cotasup){
  double ta, tb;
  int v[n] , i;
  char aviso=' ';
  double total1 ;
  ord(v,n);
  ta = microsegundos();
  fun(v,n);
  tb = microsegundos();
  total1 = tb-ta;
  if (total1<500){
    aviso='*';
    ta = microsegundos();
    for ( i =0 ; i<K ; i++){
      ord(v,n);
      fun(v,n);
    }
    tb = microsegundos();
    total1 = tb-ta;
    ta = microsegundos();
    for ( i =0 ; i<K ; i++){
      ord(v,n);
    }
    tb = microsegundos();
    total1 = (total1-(tb-ta))/K;
  }

  printf("%15i%c %15.3f %15.6f %15.6f %15.6f \n", n , aviso , total1,
  total1/cotainf, total1/cotaax,total1/cotasup);
}
/*
--------------------------------------------------------------------------------
*/
void ordShell(){
  int h;
  printf("\nOrdenacion de shell de un vector ordenado\n\n");
  printf("%16s %15s %15s %15s %15s\n", "n","t(n)", "t(n)/n", "t(n)/n^1.135",
   "t(n)/n^1.3");
  for ( h = MIN_ITER; h<MAX_ITER ; h = h*2){
     tempos(h,ord_shell,ascendente,h,pow(h,1.145),pow(h,1.3));
   }
   printf("\nOrdenacion de shell de un vector inversamente ordenado\n\n");
   printf("%16s %15s %15s %15s %15s\n", "n","t(n)", "t(n)/n", "t(n)/n^1.125",
    "t(n)/n^1.3");
   for ( h = MIN_ITER; h<MAX_ITER ; h = h*2){
      tempos(h,ord_shell,descendente,h,pow(h,1.125),pow(h,1.3));
    }
    printf("\nOrdenacion de shell de un vector aleatorio\n\n");
    printf("%16s %15s %15s %15s %15s\n", "n","t(n)","t(n)/n", "t(n)/n^1.2",
     "t(n)/n^1.4");
    for ( h = MIN_ITER; h<MAX_ITER ; h = h*2){
       tempos(h,ord_shell,aleatorio,pow(h,1),pow(h,1.2),pow(h,1.4));
     }
}
/*
--------------------------------------------------------------------------------
*/
void ordIns(){
  int h;
  printf("\nOrdenacion por insercion de un vector ordenado\n\n");
  printf("%16s %15s %15s %15s %15s\n", "n","t(n)", "t(n)/n^0.8", "t(n)/n",
   "t(n)/n^1.2");
  for ( h = MIN_ITER; h<MAX_ITER ; h = h*2){
     tempos(h,ord_ins,ascendente,pow(h,0.8),h,pow(h,1.1));
   }
   printf("\nOrdenacion por insercion de un vector inversamente ordenado\n\n");
   printf("%16s %15s %15s %15s %15s\n", "n","t(n)", "t(n)/n^1.8", "t(n)/n^2",
    "t(n)/n^2.2");
   for ( h = MIN_ITER; h<MAX_ITER ; h = h*2){
      tempos(h,ord_ins,descendente,pow(h,1.8),pow(h,2),pow(h,2.2));
    }
    printf("\nOrdenacion por insercion de un vector aleatorio\n\n");
    printf("%16s %15s %15s %15s %15s\n","n","t(n)","t(n)/n^1.8","t(n)/n^1.98",
     "t(n)/n^2.2");
    for ( h = MIN_ITER; h<MAX_ITER ; h = h*2){
       tempos(h,ord_ins,aleatorio,pow(h,1.8),pow(h,1.98),pow(h,2.2));
     }
}
/*
--------------------------------------------------------------------------------
*/
int main(){
  int n = 10;
  inicializar_semilla();
  ej1(n);
  ordIns();
  ordShell();
}
