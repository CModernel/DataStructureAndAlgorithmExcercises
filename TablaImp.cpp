#include "TablaImp.h"

#ifndef TABLAIMP_CPP
#define TABLAIMP_CPP

template <class D, class R>
inline ostream &operator<<(ostream& out, const TablaImp<D, R> &t) {
	t.Imprimir(out);
	return out;
}

template <class D, class R>
TablaImp<D, R>::TablaImp() {
	lista = new ListaOrdImp<Asociacion<D, R>>();
}

template <class D, class R>
TablaImp<D, R>::TablaImp(const Tabla<D, R> &t) {
	Tabla<D, R> * copia = t.Clon();

	while (!copia->EsVacia())
	{
		D d = copia->Elemento();
		R r = copia->Recuperar(d);
		this->Insertar(d, r);
		copia->Borrar(d);
	}
}

template <class D, class R>
TablaImp<D, R>::TablaImp(const TablaImp<D, R> &t) {
	Tabla<D, R> * aux = t.Clon();
	*this = aux;
}

template <class D, class R>
Tabla<D, R>& TablaImp<D, R>::operator=(const Tabla<D, R> &t) {
	if (this != &t) {
		this->Vaciar();
		Tabla<D, R> * copia = t.Clon();

		while (!copia->EsVacia())
		{
			D d = copia->Elemento();
			R r = copia->Recuperar(d);
			this->Insertar(d, r);
			copia->Borrar(d);
		}
	}

	return *this;
}

template <class D, class R>
Tabla<D, R>& TablaImp<D, R>::operator=(const TablaImp<D, R> &t) {
	if (this != &t) {
		this->Vaciar();
		Tabla<D, R> * copia = t.Clon();

		while (!copia->EsVacia())
		{
			D d = copia->Elemento();
			R r = copia->Recuperar(d);
			this->Insertar(d, r);
			copia->Borrar(d);
		}
	}

	return *this;
}

template <class D, class R>
TablaImp<D, R>::~TablaImp() {

}

template <class D, class R>
Tabla<D, R>* TablaImp<D, R>::CrearVacia() const {
	return new TablaImp<D, R>();
}

template <class D, class R>
void TablaImp<D, R>::Vaciar() {
	lista->Vaciar();
}

template <class D, class R>
void TablaImp<D, R>::Insertar(const D &d, const R &r) {
	Asociacion<D, R> * nuevo = new Asociacion<D, R>(d, r);
	lista->AgregarOrd(*nuevo);
}

template <class D, class R>
bool TablaImp<D, R>::EstaDefinida(const D &d) const {
	Asociacion<D, R> * nuevo = new Asociacion<D, R>(d);
	return lista->Existe(*nuevo);
}

template <class D, class R>
bool TablaImp<D, R>::operator==(const Tabla<D, R> &t) const {
	Tabla<D, R> * copia = t.Clon();

	bool existe = true;
	while (!copia->EsVacia() && existe)
	{
		D d = copia->Elemento();
		existe = this->EstaDefinida(d);
		copia->Borrar(d);
	}
	return existe;
}

template <class D, class R>
const R& TablaImp<D, R>::Recuperar(const D &d) const {
	Asociacion<D, R> *nuevo = new Asociacion<D, R>(d);
	return lista->Recuperar(*nuevo).GetRango();
}

template <class D, class R>
const D& TablaImp<D, R>::Elemento() const {

	return lista->Recuperar(lista->Maximo()).GetDominio();
}

template <class D, class R>
void TablaImp<D, R>::Borrar(const D &d) {
	Asociacion<D, R> *nuevo = new Asociacion<D, R>(d);
	return lista->Borrar(*nuevo);
}

template <class D, class R>
bool TablaImp<D, R>::EsVacia() const {

	return lista->EsVacia();
}

template <class D, class R>
bool TablaImp<D, R>::EsLlena() const {

	return false;
}

template <class D, class R>
unsigned int TablaImp<D, R>::CantidadElementos() const {

	return lista->CantidadElementos();
}

template <class D, class R>
Tabla<D, R>* TablaImp<D, R>::Clon() const {
	Tabla<D, R> * clone = new TablaImp<D, R>();
	Iterador <Asociacion<D, R>> it = this->lista->GetIterador();
	while (!it.EsFin())
	{
		Asociacion<D, R> elemento = it.Elemento();
		clone->Insertar(elemento.GetDominio(), elemento.GetRango());
		it.Resto();
	}
	return clone;
}

template <class D, class R>
void TablaImp<D, R>::Imprimir(ostream & o) const
{
	Iterador<Asociacion<D, R>> it = this->lista->GetIterador();
	while (!it.EsFin())
	{
		Asociacion<D, R> elemento = it.Elemento();
		o << "{D:" << elemento.GetDominio() << "|R:" << elemento.GetRango() << "} ";
		it.Resto();
	}

	// en luegar de hacer cout << ... poner o << ...
}


#endif