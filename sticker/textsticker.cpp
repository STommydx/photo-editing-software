#include "textsticker.h"

TextSticker::TextSticker(const QString &text, const QFont &font, const QColor &color) :
    textItem(text)
{
    textItem.setFont(font);
    textItem.setDefaultTextColor(color);
    transformHandler->init();
}

void TextSticker::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    textItem.paint(painter, option, widget);
}

QRectF TextSticker::boundingRect() const
{
    return textItem.boundingRect();
}

Sticker::Type TextSticker::getType() const
{
    return Sticker::Text;
}
