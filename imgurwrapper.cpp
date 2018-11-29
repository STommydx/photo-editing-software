#include <QBuffer>
#include <QByteArray>
#include <QHttpPart>
#include <QHttpMultiPart>
#include <QNetworkReply>
#include <QJsonDocument>
#include <QJsonObject>
#include <QMessageBox>

#include "imgurwrapper.h"

const QUrl ImgurWrapper::REQUEST_URL = QUrl("https://api.imgur.com/3/image");
const QString ImgurWrapper::CLIENT_ID = "eed9c72ff20420d";

ImgurWrapper::ImgurWrapper(QObject *parent) :
    QObject(parent),
    accessManager(new QNetworkAccessManager(this))
{

}

void ImgurWrapper::shareImage(const QImage &img, const QString &title, const QString &desc)
{
    QByteArray byteData;
    QBuffer buffer(&byteData);

    buffer.open(QIODevice::WriteOnly);
    img.save(&buffer, "JPG");

    QNetworkRequest request{REQUEST_URL};
    request.setRawHeader("Authorization", QString{"Client-ID " + CLIENT_ID}.toUtf8());

    QHttpMultiPart *multipart = new QHttpMultiPart(QHttpMultiPart::FormDataType);

    QHttpPart titlePart;
    titlePart.setHeader(QNetworkRequest::ContentTypeHeader, QVariant("text/plain"));
    titlePart.setHeader(QNetworkRequest::ContentDispositionHeader, QVariant("form-data; name=\"title\""));
    titlePart.setBody(title.toUtf8());
    multipart->append(titlePart);

    QHttpPart descPart;
    descPart.setHeader(QNetworkRequest::ContentTypeHeader, QVariant("text/plain"));
    descPart.setHeader(QNetworkRequest::ContentDispositionHeader, QVariant("form-data; name=\"description\""));
    descPart.setBody(desc.toUtf8());
    multipart->append(descPart);

    QHttpPart imagePart;
    imagePart.setHeader(QNetworkRequest::ContentTypeHeader, QVariant("image/jpeg"));
    imagePart.setHeader(QNetworkRequest::ContentDispositionHeader, QVariant("form-data; name=\"image\""));
    imagePart.setBody(byteData);
    multipart->append(imagePart);

    QNetworkAccessManager *accessManager = new QNetworkAccessManager(this);
    QNetworkReply *reply = accessManager->post(request, multipart);
    multipart->setParent(reply);

    connect(reply, &QNetworkReply::finished, [=](){
        QByteArray response = reply->readAll();
        reply->deleteLater();

        if (reply->error() != QNetworkReply::NoError) {
            QMessageBox::critical(nullptr, "Upload Fail: " + reply->errorString(), response);
            return;
        }

        QJsonDocument json = QJsonDocument::fromJson(response);
        QJsonObject jsonObj = json.object();
        QJsonObject dataObj = jsonObj.value("data").toObject();

        QString photoId = dataObj.value("id").toString();
        QString photoLink = dataObj.value("link").toString();

        emit imageUploaded(photoId, photoLink);

    });


}
