#include <iostream>
#include <list>
#include <set>
#include <string>
#include <random>
#include <ctime>

#include <Eigen/Dense>
#include <sciplot/sciplot.hpp>


class LinearRegression{
public:
    LinearRegression(){};

    void
    fit(const Eigen::VectorXd& X, Eigen::VectorXd& y);

    Eigen::VectorXd 
    predict(const Eigen::VectorXd& X);

private:
    Eigen::VectorXd w;  // Вектор весов (включая bias)

};


void
LinearRegression::fit(const Eigen::VectorXd& X, Eigen::VectorXd& y)
{
    int l = X.rows();  // число образцов (строк)

    Eigen::MatrixXd ones_column =  Eigen::MatrixXd::Ones(l,1);
    Eigen::MatrixXd X_train (l, X.cols() + 1);
    X_train << X , ones_column;

    std::cout << "YES" <<std::endl;

    w = (X_train.transpose() * X_train).inverse() * (X_train.transpose() * y);

    std::cout << "w\n" << w <<std::endl;
}

Eigen::VectorXd 
LinearRegression::predict(const Eigen::VectorXd& X)
{
    int l = X.rows();  // число образцов (строк)

    Eigen::MatrixXd ones_column =  Eigen::MatrixXd::Ones(l,1);
    Eigen::MatrixXd X_train (l, X.cols() + 1);
    X_train << X , ones_column;

    Eigen::VectorXd y_pred = X_train * w;

    return y_pred;
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


void myPlot(const Eigen::VectorXd& X_train,const Eigen::VectorXd& Y_train, 
            const Eigen::VectorXd& X_test,const Eigen::VectorXd& Y_test,
            const Eigen::VectorXd& X_real,
            const Eigen::VectorXd& y_pred)
{
    sciplot::Plot2D plot;

    plot.xlabel("x");
    plot.ylabel("y");

    plot.xrange(-6.0, 6.0);
    plot.yrange(-50.0, 50.0);

    plot.legend()
        .atOutsideBottom()
        .displayHorizontal()
        .displayExpandWidthBy(2);


    plot.drawPoints(X_train, Y_train).lineWidth(9)
                                          .pointType(0) 
                                          .lineColor("blue")
                                          .label("train");


    plot.drawPoints(X_test,  Y_test).lineWidth(9)
                                         .pointType(0)
                                         .lineColor("yellow")
                                         .label("test");


    Eigen::VectorXd Y1(X_real.size());
    const double* data = X_real.data();

    for (int i = 0; i < X_real.size(); ++i)
    {
        Y1(i) = linearExpression(data[i]);
    }


    plot.drawCurve(X_real, Y1).lineWidth(3)
                                   .label("real")
                                   .lineColor("red");



    plot.drawCurve(X_real, y_pred).lineWidth(3)
                                   .label("predicted")
                                   .lineColor("black");



    sciplot::Figure fig = {{plot}};
    sciplot::Canvas canvas = {{fig}};

    canvas.size(800, 600);

    canvas.show();
}