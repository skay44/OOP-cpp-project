#pragma once
#include "Organizm.h"
#include "Vector2.h"


class Zwierze : public Organizm {
protected:
	int zasieg;
	Vector2 nowePolozenie;
	void rozmnoz();
	void zmienPolozenie();

	bool ucieczka();
public:
	Zwierze(int x, int y);
	void akcja() override;
	void kolizja(Organizm* kolidowany) override;

	virtual void stworz(Vector2 doStworzenia) = 0;
	void zmienNowePolozenie(Vector2 np);

	bool niesmiertelnosc();
	void attackedBy(Organizm* kolidowany) override;
	virtual bool czy_ucieczka();
};