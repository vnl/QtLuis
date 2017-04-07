#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QDebug>
#include "QtLuis.h"
#include "WebClient.h"

const QString QtLuis::Endpoint = "your-endpoint"; //Change this

QtLuis::QtLuis(QString ModelID, QString SubscriptionKey)
{
	this->subscription_key = SubscriptionKey;
	this->model_id = ModelID;
}

QtLuisResult* QtLuis::Call(QString query)
{

	QtLuisResult* result = new QtLuisResult();
	WebClient* wc = new WebClient();
	wc->SetUserAgent("QtLuis 2.0");

	bool http_result = wc->get(this->Endpoint.arg(this->model_id).arg(this->subscription_key).arg(query));
	if (http_result)
	{
		QString content = wc->content();
		QJsonObject json;
		// qDebug() << content;

		QJsonDocument settdoc = QJsonDocument::fromJson(content.toUtf8());

		if (settdoc.isNull() || settdoc.isEmpty()) {
			qDebug() << "Malformed config Json!" << "\nLet you check Json validity\n\n";
			return NULL;
		}

		json = settdoc.object();

		if (!json.value("query").isNull() && !json.value("query").isUndefined() && json.value("query").isString()) {
			result->Query = json.value("query").toString();
		}

		if (!json.value("intents").isNull() && !json.value("intents").isUndefined() && json.value("intents").isArray()) {
			QJsonArray intents = json.value("intents").toArray();

			for (int i = 0; i < intents.size(); i++)
			{
				QJsonObject value = intents[i].toObject();

				QtLuisIntent intent;
				intent.Intent = value.take("intent").toString();
				intent.Score = value.take("score").toDouble();

				QJsonValue value_actions = value.take("actions");

				if (!value_actions.isNull() && !value_actions.isUndefined() && value_actions.isArray()) {

					QJsonArray actions = value_actions.toArray();
					for (int j = 0; j < actions.size(); j++)
					{
						QJsonObject value_action = actions[j].toObject();
						QtLuisAction action;
						action.Triggered = value_action.take("triggered").toBool();
						action.Name = value_action.take("name").toString();

						if (!value_action.value("parameters").isNull() && !value_action.value("parameters").isUndefined() && value_action.value("parameters").isArray())
						{
							QJsonArray array_actions_parameters = value_action.value("parameters").toArray();

							for (int k = 0; k < array_actions_parameters.size(); k++)
							{
								QJsonObject value_actions_parameters = array_actions_parameters[k].toObject();
								QtLuisActionParameter parameter;
								parameter.Name = value_actions_parameters.take("name").toString();
								parameter.Required = value_actions_parameters.take("required").toBool();

								if (!value_actions_parameters.value("value").isNull() && !value_actions_parameters.value("value").isUndefined() && value_actions_parameters.value("value").isArray()) {
									QJsonArray array_actions_parameters_values = value_actions_parameters.value("value").toArray();
									for (int h = 0; h < array_actions_parameters_values.size(); h++)
									{
										QJsonObject value_actions_parameters_value = array_actions_parameters_values[h].toObject();
										QtLuisActionParameterValue value;
										value.Entity = value_actions_parameters_value.take("entity").toString();
										value.Type = value_actions_parameters_value.take("type").toString();
										value.Score = value_actions_parameters_value.take("score").toDouble();
										parameter.Value.append(value);
									}
								}
								action.Parameters.append(parameter);
							}
						}
						intent.Actions.push_back(action);
					}
				}

				result->Intents.push_back(intent);
			}
		}

		if (!json.value("entities").isNull() && !json.value("entities").isUndefined() && json.value("entities").isArray()) {
			QJsonArray array = json.value("entities").toArray();

			for (int i = 0; i < array.size(); i++)
			{
				QJsonObject value = array[i].toObject();
				QtLuisEntity entity;

				entity.Entity = value.take("entity").toString();
				entity.Type = value.take("type").toString();
				entity.StartIndex = value.take("startIndex").toInt();
				entity.EndIndex = value.take("endIndex").toInt();
				entity.Score = value.take("score").toDouble();

				result->Entities.push_back(entity);

			}
		}

	}

	delete wc;

	return result;
}
