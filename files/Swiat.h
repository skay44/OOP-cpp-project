#pragma once
#include <fstream>
#include <iostream>
#include <Windows.h>
#include <string>
#include <conio.h>
#include <list>
#include <string>

class Organizm;

class Swiat {
private:
	std::string wyniki;
	std::list<Organizm*> organizmy;
	Vector2 rozmiar;
	bool zdolnosc;
	int ruch;

	void rysujRamke();
	bool czyNieskonczonyTekst;
	int limitTekstu;

	void zapis();
	void wczytanie();
	void nowy();
public:
	enum NR
	{
		PASYWNY,
		GORA,
		DOL,
		LEWO,
		PRAWO
	};

	struct Wlasciwosci {
		bool czlowiek;

		int wilk;
		int owca;
		int lis;
		int zolw;
		int antylopa;

		int trawa;
		int mlecz;
		int guarana;
		int jagody;
		int barszcz;

		Wlasciwosci()
		{
			czlowiek = true;

			wilk = 0;
			owca = 0;
			lis = 0;
			zolw = 0;
			antylopa = 0;

			trawa = 0;
			mlecz = 0;
			guarana = 0;
			jagody = 0;
			barszcz = 0;
		}
	};

	Swiat(int x, int y);
	Swiat(Vector2& nowyRozmiar);
	Swiat(Vector2&& nowyRozmiar);
	void gotoxy(int x, int y);

	void wejscieZKlawiatury();
	void wykonajTure();
	void rysujSwiat();
	void rysujKonsole();
	bool dodajOrganizm(Organizm* toAdd);
	void dodajLogi(std::string str);

	int getRuch();
	bool getZdolnosc();
	Vector2 getRozmiar();
	std::list<Organizm*>& getOrganizmy();

	void losujSwiat(Wlasciwosci wl);
	void setLimit(int limit);

	Wlasciwosci domysleWlasnosci();
	Wlasciwosci wczytajWlasnosci();
};
