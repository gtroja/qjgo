#include <stdlib.h>
#include "../include/Bloco.h"

Bloco::Bloco(){
	posicao.x = 0;
	posicao.y = 0;
	posicao.z = 0;
	tamanho = {0,0,0};
	d("criei o bloco; a posição é( %i, %i, %i)", posicao.x, posicao.y, posicao.z)

};

Bloco Bloco::colisao(Bloco *b){
	fprintf(stderr, "%s\n","me implemente!" );

}

Bloco Bloco::colisao(Terreno *t){
	//essa funçao assume q o terreno está em (0,0,0), que vai de y=0 até getY() e q este é positivo
	//ta bem porca tbm;

	//como, a principio, terreno só vem do chão,
	//não é necessária testar todos os lado;
	Bloco intersec;
	if(t->getY(posicao.x,posicao.z)>=posicao.y){//aqui houve colisao
		intersec.crescer({0,t->getY(posicao.x,posicao.z)-posicao.y,0});
	}
	if(t->getY(posicao.x+tamanho.x,posicao.z)>=posicao.y){
		intersec.setTamanho({0,t->getY(posicao.x+tamanho.x,posicao.z)-posicao.y,0});
	}

	return intersec;

}

//int Bloco::verificaLimites(){

	// if(Limites == NULL){
	// 	return LIMITE_NAO_DEFINIDO
	// }

	// coordenada limA, limB, bloA, bloB

	// bool ok;

	// ok = 

	// return DENTRO_DO_LIMITE;
//};

// bool Bloco::estaEntre(coordenada la, coordenada lb, coordenada p){
// 	// esta função testa se 'p' esta dentro de um paralelepipedo de diagonal 'la' ,'lb';
// 	// ATENÇÂO! por enquanto assume que lb >= la em x,y,z;

// 	bool esta;

// 	esta = la.x <= p.x;
// 	esta &= la.y <= p.y;
// 	esta &= la.z <= p.z;

// 	esta &= lb.x >= p.x;
// 	esta &= lb.y >= p.y;
// 	esta &= lb.z >= p.z;

// 	return esta;
// };

//bool Bloco::estaDentro(){/*me implemente*/};

//int Bloco::setLimites(Bloco* lim){/*me implemente*/};
int Bloco::mover(coordenada c){p("nao implementado")};
int Bloco::crescer(coordenada c){p("nao implementado")};
int Bloco::setPosicao(coordenada p){
	posicao = p;
};
int Bloco::setTamanho(coordenada t){
	tamanho = t;
};

//bool Bloco::estaDentro(coordenada d){/*me implemente*/};
//bool Bloco::estaDentro(Bloco *b){/*me implemente*/};
//bool Bloco::estaFora(Bloco *b){/*me implemente*/};

coordenada Bloco::getPosicao(){
	// d("tetntarei retornar posição")
	// d("que no caso é: ( %i, %i, %i)", posicao.x, posicao.y, posicao.z)
	return posicao;
};

coordenada Bloco::getTamanho(){ return tamanho; };

//bool Bloco::estaEntre(coordenada la, coordenada lb, coordenada p){/*me implemente*/};
//bool Bloco::estaDentro(Bloco b, coordenada p){/*me implemente*/};