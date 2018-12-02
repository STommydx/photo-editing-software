#ifndef IMGURWRAPPER_H
#define IMGURWRAPPER_H

#include <QObject>
#include <QImage>
#include <QNetworkAccessManager>

class ImgurWrapper : public QObject
{
    Q_OBJECT
public:
    explicit ImgurWrapper(QObject *parent = nullptr);
    void shareImage(const QImage &img, const QString &title = "My Awesome Photo!", const QString &desc = "- Powered by PES");

signals:
    void imageUploaded(QString imgId, QString imgLink);

public slots:

private:
    static const QUrl REQUEST_URL;
    static const QString CLIENT_ID;
    QNetworkAccessManager *accessManager; /**< @brief Pointer to network access manager */

};

#endif // IMGURWRAPPER_H
