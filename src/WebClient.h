#pragma once

#include <QObject>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QTimer>
#include <QEventLoop>

class WebClient : public QObject
{
	Q_OBJECT
	Q_CLASSINFO("author", "Vivian Lobo")

public:
	WebClient();
	~WebClient();
	void SetUserAgent(QString value);
	bool get(QString url);
	bool post(QString url);

	QByteArray content();

	int timeout();
	void setTimeout(int value);
	QString error();

private:
	bool waitForConnect(QNetworkAccessManager *manager, int nTimeOutms = 0);

signals:
	void signalReadTimeout();

	private slots:
	void slotWaitTimeout();

private:
	QNetworkAccessManager* m_manager;
	QString m_userAgent;
	QEventLoop                  m_loop;
	QNetworkReply *             m_reply;
	QNetworkReply::NetworkError m_NetworkError;
	QString m_error;

	int m_timeout;
	bool m_bReadTimeOut;
	int m_nResponse;
	QString m_strResponse;
	QByteArray m_content;
};
