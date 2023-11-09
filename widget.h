#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QLabel>
#include <set>
#include <QPoint>
#include <QKeyEvent>
#include <QTextEdit>
#include <QLineEdit>
#include <QGridLayout>
#include <QLabel>
#include <QPushButton>
#include <QString>
#include <stdexcept>
#include <QString>
#include <QKeyEvent>
#include <QGraphicsView>
#include <QGraphicsEllipseItem>
#include <QGraphicsTextItem>
#include <QComboBox>
#include <QSet>
#include <QPoint>
#include <QSlider>
#include <CustomQGraphicsScene.h>
#include <univertex.h>
#include <utility>
#include <bits/stdc++.h>
#include <rbt.h>
#include <dekart_avl_trees.h>



namespace Ui{
    class Widget;
}


class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = nullptr);
    ~Widget();
    void renderTree();
    void renderLines(Node* p);
    void renderLines_RBT(RBT* p);
    CustomQGraphicsScene* scene;

public slots:
            void addElem();
    void addRand();
    void clearTree();
    void delElem();
    void delete_elem(int);
    void on_combo_wombo_curentTextChanged(const QString &arg1);

private:
    AVL_tree atree;
    Dekart_tree dtree;
    RBT* rbtree;
    QFont mainFont;
    QPen mainPen;
    QLineEdit *vertex, *quant, *delline;
    QPushButton *add, *clear, *rand_but, *del;
    QGraphicsView* mainCanvas;
    CustomQGraphicsScene* mainScene;
    QSlider* horizontal_slider;
    QComboBox* combo_box;
    Ui::Widget *ui;
};


#endif