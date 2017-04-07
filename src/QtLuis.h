#ifndef QTLUIS_H
#define QTLUIS_H

#include "QtLuis_Global.h"
#include "QtLuisResult.h"
#include <QObject>
#include <QString>

using namespace std;

class QTLUISSHARED_EXPORT QtLuis : QObject
{
	Q_OBJECT
	Q_CLASSINFO("author", "Vivian Lobo")

public:
	QtLuis(QString ModelID, QString SubscriptionKey);
	QtLuisResult* Call(QString query);

private:

	QString subscription_key;
	QString model_id;
	const static QString Endpoint;
};

#endif // QTLUIS_H
