#ifndef PERIODICO_H
#define PERIODICO_H
#include "Defines.h"
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
#endif