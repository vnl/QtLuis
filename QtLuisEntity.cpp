#include "QtLuisEntity.h"

QtLuisEntity::QtLuisEntity()
{

}

QtLuisEntity::QtLuisEntity(const QtLuisEntity& src) {

	if (&src != this) {
		*this = src;
	}
}

QtLuisEntity& QtLuisEntity::operator =(const QtLuisEntity& src)
{
	if (&src == this)
		return *this;

	this->Entity = src.Entity;
	this->Type = src.Type;
	this->StartIndex = src.StartIndex;
	this->EndIndex = src.EndIndex;
	this->Score = src.Score;

	return *this;
}