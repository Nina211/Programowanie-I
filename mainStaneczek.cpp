#include "pch.h"
#include <iostream>
#include <fstream>
#include <string>
#include <filesystem>
#include "funkcje.h"
using namespace std;

///Glowna funkcja programu
int main(int argc, char * argv[]) {

	Zawodnik* list = nullptr; //Inicjujemy pust¹ listê jednokierunkow¹ zawodnikow
	parseCommandLine(argc, argv, list); // Odczytujemy dane z argumentów command line. Wywo³ujemy tak¿e funkcje parseMaraton
	writeDataToFiles(list);//Zapisujemy dane w pliku tekstowym
	deleteAllZawodnik(list);//Usuwamy elementy z listy

	return 0;
}