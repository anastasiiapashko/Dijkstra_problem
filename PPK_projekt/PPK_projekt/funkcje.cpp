//#include <iostream>
//#include <random>
//#include <chrono>
//#include <fstream>
//#include <vector>
//#include <map>
//#include <cmath>
#include "funkcje.h"
//#include <set>

bool odczytaj_graf(std::string nazwa_pliku, std::vector<krawedz> * krawedzie, std::set<int> * wierzcholki) { //funkcja  dla isniejacego pliku
	std::ifstream plik;    //do odczytu pliku
	plik.open(nazwa_pliku.c_str());  //otwieranie pliku
	if (!plik.good())       //Czy udało otworzyć się plik 
		return false;
	while (true)            //do poki mozemy go otworzyc
	{
		int a = 0;   //przypisanie wierzcholka pierwszego
		std::string b; //przypisanie znaku "->"
		int c = 0;           //przypisanie wierzcholka drugiego
		std::string d;   //przypisanie znaku ":"
		double waga = 0.0;     //przypisanie wagi
		plik >> a >> b >> c >> d >> waga;
		if (plik.fail())
			break; //zakończ wczytywanie danych -  nie ma więcej danych w pliku)
		

		if (b == "->") {                             //tu sprawdzamy czy jest krawędź skierowana, czy nie
			dodaj_krawedz(a, c, waga, krawedzie);
			wierzcholki->insert(a);
			wierzcholki->insert(c);
		}
		else if (b == "-") {
			
			dodaj_krawedz(a, c, waga, krawedzie);
			dodaj_krawedz(c, a, waga, krawedzie);
			wierzcholki->insert(a);
			wierzcholki->insert(c);
		}
		else {
			std::cout << "Nieprawidłowo wprowadzone dane!";
		}
	}

	plik.close();

	return true;
}


void dodaj_krawedz(int poczatek, int koniec, double waga, std::vector<krawedz>* krawedzie)
{
	krawedz naszaKrawedz;
	naszaKrawedz.nr_wierz_poczatkowy = poczatek;
	naszaKrawedz.nr_wierz_koncowy = koniec;
	naszaKrawedz.waga = waga;
	krawedzie->push_back(naszaKrawedz); //pusz_back -> dodajemy do wektora nową krawedź (zwiększamy jesgo rozmiar)
}


bool wierzchowce(std::string nazwa_pliku, std::set<int>* wierzcholki) {  //set to jest zbior unikatowych wartosci
	std::ifstream plik;													//do odczytu pliku
	plik.open(nazwa_pliku.c_str());										//otwieranie pliku
	if (!plik.good())													//Czy udało otworzyć się plik 
		return false;	
	while (true)														//do poki mozemy go otworzyc
	{
		int wieszcholek_z_pliku = 0;									//przypisanie wierzcholka
		plik >> wieszcholek_z_pliku;
		if (plik.fail())
			break;														//zakończ wczytywanie danych -  nie ma więcej danych w pliku)

		wierzcholki->insert(wieszcholek_z_pliku);						 //dodajemy do wektora nową krawedź (zwiększamy jesgo rozmiar)
	}

	plik.close();

	return true;
}


std::string szukanie_tras(std::set<int> * zbior_wierzcholkow, std::vector<krawedz>* zbior_krawedzi, int poczatkowy_wierzcholek) {
	std::map<int, double> dystans = std::map<int, double>(); //map dziala jak vector, ale ma dwa parametry, gdzie pierwszy paramtr jest unikatowy, a drugi moze sie powtarzac
	std::map<int, int> poprzedniki = std::map<int, int>();  //zbior poprzednikow wierzcholkow

	for (int wierzcholek : *zbior_wierzcholkow) {
		dystans.insert_or_assign(wierzcholek, INFINITY);
		poprzedniki.insert_or_assign(wierzcholek,0);
	}
	
	dystans.insert_or_assign(poczatkowy_wierzcholek, 0);

	std::set<int> sprawdzone = std::set<int>();    //zbior wierzcholkow sprawdzonych

	std::set<int> kolejka_wierzcholkow = std::set<int>(* zbior_wierzcholkow);//wyluskanie wartosci z pod wzkaznika na wierzcholki, robienie kopii do usuwania jej

	while (!kolejka_wierzcholkow.empty()) {

		int najmniejszy_wierzcholek = znajdz_najblizszy_wierzcholek(kolejka_wierzcholkow, dystans);

		if (najmniejszy_wierzcholek == 0) {
			break;
		}

		sprawdzone.insert(najmniejszy_wierzcholek);
		kolejka_wierzcholkow.erase(najmniejszy_wierzcholek);

		for (std::vector<krawedz>::iterator i = zbior_krawedzi->begin(); i != zbior_krawedzi->end(); i++) {
			krawedz kolejna_krawedz = *i;
			if (kolejna_krawedz.nr_wierz_poczatkowy == najmniejszy_wierzcholek) {
				//relaksacja
				if (dystans[kolejna_krawedz.nr_wierz_poczatkowy]+kolejna_krawedz.waga < dystans[kolejna_krawedz.nr_wierz_koncowy]) {
					dystans[kolejna_krawedz.nr_wierz_koncowy] = dystans[kolejna_krawedz.nr_wierz_poczatkowy] + kolejna_krawedz.waga;
					poprzedniki[kolejna_krawedz.nr_wierz_koncowy] = kolejna_krawedz.nr_wierz_poczatkowy;				
				}
			
			}
		}

	}


	std::string returned = "";

	returned += "Poczatkowy wierzcholek: " + std::to_string(poczatkowy_wierzcholek) + "\n";

	if (zbior_wierzcholkow->find(poczatkowy_wierzcholek) == zbior_wierzcholkow->end()) {
		returned += "brak wierzcholka "+  std::to_string(poczatkowy_wierzcholek)+ " w grafie\n";
	}
	else {

		for (int wierzcholek : *zbior_wierzcholkow) {

			if (wierzcholek != poczatkowy_wierzcholek)
			{

				std::stringstream ss;										//stworzymy sringsteam ss								
				ss << std::setprecision(4);									//ustalanie ile musi wypisac znakow w sringu
				ss << wypisz_trase(poprzedniki, wierzcholek);				//dodajemy do stringa wynik funkcji
				ss << " : ";												//dodajemy do stringa znak =>":"
				ss << dystans[wierzcholek];									//dodajemy do stringa dystans
				ss << "\n";													//dodajemy do stringa przejscie do nowej linijki

				std::string s = ss.str();									//przypisanie calego stringu do zmienej s typu string

				returned += s;												//doklejanie do konca stringu
			}


		}
	}

	return returned+"\n";
}


std::string wypisz_trase(std::map<int, int>& poprzedniki, int& wierzcholek)
{
	
	std::string trasa = "";
	if (poprzedniki[wierzcholek] != 0) {
		trasa = wypisz_trase(poprzedniki, poprzedniki[wierzcholek]) + " -> " + std::to_string(wierzcholek);
	}
	else {
		trasa = std::to_string(wierzcholek);
	}
	return trasa;

}

int znajdz_najblizszy_wierzcholek(std::set<int>& kolejka_wierzcholkow, std::map<int, double>& dystans)
{
	double najmniejszy_dystans = INFINITY;
	int najmniejszy_wierzcholek = 0;
	for (int wierzcholek : kolejka_wierzcholkow) {
		double kandydat = dystans[wierzcholek];                       // odczyt dystansu do wierzcholka
		if (kandydat < najmniejszy_dystans) {
			najmniejszy_dystans = kandydat;					// przypisanie mniejszego dystansu
			najmniejszy_wierzcholek = wierzcholek; // przypisanie mniejszeho wierzcholka 
		}
		
	}
	return najmniejszy_wierzcholek;
}