//#include <iostream>  // input-output stream
//#include <fstream>   // file stream
//#include <sstream>   // string stream 
//#include <vector>
//#include <string>    // std::string
//#include <set>        // biblioteka do set

#include "funkcje.h"

#define _CRTDBG_MAP_ALLOC
#include <cstdlib>
#include <crtdbg.h>


int main(int argc, char* argv[]) {
	_CrtSetReportMode(_CRT_WARN, _CRTDBG_MODE_DEBUG);
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	std::string graf = "";
	std::string wierzcholki = "";
	std::string wyniki = "";

	if (argc != 7) {
		std::cout << "Aby poprawnie uzyc program prosze wprowadzic prawidlowa skladnie polecenia \nPPK_projekt.exe -g graf.txt -w wierzcholki.txt -o wyniki.txt";
		return -1;
	}
	for (int i = 1; i < argc; i+=2)	
	{

		std::string przelacznik = argv[i];
		std::string paramtr = argv[i+1];

		if (przelacznik == "-g") {                             
			graf = paramtr;
		}
		else if (przelacznik == "-w") {
			wierzcholki = paramtr;
		}
		else if(przelacznik == "-o") {
			wyniki = paramtr;

		}
		else {
			std::cout << "Aby poprawnie uzyc program prosze wprowadzic prawidlowa skladnie polecenia \nPPK_projekt.exe -g graf.txt -w wierzcholki.txt -o wyniki.txt";
			return -1;
		}

	}

	if (graf == "" || wierzcholki == "" || wyniki == "") {
		std::cout << "Aby poprawnie uzyc program prosze wprowadzic prawidlowa skladnie polecenia \nPPK_projekt.exe -g graf.txt -w wierzcholki.txt -o wyniki.txt";
		return -1;
	}

	std::vector<krawedz> * wskaznik_na_krawedzie = new std::vector<krawedz>(); //tworzenie nowego vektora
	std::set<int> * wskaznik_na_wierzcholki = new std::set<int>();//(wywołanie konstruktora)



	std::set<int> * wskaznik_na_poczatkowe_wierzcholki = new std::set<int>();//(wywołanie konstruktora)

	if (!odczytaj_graf(graf, wskaznik_na_krawedzie, wskaznik_na_wierzcholki)) {  //sprawdzenie, czy istnieje plik o nazwie krawedzi
		std::cout << "Nie udalo sie otworzyc pliku!" << std::endl;//jezeli nie ma to wypisuje sie komunikat "Nie udalo sie otworzyc pliku!"
		return -1;
	}
	if (!wierzchowce(wierzcholki, wskaznik_na_poczatkowe_wierzcholki)) { //sprawdzenie, czy istnieje plik o nazwie krawedzi
		std::cout << "Nie udalo sie otworzyc pliku!" << std::endl;//jezeli nie ma to wypisuje sie komunikat "Nie udalo sie otworzyc pliku!"
		return -1;
	}
	std::string trasy = "";
	for (std::set<int>::iterator i = wskaznik_na_poczatkowe_wierzcholki->begin(); i != wskaznik_na_poczatkowe_wierzcholki->end(); i++) {
		trasy += szukanie_tras(wskaznik_na_wierzcholki, wskaznik_na_krawedzie, *i);
			//poruszanie sie po liscie poczatkowych wierzcholkow i sprawdzanie dla nich najkrotrzej trasy
		
	}
	
	std::ofstream zapis(wyniki);

	zapis << trasy;

	zapis.close();

	delete wskaznik_na_wierzcholki;
	delete wskaznik_na_krawedzie;
	delete wskaznik_na_poczatkowe_wierzcholki;

	return 0;
}