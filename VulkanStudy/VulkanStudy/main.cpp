#define GLFW_INCLUDE_VULKAN //GFLW + Vulkan ��� �ε�
#include <GLFW/glfw3.h>

#include <iostream>
#include <stdexcept>
#include <cstdlib>

const uint32_t WIDTH = 800;
const uint32_t HEIGHT = 600;

class HelloTriangleApplication {
public:
    void run() {
        initVulkan();
        mainLoop();
        cleanup();
    }

private:
    void initVulkan() {
        glfwInit(); //GLFW �ʱ�ȭ
        glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API); //GLFW ���̺귯�� �ʱ�ȭ
        glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE); //GFLW â ũ�� ����
        window = glfwCreateWindow(WIDTH, HEIGHT, "Vulkan", nullptr, nullptr); //���� â ����
    }

    void mainLoop() {
        while (!glfwWindowShouldClose(window))
            glfwPollEvents();
    }

    void cleanup() {
        glfwDestroyWindow(window);
        glfwTerminate();
    }
    
private:
    GLFWwindow* window;
};

int main() {
    HelloTriangleApplication app;
    
    try {
        app.run();
    }
    catch (const std::exception& e) {
        std::cerr << e.what() << std::endl;
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}