#include "ColaImp.h"
#include "NodoLista.h"

#ifndef COLAIMP_CPP
#define COLAIMP_CPP

template <class T>
ostream &operator<<(ostream& out, const ColaImp<T> &c) {
	c.Imprimir(out);
	return out;
}

template <class T>
ColaImp<T>::ColaImp() {
	this->inicio = NULL;
	this->fin = NULL;
	this->cantidad = 0;
}

template <class T>
ColaImp<T>::ColaImp(const Cola<T> &c)
{
	Cola<T> * caux = c.Clon();

	while (!caux->EsVacia())
	{
		T valor = caux->Desencolar();
		this->Encolar(valor);
	}
}

template <class T>
ColaImp<T>::ColaImp(const ColaImp<T> &c) {

	cantidad = c.CantidadElementos();
	inicio = copio(c.inicio);
	NodoLista<T> * aux = inicio;
	if (aux != NULL) {
		while (aux->sig != NULL)
		{
			aux = aux->sig;
		}
	}
	fin = aux;


}

template <class T>
Cola<T> & ColaImp<T>::operator=(const Cola<T> &c) {

	if (this != &c) {
		this->Vaciar();

		Cola<T> * caux = c.Clon();

		while (!caux->EsVacia())
		{
			T valor = caux->Desencolar();
			this->Encolar(valor);
		}
	}
	return *this;
}

template <class T>
Cola<T> & ColaImp<T>::operator=(const ColaImp<T> &c) {

	if (this != &c) {
		this->Vaciar();
		Cola<T> * caux = c.Clon();

		while (!caux->EsVacia())
		{
			T valor = caux->Desencolar();
			this->Encolar(valor);
		}
	}
	return *this;
}

template <class T>
bool ColaImp<T>::operator==(const Cola<T>& c) const {
	Cola<T> * pi = Clon();
	Cola<T> * q = c.Clon();

	bool sonIguales = true;
	while (!pi->EsVacia() && !q->EsVacia() && sonIguales)
	{
		if (pi->Desencolar() != q->Desencolar())
			sonIguales = false;

	}

	bool ret = sonIguales && q->EsVacia() && pi->EsVacia();

	delete pi;
	delete q;

	return ret;
}

template <class T>
ColaImp<T>::~ColaImp() {
	this->Vaciar();
}

template<class T>
Cola<T>* ColaImp<T>::CrearVacia() const {
	return new ColaImp<T>();
}

template <class T>
void ColaImp<T>::Encolar(const T &e)
{
	NodoLista<T> * nuevo = new NodoLista<T>(e, NULL, NULL);
	if (this->fin != NULL)
	{
		this->fin->sig = nuevo;
	}
	else
	{
		this->inicio = nuevo;
	}

	this->fin = nuevo;
	cantidad++;
}

template <class T>
T& ColaImp<T>::Principio()const {
	return this->inicio->dato;
}

template <class T>
T ColaImp<T>::Desencolar() {
	T retorno = NULL;

	retorno = this->inicio->dato;
	NodoLista<T> * aux = this->inicio;
	this->inicio = this->inicio->sig;

	if (this->inicio == NULL)
	{
		this->fin = NULL;
	}
	cantidad--;

	delete aux; // si se cae, borrar
	return retorno;
}

template <class T>
void ColaImp<T>::Vaciar() {
	while (!this->EsVacia())
	{
		this->Desencolar();
	}
}

template <class T>
unsigned int ColaImp<T>::CantidadElementos()const
{
	return cantidad;
}

template <class T>
bool ColaImp<T>::EsVacia() const
{
	return this->inicio == NULL;
}

template <class T>
bool ColaImp<T>::EsLlena() const {
	return false;
}

template <class T>
Cola<T>* ColaImp<T>::Clon()const {
	return new ColaImp<T>(*this);
}

template <class T>
void ColaImp<T>::Imprimir(ostream& o)const {
	Cola<T> * aux = this->Clon();

	while (!aux->EsVacia())
	{
		o << aux->Desencolar();

		if (!aux->EsVacia()) {
			o << " ";
		}

	}

	delete aux;
}

#endif