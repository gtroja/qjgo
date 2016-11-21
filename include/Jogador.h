#ifndef JOGADOR_H
#define JOGADOR_H
#include "Bloco.h"
#include "Periodico.h"
#include "Fase.h"
#include "Terreno.h"
#include "../include/Defines.h"

class Fase;
class Jogador: public Bloco, public Periodico{

public:
	Jogador();
	void atualiza();
	void setTime(unsigned int* t);
	void setTeclas(unsigned int* teclas);
	void setFase(Fase *fase);
	void inicializa();

	Dcoordenada getVelocidade();
	Dcoordenada getVelocidadeMaxima();
private:
	
	Fase *fase;
	Terreno* terreno;
	unsigned int* teclas;
	unsigned int* time;
	double tempoPassado;
	bool noChao;
	bool parado;


	Dcoordenada dposicao;
	Dcoordenada velocidade;//pixels por segundo
	Dcoordenada aceleracao;//p/s por segundo
	Dcoordenada atrito;//qnto por segundo a velocidade é reduzida
	Dcoordenada velocidadeMaxima;

	Bloco Limite;



};
#endif

/*
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

	coordenada getPosicao();
	coordenada getTamanho();

	//int verificaLimites();

protected:

	//bool estaEntre(coordenada la, coordenada lb, coordenada p);
	//bool estaDentro(Bloco b, coordenada p);

	coordenada posicao;
	coordenada tamanho;

	
};

class Periodico{
public:
	Periodico();
	virtual void atualiza();
	virtual void setTime(unsigned int* t);

protected:
	unsigned int* time;
	unsigned int criado;
	unsigned int ultimaVezAtualizado;	
};
*/