#ifndef REFERENCIA_H
#define REFERENCIA_H

#include <iostream>
using namespace std;

template<class T>
class Referencia
{
	
	public:
		// constructor por defecto
		Referencia();	

		// constructor que recibe puntero. 
		// Se le transfiere a la referencia la responsabilidad de eliminar el objeto apuntado por ptr
		// al no quedar referencias apuntando al objeto apuntado por ptr.
		//Referencia(T* ptr);	

		// constructor que recibe un valor. Realiza una copia del objeto recibido.
		Referencia(const T& dato);	

		// constructor copia
		Referencia(const Referencia<T>& ref); 
		
		// operador de asignacion
		Referencia<T>& operator=(const Referencia<T>& ref); 
		
		// destructor
		virtual ~Referencia();
		
		// Modificacion y acceso del objeto referenciado
		//void SetPuntero(T* ptr);
		//void SetDato (const T& dato);
		//T* GetPuntero() const;
		T& GetDato() const;
		
		// Operaciones de comparacion de referencias, supone que todos estos
		// operadores estan definidos para T
		bool operator==(const Referencia<T>& ref) const;
		bool operator!=(const Referencia<T>& ref) const;
		bool operator<=(const Referencia<T>& ref) const;	
		bool operator<(const Referencia<T>& ref) const;	
		bool operator>(const Referencia<T>& ref) const;	
		bool operator>=(const Referencia<T>& ref) const;

		bool EsVacia() const;

		void Imprimir(ostream& o) const;

	private:
		T* puntero;
		int* contador;
};

#include "Referencia.cpp"

#endif