//Compilar gcc -std=c99 -Wall ppp.c qqq.c -o xxx

#include "lista.c"

int main(){

	printf("ola mundo\n");

	Graph G = GRAPHrand(6, 10);

	GRAPHshow(G);

	GRAPHdfs3(G);

//	IMPRIME_pre_post(G);

//	GRAPHdfs_rastro(G);

	ClassificaArcos(G);

	return 0;
}