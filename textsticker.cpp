#include "textsticker.h"

TextSticker::TextSticker(const QString &text) :
    textItem(text)
{
    textItem.setFont(QFont("Times", 72, QFont::Bold));
}

void TextSticker::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    textItem.paint(painter, option, widget);
}

QRectF TextSticker::boundingRect() const
{
    return textItem.boundingRect();
}

