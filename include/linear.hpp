#include <iostream>
#include <list>
#include <set>
#include <string>
#include <random>
#include <ctime>

#include <Eigen/Dense>

class LinearRegression{
public:
    LinearRegression(){};

    void
    fit(Eigen::MatrixXd& X, Eigen::VectorXd& y);

    void
    predict(Eigen::MatrixXd& X);

private:
    Eigen::VectorXd w;  // Вектор весов (включая bias)

};


void
LinearRegression::fit(Eigen::MatrixXd& X, Eigen::VectorXd& y)
{
    int l = X.rows();  // число образцов (строк)

    Eigen::MatrixXd ones_column =  Eigen::MatrixXd::Ones(l,1);
    Eigen::MatrixXd X_train (l, X.cols() + 1);
    X_train << X , ones_column;


     w = (X_train.transpose() * X_train).ldlt().solve(X_train.transpose() * y);
}

void
LinearRegression::predict(Eigen::MatrixXd& X)
{
    int l = X.rows();  // число образцов (строк)

    Eigen::MatrixXd ones_column =  Eigen::MatrixXd::Ones(l,1);
    Eigen::MatrixXd X_train (l, X.cols() + 1);
    X_train << X , ones_column;

 //         y_pred = X_train @ self.w 
 //доделать
}



Eigen::VectorXd
normaldistribution(int size)
{
    std::random_device rd;
    std::mt19937 engine(rd());
    std::normal_distribution<double> dist(0.0, 1.0);

    Eigen::VectorXd data(size);

    for (int i = 0; i < size; ++i)
    {
        data(i) = dist(engine);
    }

     return data;
}


double
linearExpression(double x)
{
    return 5 * x + 6;
}

Eigen::VectorXd
linespace(double start, double finish, int count)
{
    Eigen::VectorXd res(count);
    double step = (finish - start) / (count -1);
    
    for (int i = 0; i < count; ++i)
    {
        res(i) =  start + i * step;
    }

    return  res;
}



std::list<Eigen::VectorXd>
trainTestSplit(const Eigen::VectorXd& X, const Eigen::VectorXd& Y, double train_size)
{
    unsigned int sizeX = (X.size() * train_size);
    unsigned int sizeY = X.size() - sizeX;

    std::random_device rd;
    std::default_random_engine engine(rd());
    std::uniform_int_distribution<int> dist(0.0, 49.0);

    std::set<int> key_train; // индексы для перемешивания
    std::set<int> key_test;

    while (key_train.size() < sizeX)
        key_train.insert(dist(engine));

    
    for (int i = 0; i < X.size(); ++i)
        if ( auto search =  key_train.find(i); search == key_train.end())
           key_test.insert(i);


    Eigen::VectorXd X_train(sizeX);
    Eigen::VectorXd X_test(sizeY);

    Eigen::VectorXd Y_train(sizeX);
    Eigen::VectorXd Y_test(sizeY);


    for (int i = 0 , train = 0 , test = 0; i < X.size(); ++i)
    {
        if ( auto searchTrain =  key_train.find(i); searchTrain != key_train.end())
        {
           X_train(train) = X(i);
           Y_train(train++) = Y(i);
           continue;
        }

        if ( auto searchTest =  key_test.find(i); searchTest != key_test.end())
        { 
            X_test(test) = X(i);
            Y_test(test++) = Y(i);
        }
    }

    return std::list<Eigen::VectorXd> {X_train, X_test, Y_train, Y_test};
}