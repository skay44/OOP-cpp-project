#pragma once
#include "Roslina.h"

class Mlecz : public Roslina {
private:
public:
	Mlecz(int x, int y);
	void znak(int wx, int wy) override;
	void akcja();
	void kolizja(Organizm* kolidowany);
	Roslina* stworz(Vector2 doStworzenia) override;
	std::string getNazwa() override;
};