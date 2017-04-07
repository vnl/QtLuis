#include "QtLuisAction.h"

QtLuisAction::QtLuisAction()
{

}

QtLuisAction::QtLuisAction(const QtLuisAction& src) {

	if (&src != this) {
		*this = src;
	}
}

QtLuisAction& QtLuisAction::operator =(const QtLuisAction& src)
{
	if (&src == this)
		return *this;

	this->Triggered = src.Triggered;
	this->Name = src.Name;
	this->Parameters = src.Parameters;

	return *this;
}
