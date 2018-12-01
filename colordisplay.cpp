/**
 * @class ColorDisplay
 * @brief The ColorDisplay class provides a simple @c QWidget for displaying and selecting colors.
 *
 */


#include "colordisplay.h"
#include <QColorDialog>

/**
 * @brief Construct a ColorDisplay with @c color.
 * @param color the default selected color
 * @param parent the parent QWidget
 */
ColorDisplay::ColorDisplay(QColor color, QWidget *parent) :
    QGraphicsView{parent},
    color{color}
{
    setScene(new QGraphicsScene(this)); // set an empty scene
    QBrush brush{color};
    setBackgroundBrush(brush); // display the color
}

/**
 * @brief Construct a ColorDisplay with default color.
 * @param parent the parent QWidget
 */
ColorDisplay::ColorDisplay(QWidget *parent) : ColorDisplay(Qt::magenta, parent) {}

/**
 * @brief Destruct the ColorDisplay widget.
 */
ColorDisplay::~ColorDisplay()
{
    delete scene();
}

/**
 * @brief Handles the action when the user clicks on the widget.
 *
 * The function opens a dialog for the user to choose a color, then set the widget to the color choosen.
 * It also emits ColorDisplay::colorChanged(QColor) signal.
 */
void ColorDisplay::mousePressEvent(QMouseEvent *)
{
    color = QColorDialog::getColor(color, this, "Color Picker"); // set the color from the color dialog
    QBrush brush{color};
    setBackgroundBrush(brush); // display the color
    emit colorChanged(color); // emit color change signal
}

/**
 * @brief Returns the color selected.
 * @return the color selected
 */
QColor ColorDisplay::getColor() const
{
    return color;
}

/**
 * @fn ColorDisplay::colorChanged(QColor color)
 * @brief The signal emitted when the selected color is changed.
 * @param color the new selected color
 */
