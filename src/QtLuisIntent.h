#pragma once

#include "QtLuis_Global.h"
#include <QString>
#include "QtLuisAction.h"

class QTLUISSHARED_EXPORT QtLuisIntent
{
public:
	QtLuisIntent();

	QtLuisIntent(const QtLuisIntent& src);
	QtLuisIntent& operator=(const QtLuisIntent& src);

	QString Intent;
	double Score;

	QVector<QtLuisIntent> Actions;
};
