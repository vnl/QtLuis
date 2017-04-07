#include "QtLuisActionParameter.h"

QtLuisActionParameter::QtLuisActionParameter()
{

}

QtLuisActionParameter::QtLuisActionParameter(const QtLuisActionParameter& src) {

	if (&src != this) {
		*this = src;
	}
}

QtLuisActionParameter& QtLuisActionParameter::operator =(const QtLuisActionParameter& src)
{
	if (&src == this)
		return *this;

	this->Name = src.Name;
	this->Required = src.Required;
	this->Value = src.Value;

	return *this;
}