#include "ListaPosImp.h"

#ifndef LISTAPOSIMP_CPP
#define LISTAPOSIMP_CPP

template <class T>
inline ostream & operator<<(ostream &out, const ListaPosImp<T> &l)
{
	l.Imprimir(out);
	return out;
}

template <class T>
ListaPos<T>* ListaPosImp<T>::CrearVacia() const
{
	return new ListaPosImp<T>();
}

template <class T>
ListaPosImp<T>::ListaPosImp()
{
	this->lista = NULL;
	this->largo = 0;
}

template <class T>
ListaPosImp<T>::ListaPosImp(const ListaPos<T> &l)
{
	ListaPos<T>* copia = l.Clon();
	this->largo = l.CantidadElementos();
	this->lista = new T[largo];
	for (int i = 0; i < largo; i++)
		this->lista[i] = copia->ElementoPos(i);
	delete copia;
}

template <class T>
T* copiarLista(const ListaPosImp<T> &l) {
	T* ret = new T[l.CantidadElementos()];
	for (int i = 0; i < l.CantidadElementos(); i++)
		ret[i] = l.ElementoPos(i);
	return ret;
}

template <class T>
ListaPosImp<T>::ListaPosImp(const ListaPosImp<T> &l)
{
	this->lista = copiarLista(l);
	this->largo = l.CantidadElementos();
}

template <class T>
ListaPos<T>& ListaPosImp<T>::operator=(const ListaPos<T> &l)
{
	this->largo = l.CantidadElementos();
	this->lista = new T[this->largo];
	for (int i = 0; i < this->largo; i++)
		this->lista[i] = l.ElementoPos(i);
	return *this;
}

template <class T>
ListaPos<T>& ListaPosImp<T>::operator=(const ListaPosImp<T> &l)
{
	if (this != &l) {
		this->largo = l.CantidadElementos();
		this->lista = new T[this->largo];
		for (int i = 0; i < this->largo; i++)
			this->largo[i] = l.ElementoPos(i);
	}
	return *this;
}

template <class T>
ListaPosImp<T>::~ListaPosImp()
{
	this->Vaciar();
}

template <class T>
void ListaPosImp<T>::AgregarPpio(const T &e)
{
	this->largo++;
	T* ret = new T[this->largo];
	ret[0] = e;
	for (int i = 1; i < this->largo; i++)
		ret[i] = this->lista[i - 1];
	this->lista = ret;
}

template <class T>
void ListaPosImp<T>::AgregarFin(const T &e)
{
	T* ret = new T[this->largo + 1];
	for (int i = 0; i < this->largo; i++)
		ret[i] = this->lista[i];
	ret[this->largo] = e;
	this->largo++;
	this->lista = ret;
}

template <class T>
void ListaPosImp<T>::AgregarPos(const T &e, unsigned int pos)
{
	this->largo++;
	T* ret = new T[this->largo];
	for (int i = 0; i < (int)pos; i++)
		ret[i] = this->lista[i];
	ret[pos] = e;
	for (int i = pos + 1; i < this->largo; i++)
		ret[i] = this->lista[i - 1];
	this->lista = ret;
}

template <class T>
void ListaPosImp<T>::BorrarPpio()
{
	T* ret = new T[this->largo - 1];
	for (int i = 1; i < this->largo; i++)
		ret[i - 1] = this->lista[i];
	this->lista = ret;
	this->largo--;
}

template <class T>
void ListaPosImp<T>::BorrarFin()
{
	this->largo--;
	T* ret = new T[this->largo];
	for (int i = 0; i < this->largo; i++)
		ret[i] = this->lista[i];
	this->lista = ret;
}

template <class T>
void ListaPosImp<T>::BorrarPos(unsigned int pos)
{
	T* ret = new T[this->largo - 1];
	bool seBorro = false;
	for (int i = 0; i < this->largo; i++)
	{
		if (i != pos && !seBorro)
			ret[i] = this->lista[i];
		else if (i != pos && seBorro)
			ret[i - 1] = this->lista[i];
		else
			seBorro = true;
	}
	this->lista = ret;
	this->largo--;
}

template <class T>
void ListaPosImp<T>::Borrar(const T &e)
{
	T* ret = new T[this->largo - 1];
	bool seBorro = false;
	for (int i = 0; i < this->largo; i++)
	{
		if (this->lista[i] != e && !seBorro)
			ret[i] = this->lista[i];
		else if (this->lista[i] != e && seBorro)
			ret[i - 1] = this->lista[i];
		else
			seBorro = true;
	}
	this->largo--;
	this->lista = ret;
}

template <class T>
T& ListaPosImp<T>::ElementoPpio() const
{
	return this->lista[0];
}

template <class T>
T& ListaPosImp<T>::ElementoFin() const
{
	return this->lista[this->largo - 1];
}

template <class T>
T& ListaPosImp<T>::ElementoPos(unsigned int pos) const
{
	return this->lista[pos];
}

template <class T>
unsigned int ListaPosImp<T>::Posicion(const T &e) const
{
	int pos = -1;
	for (int i = 0; i < this->largo && pos < 0; i++)
	{
		if (this->lista[i] == e)
			pos = i;
	}
	return pos;
}

template <class T>
bool ListaPosImp<T>::Existe(const T &e) const
{
	bool esta = false;
	for (int i = 0; i < this->largo && !esta; i++)
	{
		if (this->lista[i] == e)
			esta = true;
	}
	return esta;
}

template <class T>
void ListaPosImp<T>::Vaciar()
{
	while (!this->EsVacia())
		this->BorrarPpio();
}

template <class T>
unsigned int ListaPosImp<T>::CantidadElementos() const
{
	return this->largo;
}

template <class T>
bool ListaPosImp<T>::EsVacia() const
{
	return (this->largo == 0);
}

template <class T>
bool ListaPosImp<T>::EsLlena() const
{
	return false;
}

template <class T>
ListaPos<T>* ListaPosImp<T>::Clon() const
{
	return new ListaPosImp<T>(*this);
}

template <class T>
Iterador<T> ListaPosImp<T>::GetIterador() const
{
	return IteradorListaPosImp<T>(*this);
}

template <class T>
void ListaPosImp<T>::Imprimir(ostream& o) const
{
	if (this->largo != 0)
	{
		for (int i = 0; i < (this->largo - 1); i++)
			o << this->lista[i] << " ";
		o << this->lista[this->largo - 1];
	}
}

#endif