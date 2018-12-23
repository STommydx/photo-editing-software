#ifndef IMAGEKERNEL_H
#define IMAGEKERNEL_H

#include <QVector>
#include <QColor>
#include <QImage>
#include <QObject>

class ImageKernel : public QObject
{
    Q_OBJECT
public:
    ImageKernel(int sizeX = 1, int sizeY = 1, QObject *parent = nullptr);
    ImageKernel(int size = 1, QObject *parent = nullptr);
    virtual ~ImageKernel() = default;
    QImage convolution(const QImage &img, bool normalized = true);

protected:
    int &data(int x, int y);

private:
    const int sizeX; /**< @brief The radius of the kernel x-dimension */
    const int sizeY; /**< @brief The radius of the kernel y-dimension */
    QVector<QVector<int>> mat; /**< @brief The 2D vector storing the matrix */
    inline QRgb convolution(const QImage &img, int x, int y, bool normalized = true);

signals:
    void progressUpdated(int progress);

};

#endif // IMAGEKERNEL_H
