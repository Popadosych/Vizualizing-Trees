#include "CustomQGraphicsScene.h"
#include <QPainter>

void CustomQGraphicsScene::mousePressEvent(QGraphicsSceneMouseEvent *mouseEvent)
{
    if (mouseEvent->button() == Qt::LeftButton)
    {

        QGraphicsItem *item = itemAt(mouseEvent->scenePos(), QTransform());
        UniVertex *vert = dynamic_cast<UniVertex *>(item);
        if(vert != nullptr)
        {
            emit sig(vert->value);

        } else{
            pressed = true;
            prev = mouseEvent->pos();
        }
    }

}

void CustomQGraphicsScene::mouseReleaseEvent(QGraphicsSceneMouseEvent *event){

}