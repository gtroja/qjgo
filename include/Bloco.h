#ifndef BLOCO_H
#define BLOCO_H
#include "Defines.h"
#include "Coordenada.h"
#include "Terreno.h"


class Bloco{
public:

	Bloco();

	//int setLimites(Bloco* lim);
	int mover(coordenada c);
	int crescer(coordenada c);
	int setPosicao(coordenada p);
	int setTamanho(coordenada t);

	//bool estaDentro(coordenada d);
	//bool estaDentro(Bloco *b);
	//bool estaFora(Bloco *b);

	Bloco colisao(Bloco* b);
	Bloco colisao(Terreno* t);

	coordenada getPosicao();
	coordenada getTamanho();

	//int verificaLimites();

protected:

	//bool estaEntre(coordenada la, coordenada lb, coordenada p);
	//bool estaDentro(Bloco b, coordenada p);

	coordenada posicao;
	coordenada tamanho;

	
};
#endif