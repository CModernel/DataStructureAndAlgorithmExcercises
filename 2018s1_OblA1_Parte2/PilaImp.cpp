#include "PilaImp.h"

#ifndef PILAIMP_CPP
#define PILAIMP_CPP

template <class T>
inline ostream &operator<<(ostream& out, const PilaImp<T> &c) {
	c.Imprimir(out);
	return out;
}

template <class T>
PilaImp<T>::PilaImp() {
	this->lista = NULL;
	this->cantElem = 0;
}

template<class T>
NodoLista<T> * copio(NodoLista<T> * l)
{
	if (l == NULL)
		return NULL;
	else
	{
		NodoLista<T> * ret = new NodoLista<T>(l->dato, copio(l->ant), copio(l->sig));
		return ret;
	}
}

template<class T>
PilaImp<T>::PilaImp(const Pila<T>& p) {
	if (this != &p)
	{
		Vaciar();
		Pila<T>* paux = p.Clon();
		Pila<T>* aux = this->CrearVacia();

		while (!paux->EsVacia())
		{
			aux->Push(paux->Top());
			paux->Pop();
		};

		while (!aux->EsVacia())
		{
			this->Push(aux->Top());
			aux->Pop();
		};

		delete paux;
		delete aux;
	}

	return *this;//a=b=c; 

}

template<class T>
PilaImp<T>::PilaImp(const PilaImp<T>& p) {
	CrearVacia();
	cantElem = p.CantidadElementos();
	lista = copio(p.lista);
}

template<class T>
Pila<T>& PilaImp<T>::operator=(const Pila<T>& p) {
	if (this != &p)
	{
		Vaciar();
		Pila<T>* paux = p.Clon();
		Pila<T>* aux = this->CrearVacia();

		while (!paux->EsVacia())
		{
			aux->Push(paux->Top());
			paux->Pop();
		};

		while (!aux->EsVacia())
		{
			this->Push(aux->Top());
			aux->Pop();
		};

		delete paux;
		delete aux;
	}

	return *this;//a=b=c; 
}

template<class T>
Pila<T>& PilaImp<T>::operator=(const PilaImp<T>& p) {

	if (this != &p)
	{
		this->lista = copio(p.lista);
		this->cantElem = p->cantElem;
	}

	return *this;
}

template<class T>
bool PilaImp<T>::operator==(const Pila<T> &p) const
{
	Pila<T> * pi = Clon();
	Pila<T> * q = p.Clon();

	bool sonIguales = true;
	while (!pi->EsVacia() && !q->EsVacia() && sonIguales)
	{
		if (pi->Top() != q->Top())
			sonIguales = false;

		pi->Pop();
		q->Pop();
	}

	bool ret = sonIguales && q->EsVacia() && pi->EsVacia();

	delete pi;
	delete q;

	return ret;
}

template<class T>
PilaImp<T>::~PilaImp() {
	this->Vaciar();
}

template<class T>
Pila<T>* PilaImp<T>::CrearVacia() const {
	return new PilaImp<T>();
}

template<class T>
void PilaImp<T>::Push(const T& e) {
	NodoLista<T>* p = new NodoLista<T>(e, NULL, NULL);
	assert(p);
	p->sig = lista;
	lista = p;
	this->cantElem++;
}

template<class T>
T& PilaImp<T>::Top() const {
	assert(!EsVacia());
	return lista->dato;
}

template<class T>
T PilaImp<T>::Pop() {
	NodoLista<T>* p = lista;
	T dato = p->dato;
	lista = lista->sig;
	this->cantElem--;
	return dato;

}

template<class T>
void PilaImp<T>::Vaciar() {
	while (!EsVacia())
	{
		Pop();
	}
	//cantidadElem = 0;
}

template<class T>
unsigned int PilaImp<T>::CantidadElementos() const {

	return this->cantElem;
}

template<class T>
bool PilaImp<T>::EsVacia() const {

	return lista == NULL;
}

template <class T>
bool PilaImp<T>::EsLlena() const {
	return false;
}

template<class T>
Pila<T>* PilaImp<T>::Clon() const {
	return new PilaImp<T>(*this);
}

template<class T>
void PilaImp<T>::Imprimir(ostream & o) const
{
	Pila<T> * aux = this->Clon();

	while (!aux->EsVacia())
	{
		o << aux->Pop();
		if (!aux->EsVacia()) {
			o << " ";
		}
	}

	delete aux;
}

#endif