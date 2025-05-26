#include <GLFW/glfw3.h>
#include <Eigen/Dense>



int create_window(Eigen::VectorXd& X, Eigen::VectorXd& Y)
{
    GLFWwindow* window;

    if(!glfwInit())
        return -1;

    window = glfwCreateWindow(800, 600, "Plot", NULL, NULL);

    if (!window)
    {
        glfwTerminate();
            return -1;
    }

    glfwMakeContextCurrent(window);

    //glClearColor(1.0f, 1.f, 1.f, 1.0f);

    while (!glfwWindowShouldClose(window))
    {
        
        glClear(GL_COLOR_BUFFER_BIT);
        glColor3f(1.0f, 0.0f, 0.0f);
        glPointSize(10.0f);

        glBegin(GL_POINTS);

        for (unsigned int i = 0; i < X.size(); ++i)
        {
        glVertex2f(X(i), Y(i));
        }

        glEnd();
        


        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}