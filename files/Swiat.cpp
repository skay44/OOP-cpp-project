#include "Vector2.h"

#include "Swiat.h"
#include "Organizm.h"

#include "Wilk.h"
#include "Owca.h"
#include "Lis.h"
#include "Zolw.h"
#include "Antylopa.h"

#include "Trawa.h"
#include "Mlecz.h"
#include "Guarana.h"
#include "WilczeJagody.h"
#include "BarszczSosnowskiego.h"

#include "Czlowiek.h"

#define WIDTH_X 2
#define WIDTH_Y 1
#define OFFSET_X 2
#define OFFSET_Y 2


void Swiat::gotoxy(int x, int y)
{
	COORD c;
	c.X = x;
	c.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);
}

Swiat::Swiat(int x, int y)
{
	rozmiar.x = x;
	rozmiar.y = y;
	zdolnosc = false;
	ruch = PASYWNY;
	czyNieskonczonyTekst = true;
	limitTekstu = 30;
}

Swiat::Swiat(Vector2& nowyRozmiar)
{
	rozmiar = nowyRozmiar;
	zdolnosc = false;
	ruch = PASYWNY;
	czyNieskonczonyTekst = true;
	limitTekstu = 30;
}

Swiat::Swiat(Vector2&& nowyRozmiar)
{
	rozmiar = nowyRozmiar;
	zdolnosc = false;
	ruch = PASYWNY;
	czyNieskonczonyTekst = true;
	limitTekstu = 30;
}

void Swiat::wykonajTure()
{
	wyniki = "";
	for (int inicjatywa = 7; inicjatywa >= 0; inicjatywa--)
	{
		std::list<Organizm*>::iterator iter = organizmy.begin();
		while (iter != organizmy.end())
		{
			Organizm* x = (*iter);
			if (x->isAlive())
			{
				if (x->getInicjatywa() == inicjatywa)
					x->akcja();
				iter++;
			}
			else
			{
				std::list<Organizm*>::iterator toremove = iter;
				iter++;
				organizmy.erase(toremove);
				//delete[] x;
			}
		}
	}
}

void Swiat::rysujSwiat()
{
	system("cls");
	rysujRamke();
	HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(out, FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED);
	for (int x = 0; x < rozmiar.x; x++)
	{
		for (int y = 0; y < rozmiar.y; y++)
		{
			gotoxy((x + OFFSET_X) * WIDTH_X, (y + OFFSET_Y) * WIDTH_Y);
			for (int i = 0; i < WIDTH_X; i++)
			{
				putchar(' ');
			}
		}
	}
	for (std::list<Organizm*>::iterator iter = organizmy.begin(); iter != organizmy.end(); iter++)
	{
		Organizm* x = (*iter);
		if (x->isAlive())
			x->rysowanie(WIDTH_X, WIDTH_Y, OFFSET_X, OFFSET_Y);
	}
}

void Swiat::rysujKonsole()
{
	HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(out, FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED);

	int ile = 0;
	bool first = true;
	gotoxy((rozmiar.x + OFFSET_X + 2) * WIDTH_X, OFFSET_Y - 1 + ile);
	for (char wynik : wyniki)
	{

		if (wynik == '\n')
		{
			ile++;
			gotoxy((rozmiar.x + OFFSET_X + 2) * WIDTH_X, OFFSET_Y - 1 + ile);
			first = true;
		}
		else
		{
			if (first == true)
			{
				std::cout << ile << ": ";
				first = false;
			}
			std::cout << wynik;
		}
		if (ile > limitTekstu && czyNieskonczonyTekst == false) break;
	}
}

void Swiat::wejscieZKlawiatury()
{
	zdolnosc = false;
	char x = 0;
	while (x != -32 && x != 32)
	{
		x = _getch();
		if (x == 'z')
		{
			zdolnosc = true;
		}
		if (x == 's')
		{
			zapis();
		}
		if (x == 'w')
		{
			wczytanie();
		}
		if (x == 'n')
		{
			nowy();
		}
	}
	if (x == -32)
	{
		x = _getch();
		if (x == 'H')//gora
			ruch = GORA;
		else if (x == 'P')//dol
			ruch = DOL;
		else if (x == 'K')//lewo
			ruch = LEWO;
		else if (x == 'M')//prawo
			ruch = PRAWO;
	}
	else
		ruch = PASYWNY;
}

bool Swiat::getZdolnosc()
{
	return zdolnosc;
}

int Swiat::getRuch()
{
	return ruch;
}

void Swiat::rysujRamke()
{
	HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(out, BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_RED);
	for (int x = 0; x < rozmiar.x + 2; x++)
	{
		gotoxy((x + OFFSET_X - 1) * WIDTH_X, (OFFSET_Y - 1) * WIDTH_Y);
		for (int i = 0; i < WIDTH_X; i++)
		{
			putchar(' ');
		}
	}
	for (int x = 0; x < rozmiar.x + 2; x++)
	{
		gotoxy((x + OFFSET_X - 1) * WIDTH_X, (rozmiar.y + OFFSET_Y) * WIDTH_Y);
		for (int i = 0; i < WIDTH_X; i++)
		{
			putchar(' ');
		}
	}
	for (int y = 0; y < rozmiar.y + 2; y++)
	{
		gotoxy((OFFSET_X - 1) * WIDTH_X, (y + OFFSET_Y - 1) * WIDTH_Y);
		for (int i = 0; i < WIDTH_X; i++)
		{
			putchar(' ');
		}
	}
	for (int y = 0; y < rozmiar.y + 2; y++)
	{
		gotoxy((rozmiar.x + OFFSET_X) * WIDTH_X, (y + OFFSET_Y - 1) * WIDTH_Y);
		for (int i = 0; i < WIDTH_X; i++)
		{
			putchar(' ');
		}
	}
}

bool Swiat::dodajOrganizm(Organizm* toAdd)
{
	Vector2 polozenie = toAdd->getPolozenie();
	bool czy_udane = true;
	for (std::list<Organizm*>::iterator iter = organizmy.begin(); iter != organizmy.end(); iter++)
	{
		Organizm* x = (*iter);
		if (x->isAlive() && x->getPolozenie() == polozenie)
			czy_udane = false;
	}
	if (czy_udane)
	{
		organizmy.push_back(toAdd);
		toAdd->setGlownySwiat(this);
		return true;
	}
	return false;
}

void Swiat::dodajLogi(std::string str)
{
	wyniki.append(str);
	wyniki.append("\n");
}

Vector2 Swiat::getRozmiar()
{
	return rozmiar;
}

std::list<Organizm*>& Swiat::getOrganizmy()
{
	return organizmy;
}

void Swiat::losujSwiat(Wlasciwosci wl)
{
	Vector2 doStworzenia;
	for (int i = 0; i < wl.antylopa;)
	{
		doStworzenia.x = rand() % rozmiar.x;
		doStworzenia.y = rand() % rozmiar.y;
		
		Antylopa* a;
		a = new Antylopa(doStworzenia.x,doStworzenia.y);
		if (dodajOrganizm(a)) i++;
	}
	for (int i = 0; i < wl.barszcz;)
	{
		doStworzenia.x = rand() % rozmiar.x;
		doStworzenia.y = rand() % rozmiar.y;

		BarszczSosnowskiego* a;
		a = new BarszczSosnowskiego(doStworzenia.x, doStworzenia.y);
		if (dodajOrganizm(a)) i++;
	}
	for (int i = 0; i < wl.czlowiek ? 1 : 0;)
	{
		doStworzenia.x = rand() % rozmiar.x;
		doStworzenia.y = rand() % rozmiar.y;

		Czlowiek* a;
		a = new Czlowiek(doStworzenia.x, doStworzenia.y);
		if (dodajOrganizm(a)) i++;
	}
	for (int i = 0; i < wl.guarana;)
	{
		doStworzenia.x = rand() % rozmiar.x;
		doStworzenia.y = rand() % rozmiar.y;

		Guarana* a;
		a = new Guarana(doStworzenia.x, doStworzenia.y);
		if (dodajOrganizm(a)) i++;
	}
	for (int i = 0; i < wl.jagody;)
	{
		doStworzenia.x = rand() % rozmiar.x;
		doStworzenia.y = rand() % rozmiar.y;

		WilczeJagody* a;
		a = new WilczeJagody(doStworzenia.x, doStworzenia.y);
		if (dodajOrganizm(a)) i++;
	}
	for (int i = 0; i < wl.lis;)
	{
		doStworzenia.x = rand() % rozmiar.x;
		doStworzenia.y = rand() % rozmiar.y;

		Lis* a;
		a = new Lis(doStworzenia.x, doStworzenia.y);
		if (dodajOrganizm(a)) i++;
	}
	for (int i = 0; i < wl.mlecz;)
	{
		doStworzenia.x = rand() % rozmiar.x;
		doStworzenia.y = rand() % rozmiar.y;

		Mlecz* a;
		a = new Mlecz(doStworzenia.x, doStworzenia.y);
		if (dodajOrganizm(a)) i++;
	}
	for (int i = 0; i < wl.owca;)
	{
		doStworzenia.x = rand() % rozmiar.x;
		doStworzenia.y = rand() % rozmiar.y;

		Owca* a;
		a = new Owca(doStworzenia.x, doStworzenia.y);
		if (dodajOrganizm(a)) i++;
	}
	for (int i = 0; i < wl.trawa;)
	{
		doStworzenia.x = rand() % rozmiar.x;
		doStworzenia.y = rand() % rozmiar.y;

		Trawa* a;
		a = new Trawa(doStworzenia.x, doStworzenia.y);
		if (dodajOrganizm(a)) i++;
	}
	for (int i = 0; i < wl.wilk;)
	{
		doStworzenia.x = rand() % rozmiar.x;
		doStworzenia.y = rand() % rozmiar.y;

		Wilk* a;
		a = new Wilk(doStworzenia.x, doStworzenia.y);
		if (dodajOrganizm(a)) i++;
	}
	for (int i = 0; i < wl.zolw;)
	{
		doStworzenia.x = rand() % rozmiar.x;
		doStworzenia.y = rand() % rozmiar.y;

		Zolw* a;
		a = new Zolw(doStworzenia.x, doStworzenia.y);
		if (dodajOrganizm(a)) i++;
	}
}

void Swiat::setLimit(int limit)
{
	if (limit > 0)
	{
		czyNieskonczonyTekst = false;
		limitTekstu = limit;
	}
	else
		czyNieskonczonyTekst = true;
}

void Swiat::zapis()
{
	system("cls");
	std::string nazwa;
	std::cout << "nazwa: ";
	std::cin >> nazwa;
	nazwa.append(".bin");

	std::ofstream file(nazwa);
	file.clear();

	file.write((char*)&rozmiar, sizeof(rozmiar));
	file.write((char*)&zdolnosc, sizeof(zdolnosc));
	file.write((char*)&ruch, sizeof(ruch));

	int identyfikator;

	for (std::list<Organizm*>::iterator iter = organizmy.begin(); iter != organizmy.end(); iter++)
	{
		Organizm* x = (*iter);

		if (true)
		{
			if (dynamic_cast<Zwierze*>(x))
			{
				identyfikator = 0;//zwierze
				file.write((char*)&identyfikator, sizeof(int));
			}
			else
			{
				identyfikator = 1;//roslina
				file.write((char*)&identyfikator, sizeof(int));
			}

			identyfikator = x->getID();//id zapisywanego obiektu
			file.write((char*)&identyfikator, sizeof(int));

			if(dynamic_cast<Czlowiek*>(x))
				file.write((char*)x, sizeof(Czlowiek));
			else if (dynamic_cast<Trawa*>(x))
				file.write((char*)x, sizeof(Trawa));
			else if (dynamic_cast<Mlecz*>(x))
				file.write((char*)x, sizeof(Mlecz));
			else if (dynamic_cast<Guarana*>(x))
				file.write((char*)x, sizeof(Guarana));
			else if (dynamic_cast<WilczeJagody*>(x))
				file.write((char*)x, sizeof(WilczeJagody));
			else if (dynamic_cast<BarszczSosnowskiego*>(x))
				file.write((char*)x, sizeof(BarszczSosnowskiego));
			else if (dynamic_cast<Antylopa*>(x))
				file.write((char*)x, sizeof(Antylopa));
			else if (dynamic_cast<Lis*>(x))
				file.write((char*)x, sizeof(Lis));
			else if (dynamic_cast<Owca*>(x))
				file.write((char*)x, sizeof(Owca));
			else if (dynamic_cast<Wilk*>(x))
				file.write((char*)x, sizeof(Wilk));
			else if (dynamic_cast<Zolw*>(x))
				file.write((char*)x, sizeof(Zolw));
		}
	}
	identyfikator = -1;//-1 oznacza koniec wczytywania
	file.write((char*)&identyfikator, sizeof(int));
	
	rysujSwiat();
	file.close();
}

void Swiat::wczytanie()
{
	system("cls");
	std::string nazwa;
	std::cout << "nazwa: ";
	std::cin >> nazwa;
	nazwa.append(".bin");

	std::ifstream file(nazwa);
	if (!file.good())
	{
		std::cout << "Zla nazwa!";
		_getch();
		rysujSwiat();
		rysujKonsole();
		return;
	}

	file.read((char*)&rozmiar, sizeof(rozmiar));
	file.read((char*)&zdolnosc, sizeof(zdolnosc));
	file.read((char*)&ruch, sizeof(ruch));

	organizmy.clear();
	
	while(true)
	{
		Organizm* wczytaj;
		int noweID;
		file.read((char*)&noweID, sizeof(int));
		if (noweID == -1)
			break;
		else if (noweID == 0)//zwierze
		{
			file.read((char*)&noweID, sizeof(int));
			if (noweID == 0)
			{
				Czlowiek* n;
				n = new Czlowiek(0, 0);
				file.read((char*)n, sizeof(Czlowiek));
				dodajOrganizm(n);
			}
			else if (noweID == 1)
			{
				Wilk* n;
				n = new Wilk(0, 0);
				file.read((char*)n, sizeof(Wilk));
				dodajOrganizm(n);
			}
			else if (noweID == 2)
			{
				Owca* n;
				n = new Owca(0, 0);
				file.read((char*)n, sizeof(Owca));
				dodajOrganizm(n);
			}
			else if (noweID == 3)
			{
				Lis* n;
				n = new Lis(0, 0);
				file.read((char*)n, sizeof(Lis));
				dodajOrganizm(n);
			}
			else if (noweID == 4)
			{
				Zolw* n;
				n = new Zolw(0, 0);
				file.read((char*)n, sizeof(Zolw));
				dodajOrganizm(n);
			}
			else if (noweID == 5)
			{
				Antylopa* n;
				n = new Antylopa(0, 0);
				file.read((char*)n, sizeof(Antylopa));
				dodajOrganizm(n);
			}
			else break;
		}
		else if (noweID == 1)//roslina
		{
			file.read((char*)&noweID, sizeof(int));
			if (noweID == 1)
			{
				Trawa* n;
				n = new Trawa(0, 0);
				file.read((char*)n, sizeof(Trawa));
				dodajOrganizm(n);
			}
			else if (noweID == 2)
			{
				Mlecz* n;
				n = new Mlecz(0, 0);
				file.read((char*)n, sizeof(Mlecz));
				dodajOrganizm(n);
			}
			else if (noweID == 3)
			{
				Guarana* n;
				n = new Guarana(0, 0);
				file.read((char*)n, sizeof(Guarana));
				dodajOrganizm(n);
			}
			else if (noweID == 4)
			{
				WilczeJagody* n;
				n = new WilczeJagody(0, 0);
				file.read((char*)n, sizeof(WilczeJagody));
				dodajOrganizm(n);
			}
			else if (noweID == 5)
			{
				BarszczSosnowskiego* n;
				n = new BarszczSosnowskiego(0, 0);
				file.read((char*)n, sizeof(BarszczSosnowskiego));
				dodajOrganizm(n);
			}
		}
	}

	rysujSwiat();
	file.close();
}

void Swiat::nowy()
{
	system("cls");
	organizmy.clear();

	int x, y, z;
	std::cout << "rozmiar x, rozmiar y, czy wybor wlasnosci : ";
	std::cin >> x >> y >> z;

	if (z == 0)
	{
		if (x < 10) x = 10;
		if (y < 10) y = 10;
	}

	rozmiar.x = x;
	rozmiar.y = y;

	Wlasciwosci wl;

	if (z == 0)
		wl = domysleWlasnosci();
	else
		wl = wczytajWlasnosci();

	losujSwiat(wl);
	rysujSwiat();
}

Swiat::Wlasciwosci Swiat::domysleWlasnosci()
{
	Wlasciwosci wl;
	wl.trawa = 15;
	wl.mlecz = 2;
	wl.guarana = 5;
	wl.jagody = 3;
	wl.barszcz = 3;
	wl.wilk = 5;
	wl.antylopa = 10;
	wl.lis = 10;
	wl.zolw = 10;
	wl.owca = 10;
	return wl;
}

Swiat::Wlasciwosci Swiat::wczytajWlasnosci()
{
	int x;
	Wlasciwosci wl;
	std::cout << "trawa: ";
	std::cin >> x;
	wl.trawa = x;
	std::cout << "mlecz: ";
	std::cin >> x;
	wl.mlecz = x;
	std::cout << "guarana: ";
	std::cin >> x;
	wl.guarana = x;
	std::cout << "jagody: ";
	std::cin >> x;
	wl.jagody = x;
	std::cout << "barszcz: ";
	std::cin >> x;
	wl.barszcz = x;
	std::cout << "wilk: ";
	std::cin >> x;
	wl.wilk = x;
	std::cout << "antylopa: ";
	std::cin >> x;
	wl.antylopa = x;
	std::cout << "lis: ";
	std::cin >> x;
	wl.lis = x;
	std::cout << "zolw: ";
	std::cin >> x;
	wl.zolw = x;
	std::cout << "owca: ";
	std::cin >> x;
	wl.owca = x;
	return wl;
}