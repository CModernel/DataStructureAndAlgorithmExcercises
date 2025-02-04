
#ifndef ENTREGA2_H
#define ENTREGA2_H

#include "Definiciones.h"

#include "ColaImp.h"
#include "PilaImp.h"
#include "ListaOrd.h"
#include "TablaImp.h"
#include "MultiSet.h"
#include "ListaOrdImp.h"
#include "MultiSetImp.h"


template <class T>
ListaOrd<T>* ObtenerRepetidos(const MultiSet<T> &m)
{
	
	MultiSet<T> * copia = m.Clon();
	ListaOrd<T> * result = new ListaOrdImp<T>();

	while (!copia->EsVacia())
	{
		T e = copia->Elemento();
		if (copia->OcurrenciasElemento(e) > 1)
		{
			result->AgregarOrd(e);
		}

		copia->Borrar(e, copia->OcurrenciasElemento(e));
	}

	return result;
	


}

template <class T>
Tabla<T, int> * ContarOcurrencias(const ListaOrd<T>& l)
{

	Tabla<T, int> * retorno = new TablaImp<T, int>();
	ListaOrd<T> * aux = l.Clon();

	while (!aux->EsVacia())
	{
		T e = aux->Minimo();
		int contador = 0;

		while (aux->Existe(e))
		{
			aux->Borrar(e);
			contador++;
		}

		retorno->Insertar(e, contador);
	}
	//delete aux;

	return retorno;
}


//Observando que: AxorB = (AuB)-(AnB)
template <class T>
MultiSet<T>* Xor(const MultiSet<T> &m1, const MultiSet<T> &m2) {
	
	return (m1.Union(m2))->Diferencia(*(m1.Interseccion(m2)));
	
}

bool ParentesisBalanceados(const char *formula);

void ImprimirPorNiveles(NodoAG* a);

#endif
