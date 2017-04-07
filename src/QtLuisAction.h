#pragma once
#include "QtLuisActionParameter.h"
#include "QtLuis_Global.h"
#include <QString>
#include <QVector>

class QTLUISSHARED_EXPORT QtLuisAction
{
public:
	QtLuisAction();

	QtLuisAction(const QtLuisAction& src);
	QtLuisAction& operator=(const QtLuisAction& src);


	bool Triggered;
	QString Name;

	QVector<QtLuisActionParameter> Parameters;
};
