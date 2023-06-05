#include"filework.h"
filework:: filework(string name){
    path =  "//results//" + name + ".txt";
}
void filework:: write_to(vector<int> upar, vector<int> leftar, vector<int> rightar, vector<int> downar, vector<vector<int>> mat){
    ofstream file(QCoreApplication::applicationDirPath().toStdString() + path);
    if(!file.is_open()){
           throw invalid_argument("Не можу створити новий файл");
    }
    size_t size = mat.size();
    file << "  ";
    for(size_t i =0; i < size; i++){
        if(upar[i] == 0){
            file << '/' << ' ';
        }
        else if(upar[i] == 1){
            file << '|' << ' ';
        }
        else{
            file << '\\' << ' ';
        }
    }
    file <<endl;
    for(size_t i =0; i < size; i++){
        if(leftar[i] == 0){
            file << '/' << ' ';
        }
        else if(leftar[i] == 1){
            file << '-' << ' ';
        }
        else{
            file << '\\' << ' ';
        }
        for(size_t j = 0; j < size; j++){
            file << mat[i][j] <<' ';
        }
        if(rightar[i] == 0){
            file << '\\' << ' ';
        }
        else if(rightar[i] == 1){
            file << '-' << ' ';
        }
        else{
            file << '/' << ' ';
        }
        file << endl;

    }
    file << "  ";
    for(size_t i =0; i < size; i++){
        if(downar[i] == 0){
            file << '\\' << ' ';
        }
        else if(downar[i] == 1){
            file << '|' << ' ';
        }
        else{
            file << '/' << ' ';
        }
    }
    file.close();
}
