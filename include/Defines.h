#ifndef DEFINES_H
#define DEFINES_H
#include <stdio.h>

#define DEBUG 0

#define nroBotoes 8

#define	xmais 	0
#define	xmenos	1
#define	ymais	2
#define	ymenos	3
#define	zmais	4
#define	zmenos	5
#define	funca	6
#define	funcb	7

#define LIMITE_NAO_DEFINIDO 2
#define ULTRAPASSA_LIMITE	1
#define DENTRO_DO_LIMITE	0

//um print pra debug
#define d(...) do { if (DEBUG) { fprintf(stderr,">>"); fprintf(stderr,__VA_ARGS__); fprintf(stderr,"\n");} } while (0);
#define p(...) do { if (DEBUG) { fprintf(stderr,">>"); fprintf(stderr,__VA_ARGS__); fprintf(stderr,"\n"); getchar();} } while (0);
#endif