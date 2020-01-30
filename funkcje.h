
#pragma once
#include "pch.h"
#include <iostream> 
using namespace std;
#pragma region Struct Definitions
///struktura czas
struct TimeStruct
{
	int godziny; /**< godziny w wyniku Maratonczyka */
	int minuty; /**< minuty w wyniku Maratonczyka */
	int sekundy; /**< sekundy w wyniku Maratonczyka */
};
///struktura daty
struct DateStruct
{
	int dzien;  /**< dzien, w ktorym odbyl sie maraton */
	int miesiac; /**< miesiac, w ktorym odbyl sie maraton */
	int rok; /**< rok, w ktorym odbyl sie maraton */
};
///struktura maratonu
struct Maraton
{
	string Nazwa; /**< nazwa maratonu */
	DateStruct Data; /**< data maratonu */
	TimeStruct czas; /**< czas osiagniety w maratonie */
	Maraton* nastepnyMaraton; /**< wskaznik na kolejny maraton */
};
///struktura zawodnika
struct Zawodnik
{
	string Nazwisko; /**< nazwisko maratonczyka */
	Zawodnik *NastepnyZawodnik;  /**< wskaznik na kolejnego maratonczyka */
	Maraton* maratonHead; /**< wskaznik na glowe listy maraton */
};
#pragma endregion 


#pragma region Convert Methods
/**konwertuje TimeStruct na string
@param cz czas
@return funkcja zwraca przekonwertowany TimeStruct na string
*/
string timeToString(TimeStruct cz);
/**Konwertuje string na DateStruct
@param str string
@return funkcja zwraca przekonwertowany string na DateStruct
*/
DateStruct stringToData(string str);
/**Konwertuje string na TimeStruct
@param str string
@return funkcja zwraca przekonwertowany string na  TimeStruct
*/
TimeStruct stringToTime(string str);
#pragma endregion 

/**Porownuje dwa typy dateStruct - uzyte do sortowania dat
@param data1 pierwsza data brana do porownania
@param data2 druga data brana do porownania
*/
int compare(DateStruct data1, DateStruct data2);

/**Dodaje zawodnika na g這we listy zawodnikow
@param pHead wskaznik na g這we listy zawodnikow
@param Nazwisko nazwisko zawodnika
*/
Zawodnik * dodajZawodnika(Zawodnik * & pHead, string Nazwisko);

/**Dodaje maraton na g這we listy maratonow
@param pHead wskaznik na glowe listy maratonow
@param Nazwa nazwa maratonu
@param date data maratonu
@param czas czas osiagniety w maratonie
*/
void dodajMaraton(Maraton * & pHead, string Nazwa, DateStruct date, TimeStruct czas);

/**Odczytuje dane z pliku tworzac zawodnika
@param pHead wskaznik na g這we listy zawodnikow
@param path sciezke do pliku
*/
void parseMaraton(Zawodnik * & pHead, string path);

/**Usuwa wszystkich maratonczykow
@param Lista list maratonow
*/
void deleteAllMaraton(Maraton*&  list);

/**usuwa wszystkich zawodnikow
@param Lista list zawodnikow
*/
void deleteAllZawodnik(Zawodnik*& list);

/**Odczytuje argumenty konsoli
@param narg ilosc parametrow
@param args tablica parametrow
@param zaw wskaznik na poczatek listy zawodnikow
*/
void parseCommandLine(int narg, char* args[], Zawodnik * &zaw);

/**Zapisuje dane maratonow do plikow
@param Lista list zawodnikow
*/
void writeDataToFiles(Zawodnik* list);



