#include "MultiSetImp.h"

#ifndef MULTISET_IMP_CPP
#define MULTISET_IMP_CPP

template <class T>
MultiSetImp<T>::MultiSetImp() {
	this->lista = new ListaOrdImp<T>();
}

template <class T>
MultiSetImp<T>::MultiSetImp(const MultiSet<T> &multiSet) {
	MultiSet<T>* clonM = multiSet.Clon();
	while (!clonM->EsVacia())
	{
		T elem = clonM->Elemento();
		this->Insertar(elem, clonM->OcurrenciasElemento(elem));
		clonM->Borrar(elem, clonM->OcurrenciasElemento(elem));
	}
	delete clonM;
}

template <class T>
MultiSetImp<T>::MultiSetImp(const MultiSetImp<T> &multiSet) {
	lista = multiSet.lista->Clon();
}

template <class T>
MultiSet<T>& MultiSetImp<T>::operator=(const MultiSet<T> &multiSet) {
	if (this != &multiSet) {
		MultiSet<T>* clonM = multiSet.Clon();
		while (!clonM->EsVacia())
		{
			T elem = clonM->Elemento();
			this->Insertar(elem, clonM->OcurrenciasElemento(elem));
			clonM->Borrar(elem, clonM->OcurrenciasElemento(elem));
		}
		delete clonM;
	}
	return *this;
}

template <class T>
MultiSet<T>& MultiSetImp<T>::operator=(const MultiSetImp<T> &multiSet) {
	if (this != &multiSet) {
		MultiSet<T>* clonM = multiSet.Clon();
		while (!clonM->EsVacia())
		{
			T elem = clonM->Elemento();
			this->Insertar(elem, clonM->OcurrenciasElemento(elem));
			clonM->Borrar(elem, clonM->OcurrenciasElemento(elem));
		}
		delete clonM;
	}
	return *this;
}

template <class T>
bool MultiSetImp<T>::operator==(const MultiSet<T> &multiSet) const {

	bool existe = true;
	MultiSet<T> * aux = this->Clon();
	MultiSet<T> * aux2 = multiSet.Clon();

	while ((!aux->EsVacia() && !aux2->EsVacia()) && existe)
	{
		T e = aux->Elemento();
		if ((aux2->Pertenece(e)) && (aux->OcurrenciasElemento(e) == aux2->OcurrenciasElemento(e)))
		{
			aux->Borrar(e, aux->OcurrenciasElemento(e));
			aux2->Borrar(e, aux2->OcurrenciasElemento(e));
		}
		else
		{
			existe = false;
		}
	}

	if ((aux->EsVacia() || aux2->EsVacia()) && !(aux->EsVacia() && aux2->EsVacia()))
	{
		existe = false;
	}

	return existe;
}

template <class T>
MultiSetImp<T>::~MultiSetImp() {
	// NO IMPLEMENTADA
}

template <class T>
void MultiSetImp<T>::Insertar(const T &e, unsigned int cantidad) {
	for (unsigned int i = 1; i <= cantidad; i++)
	{
		this->lista->AgregarOrd(e);		
	}
}

template <class T>
void MultiSetImp<T>::Borrar(const T &e, unsigned int cantidad) {
	for (unsigned int i = 1; i <= cantidad; i++)
	{
		this->lista->Borrar(e);
	}
}

template <class T>
const T& MultiSetImp<T>::Elemento() const {

	return this->lista->Minimo();
}

template <class T>
const T& MultiSetImp<T>::Recuperar(const T &e) const {
	return this->lista->Recuperar(e);
}

template <class T>
unsigned int MultiSetImp<T>::OcurrenciasElemento(const T &e) const {
	int contador = 0;
	ListaOrd<T> * copia = this->lista->Clon();

	while (copia->Existe(e))
	{
		contador++;
		copia->Borrar(e);
	}

	return contador;
}

template <class T>
bool MultiSetImp<T>::Pertenece(const T &e) const {
	return this->lista->Existe(e);
}

template <class T>
void MultiSetImp<T>::Vaciar() {
	lista->Vaciar();
}

template <class T>
bool MultiSetImp<T>::EsVacia() const {
	return lista->EsVacia();
}

template <class T>
bool MultiSetImp<T>::EsLlena() const {
	return false;
}

template <class T>
unsigned int MultiSetImp<T>::Cardinal() const {
	int contador = 0;
	ListaOrd<T> * aux = this->lista->Clon();
	while (!aux->EsVacia())
	{
		T e = aux->Minimo();
		contador++;

		while (aux->Existe(e))
		{
			aux->Borrar(e);
		}
	}
	return contador;
}

template <class T>
MultiSet<T>* MultiSetImp<T>::Union(const MultiSet<T>& s) const
{
	MultiSet<T> * aux = this->Clon();
	MultiSet<T> * aux2 = s.Clon();

	MultiSet<T> * retorno = new MultiSetImp<T>();
	int cantidad = 0;

	while (!aux->EsVacia() || !aux2->EsVacia())
	{
		T e;
		if (!aux->EsVacia())
		{
			e = aux->Elemento();
		}
		else
		{
			e = aux2->Elemento();
		}

		if (aux->OcurrenciasElemento(e) > aux2->OcurrenciasElemento(e))
		{
			cantidad = aux->OcurrenciasElemento(e);
		}
		else
		{
			cantidad = aux2->OcurrenciasElemento(e);
		}
		retorno->Insertar(e, cantidad);
		aux->Borrar(e, aux->OcurrenciasElemento(e));
		aux2->Borrar(e, aux2->OcurrenciasElemento(e));

	}
	return retorno;
}

template <class T>
MultiSet<T>* MultiSetImp<T>::Interseccion(const MultiSet<T>& s) const
{
	MultiSet<T> * copiaThis = Clon();
	MultiSet<T> * copiaS = s.Clon();
	MultiSet<T> * ret = new MultiSetImp<T>();

	while (!copiaThis->EsVacia() && !copiaS->EsVacia()) {
		T e = copiaThis->Elemento();
		int cantidad;
		int ocurrenciasThis = copiaThis->OcurrenciasElemento(e);
		int ocurrenciasS = copiaS->OcurrenciasElemento(e);

		if (ocurrenciasThis > ocurrenciasS)
			cantidad = ocurrenciasS;
		else
			cantidad = ocurrenciasThis;

		ret->Insertar(e, cantidad);
		copiaThis->Borrar(e, copiaThis->OcurrenciasElemento(e));
		copiaS->Borrar(e, copiaS->OcurrenciasElemento(e));
	}
	return ret;
}

template <class T>
MultiSet<T>* MultiSetImp<T>::Diferencia(const MultiSet<T>& s) const
{
	MultiSet<T> * retorno = this->Clon();
	MultiSet<T> * aux = s.Clon();

	while (!aux->EsVacia())
	{
		T e = aux->Elemento();
		int ocurrenciasRetorno = retorno->OcurrenciasElemento(e);
		int ocurrenciasAux = aux->OcurrenciasElemento(e);

		if (retorno->Pertenece(e))
		{
			int cantidad = 0;

			if (ocurrenciasRetorno > ocurrenciasAux)
				cantidad = ocurrenciasRetorno - ocurrenciasAux;

			retorno->Borrar(e, ocurrenciasAux);
		}
		aux->Borrar(e, ocurrenciasAux);
	}

	return retorno;
}


template <class T>
bool MultiSetImp<T>::ContenidoEn(const MultiSet<T> &s) const {
	return *(this->Interseccion(s)) == *this;
}

template <class T>
MultiSet<T>* MultiSetImp<T>::Clon() const {
	MultiSetImp<T> * retorno = new MultiSetImp<T>();
	retorno->lista = this->lista->Clon();
	return retorno;
}

template <class T>
MultiSet<T>* MultiSetImp<T>::CrearVacia() const {
	
	return new MultiSetImp<T>();
}

template<class T>
void MultiSetImp<T>::Imprimir(ostream& o) const
{

	Iterador<T> it = this->lista->GetIterador();
	while (!it.EsFin())
	{
		o << it++;
		if (!it.EsFin())
			o << " ";
	}



	// en luegar de hacer cout << ... poner o << ...
}

#endif