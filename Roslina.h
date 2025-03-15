#pragma once
#include "Organizm.h"

class Roslina : public Organizm {
protected:
	int szansaZasiania;
public:
	Roslina(int x, int y);
	void akcja() override;
	void kolizja(Organizm* kolidowany) override;

	virtual Roslina* stworz(Vector2 doStworzenia) = 0;

	bool niesmiertelnosc();
	void attackedBy(Organizm* kolidowany) override;
};