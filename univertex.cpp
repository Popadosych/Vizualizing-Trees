#include "univertex.h"

UniVertex::UniVertex()
{

}

QRectF UniVertex::boundingRect() const {

    return QRectF(0, 0, width, height);
}


void UniVertex::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget){
    Q_UNUSED(option);  Q_UNUSED(widget);
    if(color == 0){
        br->setColor("Grey");
    }
    if(color == 1){
        br->setColor("Red");
    }
    if(color == 2){
        br->setColor("Green");
    }
    if(color == 3){
        br->setColor("#FEA000");
    }
    painter->setBrush(*br);
    painter->drawRoundedRect(0, 0, width, height, 2, 2);
    QFont fnt;
    fnt.setPixelSize(width / 5);
    if(color == 0){
        br->setColor("Red");
        painter->setBrush(*br);
    }
    painter->setFont(fnt);
    painter->drawText(QRect(0, 0, width, height), Qt::AlignCenter, QString::number(value));//this->value));

}