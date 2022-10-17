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
        glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API); // OpenGL Context�� ������ �ʵ��� ����
        glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE); //GFLW â ũ�� ���� ��Ȱ��ȭ
        window = glfwCreateWindow(WIDTH, HEIGHT, "Vulkan", nullptr, nullptr); //���� â ����

        createInstance();
    }

    void mainLoop() {
        while (!glfwWindowShouldClose(window)) //GLFW�� ����Ǳ� ������ ����(����)
            glfwPollEvents(); //�� �̺�Ʈ �߻� Ȯ��
    }

    void cleanup() {
        vkDestroyInstance(instance, nullptr);
        glfwDestroyWindow(window);
        glfwTerminate(); //��� �ڿ� ����
    }

    void createInstance() { //App�� Vulkan Lib�� �����ϴ� �ν��Ͻ� ����

        //App�� ���� ���� ä���
        VkApplicationInfo appInfo{}; 
        appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
        appInfo.pApplicationName = "Hello Triangle";
        appInfo.applicationVersion = VK_MAKE_VERSION(1, 0, 0);
        appInfo.pEngineName = "No Engine";
        appInfo.engineVersion = VK_MAKE_VERSION(1, 0, 0);
        appInfo.apiVersion = VK_API_VERSION_1_0;

        //Instance�� ���� ���� ä���
        VkInstanceCreateInfo createInfo{}; 
        createInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
        createInfo.pApplicationInfo = &appInfo;

        uint32_t glfwExtensionCount = 0;
        const char** glfwExtensions;
        glfwExtensions = glfwGetRequiredInstanceExtensions(&glfwExtensionCount);
        createInfo.enabledExtensionCount = glfwExtensionCount;
        createInfo.ppEnabledExtensionNames = glfwExtensions;
        createInfo.enabledLayerCount = 0;

        //Instance ����
        VkResult result = vkCreateInstance(&createInfo, nullptr, &instance);
        if (result != VK_SUCCESS) throw std::runtime_error("failed to create instance!");
    }
    
private:
    GLFWwindow* window;
    VkInstance instance;
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