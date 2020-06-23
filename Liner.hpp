//
// Created by LeiLei on 2020/6/22.
//

#ifndef Liner_HPP
#define Liner_HPP
#include "Matrix.hpp"
class Liner{
public:
    //构造函数
    Liner();
    //自定义学习率
    explicit Liner(const float&rate);
    //自定义循环次数
    explicit Liner(const int&cycle);
    //学习率、循环次数都进行自定义
    Liner(const float&rate, const int&cycle);
    //析构函数
    ~Liner() = default;
    //样本矩阵的重新构建
    static Matrix remake(Matrix & sample);
    //进行训练
    void train(Matrix & sample, Matrix & label);
    //模式的选择，自适应选择
    enum Mode{LINER_BASE=1, LINER_ALL=2};           //设定选择的模式
private:
    //确定模式
    virtual Mode fix(const Matrix &mat);
    //基础最小二乘的算法进行线性回归，使用梯度下降算法
    void BaseLiner(Matrix & sample, Matrix & label) const;
    //符合多元特征的线性回归模型的刻画
    void liner(Matrix & sample, Matrix & label) const;
    //学习率
    float rate;
    //循环次数
    int cycles;
};
#endif //Liner_HPP
