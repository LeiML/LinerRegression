//
// Created by LeiLei on 2020/6/22.
//

#include "Liner.hpp"

Liner::Mode Liner::fix(const Matrix &mat) {
    return mat.col == 1?Mode::LINER_BASE:Mode::LINER_ALL;
}

Liner::Liner() : rate(0.01), cycles(100){}

Liner::Liner(const float &rate) : rate(rate), cycles(100){}

Liner::Liner(const int &cycle) : rate(0.01), cycles(cycle){}

Liner::Liner(const float &rate, const int &cycle) : rate(rate), cycles(cycle){}

Matrix Liner::remake(Matrix &sample) {
    Matrix mat = Matrix(sample.row, sample.col+1);
    for(int i=0;i<sample.row;i++){
        for(int j=0;j<mat.col;j++){
            mat.at(i, j) = j == 0?1:sample.at(i, j-1);
        }
    }
    return mat;
}

void Liner::train(Matrix &sample, Matrix &label) {
    try{if (sample.row != label.row) throw MyException("【Error】the label's rows is not equal sample's row");}
    catch (MyException & e) {
        cerr << e.what() << endl;
        exit(-1);
    }
    //判断模式
    if (this->fix(sample) == Mode::LINER_BASE) BaseLiner(sample, label);
    else liner(sample, label);
}

void Liner::BaseLiner(Matrix &sample, Matrix &label) const {
    double k = 1.0;
    double b = 1.0;             //初始化两个基本参数
    for (int i=0;i<this->cycles;i++){
        double sum_k = 0.0;
        double sum_b = 0.0;
        for (int m=0;m<sample.row;m++){
            Matrix temp = sample.rows(m) * k + b;
            Matrix error = temp - label.rows(m);
            sum_k += error.at(0, 0) * sample.at(m, 0);
            sum_b += error.at(0, 0);
        }
        k = k - this->rate * (sum_k / sample.row);
        b = b - this->rate * (sum_b / sample.row);
    }
}

void Liner::liner(Matrix &sample, Matrix &label) const {
    //重新创建新的样本矩阵，添加一条数据。1
    Matrix samp = this->remake(sample);
    //初始化权值矩阵，全为1的矩阵，是一个列向量
    Matrix weight = Matrix::ones(samp.col, 1);
    for(int i=0;i<this->cycles;i++){        //循环次数
        //求取预测值
        Matrix temp = samp.dot(weight);
        //求取误差矩阵
        Matrix error = temp - label;
        //更新权重
        weight = weight - samp.transpose().dot(error) * this->rate;
        cout << weight << endl;
    }
}
