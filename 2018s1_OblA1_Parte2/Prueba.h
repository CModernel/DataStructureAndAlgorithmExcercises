#ifndef PRUEBA_H
#define PRUEBA_H


#include "TipoRetorno.h"
#include "ConductorPrueba.h"
#include "ManejadorImpresionPrueba.h"
#include "ManejadorSalidaPrueba.h"

#include <iostream>
using namespace std;
#include <string.h>

class ConductorPrueba;

class Prueba  
{
public:
	Prueba(ConductorPrueba* conductor);
	virtual ~Prueba();

	virtual void correrPrueba(bool paraParseo = false);
protected:
	virtual void correrPruebaConcreta()=0;
	virtual const char* getNombre()const=0;
	ManejadorImpresionPrueba	getManejadorImpresion();
	ManejadorSalidaPrueba		getManejadorSalida();

	void ver(TipoRetorno retorno, TipoRetorno retornoEsperado, const char* comentario = "");
	void ver2(TipoRetorno retorno, TipoRetorno retornoEsperado, const char* comentario = "");
	void ver3(const char* comentario);
	void ver3(const char* comentario, double puntaje);

	EstadisticaPrueba& getEstadisticaPrueba();
private:
	EstadisticaPrueba estadisticaPrueba;
	ConductorPrueba* conductorPrueba;
};

#endif