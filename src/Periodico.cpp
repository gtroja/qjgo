#include <stdlib.h>
#include "../include/Periodico.h"

Periodico::Periodico(){
	time = NULL;
	criado = 0;
	ultimaVezAtualizado = 0;
}

 void Periodico::atualiza(){
	if(time != NULL)
	ultimaVezAtualizado = *time;
}

 void Periodico::setTime(unsigned int* t){
	time = t;
	criado = *time;
	ultimaVezAtualizado = *time;
 	d("setei um time %i",*time);
}
