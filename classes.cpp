#include "classes.h"
cell:: cell(int n){
    num = n;
    num_of_arrows = 0;
}
cell:: cell(){
    num = 0;
    num_of_arrows = 0;
}
void cell:: add_arrow(){
    num_of_arrows++;
}
void cell:: remove_arrow(){
    num_of_arrows--;
}
bool cell:: is_safe(){
    return num > num_of_arrows;
}
bool cell:: is_solved(){
    return num == num_of_arrows;
}
field:: field(){}
field:: field(vector<vector<int>> num_field){
    square.resize(num_field.size());
    right.resize(num_field.size());
    left.resize(num_field.size());
    up.resize(num_field.size());
    down.resize(num_field.size());
    for(size_t i =0; i < num_field.size(); i++){
        square[i].resize(num_field.size());
    }
    for(size_t i=0; i< num_field.size(); i++){
        for(size_t j = 0; j<num_field.size(); j++){
            square[i][j] = cell(num_field[i][j]);
        }
    }
}
void field:: add_arrow(int ar, size_t pos, char c){
    switch(c){
    case('u'):
        if(ar == 1){
            for(size_t i =0; i< square.size(); i++){
                square[i][pos].add_arrow();
            }
        }
        else if(ar == 0){
            if(pos > 0){
                for(size_t i = 0, j = pos - 1; j != size_t(-1); i++, j--){
                    square[i][j].add_arrow();
                }
            }
        }
        else{
            for(size_t i = 0, j = pos + 1; j<square.size(); i++, j++){
                square[i][j].add_arrow();
            }
        }
        up[pos] = ar;
        break;
    case('d'):
        if(ar == 1){
            for(size_t i =0; i< square.size(); i++){
                square[i][pos].add_arrow();
            }
        }
        else if(ar == 0){
            if(pos > 0){
                for(size_t i = square.size()-1, j = pos - 1; j!= size_t(-1); i--, j--){
                    square[i][j].add_arrow();
                }
            }
        }
        else{
            for(size_t i = square.size() - 1, j = pos + 1; j<square.size(); i--, j++){
                square[i][j].add_arrow();
            }
        }
        down[pos] = ar;
        break;
    case('r'):
        if(ar == 1){
            for(size_t i =0; i< square.size(); i++){
                square[pos][i].add_arrow();
            }
        }
        else if(ar == 0){
            if(pos > 0){
                for(size_t i = pos - 1, j = square.size() - 1; i!= size_t(-1); i--, j--){
                    square[i][j].add_arrow();
                }
            }
        }
        else{
            for(size_t i = pos+1, j = square.size() - 1; i< square.size(); i++, j--){
                square[i][j].add_arrow();
            }
        }
        right[pos] = ar;
        break;
    case('l'):
        if(ar == 1){
            for(size_t i =0; i< square.size(); i++){
                square[pos][i].add_arrow();
            }
        }
        else if(ar == 0){
            if(pos > 0){
                for(size_t i = pos-1, j = 0; i!= size_t(-1); i--, j++){
                    square[i][j].add_arrow();
                }
            }
        }
        else{
            for(size_t i = pos+1, j = 0; i< square.size(); i++, j++){
                square[i][j].add_arrow();
            }
        }
        left[pos] = ar;
        break;
    }
}
bool field:: is_safe(int n, size_t pos, char c){
    int ar = n;
    switch(c){
    case('u'):
        if(ar == 1){
            for(size_t i =0; i< square.size(); i++){
                if(!square[i][pos].is_safe()) return false;
            }
        }
        else if(ar == 0){
            if(pos > 0){
            for(size_t i = 0, j = pos - 1; j!= size_t(-1); i++, j--){
                if(!square[i][j].is_safe()) return false;
            }
            }
        }
        else{
            for(size_t i = 0, j = pos + 1; j<square.size(); i++, j++){
                if(!square[i][j].is_safe()) return false;
            }
        }
        break;
    case('d'):
        if(ar == 1){
            for(size_t i =0; i< square.size(); i++){
                if(!square[i][pos].is_safe()) return false;
            }
        }
        else if(ar == 0){
            if(pos > 0){
            for(size_t i = square.size()-1, j = pos - 1; j!= size_t(-1); i--, j--){
                if(!square[i][j].is_safe()) return false;
            }
            }
        }
        else{
            for(size_t i = square.size() - 1, j = pos + 1; j<square.size(); i--, j++){
                if(!square[i][j].is_safe()) return false;
            }
        }
        break;
    case('r'):
        if(ar == 1){
            for(size_t i =0; i< square.size(); i++){
                if(!square[pos][i].is_safe()) return false;
            }
        }
        else if(ar == 0){
            if(pos > 0){
            for(size_t i = pos-1, j = square.size() - 1; i!= size_t(-1); i--, j--){
                if(!square[i][j].is_safe()) return false;
            }
            }
        }
        else{
            for(size_t i = pos+1, j = square.size() - 1; i< square.size(); i++, j--){
                if(!square[i][j].is_safe()) return false;
            }
        }
        break;
    case('l'):
        if(ar == 1){
            for(size_t i =0; i< square.size(); i++){
                if(!square[pos][i].is_safe()) return false;
            }
        }
        else if(ar == 0){
            if(pos > 0){
            for(size_t i = pos-1, j = 0; i!= size_t(-1); i--, j++){
                if(!square[i][j].is_safe()) return false;
            }
            }
        }
        else{
            for(size_t i = pos+1, j = 0; i< square.size(); i++, j++){
                if(!square[i][j].is_safe()) return false;
            }
        }
        break;
    }
    return true;
}
void field:: remove_arrow(size_t pos, char c){
    int ar;
    switch(c){
    case('u'):
        ar = up[pos];
        if(ar == 1){
            for(size_t i =0; i< square.size(); i++){
                square[i][pos].remove_arrow();
            }
        }
        else if(ar == 0){
            if(pos > 0){
            for(size_t i = 0, j = pos - 1; j!= size_t(-1); i++, j--){
                square[i][j].remove_arrow();
            }
            }
        }
        else{
            for(size_t i = 0, j = pos + 1; j<square.size(); i++, j++){
                square[i][j].remove_arrow();
            }
        }
        break;
    case('d'):
        ar = down[pos];
        if(ar == 1){
            for(size_t i =0; i< square.size(); i++){
                square[i][pos].remove_arrow();
            }
        }
        else if(ar == 0){
            if(pos > 0){
            for(size_t i = square.size()-1, j = pos - 1; j!= size_t(-1); i--, j--){
                square[i][j].remove_arrow();
            }
            }
        }
        else{
            for(size_t i = square.size() - 1, j = pos + 1; j<square.size(); i--, j++){
                square[i][j].remove_arrow();
            }
        }
        break;
    case('r'):
        ar=right[pos];
        if(ar == 1){
            for(size_t i =0; i< square.size(); i++){
                square[pos][i].remove_arrow();
            }
        }
        else if(ar == 0){
            if(pos > 0){
            for(size_t i = pos-1, j = square.size() - 1; i!= size_t(-1); i--, j--){
                square[i][j].remove_arrow();
            }
            }
        }
        else{
            for(size_t i = pos+1, j = square.size() - 1; i< square.size(); i++, j--){
                square[i][j].remove_arrow();
            }
        }
        break;
    case('l'):
        ar = left[pos];
        if(ar == 1){
            for(size_t i =0; i< square.size(); i++){
                square[pos][i].remove_arrow();
            }
        }
        else if(ar == 0){
            if(pos > 0){
            for(size_t i = pos-1, j = 0; i!= size_t(-1); i--, j++){
                square[i][j].remove_arrow();
            }
            }
        }
        else{
            for(size_t i = pos+1, j = 0; i< square.size(); i++, j++){
                square[i][j].remove_arrow();
            }
        }
        break;
    }
}
pair<size_t, char> field:: next(pair<size_t, char> curr){
    pair<size_t, char> n;
    switch(curr.second){
    case('u'):
        if(curr.first < square.size() - 1){
            n.first = curr.first + 1;
            n.second ='u';
        }
        else{
            n.first = 0;
            n.second = 'r';
        }
        break;
    case('r'):
        if(curr.first < square.size() - 1){
            n.first = curr.first + 1;
            n.second ='r';
        }
        else{
            n.first = 0;
            n.second = 'd';
        }
        break;
    case('d'):
        if(curr.first < square.size() - 1){
            n.first = curr.first + 1;
            n.second ='d';
        }
        else{
            n.first = 0;
            n.second = 'l';
        }
        break;
    case('l'):
            n.first = curr.first + 1;
            n.second ='l';
        break;
    }
    return n;
}
bool field:: is_solved(){
    for(size_t i = 0; i < square.size(); i++){
        for(size_t j = 0; j<square.size(); j++){
            if(!square[i][j].is_solved()){
                return false;
            }
        }
    }
    return true;
}
bool field::solve(pair<size_t, char> nextPos){
    if (nextPos.first == square.size() && nextPos.second == 'l') {
        if(is_solved()) return true;
        return false;
    }
    pair<size_t, char> newPos = next(nextPos);
    // Try placing arrows in all possible directions
    for (int i = 0; i<3; i++) {
        if (is_safe(i, nextPos.first, nextPos.second)) {
            add_arrow(i, nextPos.first, nextPos.second);
            if (solve(newPos)) {
                return true;
            }
            remove_arrow(nextPos.first, nextPos.second);
        }
    }
    return false;
}
vector<int> field:: getup(){
    return up;
}
vector<int> field:: getleft(){
    return left;
}
vector<int> field:: getright(){
    return right;
}
vector<int> field:: getdown(){
    return down;
}

int random(int min, int max)
{return(min + rand()%(max-min + 1));
}
vector<vector<int>> generate(size_t num){

    vector<int> up(num);
    vector<int> right(num);
    vector<int> left(num);
    vector<int> down(num);


    int ar;


    for(size_t i = 0; i < num; i++){
        up[i] = random(0, 2);
        right[i] = random(0, 2);
        left[i] = random(0, 2);
        down[i] = random(0, 2);
    }


    vector<vector<int>> square;
    square.resize(num);


    for(size_t i = 0; i< num; i++){
        square[i].resize(num);
        for(size_t j =0; j < num; j++){
            square[i][j] = 0;
        }
    }


    for(size_t pos = 0; pos< num; pos++){

        ar = up[pos];
        if(ar == 1){
            for(size_t i =0; i< square.size(); i++){
                square[i][pos]++;
            }
        }
        else if(ar == 0){
            if(pos > 0){
                for(size_t i = 0, j = pos - 1; j != size_t(-1); i++, j--){
                    square[i][j]++;
                }
            }
        }
        else{
            for(size_t i = 0, j = pos + 1; j<square.size(); i++, j++){
                square[i][j]++;
            }
        }


        ar = down[pos];
        if(ar == 1){
            for(size_t i =0; i< square.size(); i++){
                square[i][pos]++;
            }
        }
        else if(ar == 0){
            if(pos > 0){
                for(size_t i = square.size()-1, j = pos - 1; j!= size_t(-1); i--, j--){
                    square[i][j]++;
                }
            }
        }
        else{
            for(size_t i = square.size() - 1, j = pos + 1; j<square.size(); i--, j++){
                square[i][j]++;
            }
        }


        ar = right[pos];
        if(ar == 1){
            for(size_t i =0; i< square.size(); i++){
                square[pos][i]++;
            }
        }
        else if(ar == 0){
            if(pos > 0){
                for(size_t i = pos - 1, j = square.size() - 1; i!= size_t(-1); i--, j--){
                    square[i][j]++;
                }
            }
        }
        else{
            for(size_t i = pos+1, j = square.size() - 1; i< square.size(); i++, j--){
                square[i][j]++;
            }
        }


        ar = left[pos];
        if(ar == 1){
            for(size_t i =0; i< square.size(); i++){
                square[pos][i]++;
            }
        }
        else if(ar == 0){
            if(pos > 0){
                for(size_t i = pos-1, j = 0; i!= size_t(-1); i--, j++){
                    square[i][j]++;
                }
            }
        }
        else{
            for(size_t i = pos+1, j = 0; i< square.size(); i++, j++){
                square[i][j]++;
            }
        }

    }
    return square;
}
