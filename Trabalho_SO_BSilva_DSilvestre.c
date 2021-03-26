#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <pthread.h>
#include <time.h>


void *threadFun(void *Arg)
{
	double x, y;
  double numeroPontos = *((int*)Arg); 
	double pontosCirculo = 0;
	double pi;

	for (int i = 0; i < numeroPontos; i++)
	{
		x = (double)rand() / RAND_MAX; 
		y = (double)rand() / RAND_MAX;

		double verifica = (x*x) + (y*y);
		if (verifica <= 1)
		{
			pontosCirculo++;
		}
	}

	pi = ((double)(4*pontosCirculo)/numeroPontos); 
  
  
  double* valor = malloc(sizeof(double));

	*valor = pi; 
	return (void*) valor;
 
}



int main()
{	
  int threads[4] = { 2, 4, 6, 8 };
  int pontos[4] = { 20000, 100000, 1000000, 10000000 };
	int tamanhoThreads = sizeof(threads)/sizeof(threads[0]);
	int tamanhoPontos = sizeof(pontos)/sizeof(pontos[0]);
  int pontosThread;
	double* apontapi;
	void* aux;
	
	printf("\n__.-.__.-.__.-.__.-.__.-.__.-.__.-.__.-.__.-.__.-.__.-.__.-.__.-.__.-.__.-.__.-.__\n");
	printf("\n                                Método de Monte Carlo                              \n");
	printf("\n                               Cálculo do Valor de PI                              \n");
	printf("\n-----------------------------------------------------------------------------------\n\n");
	
	
	for (int a = 0; a < tamanhoPontos; a++)
	{
		int numeroPontos = pontos[a];
		
		printf("\n__|.:|__|. |__|:.|__|::|__   Cálculo para %d pontos   __|.:|__|. |__|:.|__|::|__       \n", pontos[a]);
		for (int b = 0; b < tamanhoThreads; b++)
		{
			double total = 0; 
      double calculoTempo = 0;
			double totalTempo = 0;

			pthread_t thread_id[threads[b]]; 
			printf("\n\n--------------------------------  Tarefa com %d threads  --------------------------------\n\n\n", threads[b]); 

			for (int c = 0; c < threads[b]; c++)
			{
				pontosThread = numeroPontos / threads[b];       			
				clock_t inicio = clock();
				
				
				pthread_create(&thread_id[c], NULL, &threadFun, (void*)&pontosThread); 
				
				pthread_join(thread_id[c], &aux);
				
				apontapi = (double*)aux;

				clock_t fim = clock();
        calculoTempo = (double)(fim - inicio) * 1000 / CLOCKS_PER_SEC;

				total = total + *apontapi;
				totalTempo = totalTempo + calculoTempo;
				printf(" %dª Thread com %d pontos.  Valor de PI = %f e tempo CPU = %f miliseg.\n",  c+1, pontosThread, *apontapi, calculoTempo);
			}
			double resultado_totalTempo = (double)totalTempo/(threads[b]);
			double resultado = (double)total/(threads[b]);
      double erro = fabs((M_PI - resultado)*100/M_PI);
    
			printf("\n Valor médio de PI: %f   Tempo médio de CPU: %f miliseg.\n", resultado, resultado_totalTempo);
			printf(" Valor real de PI: %.6f    Erro de cálculo da simulação: %.3f %%\n\n", M_PI, erro);
		}
	}
	printf("\n__.-.__.-.__.-.__.-.__.-.__.-.__.-.__.-.__.-.__.-.__.-.__.-.__.-.__.-.__.-.__.-.__.-.__\n");
}