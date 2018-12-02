/**
 * @class ImgurWrapper
 * @brief The ImgurWrapper class provides a wraper around the Imgur API
 *
 * This class wraps around the Imgur API so API calls can be done easily.
 */
#include <QBuffer>
#include <QByteArray>
#include <QHttpPart>
#include <QHttpMultiPart>
#include <QNetworkReply>
#include <QJsonDocument>
#include <QJsonObject>
#include <QMessageBox>

#include "imgurwrapper.h"

/**
 * @brief The request url.
 */
const QUrl ImgurWrapper::REQUEST_URL = QUrl("https://api.imgur.com/3/image");
/**
 * @brief The client id of the application
 */
const QString ImgurWrapper::CLIENT_ID = "eed9c72ff20420d";

/**
 * @brief Construct an ImgurWrapper with the given @a parent
 * @param parent the parent QObject
 */
ImgurWrapper::ImgurWrapper(QObject *parent) :
    QObject(parent), // parent constructor
    accessManager(new QNetworkAccessManager(this)) // instatiate network accesser
{

}

/**
 * @brief Share an image with a given title and description
 * @param img the image
 * @param title the title of the image
 * @param desc the description of the image
 */
void ImgurWrapper::shareImage(const QImage &img, const QString &title, const QString &desc)
{
    // byte array for storing the image
    QByteArray byteData;
    QBuffer buffer(&byteData);

    // save the image into the byte array
    buffer.open(QIODevice::WriteOnly);
    img.save(&buffer, "JPG");

    // initialize the request with the url and specific heafer
    QNetworkRequest request{REQUEST_URL};
    request.setRawHeader("Authorization", QString{"Client-ID " + CLIENT_ID}.toUtf8());

    // construct the payload
    QHttpMultiPart *multipart = new QHttpMultiPart(QHttpMultiPart::FormDataType);

    // title part of the payload
    QHttpPart titlePart;
    titlePart.setHeader(QNetworkRequest::ContentTypeHeader, QVariant("text/plain"));
    titlePart.setHeader(QNetworkRequest::ContentDispositionHeader, QVariant("form-data; name=\"title\""));
    titlePart.setBody(title.toUtf8());
    multipart->append(titlePart);

    // body part of the payload
    QHttpPart descPart;
    descPart.setHeader(QNetworkRequest::ContentTypeHeader, QVariant("text/plain"));
    descPart.setHeader(QNetworkRequest::ContentDispositionHeader, QVariant("form-data; name=\"description\""));
    descPart.setBody(desc.toUtf8());
    multipart->append(descPart);

    // image part of the payload
    QHttpPart imagePart;
    imagePart.setHeader(QNetworkRequest::ContentTypeHeader, QVariant("image/jpeg"));
    imagePart.setHeader(QNetworkRequest::ContentDispositionHeader, QVariant("form-data; name=\"image\""));
    imagePart.setBody(byteData);
    multipart->append(imagePart);

    // a post request!
    QNetworkReply *reply = accessManager->post(request, multipart);
    multipart->setParent(reply);

    // connect the reply handler to the signal
    connect(reply, &QNetworkReply::finished, [=](){
        QByteArray response = reply->readAll(); // read the reply
        reply->deleteLater(); // schedule deletion

        if (reply->error() != QNetworkReply::NoError) {
            QMessageBox::critical(nullptr, "Upload Fail: " + reply->errorString(), response); // prompt the user if upload fails
            return;
        }

        // parse the json response
        QJsonDocument json = QJsonDocument::fromJson(response);
        QJsonObject jsonObj = json.object();
        QJsonObject dataObj = jsonObj.value("data").toObject();

        QString photoId = dataObj.value("id").toString();
        QString photoLink = dataObj.value("link").toString();

        // emit uploaded signal
        emit imageUploaded(photoId, photoLink);

    });


}
