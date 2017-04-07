#pragma once

#include "QtLuis_Global.h"
#include <QString>

class QTLUISSHARED_EXPORT QtLuisActionParameterValue
{
public:
	QtLuisActionParameterValue();

	QtLuisActionParameterValue(const QtLuisActionParameterValue& src);
	QtLuisActionParameterValue& operator=(const QtLuisActionParameterValue& src);

	QString Entity;
	QString Type;
	double Score;
};