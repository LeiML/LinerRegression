//
// Created by LeiLei on 2020/6/18.
//

#ifndef MATRIX_HPP
#define MATRIX_HPP
#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

class MyException : public exception{
public:
    explicit MyException(const char* error):exception(error){};
};

class Size{
public:
    Size();
    Size(int row, int col);
    friend ostream& operator<<(ostream &os, const Size&);
    int rows;               //行数
    int cols;               //列数
};

class Matrix{
public:
    //无参数构造函数
    Matrix();
    //使用行列构造矩阵
    Matrix(int row, int col);
    //使用size构造函数
    explicit Matrix(Size size);
    //使用矩阵构建矩阵
    Matrix(Matrix &mat);
    //使用二维指针数组构造构建矩阵
    Matrix(double **data, int row, int col);
    //使用二维的vector构造
    explicit Matrix(vector<vector<double>>&data);
    //虚析构函数
    virtual ~Matrix();
    //创建全部都是0的矩阵
    static Matrix zeros(int rows, int cols);
    //创建全部都是1的矩阵
    static Matrix ones(int rows, int cols);
    //创建全部都是某一个值的矩阵
    static Matrix create(int rows, int cols, double num);
    //访问某个位置的元素
    virtual double &at(const int&rows, const int &cols);
    //访问某一行的元素
    virtual Matrix rows(const int&r);
    //访问某一列的元素
    virtual Matrix cols(const int&c);
    //获取矩阵的行数与列数
    virtual Size size();
    //求取一个列向量的元素求和
    double sum();
    //矩阵的乘法运算（点乘）
    virtual Matrix dot(Matrix & matrix);
    //向量的转置
    virtual Matrix transpose();
    //矩阵求幂运算，e为底
    virtual Matrix exp();
    //矩阵的幂运算，函数重载，任意为底
    virtual Matrix exp(int pow);
    //重载运算符         重载输出运算符
    friend ostream &operator<<(ostream&os, const Matrix&matrix);
    //重载等号=，修改矩阵的值
    Matrix& operator=(Matrix mat);
    //基础的四则运算（+，-，*，/）      重载+
    Matrix operator+(double num);
    //矩阵的加法运算
    Matrix operator+(Matrix mat);
    //重载-
    Matrix operator-(double num);
    //矩阵的减法运算
    Matrix operator-(Matrix mat);
    //符号的运算符重载
    Matrix operator-();
    //重载*
    Matrix operator*(double num);
    //重载俩矩阵之间的×乘
    Matrix operator*(Matrix mat);
    //重载除
    Matrix operator/(double num);
    //一些基础的参数
    int row;                    //矩阵的行数
    int col;                    //矩阵的列数
    double **data{};            //矩阵的数据存储的指针
private:
    //初始化数据矩阵的数据
    void init();
};

template<class Tp>
int length(Tp &data){
    return sizeof(data) / sizeof(data[0]);
}

#endif //MATRIX_HPP
