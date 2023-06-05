#include "mainwindow.h"
#include "ui_mainwindow.h"
CustomTableModel:: CustomTableModel(const vector<vector<int>>& data, char a_flag, QObject* parent = nullptr)
        : QAbstractTableModel(parent), m_data(data), flag(a_flag)
    {
    }
int CustomTableModel:: rowCount(const QModelIndex& parent = QModelIndex())const
    {
        if (parent.isValid())
            return 0;
        return static_cast<int>(m_data.size());
    }
QWidget* NumericDelegate:: createEditor(QWidget* parent, const QStyleOptionViewItem& option, const QModelIndex& index) const
{
    Q_UNUSED(option);

    QLineEdit* editor = new QLineEdit(parent);
            int rowCount = index.model()->rowCount();

            if (index.row() == index.column()) {
                if (index.row() == rowCount - index.row() - 1) {
                    QIntValidator* validator = new QIntValidator(0, 4, editor);
                    editor->setValidator(validator);
                }
                else {
                    QIntValidator* validator = new QIntValidator(0, 6, editor);
                    editor->setValidator(validator);
                }
            }
            else if (index.column() == rowCount - index.row() - 1) {
                QIntValidator* validator = new QIntValidator(0, 6, editor);
                editor->setValidator(validator);
            }
            else {
                QIntValidator* validator = new QIntValidator(0, 8, editor);
                editor->setValidator(validator);
            }

    return editor;
}

int CustomTableModel:: columnCount(const QModelIndex& parent = QModelIndex()) const
    {
        if (parent.isValid() || m_data.empty())
            return 0;
        return static_cast<int>(m_data[0].size());
    }

QVariant CustomTableModel:: data(const QModelIndex& index, int role = Qt::DisplayRole) const
    {
        if (!index.isValid() || role != Qt::DisplayRole)
            return QVariant();

        int row = index.row();
        int col = index.column();

        if (row < 0 || row >= static_cast<int>(m_data.size()) || col < 0 || col >= static_cast<int>(m_data[0].size()))
            return QVariant();

        return m_data[static_cast<unsigned long long>(row)][static_cast<unsigned long long>(col)];
    }
bool CustomTableModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if (!index.isValid() || role != Qt::EditRole)
        return false;

    int row = index.row();
    int col = index.column();

    if (row < 0 || row >= static_cast<int>(m_data.size()) || col < 0 || col >= static_cast<int>(m_data[0].size()))
        return false;

    m_data[static_cast<unsigned long long>(row)][static_cast<unsigned long long>(col)] = value.toInt();
    emit dataChanged(index, index);
    return true;
}
Qt::ItemFlags CustomTableModel::flags(const QModelIndex &index) const
{
    Qt::ItemFlags flags = QAbstractTableModel::flags(index);
    if (index.isValid() && flag == 'e')
        flags |= Qt::ItemIsEditable;
    return flags;
}
void Arrowgame:: check_result(){
    size_t num = data.size();
    vector<vector<int>> matrix = data;
    for(size_t i = 0; i < num; i++){
        for(size_t j = 0; j < num;  j++){
            matrix[i][j] = 0;
        }
    }

    bool is_empty = false;

    for(size_t i = 0; i < num; i++){
        if(u[i] == 5 || r[i] == 5 || l[i] == 5 || d[i] == 5){
            is_empty = true;
        }
    }

    if(is_empty){
        throw(invalid_argument("Не всі стрілки розставлені"));
    }

    int ar;
    for(size_t pos = 0; pos< num; pos++){

        ar = u[pos];
        if(ar == 1){
            for(size_t i =0; i< num; i++){
                matrix[i][pos]++;
            }
        }
        else if(ar == 0){
            if(pos > 0){
                for(size_t i = 0, j = pos - 1; j != size_t(-1); i++, j--){
                    matrix[i][j]++;
                }
            }
        }
        else{
            for(size_t i = 0, j = pos + 1; j<num; i++, j++){
                matrix[i][j]++;
            }
        }


        ar = d[pos];
        if(ar == 1){
            for(size_t i =0; i< num; i++){
                matrix[i][pos]++;
            }
        }
        else if(ar == 0){
            if(pos > 0){
                for(size_t i = num-1, j = pos - 1; j!= size_t(-1); i--, j--){
                    matrix[i][j]++;
                }
            }
        }
        else{
            for(size_t i = num - 1, j = pos + 1; j<num; i--, j++){
                matrix[i][j]++;
            }
        }


        ar = r[pos];
        if(ar == 1){
            for(size_t i =0; i< num; i++){
                matrix[pos][i]++;
            }
        }
        else if(ar == 0){
            if(pos > 0){
                for(size_t i = pos - 1, j = num - 1; i!= size_t(-1); i--, j--){
                    matrix[i][j]++;
                }
            }
        }
        else{
            for(size_t i = pos+1, j = num - 1; i< num; i++, j--){
                matrix[i][j]++;
            }
        }


        ar = l[pos];
        if(ar == 1){
            for(size_t i =0; i< num; i++){
                matrix[pos][i]++;
            }
        }
        else if(ar == 0){
            if(pos > 0){
                for(size_t i = pos-1, j = 0; i!= size_t(-1); i--, j++){
                    matrix[i][j]++;
                }
            }
        }
        else{
            for(size_t i = pos+1, j = 0; i< num; i++, j++){
                matrix[i][j]++;
            }
        }
    }
    for(size_t i = 0; i < num; i++){
        for(size_t j = 0; j < num;  j++){
            if(matrix[i][j] != data[i][j]){
                throw(invalid_argument("Пазл розв'язано не правильно"));
            }
        }
    }
}
void Arrowgame::genTablesView(size_t n, char f)
{
    CustomTableModel *model = new CustomTableModel(data, f, this);
    ui->tableView->setModel(model);
    ui->tableView->setEditTriggers(QAbstractItemView:: DoubleClicked | QAbstractItemView::EditKeyPressed);

    // Adjust the size of the table view based on the value of n
    int tableHeight = static_cast<int>(40 * n + 2);
    int tableWidth = static_cast<int>(40 * n + 2);


    QPoint Pos = ui->tableView->pos();
    QPoint downpos = ui->downarrows->pos();
    QPoint rightpos = ui->rightarrows->pos();

    QStandardItemModel *leftmodel = new QStandardItemModel(this);
    QStandardItemModel *rightmodel = new QStandardItemModel(this);
    QStandardItemModel *upmodel = new QStandardItemModel(this);
    QStandardItemModel *downmodel = new QStandardItemModel(this);
    for (size_t i = 0; i<n; i++) {
        QStandardItem *item = new QStandardItem;
        QIcon icon;
        item->setIcon(icon);
        leftmodel->appendRow(item);
        rightmodel->appendRow(item);
        QList<QStandardItem*> itemlist;
        itemlist.push_back(item);
        upmodel->appendColumn(itemlist);
        downmodel->appendColumn(itemlist);
    }

    ui->uparrows->setModel(upmodel);
    ui->rightarrows->setModel(rightmodel);
    ui->leftarrows->setModel(leftmodel);
    ui->downarrows->setModel(downmodel);


    ui->downarrows->move(downpos.x(), Pos.y() + tableHeight);
    ui->rightarrows->move(Pos.x() + tableWidth, rightpos.y());


    ui->uparrows->setFixedWidth(tableWidth);
    ui->downarrows->setFixedWidth(tableWidth);
    ui->rightarrows->setFixedHeight(tableHeight);
    ui->leftarrows->setFixedHeight(tableHeight);
    ui->tableView->setFixedHeight(tableHeight);
    ui->tableView->setFixedWidth(tableWidth);


    ui->tableView->verticalHeader()->setDefaultSectionSize(40);
    ui->tableView->horizontalHeader()->setDefaultSectionSize(40);
    ui->uparrows->verticalHeader()->setDefaultSectionSize(40);
    ui->uparrows->horizontalHeader()->setDefaultSectionSize(40);
    ui->rightarrows->verticalHeader()->setDefaultSectionSize(40);
    ui->rightarrows->horizontalHeader()->setDefaultSectionSize(40);
    ui->downarrows->verticalHeader()->setDefaultSectionSize(40);
    ui->downarrows->horizontalHeader()->setDefaultSectionSize(40);
    ui->leftarrows->verticalHeader()->setDefaultSectionSize(40);
    ui->leftarrows->horizontalHeader()->setDefaultSectionSize(40);


    ui->tableView->verticalHeader()->setVisible(false);
    ui->tableView->horizontalHeader()->setVisible(false);
    ui->uparrows->verticalHeader()->setVisible(false);
    ui->uparrows->horizontalHeader()->setVisible(false);
    ui->rightarrows->verticalHeader()->setVisible(false);
    ui->rightarrows->horizontalHeader()->setVisible(false);
    ui->downarrows->verticalHeader()->setVisible(false);
    ui->downarrows->horizontalHeader()->setVisible(false);
    ui->leftarrows->verticalHeader()->setVisible(false);
    ui->leftarrows->horizontalHeader()->setVisible(false);

    ui->uparrows->setVisible(true);
    ui->downarrows->setVisible(true);
    ui->rightarrows->setVisible(true);
    ui->leftarrows->setVisible(true);
    ui->tableView->setVisible(true);

    ui->uparrows->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->rightarrows->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->leftarrows->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->downarrows->setEditTriggers(QAbstractItemView::NoEditTriggers);

    ui->uparrows->setSelectionMode(QAbstractItemView::NoSelection);
    ui->rightarrows->setSelectionMode(QAbstractItemView::NoSelection);
    ui->leftarrows->setSelectionMode(QAbstractItemView::NoSelection);
    ui->downarrows->setSelectionMode(QAbstractItemView::NoSelection);

    NumericDelegate* delegate = new NumericDelegate;
    ui->tableView->setItemDelegate(delegate);
}
void Arrowgame:: updateTablesView(){

    vector<int> uparrow = game.getup();
    vector<int> downarrow = game.getdown();
    vector<int> leftarrow = game.getleft();
    vector<int> rightarrow = game.getright();

    u = uparrow;
    d = downarrow;
    l = leftarrow;
    r = rightarrow;

    QStandardItemModel *leftmodel = new QStandardItemModel(this);
    QStandardItemModel *rightmodel = new QStandardItemModel(this);
    QStandardItemModel *upmodel = new QStandardItemModel(this);
    QStandardItemModel *downmodel = new QStandardItemModel(this);
    for (int c : leftarrow) {
        QStandardItem *item = new QStandardItem;
        if(c == 1){
            QIcon icon("://images//right.png");
            item->setIcon(icon);
            leftmodel->appendRow(item);
        }
        else if(c == 2){
           QIcon icon("://images//right-down.png");
           item->setIcon(icon);
           leftmodel->appendRow(item);
        }
        else{
            QIcon icon("://images//right-up.png");
            item->setIcon(icon);
            leftmodel->appendRow(item);
        }
    }

    for (int c : uparrow) {
        QStandardItem *item = new QStandardItem;
        if(c == 1){
            QIcon icon("://images//down.png");
            item->setIcon(icon);
            QList<QStandardItem*> itemlist;
            itemlist.push_back(item);
            upmodel->appendColumn(itemlist);
        }
        else if(c == 2){
           QIcon icon("://images//right-down.png");
           item->setIcon(icon);
           QList<QStandardItem*> itemlist;
           itemlist.push_back(item);
           upmodel->appendColumn(itemlist);
        }
        else{
            QIcon icon("://images//left-down.png");
            item->setIcon(icon);
            QList<QStandardItem*> itemlist;
            itemlist.push_back(item);
            upmodel->appendColumn(itemlist);
        }

    }

    for (int c : downarrow) {
        QStandardItem *item = new QStandardItem;
        if(c == 1){
            QIcon icon("://images//up.png");
            item->setIcon(icon);
            QList<QStandardItem*> itemlist;
            itemlist.push_back(item);
            downmodel->appendColumn(itemlist);
        }
        else if(c == 0){
           QIcon icon("://images//left-up.png");
           item->setIcon(icon);
           QList<QStandardItem*> itemlist;
           itemlist.push_back(item);
           downmodel->appendColumn(itemlist);
        }
        else{
            QIcon icon("://images//right-up.png");
            item->setIcon(icon);
            QList<QStandardItem*> itemlist;
            itemlist.push_back(item);
            downmodel->appendColumn(itemlist);
        }

    }
    for (int c : rightarrow) {
        QStandardItem *item = new QStandardItem;
        if(c == 1){
            QIcon icon("://images//left.png");
            item->setIcon(icon);
            rightmodel->appendRow(item);
        }
        else if(c == 0){
           QIcon icon("://images//left-up.png");
           item->setIcon(icon);
           rightmodel->appendRow(item);
        }
        else{
            QIcon icon("://images//left-down.png");
            item->setIcon(icon);
            rightmodel->appendRow(item);
        }

    }

    ui->uparrows->setModel(upmodel);
    ui->rightarrows->setModel(rightmodel);
    ui->leftarrows->setModel(leftmodel);
    ui->downarrows->setModel(downmodel);

    ui->uparrows->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->rightarrows->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->leftarrows->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->downarrows->setEditTriggers(QAbstractItemView::NoEditTriggers);

    ui->uparrows->setSelectionMode(QAbstractItemView::NoSelection);
    ui->rightarrows->setSelectionMode(QAbstractItemView::NoSelection);
    ui->leftarrows->setSelectionMode(QAbstractItemView::NoSelection);
    ui->downarrows->setSelectionMode(QAbstractItemView::NoSelection);

}

void Arrowgame:: readfromTable(){
    QAbstractItemModel* model = ui->tableView->model();

    size_t rowCount = static_cast<unsigned long long>(model->rowCount());
    size_t columnCount = static_cast<unsigned long long>(model->columnCount());

    // Проходимося по кожній комірці і зчитуємо значення
    for (size_t row = 0; row < rowCount; ++row) {
        for (size_t col = 0; col < columnCount; ++col) {
            QModelIndex index = model->index(static_cast<int>(row), static_cast<int>(col));
            int value = model->data(index, Qt::DisplayRole).toInt();
            data[row][col] = value;
        }
    }
}
Arrowgame::Arrowgame(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Arrowgame)
{   is_solved = false;
    ui->setupUi(this);

    this->setWindowIcon(QIcon("C:\\Users\\goros\\OneDrive\\Documents\\kurs\\left-up.png"));

    ui->uparrows->setVisible(false);
    ui->downarrows->setVisible(false);
    ui->rightarrows->setVisible(false);
    ui->leftarrows->setVisible(false);
    ui->tableView->setVisible(false);
    ui->to_solve->setVisible(false);
    ui->to_check->setVisible(false);
    ui->to_play->setVisible(false);
    ui->to_confirm->setVisible(false);
    ui->to_hint->setVisible(false);
    ui->lab->setVisible(false);
    ui->lineEdit->setVisible(false);
    ui->to_write->setVisible(false);
    ui->b1->setVisible(false);
    ui->b2->setVisible(false);
    ui->b3->setVisible(false);



    QObject::connect(ui->to_gen, &QPushButton::clicked, [&]() {
        is_solved = false;
        size_t num = static_cast<unsigned long long>(ui->spinBox->value());
        data = generate(num);

        u.resize(num);
        l.resize(num);
        r.resize(num);
        d.resize(num);

        for(size_t i = 0; i < num; i++){
            u[i] = 5;
            l[i] = 5;
            r[i] = 5;
            d[i] = 5;
        }

        genTablesView(num, 'g');
        ui->tableView->setSelectionMode(QAbstractItemView::NoSelection);
        ui->to_solve->setVisible(true);
        ui->to_play->setVisible(true);
        ui->to_check->setVisible(false);
        ui->to_hint->setVisible(false);
        ui->to_confirm->setVisible(false);
        clickable = 't';
        ui->b1->setVisible(false);
        ui->b2->setVisible(false);
        ui->b3->setVisible(false);

        ui->lab->setVisible(false);
        ui->lineEdit->setVisible(false);
        ui->to_write->setVisible(false);
    });

    QObject::connect(ui->to_enter, &QPushButton::clicked, [&]() {
        is_solved = false;
        size_t num = static_cast<unsigned long long>(ui->spinBox->value());
        data.resize(num);
        for(size_t i = 0; i < num; i++){
            data[i].resize(num);
        }
        u.resize(num);
        l.resize(num);
        r.resize(num);
        d.resize(num);
        for(size_t i = 0; i < num; i++){
            u[i] = 5;
            l[i] = 5;
            r[i] = 5;
            d[i] = 5;
        }

        genTablesView(num, 'e');
        ui->to_check->setVisible(true);
        ui->to_play->setVisible(false);
        ui->to_solve->setVisible(false);
        ui->to_hint->setVisible(false);
        ui->to_confirm->setVisible(false);
        clickable = 't';
        ui->b1->setVisible(false);
        ui->b2->setVisible(false);
        ui->b3->setVisible(false);

        ui->lab->setVisible(false);
        ui->lineEdit->setVisible(false);
        ui->to_write->setVisible(false);
    });

    QObject::connect(ui->to_check, &QPushButton::clicked, [&]() {
        readfromTable();
        game = field(data);
        pair<size_t, char> p(0, 'u');
        if(!game.solve(p)){
            QMessageBox::information(this, "Помилка", "Даний пазл неможливо розв'язати");
        }
        else{
            is_solved = true;
            ui->tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
            ui->tableView->setSelectionMode(QAbstractItemView::NoSelection);
            ui->to_solve->setVisible(true);
            ui->to_play->setVisible(true);
            ui->to_check->setVisible(false);
        }
    });

    QObject::connect(ui->to_hint, &QPushButton::clicked, [&]() {
        if(!is_solved){
            readfromTable();
            game = field(data);
            pair<size_t, char> p(0, 'u');
            game.solve(p);
        }
        if(handlehintClicked()){
            QMessageBox::information(this, "Помилка", "Всі стрілки вже розставлено правильно");
        }
        ui->b1->setVisible(false);
        ui->b2->setVisible(false);
        ui->b3->setVisible(false);
    });

    QObject::connect(ui->uparrows, &QTableView::clicked, this, &Arrowgame::handleupClicked);

    QObject::connect(ui->leftarrows, &QTableView::clicked, this, &Arrowgame::handleleftClicked);

    QObject::connect(ui->downarrows, &QTableView::clicked, this, &Arrowgame::handledownClicked);

    QObject::connect(ui->rightarrows, &QTableView::clicked, this, &Arrowgame::handlerightClicked);

    QObject::connect(ui->b1, &QPushButton::clicked, this, &Arrowgame::handleb1Clicked);

    QObject::connect(ui->b2, &QPushButton::clicked, this, &Arrowgame::handleb2Clicked);

    QObject::connect(ui->b3, &QPushButton::clicked, this, &Arrowgame::handleb3Clicked);

    QObject::connect(ui->to_play, &QPushButton::clicked, [&]() {

        clickable = 'p';
        ui->to_check->setVisible(false);
        ui->to_play->setVisible(false);
        ui->to_confirm->setVisible(true);
        ui->to_hint->setVisible(true);
        ui->to_solve->setVisible(false);

    });

    QObject::connect(ui->to_solve, &QPushButton::clicked, [&]() {
        if(!is_solved){
            readfromTable();
            game = field(data);
            pair<size_t, char> p(0, 'u');
            game.solve(p);
            is_solved = true;
        }
        updateTablesView();
        clickable = 't';
        ui->to_play->setVisible(false);
        ui->to_solve->setVisible(false);
        ui->to_confirm->setVisible(false);
        ui->to_hint->setVisible(false);
        ui->lab->setVisible(true);
        ui->lineEdit->setVisible(true);
        ui->to_write->setVisible(true);

    });

    QObject::connect(ui->to_confirm, &QPushButton::clicked, [&]() {
        ui->b1->setVisible(false);
        ui->b2->setVisible(false);
        ui->b3->setVisible(false);
        try{
            check_result();
            QMessageBox::information(this, "Вітання", "Пазл розв'язано");
            ui->to_hint->setVisible(false);
            ui->to_solve->setVisible(false);
            ui->to_confirm->setVisible(false);
            ui->lab->setVisible(true);
            ui->lineEdit->setVisible(true);
            ui->to_write->setVisible(true);
        }
        catch(invalid_argument& e){
            QMessageBox::information(this, "Помилка", e.what());
        }
    });

    QObject::connect(ui->to_write, &QPushButton::clicked, [&]() {
        try{
            QString userInput = ui->lineEdit->text();
            string filename = userInput.toStdString();
            filework workf(filename);
            workf.write_to(u, l, r, d, data);
            ui->lab->setVisible(false);
            ui->lineEdit->setVisible(false);
            ui->to_write->setVisible(false);

        }
        catch(invalid_argument& e){
            QMessageBox::information(this, "Помилка", e.what());
        }
        ui->lineEdit->clear();
    });
}

Arrowgame::~Arrowgame()
{
    delete ui;
}

