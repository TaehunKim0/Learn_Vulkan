#define GLFW_INCLUDE_VULKAN //GFLW + Vulkan 헤더 로드
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
        glfwInit(); //GLFW 초기화
        glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API); // OpenGL Context를 만들지 않도록 지시
        glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE); //GFLW 창 크기 조정 비활성화
        window = glfwCreateWindow(WIDTH, HEIGHT, "Vulkan", nullptr, nullptr); //실제 창 생성

        createInstance();
    }

    void mainLoop() {
        while (!glfwWindowShouldClose(window)) //GLFW가 종료되기 전까지 루프(쿼리)
            glfwPollEvents(); //앱 이벤트 발생 확인
    }

    void cleanup() {
        vkDestroyInstance(instance, nullptr);
        glfwDestroyWindow(window);
        glfwTerminate(); //모든 자원 정리
    }

    void createInstance() { //App과 Vulkan Lib를 연결하는 인스턴스 생성

        //App에 대한 정보 채우기
        VkApplicationInfo appInfo{}; 
        appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
        appInfo.pApplicationName = "Hello Triangle";
        appInfo.applicationVersion = VK_MAKE_VERSION(1, 0, 0);
        appInfo.pEngineName = "No Engine";
        appInfo.engineVersion = VK_MAKE_VERSION(1, 0, 0);
        appInfo.apiVersion = VK_API_VERSION_1_0;

        //Instance에 대한 정보 채우기
        VkInstanceCreateInfo createInfo{}; 
        createInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
        createInfo.pApplicationInfo = &appInfo;

        uint32_t glfwExtensionCount = 0;
        const char** glfwExtensions;
        glfwExtensions = glfwGetRequiredInstanceExtensions(&glfwExtensionCount);
        createInfo.enabledExtensionCount = glfwExtensionCount;
        createInfo.ppEnabledExtensionNames = glfwExtensions;
        createInfo.enabledLayerCount = 0;

        //Instance 생성
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