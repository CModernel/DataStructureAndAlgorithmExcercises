#include "ListaOrdImp2.h"


#ifndef LISTAORDIMP2_CPP
#define LISTAORDIMP2_CPP


template <class T>
bool esVacio(NodoABB<T> *raiz) {
	return raiz == NULL;
}


template <class T>
inline ostream &operator<<(ostream& out, const ListaOrdImp2<T> &l)
{
	l.Imprimir(out);
	return out;
}

template <class T>
ListaOrd<T>* ListaOrdImp2<T>::CrearVacia() const
{
	return new ListaOrdImp2<T>();
}

template <class T>
ListaOrdImp2<T>::ListaOrdImp2()
{
	this->raiz = NULL;
	this->cantidad = 0;
}

template <class T>
ListaOrdImp2<T>::ListaOrdImp2(const ListaOrd<T> &l)
{
	for (Iterador<T> i = l.GetIterador(); !i.EsFin();) {
		AgregarOrd(i++);
	}
}


template <class T>
NodoABB<T> * copio(NodoABB<T> * r) {
	if (r == NULL)
		return r;
	else {
		NodoABB<T> * ret = new NodoABB<T>(r->dato, copio(r->izq), copio(r->der));
		return ret;
	}
}


template <class T>
ListaOrdImp2<T>::ListaOrdImp2(const ListaOrdImp2<T> &l)
{
	raiz = copio(l.raiz);
	cantidad = l.cantidad;
}

template <class T>
ListaOrd<T> &ListaOrdImp2<T>::operator=(const ListaOrd<T> &l)
{
	if (this != &l) {
		this->Vaciar();
		for (Iterador<T> i = l.GetIterador(); !i.EsFin();) {
			AgregarOrd(i++);
		}
	}
	return *this;
}

template <class T>
ListaOrd<T> &ListaOrdImp2<T>::operator=(const ListaOrdImp2<T> &l)
{
	if (this != &l) {
		Vaciar();
		cantidad = l.cantidad;
		this->raiz = copio(l.raiz);
	}
	return *this;
}

template <class T>
ListaOrdImp2<T>::~ListaOrdImp2()
{
	Vaciar();
}

template <class T>
void ListaOrdImp2<T>::AgregarOrd(const T &e)
{
	Asociacion<T, int> a(e);
	NodoABB<Asociacion<T, int>> *& p = busco(raiz, a);
	if (p != NULL)
		p->dato.GetRangoInseguro()++;
	else {
		Asociacion<T, int> b(e, 1);
		p = new NodoABB<Asociacion<T, int>>(b, NULL, NULL);
	}
	cantidad++;
}


template <class T>
NodoABB<T> *& busco(NodoABB<T> *& r, const T &t)
{
	if (esVacio(r))
		return r;
	if (r->dato == t)
		return r;
	if (r->dato < t)
		return busco(r->der, t);
	else
		return busco(r->izq, t);


}


template <class T>
NodoABB<T> *& masIzquierdo(NodoABB<T> *& raiz)
{
	assert(raiz != NULL);
	if (raiz->izq == NULL)
		return raiz;
	else
		return masIzquierdo(raiz->izq);
}

template <class T>
void ListaOrdImp2<T>::BorrarMinimo()
{
	if (raiz != NULL) {
		NodoABB <Asociacion<T, int>> *& p = masIzquierdo(raiz);
		assert(p);
		if (p->dato.GetRangoInseguro() == 0) {
			borrarNodoRaiz(p);
		}
		else {
			p->dato.GetRangoInseguro()--;
		}
	}
	cantidad--;
}

template <class T>
NodoABB<T> *& masDerecho(NodoABB<T> *& r)
{
	assert(r != NULL);
	if (r->der == NULL)
		return r;
	else
		return masIzquierdo(r->der);
}


template <class T>
void ListaOrdImp2<T>::BorrarMaximo()
{
	if (raiz != NULL) {
		NodoABB <Asociacion<T, int>> *& p = masDerecho(raiz);
		assert(p);
		if (p->dato.GetRangoInseguro() == 0) {
			borrarNodoRaiz(raiz);
		}
		else {
			p->dato.GetRangoInseguro()--;
		}
	}
	cantidad--;
}

template <class T>
bool esUnaHoja(NodoABB<T>* r)
{
	return r->izq == NULL && r->der == NULL;
}

template <class T>
void  buscoYBorro(NodoABB<Asociacion<T, int>> *& r, const T &t)
{
	Asociacion<T, int> a(t);

	NodoABB<Asociacion<T, int>> *& posDato = busco(r, a);
	if (esVacio(posDato))
		return;
	else
	{
		NodoABB<T> * q = posDato;
		if (esUnaHoja(posDato))
		{
			posDato = NULL;
		}
		else
		{
			if (esVacio(posDato->izq))
			{
				posDato = posDato->der;
			}
			else
			{
				if (esVacio(posDato->der))
				{
					posDato = posDato->izq;
				}
				else //tiene 2 subarboles no vacios
				{
					posDato->dato = masIzquierdo(posDato->der)->dato;
					buscoYBorro(posDato->der, posDato->dato);
				}
			}
			delete q;
		}
	}
}

template <class T>
NodoABB<T> * buscoMasIzq(NodoABB<T> *& r)
{
	if (r != NULL)
	{
		NodoABB<T> * ret = r;

		if (r->izq == NULL && r->der == NULL)
		{
			ret = r;
			r = NULL;
			return ret;
		}
		else
		{
			if (r->izq != NULL)
			{
				return buscoMasIzq(r->izq);
			}
			else
			{
				ret->dato = r->dato;
				r = r->der;
				return ret;
			}
		}
	}
	return NULL;
}

template <class T>
void borrarNodoRaiz(NodoABB<T> * & A)
{
	if (A != NULL)
	{
		if (A->der != NULL || A->izq != NULL)
		{
			if (A->izq == NULL)
			{
				A = A->der;
			}
			else
			{
				if (A->der == NULL)
				{
					A = A->izq;
				}
				else
				{
					NodoABB<T> * aux = buscoMasIzq(A->der);
					A->dato = aux->dato;
				}
			}
		}
		else
		{
			NodoABB<T> *q = A;
			A = NULL;
			delete q;
		}
	}
}

template <class T>
void ListaOrdImp2<T>::Borrar(const T &e)
{
	Asociacion<T, int> a(e);
	NodoABB<Asociacion<T, int>> *& p = busco(raiz, a);
	if (p == NULL) {
		return;
	}
	else {
		p->dato.GetRangoInseguro()--;
		if (p->dato.GetRango() == 0) {
			borrarNodoRaiz(p);
		}
	}
}

template <class T>
const T& ListaOrdImp2<T>::Minimo() const
{

	NodoABB<Asociacion<T, int>> *aux = raiz;
	NodoABB<Asociacion<T, int>> *p = masIzquierdo<Asociacion<T, int>>(aux);

	assert(p != NULL);
	return p->dato.GetDominio();
}

template <class T>
const T& ListaOrdImp2<T>::Maximo() const
{
	
	NodoABB<Asociacion<T, int>> *aux = raiz;
	NodoABB<Asociacion<T, int>> * p = masDerecho(aux);
	assert(p != NULL);
	return p->dato.GetDominio();
}

template <class T>
const T& ListaOrdImp2<T>::Recuperar(const T &e) const
{
	Asociacion<T, int> a(e);
	NodoABB<Asociacion<T, int>>* aux = raiz;
	NodoABB<Asociacion<T, int>>* asoc = busco(aux, a);
	return asoc->dato.GetDominio();

}

template <class T>
bool ListaOrdImp2<T>::Existe(const T &e) const
{
	Asociacion<T, int> a(e);
	NodoABB<Asociacion<T, int>> *aux = raiz;
	NodoABB<Asociacion<T, int>> *p = busco(aux, a);
	return p != NULL;
}


template<class T>
void vaciarAux(NodoABB<T> *& r) {
	if (r == NULL)
		return;
	else {
		buscoYBorro(r, r->dato);
		vaciarAux(r->izq);
		vaciarAux(r->der);
	}
}


template <class T>
void ListaOrdImp2<T>::Vaciar()
{
	while (!EsVacia()) {
		borrarNodoRaiz(raiz);
		cantidad--;
	}
}

template <class T>
unsigned int ListaOrdImp2<T>::CantidadElementos()const
{

	return cantidad;
}

template <class T>
bool ListaOrdImp2<T>::EsVacia()const
{
	return raiz == NULL;
}

template <class T>
bool ListaOrdImp2<T>::EsLlena()const
{
	return false;
}

template<class T>
ListaOrd<T>* ListaOrdImp2<T>::Clon() const
{
	return new ListaOrdImp2<T>(*this);
}



template<class T>
void ArbolALista(NodoABB<Asociacion<T, int>>* a, ListaPosImp<T>* &l)
{
	if (a != NULL)
	{
		ArbolALista(a->izq, l);
		int k = a->dato.GetRango();
		for (int i = 1; i <= k; i++)
		{
			l->AgregarFin(a->dato.GetDominio());
		}
		ArbolALista(a->der, l);
	}
}

template <class T>
Iterador<T> ListaOrdImp2<T>::GetIterador() const
{
	ListaPosImp<T>* l = new ListaPosImp<T>();
	ArbolALista(raiz, l);
	return IteradorListaOrdImp2<T>(*l);
}

template <class T>
void ListaOrdImp2<T>::Imprimir(ostream& o) const
{
	Iterador<T> it = this->GetIterador();
	while (!it.EsFin())
	{
		o << it++;
		if (!it.EsFin())
			o << " ";
	}
	// en luegar de hacer cout << ... poner o << ...
}


#endif