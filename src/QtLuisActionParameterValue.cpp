#include "QtLuisActionParameterValue.h"

QtLuisActionParameterValue::QtLuisActionParameterValue()
{

}

QtLuisActionParameterValue::QtLuisActionParameterValue(const QtLuisActionParameterValue& src) {

	if (&src != this) {
		*this = src;
	}
}

QtLuisActionParameterValue& QtLuisActionParameterValue::operator =(const QtLuisActionParameterValue& src)
{
	if (&src == this)
		return *this;

	this->Entity = src.Entity;
	this->Type = src.Type;
	this->Score = src.Score;

	return *this;
}