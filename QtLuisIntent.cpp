#include "QtLuisIntent.h"

QtLuisIntent::QtLuisIntent()
{
}

QtLuisIntent::QtLuisIntent(const QtLuisIntent& src) {

	if (&src != this) {
		*this = src;
	}
}

QtLuisIntent& QtLuisIntent::operator =(const QtLuisIntent& src)
{
	if (&src == this)
		return *this;

	this->Intent = src.Intent;
	this->Score = src.Score;
	this->Actions = src.Actions;

	return *this;
}