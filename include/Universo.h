#ifndef UNIVERSO_H
#define UNIVERSO_H
#include "Defines.h"
#include "Jogador.h"
#include "Fase.h"
#include "EntradaSaida.h"

#define DEBUG 1

/*
Universo é a classe principal do programa;
nele são instanciadas as classe que controlam 
a fase, o jogador, a Entrada(teclado) e Saida(tela),
o jogo (enquanto este está rodando), como tambem editor
de fases e a interface de menus.

as classes se comunicam; o jogador está numa fase, e ele
só pode se mover onde é possivel se mover; a fase responde
ao jogador tambem;
*/


//enum estados = {jogando, editor, pausado, menu};

class Universo{
    
    public:
        Universo();
    	~Universo();
    	void ligaTudo();//função que conecta os objetos e inicializa eles
        void loop();//loop principal do programa
        void dummy();//gera dados de configuração hardcoded
        //void leArquivo();
    private:

    	//jogo
    	//editor
    	//menu
        Jogador     jogador;
        Fase        fase;
        EntradaSaida    io;

        unsigned int time;
        unsigned int *teclas;



        //implementar estados/flags


        //arquivos de configuração

};

#endif // UNIVERSO_H
