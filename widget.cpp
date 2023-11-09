#include "widget.h"
#include "ui_widget.h"

using namespace std;

Widget::Widget(QWidget *parent)
        : QWidget(parent),
          ui(new Ui::Widget)
{

    ui->setupUi(this);
    setFixedSize(1300, 750);
    setWindowTitle(QString("Trees"));

    mainScene = new CustomQGraphicsScene();

    mainScene->setBackgroundBrush(QColor(255, 255, 255));
    mainCanvas = new QGraphicsView(mainScene);

    connect(mainScene,SIGNAL(sig(int)), this, SLOT(delete_elem(int)));
    mainFont = QFont("Arial", 12, QFont::Bold);
    mainPen = QPen(Qt::black, 3);
    atree = AVL_tree();
    dtree = Dekart_tree();
    rbtree = nullptr;

    add = new QPushButton("Add");
    add->setFont(mainFont);
    add->setStyleSheet("background-color: rgb(255, 255, 255);");
    connect(add, SIGNAL(clicked()), this, SLOT(addElem()));

    rand_but = new QPushButton("Add some rand");
    rand_but->setFont(mainFont);
    rand_but->setStyleSheet("background-color: rgb(255, 255, 255);");
    connect(rand_but, SIGNAL(clicked()), this, SLOT(addRand()));

    clear = new QPushButton("Clear tree");
    clear->setFont(mainFont);
    clear->setStyleSheet("background-color: rgb(255, 255, 255);");
    connect(clear, SIGNAL(clicked()), this, SLOT(clearTree()));

    del = new QPushButton("Delete vertex");
    del->setFont(mainFont);
    del->setStyleSheet("background-color: rgb(255, 255, 255);");
    connect(del, SIGNAL(clicked()), this, SLOT(delElem()));

    horizontal_slider = new QSlider(Qt::Horizontal);

    combo_box = new QComboBox();
    combo_box->addItem("AVL Tree");
    combo_box->addItem("Dekart Tree");
    combo_box->addItem("Red-Black Tree");
    combo_box->setFont(mainFont);
    connect(combo_box, SIGNAL(currentTextChanged(const QString&)), this, SLOT(on_combo_wombo_curentTextChanged(const QString&)));


    vertex = new QLineEdit;
    vertex->setFont(mainFont);
    vertex->setMaxLength(10);
    quant = new QLineEdit;
    quant->setFont(mainFont);
    quant->setMaxLength(10);
    delline = new QLineEdit;
    delline->setFont(mainFont);
    delline->setMaxLength(10);


    // Widgets
    auto mainLayout = new QGridLayout;
    mainLayout->addWidget(mainCanvas, 5, 0, 100, 100);
    mainLayout->addWidget(vertex, 20, 100, 5, 10);
    mainLayout->addWidget(add, 25, 100, 10, 10);
    mainLayout->addWidget(quant, 40, 100, 5, 10);
    mainLayout->addWidget(rand_but, 45, 100, 10, 10);
    mainLayout->addWidget(delline, 60, 100, 5, 10);
    mainLayout->addWidget(del, 65, 100, 10, 10);
    mainLayout->addWidget(clear, 80, 100, 10, 10);
    mainLayout->addWidget(horizontal_slider, 90, 100, 10, 10);
    mainLayout->addWidget(combo_box, 5, 100, 15, 10);
    this->setLayout(mainLayout);
}

void Widget::addElem() {
    int key;
    try {
        key = vertex->text().toInt();
    }
    catch(...) {
        return;
    }
    try {
        if (!atree._checker(atree.get_tree(), key)) return;
        atree.insert(key);
        Node* new_node = new Node(key);
        Node* res = dtree.insert(dtree.get_tree(), new_node);
        dtree.root = res;
        rbtree->insert(rbtree, key);
    }
    catch(std::invalid_argument) {
        return;
    }
    renderTree();
    auto e = combo_box->currentText();
    if (e == "AVL Tree") renderLines(atree.get_tree());
    else if (e == "Dekart Tree") renderLines(dtree.get_tree());
    else if (e == "Red-Black Tree") renderLines_RBT(rbtree);
}

void Widget::addRand() {
    int n;
    int left = 1, right = 20000000;
    try {
        n = quant->text().toInt();
    }
    catch(...) {
        return;
    }
    for (int i = 0; i < n; ++i) {
        int key = (rand() % right + left) % right;
        while (!atree._checker(atree.root, key)) {
            key = (rand() % right + left) % right;
        }
        try {
            atree.insert(key);
            Node* new_node = new Node(key);
            Node* res = dtree.insert(dtree.get_tree(), new_node);
            dtree.root = res;
            rbtree->insert(rbtree, key);
        }
        catch(std::invalid_argument) {
            return;
        }
    }
    renderTree();
    auto e = combo_box->currentText();
    if (e == "AVL Tree") renderLines(atree.get_tree());
    else if (e == "Dekart Tree") renderLines(dtree.get_tree());
    else if (e == "Red-Black Tree") renderLines_RBT(rbtree);
}

void Widget::delElem() {
    int key;
    try {
        key = delline->text().toInt();
    }
    catch(...) {
        return;
    }
    delete_elem(key);
}

void Widget::delete_elem(int key) {
    if (atree.height() == 1) {
        clearTree();
        return;
    }
    atree.remove(key);
    rbtree->erase(rbtree, key);
    Node* res;
    if (dtree.get_tree()->key == key) {
        res = dtree.erase(dtree.get_tree(), key);
    }
    else {
        res = dtree.erase(dtree.get_tree(), key);
    }
    dtree.root = res;
    renderTree();
    auto e = combo_box->currentText();
    if (e == "AVL Tree") renderLines(atree.get_tree());
    else if (e == "Dekart Tree") renderLines(dtree.get_tree());
    else if (e == "Red-Black Tree") renderLines_RBT(rbtree);
}

void Widget::clearTree() {
    mainScene->clear();
    mainScene->update();
    atree.clear();
    dtree.clear();
    rbtree->clear(rbtree);
    rbtree = nullptr;
}

void Widget::renderTree() {
    mainScene->clear();
    mainScene->update();
    auto mode = combo_box->currentText();
    if (mode == "AVL Tree") {
        int prev = 0;
        for (auto elem = atree.begin(); elem != atree.end(); elem = elem->next()) {
            auto x = prev++ * 150;
            auto y = elem->height * 150;
            auto xe = x - 15 - 5 * (10 - QString::number(elem->key).size());
            elem->high = {xe+125, y};
            elem->low = {xe+125, y + 30};

            auto e = new UniVertex(150, 30);
            e->color = 2;
            e->value = elem->key;


            e->setX(x);
            e->setY(y);
            e->setZValue(1000);
            mainScene->addItem(e);
        }
    } else if (mode == "Dekart Tree") {
        int prev = 0;
        for (auto elem = dtree.begin(); elem != dtree.end(); elem = elem->next()) {
            auto x = prev++ * 150;
            auto y = elem->height * 150;
            auto xe = x - 15 - 5 * (10 - QString::number(elem->key).size());
            elem->high = {xe+125, y};
            elem->low = {xe+125, y + 30};

            auto e = new UniVertex(150, 30);
            e->color = 3;
            e->value = elem->key;

            e->setX(x);
            e->setY(y);
            e->setZValue(1000);
            mainScene->addItem(e);
        }
    } else if (mode == "Red-Black Tree") {
        if (rbtree == nullptr) return;
        int prev = 0;
        rbtree->par = nullptr;
        rbtree->recountParents(rbtree);
        for (auto elem = rbtree->begin(); elem != nullptr; elem = elem->next(elem)) {
            auto x = prev++ * 150;
            auto y = elem->height_ * 150;
            auto xe = x - 15 - 5 * (10 - QString::number(elem->elem()).size());
            elem->high = {xe+125, y};
            elem->low = {xe+125, y + 30};

            auto e = new UniVertex(150, 30);
            if (elem->red()) e->color = 1;
            else e->color = 0;
            e->value = elem->elem();

            e->setX(x);
            e->setY(y);
            e->setZValue(1000);
            mainScene->addItem(e);
        }
    }
}

void Widget::renderLines(Node* p) {
    if (p == nullptr) {
        return;
    }
    if (p->left != nullptr) {
        QLine l = QLine(p->low, p->left->high);

        mainScene->addLine(l, mainPen);
    }
    if (p->right != nullptr) {
        QLine l = QLine(p->low, p->right->high);
        mainScene->addLine(l, mainPen);
    }
    renderLines(p->left);
    renderLines(p->right);
}

void Widget::renderLines_RBT(RBT* p) {
    if (p == nullptr) {
        return;
    }
    if (p->left != nullptr) {
        QLine l = QLine(p->low, p->left->high);
        mainScene->addLine(l, mainPen);
    }
    if (p->right != nullptr) {
        QLine l = QLine(p->low, p->right->high);
        mainScene->addLine(l, mainPen);
    }
    renderLines_RBT(p->left);
    renderLines_RBT(p->right);
}

void Widget::on_combo_wombo_curentTextChanged(const QString &arg1) {
    renderTree();
    if (arg1 == "Dekart Tree" && dtree.get_tree() != nullptr) renderLines(dtree.get_tree());
    if (arg1 == "AVL Tree" && atree.get_tree() != nullptr) renderLines(atree.get_tree());
    if (arg1 == "Red-Black Tree" && rbtree != nullptr) renderLines_RBT(rbtree);
}



Widget::~Widget()
{
    delete ui;
}
