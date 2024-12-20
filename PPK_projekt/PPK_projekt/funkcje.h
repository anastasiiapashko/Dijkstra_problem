#include <iostream>
#include <random>
#include <chrono>
#include <fstream>
#include <vector>
#include <map>
#include <cmath>
#include <set>
#include <string>
#include <sstream>
#include <iomanip>
#include <format>
/**
 * @include file.
 */
//Deklaracje (Nagłówki) Finkcji
/** @file */
#ifndef FUNKCJE_H // zabezpieczenie przed wielokrotnym dołaczaniem pliku nagłówkowego
#define FUNKCJE_H

/** 
*Tworzona strukura o nazwie "krawedz"
*tworzone sa zmiene o wartosciach parametrow krawedzi : z ktorego do ktorego wierzcholka i jego waga
*@brief
*
*/

struct krawedz
{
	int nr_wierz_poczatkowy;
	int nr_wierz_koncowy;
	double waga;
};

/**

*@param nazwa_pliku nazwa pliku z ktorego wczytujemy graf
*@param krawedzie wskaznik na wektor przechowujacy krawędzi
*@param wierzcholki wskaznik na zbior przechowujacy wierzcholki
*@return zwraca czy funkcja się udała
*  @brief Funkcja co sprawdza i odczytuje dane z pliku krawedzie i wierzcholki
*/
bool odczytaj_graf(std::string nazwa_pliku, std::vector<krawedz>* krawedzie, std::set<int>* wierzcholki);


/**
* @brief 
 * Funkcha do tworzenia listy krawedzi z jej watrosciami do kazdego parametra
 *
 * @param poczatek wierzcholek oznaczjacy poczatek krawedzi
 * @param koniec wierzcholek oznaczjacy koniec krawedzi
 * @param waga waga samej krawedzi miedzy poczatkowym a koncowym wierzcholkiem
 * @param krawedzie wskaznik na wektor przechowujacy krawędzi
 */
void dodaj_krawedz(int poczatek, int koniec, double waga, std::vector<krawedz>* krawedzie);

/**
*
* @param nazwa_pliku nazwa pliku z ktorego wczytujemy wierzcholki
* @param wierzcholki wskaznik na zbior przechowujacy wierzcholki
* @return zwraca czy funkcja się udała
*  @brief Funkcja co sprawdza i odczytuje wierzcholki z pliku wierzcholki
*/
bool wierzchowce(std::string nazwa_pliku, std::set<int>* wierzcholki);



/**
*
 * @param poczatek wierzchołek początku
 * @param koniec wierzchołek końca
 * @param waga waga od poczatku do konca
 * @param krawedzie wskażnik na wektor krawędzi
 *  @brief  dodajemy nową krawedż do wektora
 */
void dodaj_krawedz(int poczatek, int koniec, double waga, std::vector<krawedz>* krawedzie);



/**
 *
 * @param zbior_wierzcholkow przypisanie zbioru wierzcholkow
 * @param zbior_krawedzi przypisanie zbioru krawedzi
 * @param poczatkowy_wierzcholek poczatkowy wierzcholek
 * @return zwraca szukane trasy w postacie string
 * 
 * 
 * @brief Funkacja do odszukiwania szukanych najkrotszych tras.
 * Pobiera wierzcholki razem z ich dystansem bez powtorzen za pomoca "insert_or_assign". Dodawanie elementów odbywa się przy 
 *  użyciu metody insert(), do której podajemy klucz do dodania (wierzcholek, INFINITY).
 *  Jeśli klucz już istnieje w zbiorze, operacja dodawania nie zmienia w żaden sposób zawartości juz pobranych wierzcholkow.
 * Nastepnie tworzenie zbiorow sprawdzonych wierzcholkow; 
 * wyluskanie wartosci z pod wzkaznika na wierzcholki, robienie kopii do usuwania jej;
 * dopoki kolejka pobranych wierzcholkow nie jest pusta, to idzie przypisywanie do naimniejszego wierzchowka z funkcji "znajdz_najblizszy_wierzcholek"
 *  ktory to wierzcholek jest razem z jestgo dystansem, jezeli juz wszystko zostalo przeczytane to konczy sie proces przypisywania;
 * po nim do sprawdzonych wierzcholkow beda sie przepisywali wierzcholki bez dublowania, a z kolejki wierzcholkow beda usuwac sie sprawdzone wierzcholki;
 * w kolejnym kroku wykonuje sie relaksacja; 
 * i na konie wypisywanie wszystkich informacji w postacie sringu
 */
std::string szukanie_tras(std::set<int>* zbior_wierzcholkow, std::vector<krawedz>* zbior_krawedzi, int poczatkowy_wierzcholek);


/**

 * @param poprzedniki zbior poprzednikow wierzchplkow
 * @param wierzcholek wierzcholek do ktorego jest odszukiwana trasa
 * @return zwraca trase z koncowym wierzkowkiem razem z jego poprzednikiem
 *@brief  Funkcka do wypisywania trasy od zadanego wierzcholka do wierzcholka o najmniejszej wadze,
  przy waronku, ze poprzedni wierzcholek nie jest 0
 *
 */
std::string wypisz_trase(std::map<int, int>& poprzedniki, int& wierzcholek);

/**
@brief  Funkja do odznalezienia najblizszego wierzcholka. Pszypisaanie poczatkowych wartosci do dystansu(INFINITY), a do pierwszego wierzcholka (0).
 * Dopoki wierzcholki sa odczytywane z kolejki, idzie porownanie kazdego dystansu, aby odszukac naijmniejszy z nich.
 * Koniecznie jest odznaleziony wierzcholek o najkrotszym dystansie 
 *
 * @param kolejka_wierzcholkow rozpatrywane wierzcholki 
 * @param dystans dystans do wierzcholkow
 * @return zwaraca naimniejszy wierzcholek
 * 
 * @brief  Funkja do odznalezienia najblizszego wierzcholka. Pszypisaanie poczatkowych wartosci do dystansu(INFINITY), a do pierwszego wierzcholka (0).
 * Dopoki wierzcholki sa odczytywane z kolejki, idzie porownanie kazdego dystansu, aby odszukac naijmniejszy z nich.
 * Koniecznie jest odznaleziony wierzcholek o najkrotszym dystansie 
 */
int znajdz_najblizszy_wierzcholek(std::set<int>& kolejka_wierzcholkow, std::map<int, double>& dystans);

#endif


