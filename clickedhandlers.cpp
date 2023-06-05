#include "mainwindow.h"
#include "ui_mainwindow.h"
void Arrowgame::handleupClicked(const QModelIndex &index)
{
    if (index.isValid()&& clickable == 'p') {
            int column = index.column();
            int width = 40 * column;
            QPoint Pos = ui->uparrows->pos();

            currindex = index;
            currar = 'u';

            ui->b1->move(Pos.x() + width - 40, Pos.y() - 40);
            ui->b2->move(Pos.x() + width, Pos.y() - 40);
            ui->b3->move(Pos.x() + width + 40, Pos.y() - 40);

            ui->b1->setIcon(QIcon("://images//left-down.png"));
            ui->b2->setIcon(QIcon("://images//down.png"));
            ui->b3->setIcon(QIcon("://images//right-down.png"));

            ui->b1->setVisible(true);
            ui->b2->setVisible(true);
            ui->b3->setVisible(true);

        }
}
void Arrowgame::handlerightClicked(const QModelIndex &index)
{
    if (index.isValid()&& clickable == 'p') {
            int row = index.row();
            int height = 40 * row;
            QPoint Pos = ui->rightarrows->pos();

            currindex = index;
            currar = 'r';

            ui->b1->move(Pos.x() +  40, Pos.y() + height - 40);
            ui->b2->move(Pos.x() + 40, Pos.y() + height);
            ui->b3->move(Pos.x() + 40, Pos.y() + height + 40);

            ui->b1->setIcon(QIcon("://images//left-up.png"));
            ui->b2->setIcon(QIcon("://images//left.png"));
            ui->b3->setIcon(QIcon("://images//left-down.png"));

            ui->b1->setVisible(true);
            ui->b2->setVisible(true);
            ui->b3->setVisible(true);

        }
}
void Arrowgame::handleleftClicked(const QModelIndex &index)
{
    if (index.isValid() && clickable == 'p') {
            int row = index.row();
            int height = 40 * row;
            QPoint Pos = ui->leftarrows->pos();

            currindex = index;
            currar = 'l';

            ui->b1->move(Pos.x() - 40, Pos.y() + height - 40);
            ui->b2->move(Pos.x() - 40, Pos.y() + height);
            ui->b3->move(Pos.x() - 40, Pos.y() + height + 40);

            ui->b1->setIcon(QIcon("://images//right-up.png"));
            ui->b2->setIcon(QIcon("://images//right.png"));
            ui->b3->setIcon(QIcon("://images//right-down.png"));

            ui->b1->setVisible(true);
            ui->b2->setVisible(true);
            ui->b3->setVisible(true);

        }
}
void Arrowgame::handledownClicked(const QModelIndex &index)
{
    if (index.isValid() && clickable == 'p') {
            int column = index.column();
            int width = 40 * column;
            QPoint Pos = ui->downarrows->pos();

            currindex = index;
            currar = 'd';

            ui->b1->move(Pos.x() + width - 40, Pos.y() + 40);
            ui->b2->move(Pos.x() + width, Pos.y() + 40);
            ui->b3->move(Pos.x() + width + 40, Pos.y() + 40);

            ui->b1->setIcon(QIcon("://images//left-up.png"));
            ui->b2->setIcon(QIcon("://images//up.png"));
            ui->b3->setIcon(QIcon("://images//right-up.png"));

            ui->b1->setVisible(true);
            ui->b2->setVisible(true);
            ui->b3->setVisible(true);
        }
}

void Arrowgame::handleb1Clicked(){
    if(currar == 'u'){
        QAbstractItemModel *model = ui->uparrows->model();
        QVariant variant;
        QIcon icon("://images//left-down.png");
        variant.setValue(icon);
        model->setData(currindex, variant, Qt::DecorationRole);
        ui->uparrows->viewport()->update();
        u[static_cast<unsigned long long>(currindex.column())] = 0;
    }
    else if(currar == 'r'){
        QAbstractItemModel *model = ui->rightarrows->model();
        QVariant variant;
        QIcon icon("://images//left-up.png");
        variant.setValue(icon);
        model->setData(currindex, variant, Qt::DecorationRole);
        ui->rightarrows->viewport()->update();
        r[static_cast<unsigned long long>(currindex.row())] = 0;
    }
    else if(currar == 'l'){
        QAbstractItemModel *model = ui->leftarrows->model();
        QVariant variant;
        QIcon icon("://images//right-up.png");
        variant.setValue(icon);
        model->setData(currindex, variant, Qt::DecorationRole);
        ui->leftarrows->viewport()->update();
        l[static_cast<unsigned long long>(currindex.row())] = 0;
    }
    else{
        QAbstractItemModel *model = ui->downarrows->model();
        QVariant variant;
        QIcon icon("://images//left-up.png");
        variant.setValue(icon);
        model->setData(currindex, variant, Qt::DecorationRole);
        ui->downarrows->viewport()->update();
        d[static_cast<unsigned long long>(currindex.column())] = 0;
    }
    ui->b1->setVisible(false);
    ui->b2->setVisible(false);
    ui->b3->setVisible(false);
}
void Arrowgame::handleb2Clicked(){
    if(currar == 'u'){
        QAbstractItemModel *model = ui->uparrows->model();
        QVariant variant;
        QIcon icon("://images//down.png");
        variant.setValue(icon);
        model->setData(currindex, variant, Qt::DecorationRole);
        ui->uparrows->viewport()->update();
        u[static_cast<unsigned long long>(currindex.column())] = 1;
    }
    else if(currar == 'r'){
        QAbstractItemModel *model = ui->rightarrows->model();
        QVariant variant;
        QIcon icon("://images//left.png");
        variant.setValue(icon);
        model->setData(currindex, variant, Qt::DecorationRole);
        ui->rightarrows->viewport()->update();
        r[static_cast<unsigned long long>(currindex.row())] = 1;
    }
    else if(currar == 'l'){
        QAbstractItemModel *model = ui->leftarrows->model();
        QVariant variant;
        QIcon icon("://images//right.png");
        variant.setValue(icon);
        model->setData(currindex, variant, Qt::DecorationRole);
        ui->leftarrows->viewport()->update();
        l[static_cast<unsigned long long>(currindex.row())] = 1;
    }
    else{
        QAbstractItemModel *model = ui->downarrows->model();
        QVariant variant;
        QIcon icon("://images//up.png");
        variant.setValue(icon);
        model->setData(currindex, variant, Qt::DecorationRole);
        ui->downarrows->viewport()->update();
        d[static_cast<unsigned long long>(currindex.column())] = 1;
    }
    ui->b1->setVisible(false);
    ui->b2->setVisible(false);
    ui->b3->setVisible(false);
}
void Arrowgame::handleb3Clicked(){
    if(currar == 'u'){
        QAbstractItemModel *model = ui->uparrows->model();
        QVariant variant;
        QIcon icon("://images//right-down.png");
        variant.setValue(icon);
        model->setData(currindex, variant, Qt::DecorationRole);
        ui->uparrows->viewport()->update();
        u[static_cast<unsigned long long>(currindex.column())] = 2;
    }
    else if(currar == 'r'){
        QAbstractItemModel *model = ui->rightarrows->model();
        QVariant variant;
        QIcon icon("://images//left-down.png");
        variant.setValue(icon);
        model->setData(currindex, variant, Qt::DecorationRole);
        ui->rightarrows->viewport()->update();
        r[static_cast<unsigned long long>(currindex.row())] = 2;
    }
    else if(currar == 'l'){
        QAbstractItemModel *model = ui->leftarrows->model();
        QVariant variant;
        QIcon icon("://images//right-down.png");
        variant.setValue(icon);
        model->setData(currindex, variant, Qt::DecorationRole);
        ui->leftarrows->viewport()->update();
        l[static_cast<unsigned long long>(currindex.row())] = 2;
    }
    else{
        QAbstractItemModel *model = ui->downarrows->model();
        QVariant variant;
        QIcon icon("://images//right-up.png");
        variant.setValue(icon);
        model->setData(currindex, variant, Qt::DecorationRole);
        ui->downarrows->viewport()->update();
        d[static_cast<unsigned long long>(currindex.column())] = 2;
    }
    ui->b1->setVisible(false);
    ui->b2->setVisible(false);
    ui->b3->setVisible(false);
}
bool Arrowgame::handlehintClicked(){
    vector<int> uparrow = game.getup();
    vector<int> downarrow = game.getdown();
    vector<int> leftarrow = game.getleft();
    vector<int> rightarrow = game.getright();

    size_t num = data.size();

    for(size_t i = 0; i < num; i++){
        if(u[i] != uparrow[i]){
            int col = static_cast<int>(i);
            QAbstractItemModel *model = ui->uparrows->model();
            QVariant variant;
            QModelIndex index = model->index(0, col);
            if(uparrow[i] == 0){
                QIcon icon("://images//left-down.png");
                variant.setValue(icon);
            }
            else if(uparrow[i] == 1){
                QIcon icon("://images//down.png");
                variant.setValue(icon);
            }
            else{
                QIcon icon("://images//right-down.png");
                variant.setValue(icon);
            }
            model->setData(index, variant, Qt::DecorationRole);
            ui->uparrows->viewport()->update();
            u[i] = uparrow[i];
            return false;
        }
    }
    for(size_t i = 0; i < num; i++){
        if(r[i] != rightarrow[i]){
            int row = static_cast<int>(i);
            QAbstractItemModel *model = ui->rightarrows->model();
            QVariant variant;
            QModelIndex index = model->index(row, 0);
            if(rightarrow[i] == 0){
                QIcon icon("://images//left-up.png");
                variant.setValue(icon);
            }
            else if(rightarrow[i] == 1){
                QIcon icon("://images//left.png");
                variant.setValue(icon);
            }
            else{
                QIcon icon("://images//left-down.png");
                variant.setValue(icon);
            }
            model->setData(index, variant, Qt::DecorationRole);
            ui->rightarrows->viewport()->update();
            r[i] = rightarrow[i];
            return false;
        }
    }
    for(size_t i = 0; i < num; i++){
        if(d[i] != downarrow[i]){
            int col = static_cast<int>(i);
            QAbstractItemModel *model = ui->downarrows->model();
            QVariant variant;
            QModelIndex index = model->index(0, col);
            if(downarrow[i] == 0){
                QIcon icon("://images//left-up.png");
                variant.setValue(icon);
            }
            else if(downarrow[i] == 1){
                QIcon icon("://images//up.png");
                variant.setValue(icon);
            }
            else{
                QIcon icon("://images//right-up.png");
                variant.setValue(icon);
            }
            model->setData(index, variant, Qt::DecorationRole);
            ui->downarrows->viewport()->update();
            d[i] = downarrow[i];
            return false;
        }
    }
    for(size_t i = 0; i < num; i++){
        if(l[i] != leftarrow[i]){
            int row = static_cast<int>(i);
            QAbstractItemModel *model = ui->leftarrows->model();
            QVariant variant;
            QModelIndex index = model->index(row, 0);
            if(leftarrow[i] == 0){
                QIcon icon("://images//right-up.png");
                variant.setValue(icon);
            }
            else if(leftarrow[i] == 1){
                QIcon icon("://images//right.png");
                variant.setValue(icon);
            }
            else{
                QIcon icon("://images//right-down.png");
                variant.setValue(icon);
            }
            model->setData(index, variant, Qt::DecorationRole);
            ui->leftarrows->viewport()->update();
            l[i] = leftarrow[i];
            return false;
        }
    }
    return true;

}
