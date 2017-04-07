#pragma once

#include <QString>
#include <QVector>
#include "QtLuis_Global.h"
#include "QtLuisActionParameterValue.h"

class QTLUISSHARED_EXPORT QtLuisActionParameter
{
public:
	QtLuisActionParameter();

	QtLuisActionParameter(const QtLuisActionParameter& src);
	QtLuisActionParameter& operator=(const QtLuisActionParameter& src);

	QString Name;
	bool Required;
	QVector<QtLuisActionParameterValue> Value;
};
