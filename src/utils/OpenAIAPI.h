//
// Created by Touka on 2023/12/6.
//

#ifndef OPENAIAPI_H
#define OPENAIAPI_H

#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QJsonDocument>
#include <QJsonObject>
#include <QEventLoop>
#include <QDebug>
#include <utility>

#include "async_simple/coro/Lazy.h"

namespace touka {

class OpenAIAPI {
private:
    const QString API_URL = "https://api.openai.com/v1/";
    const QString API_KEY;

public:
    explicit OpenAIAPI(QString  apiKey) : API_KEY(std::move(apiKey)) {}

    // [[nodiscard]] auto sendGetRequest(const QString &endpoint) const -> async_simple::coro::Lazy<QJsonObject> {
    //     QNetworkAccessManager manager;
    //     QNetworkRequest request;
    //
    //     // Setup URL and headers for request
    //     request.setUrl(QUrl(API_URL + endpoint));
    //     request.setRawHeader("Authorization", QString("Bearer " + API_KEY).toLocal8Bit());
    //
    //     // Send GET request and wait for reply
    //     std::unique_ptr<QNetworkReply> reply(manager.get(request));
    //     QEventLoop loop;
    //     QObject::connect(reply.get(), SIGNAL(finished()), &loop, SLOT(quit()));
    //     co_await loop.exec();
    //
    //     // Parse the JSON reply
    //     QJsonDocument document = QJsonDocument::fromJson(reply->readAll());
    //     QJsonObject json = document.object();
    //
    //     // Don't forget to handle possible errors
    //     if(reply->error() != QNetworkReply::NoError) {
    //         qDebug() << "API request error: " << reply->errorString();
    //     }
    //
    //     co_return json;
    // }
};

} // touka

#endif //OPENAIAPI_H
