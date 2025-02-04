#include "ConductorPruebaObl2.h"
#include "ManejadorArchivos.h"
#include <iostream>
#include <fstream>
#include "ListaOrdImp2.h"

using namespace std;

// NO MODIFICAR ACA. HACER LAS PRUEBAS EN EL ARCHIVO PRUEBASPROPIAS.CPP
int main()
{
	ListaOrdImp2 <int> l;
	ConductorPrueba* prueba = new ConductorPruebaObl2();
	prueba->correrPrueba();
	delete prueba;

	char rutaLectura1[] = "../SalidaDeLasPruebas/PruebasEjemploDeUsoEntrega1/PruebasEjemploDeUsoEntrega1.txt";
	char rutaCorreccion1[] = "../PruebasEjemploDeUsoEntrega1.txt";
	char rutaEscritura1[] = "../SalidaDeLasPruebas/PruebasEjemploDeUsoEntrega1/PruebasEjemploDeUsoEntrega1Resultado.txt";
	ManejadorArchivos* m = new ManejadorArchivos(rutaLectura1, rutaCorreccion1, rutaEscritura1);
	
	// Comparar
	// - Parametro 1: si se le pasa true muestra el resultado de todas las salidas incluso cuando dan OK
	// - Parametro 2: si se le pasa true solamente muestra las pruebas que no están correctas
	m->Comparar(false, false); 
	delete m;

	char rutaLectura2[] = "../SalidaDeLasPruebas/PruebasEjemploDeUsoEntrega2/PruebasEjemploDeUsoEntrega2.txt";
	char rutaCorreccion2[] = "../PruebasEjemploDeUsoEntrega2.txt";
	char rutaEscritura2[] = "../SalidaDeLasPruebas/PruebasEjemploDeUsoEntrega2/PruebasEjemploDeUsoEntrega2Resultado.txt";
	m = new ManejadorArchivos(rutaLectura2, rutaCorreccion2, rutaEscritura2);
	
	// Comparar
	// - Parametro 1: si se le pasa true muestra el resultado de todas las salidas incluso cuando dan OK
	// - Parametro 2: si se le pasa true solamente muestra las pruebas que no están correctas
	m->Comparar(false, false); 
	delete m;

	char rutaLectura3[] = "../SalidaDeLasPruebas/PruebasCorreccion/PruebasCorreccion.txt";
	char rutaCorreccion3[] = "../PruebasCorreccion.txt";
	char rutaEscritura3[] = "../SalidaDeLasPruebas/PruebasCorreccion/PruebasCorreccionResultado.txt";
	m = new ManejadorArchivos(rutaLectura3, rutaCorreccion3, rutaEscritura3);
	
	// Comparar
	// - Parametro 1: si se le pasa true muestra el resultado de todas las salidas incluso cuando dan OK
	// - Parametro 2: si se le pasa true solamente muestra las pruebas que no están correctas
	m->Comparar(false, false); 
	delete m;

	char rutaLectura4[] = "../SalidaDeLasPruebas/PruebasPropias/PruebasPropias.txt";
	char rutaCorreccion4[] = "../PruebasPropias.txt";
	char rutaEscritura4[] = "../SalidaDeLasPruebas/PruebasPropias/PruebasPropiasResultado.txt";
	m = new ManejadorArchivos(rutaLectura4, rutaCorreccion4, rutaEscritura4);
	
	// Comparar
	// - Parametro 1: si se le pasa true muestra el resultado de todas las salidas incluso cuando dan OK
	// - Parametro 2: si se le pasa true solamente muestra las pruebas que no están correctas
	m->Comparar(false, false); 
	delete m;

	//system("pause");
	return 0;
}

