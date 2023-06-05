#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QMainWindow>
#include <QItemDelegate>
#include <QStandardItem>
#include <QMessageBox>
#include <QApplication>
#include "filework.h"
#include "classes.h"
namespace Ui {
class Arrowgame;
}


class Arrowgame : public QMainWindow
{
    Q_OBJECT

public:
    explicit Arrowgame(QWidget *parent = nullptr);
    ~Arrowgame();


private:
    void genTablesView(size_t, char);
    void updateTablesView();
    void readfromTable();
    void handleupClicked(const QModelIndex&);
    void handledownClicked(const QModelIndex&);
    void handlerightClicked(const QModelIndex&);
    void handleleftClicked(const QModelIndex&);
    bool handlehintClicked();
    void handleb1Clicked();
    void handleb2Clicked();
    void handleb3Clicked();
    void check_result();

    vector<int> u;
    vector<int> r;
    vector<int> l;
    vector<int> d;
    vector<vector<int>> data;
    QModelIndex currindex;
    char currar;
    char clickable;
    field game;
    Ui::Arrowgame *ui;
    bool is_solved;
};
class CustomTableModel : public QAbstractTableModel
{
    vector<vector<int>> m_data;
    char flag;
public:
    bool setData(const QModelIndex &, const QVariant &, int) override;
    Qt::ItemFlags flags(const QModelIndex &) const override;
    explicit CustomTableModel(const vector<vector<int>>&,char, QObject*);
    int rowCount(const QModelIndex&) const override;
    int columnCount(const QModelIndex& ) const override;

    QVariant data(const QModelIndex&, int) const override;
};
class NumericDelegate : public QItemDelegate
{
public:
    QWidget* createEditor(QWidget*, const QStyleOptionViewItem&, const QModelIndex&) const override;
};
#endif // MAINWINDOW_H
