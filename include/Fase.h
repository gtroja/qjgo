#ifndef FASE_H
#define FASE_H

#include "Coordenada.h"
#include "Jogador.h"
#include "Bloco.h"
#include "Terreno.h"
#include "Periodico.h"

class Jogador;
class Fase : public Bloco, public Periodico{
public:
	
	int adicionaTerreno(char* arquivo, coordenada mult, coordenada onde);//adiciona um terreno, carregando o arquivo bmp do primeiro argumento, definindo um multiplicador, e a posição do terreno
	//Terreno getTerreno(Bloco onde);
	Terreno* getTerreno();
	int setJogador(Jogador *j);
	void inicializa();
	void setInicio(coordenada c);
	void setFim(coordenada c);
	coordenada getInicio();
	coordenada getFim();
	//void setInicioFim(coordenada i, coordenada f);

private:

	Terreno terreno;
	Bloco skybox;
	
	//externos
	Jogador *jogador;
	coordenada inicio;
	coordenada fim;

};
#endif