#ifndef NODOLISTA_H
#define NODOLISTA_H

#include <iostream>
#include <assert.h>

template <class U>
class NodoLista {
	public:
		U dato;
		NodoLista<U> *ant;
		NodoLista<U> *sig;

		NodoLista(const U &e, NodoLista<U> *a, NodoLista<U> *s) : dato(e), ant(a), sig(s) {}
		virtual ~NodoLista() {}
	private:
		NodoLista(const NodoLista<U> &n) : dato(n.dato), ant(n.ant), sig(n.sig)  {}

		NodoLista<U> &operator=(const NodoLista<U> &n) { assert(false); return *this; }
};

#endif