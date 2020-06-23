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
    int rows;               //����
    int cols;               //����
};

class Matrix{
public:
    //�޲������캯��
    Matrix();
    //ʹ�����й������
    Matrix(int row, int col);
    //ʹ��size���캯��
    explicit Matrix(Size size);
    //ʹ�þ��󹹽�����
    Matrix(Matrix &mat);
    //ʹ�ö�άָ�����鹹�칹������
    Matrix(double **data, int row, int col);
    //ʹ�ö�ά��vector����
    explicit Matrix(vector<vector<double>>&data);
    //����������
    virtual ~Matrix();
    //����ȫ������0�ľ���
    static Matrix zeros(int rows, int cols);
    //����ȫ������1�ľ���
    static Matrix ones(int rows, int cols);
    //����ȫ������ĳһ��ֵ�ľ���
    static Matrix create(int rows, int cols, double num);
    //����ĳ��λ�õ�Ԫ��
    virtual double &at(const int&rows, const int &cols);
    //����ĳһ�е�Ԫ��
    virtual Matrix rows(const int&r);
    //����ĳһ�е�Ԫ��
    virtual Matrix cols(const int&c);
    //��ȡ���������������
    virtual Size size();
    //��ȡһ����������Ԫ�����
    double sum();
    //����ĳ˷����㣨��ˣ�
    virtual Matrix dot(Matrix & matrix);
    //������ת��
    virtual Matrix transpose();
    //�����������㣬eΪ��
    virtual Matrix exp();
    //����������㣬�������أ�����Ϊ��
    virtual Matrix exp(int pow);
    //���������         ������������
    friend ostream &operator<<(ostream&os, const Matrix&matrix);
    //���صȺ�=���޸ľ����ֵ
    Matrix& operator=(Matrix mat);
    //�������������㣨+��-��*��/��      ����+
    Matrix operator+(double num);
    //����ļӷ�����
    Matrix operator+(Matrix mat);
    //����-
    Matrix operator-(double num);
    //����ļ�������
    Matrix operator-(Matrix mat);
    //���ŵ����������
    Matrix operator-();
    //����*
    Matrix operator*(double num);
    //����������֮��ġ���
    Matrix operator*(Matrix mat);
    //���س�
    Matrix operator/(double num);
    //һЩ�����Ĳ���
    int row;                    //���������
    int col;                    //���������
    double **data{};            //��������ݴ洢��ָ��
private:
    //��ʼ�����ݾ��������
    void init();
};

template<class Tp>
int length(Tp &data){
    return sizeof(data) / sizeof(data[0]);
}

#endif //MATRIX_HPP
