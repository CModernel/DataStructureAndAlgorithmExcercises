#include "Entrega2.h"

#ifndef ENTREGA2_CPP
#define ENTREGA2_CPP
bool HayMasCaracteres(const char* caracter)
{
	bool retorno = true;

	if (*caracter == '\0')
		retorno = false;

	return retorno;
}

bool EsParentesisCerrado(const char *c)
{
	if (*c == ')' || *c == '}' || *c == ']')
		return true;

	return false;
}	

bool EsParentesisAbierto(const char *c)
{
	if (*c == '(' || *c == '{' || *c == '[')
		return true;

	return false;
}

char * CerrarParentesis(char * c)
{
	switch (*c)
	{
	case '(':
		return new char(')');
	case '{':
		return new char('}');
	case '[':
		return new char(']');
	default:
		break;
	}
}

bool ParentesisBalanceados(const char *formula)
{
	
	Pila<char> * auxParentesis = new PilaImp<char>();

	int i = 0;

	while (HayMasCaracteres(formula + i))
	{
		const char * caracter = (formula + i);

		if (EsParentesisAbierto(caracter))
		{
			auxParentesis->Push(*caracter);
		}
		else if (EsParentesisCerrado(caracter))
		{
			if (!auxParentesis->EsVacia()) {
				char * c = CerrarParentesis(new char(auxParentesis->Pop()));

				if (*c != *caracter) {
					return false;
				}
			}
			else
				return false;
		}

		i++;
	}

	if (auxParentesis->EsVacia())
		return true;
	
	return false;
	
}



void ImprimirPorNiveles(NodoAG* a)
{
	
	Cola<NodoAG*> * c = new ColaImp<NodoAG*>();
	if (a != NULL)
	{
		c->Encolar(a);
	}
	while (!c->EsVacia())
	{
		NodoAG * temp = c->Principio();
		cout << temp->dato << " ";
		if (temp->ph != NULL)
		{
			c->Encolar(temp->ph);
		}
		NodoAG * hermano = temp->sh;
		while (hermano != NULL)
		{
			cout << hermano->dato << " ";
			if (hermano->ph != NULL)
				c->Encolar(hermano->ph);
			hermano = hermano->sh;
		}
		c->Desencolar();
	}
	delete c;
	
}

#endif
