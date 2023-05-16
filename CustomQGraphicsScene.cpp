#include "CustomQGraphicsScene.h"
#include <QPainter>
#include <QDebug>

void CustomQGraphicsScene::mousePressEvent(QGraphicsSceneMouseEvent *mouseEvent)
{
    //qDebug() << "in";
    if (mouseEvent->button() == Qt::LeftButton)
    {

        QGraphicsItem *item = itemAt(mouseEvent->scenePos(), QTransform());// it is your clicked item, you can do everything what you want. for example send it somewhere
        UniVertex *vert = dynamic_cast<UniVertex *>(item);
        if(vert != nullptr)
        {
            qDebug() << "   eeeeell" << vert->value;
              emit sig(vert->value);
//            vert->br->setColor("yellow");

        } else{
            pressed = true;
            prev = mouseEvent->pos();
            qDebug() << "  notffsdfa ell" << mouseEvent->scenePos();
        }
    }

}

void CustomQGraphicsScene::mouseReleaseEvent(QGraphicsSceneMouseEvent *event){

}
