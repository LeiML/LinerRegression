//
// Created by LeiLei on 2020/6/22.
//

#ifndef Liner_HPP
#define Liner_HPP
#include "Matrix.hpp"
class Liner{
public:
    //���캯��
    Liner();
    //�Զ���ѧϰ��
    explicit Liner(const float&rate);
    //�Զ���ѭ������
    explicit Liner(const int&cycle);
    //ѧϰ�ʡ�ѭ�������������Զ���
    Liner(const float&rate, const int&cycle);
    //��������
    ~Liner() = default;
    //������������¹���
    static Matrix remake(Matrix & sample);
    //����ѵ��
    void train(Matrix & sample, Matrix & label);
    //ģʽ��ѡ������Ӧѡ��
    enum Mode{LINER_BASE=1, LINER_ALL=2};           //�趨ѡ���ģʽ
private:
    //ȷ��ģʽ
    virtual Mode fix(const Matrix &mat);
    //������С���˵��㷨�������Իع飬ʹ���ݶ��½��㷨
    void BaseLiner(Matrix & sample, Matrix & label) const;
    //���϶�Ԫ���������Իع�ģ�͵Ŀ̻�
    void liner(Matrix & sample, Matrix & label) const;
    //ѧϰ��
    float rate;
    //ѭ������
    int cycles;
};
#endif //Liner_HPP
