#include "Liner.hpp"

int main(int argc, char **argv){
    vector<vector<double>>data = {{1, 1}, {2, 1}, {3, 2}, {4, 5}};
    vector<vector<double>>lab = {{6}, {8}, {13}, {24}};
    Matrix sample = Matrix(data);
    Matrix label = Matrix(lab);
    Liner liner = Liner(0.01, 100);
    liner.train(sample, label);
}
