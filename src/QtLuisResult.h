#pragma once

#include "QtLuis_Global.h"
#include <QString>
#include <QVector>
#include "QtLuisIntent.h"
#include "QtLuisEntity.h"

class QTLUISSHARED_EXPORT QtLuisResult
{

public:
	QtLuisResult();

	QtLuisResult(const QtLuisResult& src);
	QtLuisResult& operator=(const QtLuisResult& src);


	QString Query;
	QVector<QtLuisIntent> Intents;
	QVector<QtLuisEntity> Entities;
};
