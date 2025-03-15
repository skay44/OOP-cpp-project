#pragma once
#include "Roslina.h"

class WilczeJagody : public Roslina {
private:
public:
	WilczeJagody(int x, int y);
	void znak(int wx, int wy) override;
	void akcja();
	void kolizja(Organizm* kolidowany);
	Roslina* stworz(Vector2 doStworzenia) override;
	std::string getNazwa() override;
	void attackedBy(Organizm* kolidowany) override;
};