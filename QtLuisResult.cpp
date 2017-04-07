#include "QtLuisResult.h"

QtLuisResult::QtLuisResult()
{

}

QtLuisResult::QtLuisResult(const QtLuisResult& src) {

	if (&src != this) {
		*this = src;
	}
}

QtLuisResult& QtLuisResult::operator =(const QtLuisResult& src)
{
	if (&src == this)
		return *this;

	this->Query = src.Query;
	this->Intents = src.Intents;
	this->Entities = src.Entities;

	return *this;
}