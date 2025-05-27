#include "linear.hpp"

int main(){

//по признакам сгенерируем значения таргетов с некоторым шумом
    int objects_num = 50;
    Eigen::VectorXd X1 = linespace(-5, 5, objects_num);

    Eigen::VectorXd Y1(objects_num);

    double* data = X1.data();
    Eigen::VectorXd distribution = normaldistribution(50);

    for (int i = 0; i < X1.size(); ++i)
    {
        Y1(i) = linearExpression(data[i]) + distribution(i) * 5;
    }


    std::list<Eigen::VectorXd> list = trainTestSplit(X1, Y1, 0.5);

    Eigen::VectorXd X_train = list.front();
    list.pop_front();

    Eigen::VectorXd X_test = list.front();
    list.pop_front();

    Eigen::VectorXd Y_train = list.front();
    list.pop_front();

    Eigen::VectorXd Y_test = list.front();
    list.pop_front();

    
// Обучение модели
     LinearRegression model;
     model.fit(X_train, Y_train);
     Eigen::VectorXd y_pred =  model.predict(X_test);
    Eigen::VectorXd y_pred2 =  model.predict(X1);


     myPlot(X_train, Y_train, X_test, y_pred, X1, y_pred2);


    return  0;
}