#include <QGraphicsScene>
#include <univertex.h>
#include <QPoint>
#include <QGraphicsSceneMouseEvent>
#include <QMouseEvent>
#include <QGraphicsItem>
class CustomQGraphicsScene : public QGraphicsScene
{

    Q_OBJECT

            signals:
            void sig(int);
protected:
    bool pressed = false;
    QPointF prev;
    void mousePressEvent(QGraphicsSceneMouseEvent *mouseEvent);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);

};