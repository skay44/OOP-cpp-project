#pragma once
#include "Organizm.h"

Organizm::Organizm(int x, int y) {
	polozenie.x = x;
	polozenie.y = y;
	dead = false;
}

Organizm::Organizm(Vector2& nowePolozenie) {
	polozenie = nowePolozenie;
	dead = false;
}

Organizm::Organizm(Vector2&& nowePolozenie) {
	polozenie = nowePolozenie;
	dead = false;
}

Vector2 Organizm::getPolozenie()
{
	return polozenie;
}

void Organizm::setGlownySwiat(Swiat* nowyGlownySwiat)
{
	glownySwiat = nowyGlownySwiat;
}

void Organizm::setPolozenie(Vector2 nowePolozenie)
{
	polozenie = nowePolozenie;
}

int Organizm::getSila()
{
	return sila;
}
int Organizm::getInicjatywa()
{
	return inicjatywa;
}
void Organizm::kill()
{
	if (dead == false)
	{
		glownySwiat->dodajLogi(getNazwa() +
			" [" + std::to_string(getPolozenie().x) + "," + std::to_string(getPolozenie().y) +
			"] umiera"
		);
		dead = true;
	}
}
bool Organizm::isAlive()
{
	return !dead;
}
Swiat* Organizm::getGlownySwiat()
{
	return glownySwiat;
}
int Organizm::getID()
{
	return id;
}

void Organizm::rysowanie(int widthX, int widthY, int offsetX, int offsetY)
{
	glownySwiat->gotoxy((polozenie.x + offsetX) * widthX, (polozenie.y + offsetY) * widthY);
	znak(widthX,widthY);
}

void Organizm::setSila(int nowaSila){
	sila = nowaSila;
}


