#ifndef ENTREGA1_H
#define ENTREGA1_H

#include "Definiciones.h"

#include "ListaOrd.h"
#include "ListaPos.h"
#include "Pila.h"
#include "Cola.h"

#include "ListaOrdImp.h"
#include "ListaPosImp.h"
#include "PilaImp.h"
#include "ColaImp.h"

// Ver Entrega1.txt para la documentación de estas funciones



template <class T>
ListaOrd<T> *UnionListaOrd(const ListaOrd<T> &l1, const ListaOrd<T> &l2) {
	ListaOrd<T> *ret = new ListaOrdImp<T>();
	Iterador<T> aux1 = l1.GetIterador();
	Iterador<T> aux2 = l2.GetIterador();

	while (!aux1.EsFin()) {

		T dato = aux1.Elemento();
		ret->AgregarOrd(dato);
		aux1.Resto();
	}

	while (!aux2.EsFin()) {
		T dato = aux2.Elemento();
		ret->AgregarOrd(dato);
		aux2.Resto();
	}
	return ret;
}

ListaOrd<int>* Enlistar(NodoAB* a);


template <class T>
bool EstaContenida(const Pila<T> &p1, const Pila<T> &p2)
{
	Pila<T> * aux1 = p1.Clon();
	Pila<T> * aux2 = p2.Clon();
	Pila<T> * aux3 = new PilaImp<T>();

	while (!aux1->EsVacia() && !aux2->EsVacia())
	{
		T elem = aux2->Pop();
		if (aux1->Top() != elem)
		{
			aux3->Push(elem);
		}
		else
		{
			aux1->Pop();
			while (!aux3->EsVacia())
			{
				T ele = aux3->Pop();
				aux2->Push(ele);
			}
		}
	}

	return aux1->EsVacia();
}
unsigned int CantidadDeHojas(NodoAB* a);

void ImprimirPorNiveles(NodoAB *a);

#endif