#include "Entrega1.h"

#ifndef ENTREGA1_CPP
#define ENTREGA1_CPP

void auxEnlistar(NodoAB * nodo, ListaOrd<int> *& l)
{
	if (nodo != NULL)
	{
		auxEnlistar(nodo->izq, l);
		l->AgregarOrd(nodo->dato);
		auxEnlistar(nodo->der, l);
	}
}

ListaOrd<int>* Enlistar(NodoAB* a)
{
	ListaOrd<int> * nuevaLista = new ListaOrdImp<int>();

	auxEnlistar(a, nuevaLista);

	return nuevaLista;
}

unsigned int CantidadDeHojas(NodoAB* a)
{
	Cola<NodoAB *> * aux = new ColaImp<NodoAB *>();
	int contador = 0;
	aux->Encolar(a);
	while (!aux->EsVacia())
	{
		NodoAB * arb = aux->Desencolar();
		if ((arb->izq == NULL) && (arb->der == NULL))
		{
			contador++;
		}
		else
		{
			if (arb->izq != NULL)
				aux->Encolar(arb->izq);
			if (arb->der != NULL)
				aux->Encolar(arb->der);
		}
	}
	return contador++;

	return 0;
}

void ImprimirPorNiveles(NodoAB *a)
{
	if (a == NULL)
		return;
	Cola<NodoAB*>* c = new ColaImp<NodoAB*>();
	Pila<NodoAB*>* p = new PilaImp<NodoAB*>();
	c->Encolar(a);
	while (!c->EsVacia())
	{
		NodoAB* tope = c->Principio();
		if (tope != NULL)
		{
			p->Push(c->Desencolar());
			c->Encolar(tope->izq);
			c->Encolar(tope->der);
		}
		else
			c->Desencolar();
	}
	while (!p->EsVacia())
	{
		cout << p->Pop()->dato << " ";
	}
}

#endif