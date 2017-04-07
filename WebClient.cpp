#include "WebClient.h"
#include <QDebug>

WebClient::WebClient()
{
	m_manager = new QNetworkAccessManager(this);
	m_userAgent = "";
	m_bReadTimeOut = false;
}

WebClient::~WebClient()
{
}

void WebClient::SetUserAgent(QString value)
{
	m_userAgent = value;
}

bool WebClient::get(QString url)
{
	QNetworkRequest request;
	request.setUrl(QUrl(url));
	request.setRawHeader("User-Agent", m_userAgent.toUtf8());

	request.setSslConfiguration(QSslConfiguration::defaultConfiguration());

	m_content = "";

	m_reply = m_manager->get(request);	

	if (!waitForConnect(m_manager, m_timeout))
	{
		qDebug() << "webfile::open(): timeout";
		m_NetworkError = QNetworkReply::TimeoutError;
		return false;
	}

	if (m_reply == NULL)
	{
		qDebug() << "webfile::open(): cancelled";
		m_NetworkError = QNetworkReply::OperationCanceledError;
		return false;
	}

	if (m_reply->error() != QNetworkReply::NoError)
	{
		qDebug() << "webfile::open(): error" << m_reply->errorString();
		m_NetworkError = m_reply->error();
		m_error = m_reply->errorString();
		return false;
	}

	m_nResponse = m_reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt();
	m_strResponse = m_reply->attribute(QNetworkRequest::HttpReasonPhraseAttribute).toString();

	//qDebug() << m_strResponse;
	if (m_nResponse == 200)
	{
		m_content = m_reply->readAll();
	}
	else
		return false;

	return true;
}

bool WebClient::post(QString url)
{
	QNetworkRequest request;
	request.setUrl(QUrl(url));
	request.setRawHeader("User-Agent", m_userAgent.toUtf8());

	m_content = "";

	m_reply = m_manager->get(request);
	
	if (!waitForConnect(m_manager, m_timeout))
	{
		qDebug() << "webfile::open(): timeout";
		m_NetworkError = QNetworkReply::TimeoutError;
		return false;
	}

	if (m_reply == NULL)
	{
		qDebug() << "webfile::open(): cancelled";
		m_NetworkError = QNetworkReply::OperationCanceledError;
		return false;
	}

	if (m_reply->error() != QNetworkReply::NoError)
	{
		qDebug() << "webfile::open(): error" << m_reply->errorString();
		m_NetworkError = m_reply->error();
		m_error = m_reply->errorString();
		return false;
	}

	m_nResponse = m_reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt();
	m_strResponse = m_reply->attribute(QNetworkRequest::HttpReasonPhraseAttribute).toString();

	//qDebug() << m_strResponse;
	if (m_nResponse == 200)
	{
		m_content = m_reply->readAll();
		//m_content = "{\"45\":\"unlimited\",\"47\":\"vodafone\",\"48\":\"vodafone unlimited\",\"236\":\"credito\"}";
	}
	else
		return false;

	return true;
}


bool WebClient::waitForConnect(QNetworkAccessManager *manager, int nTimeOutms)
{
	QTimer *timer = NULL;
	QEventLoop eventLoop;
	bool bReadTimeOut = false;

	m_bReadTimeOut = false;

	if (nTimeOutms > 0)
	{
		timer = new QTimer(this);

		connect(timer, SIGNAL(timeout()), this, SLOT(slotWaitTimeout()));
		timer->setSingleShot(true);
		timer->start(nTimeOutms);

		connect(this, SIGNAL(signalReadTimeout()), &eventLoop, SLOT(quit()));
	}

	// Wait on QNetworkManager reply here
	connect(manager, SIGNAL(finished(QNetworkReply *)), &eventLoop, SLOT(quit()));

	if (m_reply != NULL)
	{
		// Preferrably we wait for the first reply which comes faster than the finished signal
		connect(m_reply, SIGNAL(readyRead()), &eventLoop, SLOT(quit()));
	}
	eventLoop.exec();

	if (timer != NULL)
	{
		timer->stop();
		delete timer;
		timer = NULL;
	}

	bReadTimeOut = m_bReadTimeOut;
	m_bReadTimeOut = false;

	return !bReadTimeOut;
}

int WebClient::timeout()
{
	return m_timeout;
}

void WebClient::setTimeout(int value)
{
	m_timeout = value;
}

// Wait timeout
void WebClient::slotWaitTimeout()
{
	m_bReadTimeOut = true;  // Report timeout
	emit signalReadTimeout();
}

QByteArray WebClient::content()
{
	return m_content;

}

QString WebClient::error()
{
	return m_error;
}
