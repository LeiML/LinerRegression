//
// Created by LeiLei on 2020/6/18.
//

#include "Matrix.hpp"

ostream &operator<<(ostream &os, const Size &s) {
    os << "[" << s.rows << " * "<< s.cols << "]";
    return os;
}

Size::Size() : rows(0), cols(0) {}

Size::Size(int row, int col) : rows(row), cols(col){}

Matrix::Matrix() : row(1), col(1) {
    this->init();
}

Matrix::Matrix(Size size) : row(size.rows), col(size.cols){
    this->init();
}

Matrix::~Matrix() {
    for(int i=0;i<this->row;i++)
        delete []this->data[i];                    //释放内存
    delete []this->data;
}

Matrix::Matrix(int row, int col) {
    this->row = row;
    this->col = col;
    this->init();
}

void Matrix::init() {
    this->data = new double *[this->row];              //开辟行数个指针空间
    for(int i=0;i<this->row;i++)
        this->data[i] = new double[this->col];
}

Matrix::Matrix(Matrix &mat) : row(mat.row), col(mat.col) {
    this->init();                           //开辟出内存空间
    for(int i=0;i<mat.row;i++){
        for(int j=0;j<mat.col;j++){
            this->data[i][j] = mat.data[i][j];   //p参数的赋值
        }
    }
}

Matrix::Matrix(double **dat, int row, int col) : row(row), col(col){
    this->init();
    for(int i=0;i<row;i++){
        for(int j=0;j<col;j++) {
            this->data[i][j] = *((double *)dat + i * col+ j);
        }
    }
}

Matrix::Matrix(vector<vector<double>> &dat) : row(dat.size()), col(dat.at(0).size()) {
    init();
    for(int i=0;i<row;i++){
        for(int j=0;j<col;j++) {
            try {
                this->data[i][j] = dat.at(i).at(j);
            }
            catch (out_of_range &e) {
                this->data[i][j] = 0;
            }
        }
    }
}

Matrix Matrix::rows(const int &r) {
    Matrix mat = Matrix(1, this->col);
    for(int i=0;i<this->col;i++)
        mat.data[0][i] = this->data[r][i];
    return mat;
}

ostream &operator<<(ostream &os, const Matrix &matrix) {
    os<<"array([";
    for(int i=0;i<matrix.row;i++){
        os<<"[";
        for(int j=0;j<matrix.col;j++) {
            string temp = j == matrix.col - 1 ? ",]" : ",";
            os << matrix.data[i][j] << temp;
        }
        string temp = i == matrix.row - 1 ? "])" : "\n";
        os<<temp;
    }
    return os;
}

double &Matrix::at(const int&rows, const int &cols) {
    return this->data[rows][cols];
}

Matrix Matrix::cols(const int &c) {
    Matrix matrix = Matrix(this->row, 1);
    for(int i=0;i<this->row;i++)
        matrix.at(i, 0) = this->at(i, c);
    return matrix;
}

Matrix Matrix::zeros(int rows, int cols) {
    Matrix mat = Matrix(rows, cols);
    for(int i=0;i<rows;i++){
        for(int j=0;j<cols;j++)
            mat.at(i, j) = 0;
    }
    return mat;
}

Matrix Matrix::ones(int rows, int cols) {
    Matrix mat = Matrix(rows, cols);
    for(int i=0;i<rows;i++){
        for(int j=0;j<cols;j++)
            mat.at(i, j) = 1;
    }
    return mat;
}

Matrix Matrix::create(int rows, int cols, double num) {
    Matrix mat = Matrix(rows, cols);
    for(int i=0;i<rows;i++){
        for(int j=0;j<cols;j++)
            mat.at(i, j) = num;
    }
    return mat;
}

Size Matrix::size() {
    return Size(this->row, this->col);
}

Matrix Matrix::operator+(Matrix mat) {
    try{
        if (this->row!=mat.row||this->col!=mat.col) throw MyException("【Error】the two matrix's Dimension is not equal");
    } catch (MyException & e) {
        cerr << e.what() <<endl;
        exit(-1);
    }
    Matrix result = Matrix(mat.size());
    for(int i=0;i<this->row;i++){
        for(int j=0;j<this->col;j++){
            result.at(i, j) = this->at(i, j) + mat.at(i, j);
        }
    }
    return result;
}

Matrix Matrix::operator-(Matrix mat) {
    try{
        if (this->row!=mat.row||this->col!=mat.col) throw MyException("【Error】the two matrix's Dimension is not equal");
    } catch (MyException & e) {
        cerr << e.what() <<endl;
        exit(-1);
    }
    Matrix result = Matrix(mat.size());
    for(int i=0;i<this->row;i++){
        for(int j=0;j<this->col;j++){
            result.at(i, j) = this->at(i, j) - mat.at(i, j);
        }
    }
    return result;
}

Matrix Matrix::operator-() {
    Matrix result = Matrix(this->size());
    for(int i=0;i<this->row;i++){
        for(int j=0;j<this->col;j++){
            result.at(i, j) = -this->at(i, j);
        }
    }
    return result;
}

Matrix Matrix::operator*(Matrix mat) {
    try{
        if (this->row!=mat.row||this->col!=mat.col) throw MyException("【Error】the two matrix's Dimension is not equal");
    } catch (MyException & e) {
        cerr << e.what() <<endl;
        exit(-1);
    }
    Matrix result = Matrix(mat.size());
    for(int i=0;i<this->row;i++){
        for(int j=0;j<this->col;j++){
            result.at(i, j) = this->at(i, j) * mat.at(i, j);
        }
    }
    return result;
}

Matrix Matrix::dot(Matrix &matrix) {
    try{
        if (this->col != matrix.row)  throw MyException("【Error】the two matrix's Dimension is not To meet the conditions");
    } catch (MyException & e) {
        cerr << e.what() <<endl;
        exit(-1);
    }
    Matrix result = Matrix(this->row, matrix.col);
    for(int i=0;i<this->row;i++){
        for(int j=0;j<matrix.col;j++){
            Matrix temp = this->rows(i).transpose() * matrix.cols(j);
            result.at(i, j) = temp.sum();
        }
    }
    return result;
}

double Matrix::sum() {
    double sum = 0;
    for(int i=0;i<this->row;i++)
        sum += this->at(i, 0);
    return sum;
}

Matrix Matrix::operator+(double num) {
    Matrix mat = Matrix(this->row, this->col);
    for(int i=0;i<this->row;i++){
        for(int j=0;j<this->col;j++)
            mat.at(i, j) = this->at(i, j) + num;
    }
    return mat;
}

Matrix Matrix::operator-(double num){
    Matrix mat = Matrix(this->row, this->col);
    for(int i=0;i<this->row;i++){
        for(int j=0;j<this->col;j++)
            mat.at(i, j) = this->at(i, j) - num;
    }
    return mat;
}

Matrix Matrix::operator*(double num) {
    Matrix mat = Matrix(this->row, this->col);
    for(int i=0;i<this->row;i++){
        for(int j=0;j<this->col;j++)
            mat.at(i, j) = this->at(i, j) * num;
    }
    return mat;
}

Matrix Matrix::operator/(double num) {
    try {
        if (num == 0)   throw MyException("【Error】the num is 0");
    } catch (MyException & e) {
        cerr << e.what() <<endl;
        exit(-1);
    }
    Matrix mat = Matrix(this->row, this->col);
    for(int i=0;i<this->row;i++){
        for(int j=0;j<this->col;j++)
            mat.at(i, j) = this->at(i, j) / num;
    }
    return mat;
}

Matrix Matrix::transpose() {
    Matrix mat = Matrix(this->col, this->row);
    for(int i=0;i<this->row;i++){
        for(int j=0;j<this->col;j++){
            mat.at(j, i) = this->at(i, j);
        }
    }
    return mat;
}

Matrix Matrix::exp() {
    Matrix mat = Matrix(this->size());
    for(int i=0;i<this->row;i++){
        for (int j=0;j<this->col;j++)
            mat.at(i, j) = std::exp(this->at(i, j));
    }
    return mat;
}

Matrix Matrix::exp(int pow) {
    Matrix mat = Matrix(this->size());
    for(int i=0;i<this->row;i++){
        for (int j=0;j<this->col;j++)
            mat.at(i, j) = std::pow(this->at(i, j), pow);
    }
    return mat;
}

Matrix& Matrix::operator=(Matrix mat) {
    for(int i=0;i<mat.row;i++){
        for (int j=0;j<mat.col;j++){
            this->at(i, j) = mat.at(i, j);
        }
    }
    return *this;
}
