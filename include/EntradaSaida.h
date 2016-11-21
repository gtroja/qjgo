#ifndef ENTRADASAIDA_H
#define ENTRADASAIDA_H
#include <SDL2/SDL.h>
#include "Bloco.h"
#include "Jogador.h"
#include "Fase.h"
#include "Periodico.h"
#include "Defines.h"


class EntradaSaida : public Bloco, public Periodico{
public:
	EntradaSaida();
	int inicializa();
	int setSeguirBloco(Bloco *b);
	int setBordasSeguido(Bloco b);
	int setTeclas(unsigned int *teclas);
	int setFase(Fase *fase);
	int setJogador(Jogador *jogador);
	int renderiza();
	void atualizaCamera();
	void setTime(unsigned int* t);

	void getEntradas();

private:

	int tempoPassado;

	Bloco *seguindo;
	Bloco camera;
	coordenada perspectiva;//a diferença de tamanho entre o plano mais distante da camera e o mais proximo; simula uma perspectiva
	//Bloco bordas;

	//externos
	unsigned int *teclas;
	Jogador     *jogador;
	Fase        *fase;


	//Janela
	SDL_Window *janela;
	char		janelaNome[100];
	int	  		janelaLargura;
	int   		janelaAltura;


	//Render
	SDL_Renderer* render;

	//coisas do sdl
	SDL_Event e;
	const Uint8* currentKeyStates;


	SDL_Texture* textura;
	SDL_Texture* texturaTela;
	SDL_Rect 	quadrado;
	SDL_Rect	rectTela;
	
};
#endif