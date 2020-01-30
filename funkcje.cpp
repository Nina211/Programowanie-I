
#pragma once
#include "pch.h"
#include <iostream>
#include <fstream>
#include <string>
#include "funkcje.h"
using namespace std;

#pragma region Convert Methods
//konwertuje TimeStruct na string
string timeToString(TimeStruct cz) {
	return to_string(cz.godziny) + ":" + to_string(cz.minuty) + ":" + to_string(cz.sekundy);
}
//konwertuje string do DateStruct
DateStruct stringToData(string str) {

	int values[3] = {};
	int index = 0;
	string tmp = "";

	for (int i = 0; i < str.length(); i++)
	{
		if (str[i] == '-')
		{
			values[index] = stoi(tmp);
			index++;
			tmp = "";
			continue;
		}

		tmp += str[i];
	}

	values[index] = stoi(tmp);

	DateStruct data = { 1,1,1 };
	data.rok = values[0];
	data.miesiac = values[1];
	data.dzien = values[2];
	return data;
}
//konwertuje string na TimeStruct
TimeStruct stringToTime(string str) {

	int values[3] = {};
	int index = 0;
	string tmp = "";

	for (int i = 0; i < str.length(); i++)
	{
		if (str[i] == ':')
		{
			values[index] = stoi(tmp);
			index++;
			tmp = "";
			continue;
		}

		tmp += str[i];
	}

	values[index] = stoi(tmp);

	TimeStruct time = { 1,1,1 };
	time.godziny = values[0];
	time.minuty = values[1];
	time.sekundy = values[2];
	return time;
}

#pragma endregion 

//Porownuje dwa typy dateStruct - uzyte do sortowania dat
int compare(DateStruct data1, DateStruct data2) {

	if (data1.rok > data2.rok)
		return -1;
	else
		if (data1.rok < data2.rok)
			return 1;
		else
			if (data1.miesiac > data2.miesiac)
				return -1;
			else
				if (data1.miesiac < data2.miesiac)
					return 1;
				else
					if (data1.dzien > data2.dzien)
						return -1;
					else
						if (data1.dzien < data2.dzien)
							return 1;
						else
							return 0;
}
//Dodaje zawodnika na glowe listy zawodnikow
Zawodnik * dodajZawodnika(Zawodnik * & pHead, string Nazwisko) {

	Zawodnik * pom = pHead;
	while (pom != nullptr)
	{
		if (pom->Nazwisko == Nazwisko)
			return pom;
		pom = pom->NastepnyZawodnik;
	}

	return pHead = new Zawodnik{ Nazwisko, pHead };
}
//Dodaje maraton na glowe listy maratonow
void dodajMaraton(Maraton * & pHead, string Nazwa, DateStruct date, TimeStruct czas) {

	if (pHead == nullptr)
	{
		pHead = new Maraton{ Nazwa,date, czas,nullptr };
	}
	else {

		if (compare(pHead->Data, date) == -1) {
			pHead = new Maraton{ Nazwa,date, czas,pHead };
			return;
		}

		Maraton * pom = pHead;
		while (pom->nastepnyMaraton != nullptr) {

			if (compare(pom->nastepnyMaraton->Data, date) == -1) {
				pom->nastepnyMaraton = new Maraton{ Nazwa, date, czas, pom->nastepnyMaraton };
				return;
			}

			pom = pom->nastepnyMaraton;
		}

		pom->nastepnyMaraton = new Maraton{ Nazwa,date, czas,nullptr };

	}

}
//Odczytuje dane z pliku tworzac zawodnika
void parseMaraton(Zawodnik * & pHead, string path)
{
		ifstream inf(path);
 
		if (!inf) {
			cerr << "Nie mozna otworzyc pliku do odczytu  " << path << endl;
			system("pause");
			exit(1);
		}

		string strInput;
		getline(inf, strInput); //Input stringa
		string nazwa = strInput;
		getline(inf, strInput); //input nazwy
		string data = strInput;//input daty

		while (getline(inf, strInput)) { //iteruje dopoki getline nie zwroci informacji ktora sugeruje, ze jest koniec pliku (EOF)
			string infoMaratonczyk[4] = {}; //Tablica informacji o maratonczyku

			int index = 0;
	
			for (int i = 0; i < strInput.length(); i++) { //Iterujemy, dopoki nie skonczy sie dana linijka
				if (strInput[i] == ',')
				{
					index++;
					continue;
				}
				else if (strInput[i] == ' ') continue;

				infoMaratonczyk[index] += strInput[i];

			}
			Zawodnik* actual = dodajZawodnika(pHead, infoMaratonczyk[1]); //Dodaje zawodnika
			dodajMaraton(actual->maratonHead, nazwa, stringToData(data), stringToTime(infoMaratonczyk[3])); //Dodaje maraton
		}
		
}
//Usuwa wszystkich maratonczykow
void deleteAllMaraton(Maraton*&  list)
{

	Maraton* pom = list;
	Maraton* nastPom = list;
	while (nastPom != nullptr) {
		pom = nastPom;
		nastPom = pom->nastepnyMaraton;
		delete pom;
	}
	list = nullptr;
}
//usuwa wszystykich zawodnikow
void deleteAllZawodnik(Zawodnik*& list)
{

	Zawodnik* pom = list;
	Zawodnik* nastPom = list;
	while (nastPom != nullptr) {
		pom = nastPom;
		nastPom = pom->NastepnyZawodnik;
		deleteAllMaraton(pom->maratonHead);
		delete pom;
	}
	list = nullptr;
}
//Odczytuje argumenty konsoli
void parseCommandLine(int narg, char* args[], Zawodnik * &zaw)
{
	if (strlen(args[1]) == 2)
	{
			if (args[1][1] == 'i' && args[1][0] == '-')
			{
				 for (int i = 2; i < narg; i++)
				{
					parseMaraton(zaw, args[i]);
				}
			}
			else cout << "Wystapil blad w odczycie pliku. Upewnij sie ze przelacznik jest prawidlowy" << endl;	
	}
	else cout << "Wystapil blad w odczycie pliku. Upewnij sie ze przelacznik jest prawidlowy" << endl;
}
//Zapisuje dane maratonow do plikow
void writeDataToFiles(Zawodnik* list)
{
	Zawodnik* pomZaw = list;
	if (!list)
		cout << "Pliki do odczytu nie zostaly podane";
	else
	while (pomZaw != nullptr) {
		ofstream myfile;
		myfile.open(pomZaw->Nazwisko + ".txt");
		myfile << pomZaw->Nazwisko << endl << endl;
		cout << pomZaw->Nazwisko << endl;
		Maraton* pomMar = pomZaw->maratonHead;
		while (pomMar != nullptr) {
			myfile << pomMar->Data.rok << "-" << pomMar->Data.miesiac << "-" << pomMar->Data.dzien << " " << pomMar->Nazwa << " " << timeToString(pomMar->czas) << endl;
			cout << "\t\t" << pomMar->Data.rok << "-" << pomMar->Data.miesiac << "-" << pomMar->Data.dzien << " - " << pomMar->Nazwa << " - " << timeToString(pomMar->czas) << endl;
			pomMar = pomMar->nastepnyMaraton;
		}
		pomZaw = pomZaw->NastepnyZawodnik;
		myfile.close();
	}
}
