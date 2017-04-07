#pragma once

#include "QtLuis_Global.h"
#include <QString>

class QTLUISSHARED_EXPORT QtLuisEntity
{
public:
	QtLuisEntity();

	QtLuisEntity(const QtLuisEntity& src);
	QtLuisEntity& operator=(const QtLuisEntity& src);

	QString Entity;
	QString Type;
	int StartIndex;
	int EndIndex;
	double Score;
};