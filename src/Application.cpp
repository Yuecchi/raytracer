#include <cstdlib>
#include <ctime>
#include <iostream>
#include <chrono>

#include "Application.hpp"
#include "Renderer.hpp"  
#include "Scene.hpp"
#include "Mesh.hpp"


Application::Application(const char* name, unsigned int window_width, unsigned int window_height) : m_name(name) {
    m_window = new Window(m_name, window_width, window_height);
    Renderer::init(window_width, window_height);
    run();
}

void Application::run() {

    srand(time(NULL));
    
    Scene *scene = Scene::createScene(); 

    Material phongRed    = { glm::vec3(1.0f, 0.0f, 0.0f), 0.1f, 0.9f, 0.9f, 0.5f, 128 };
    Material phongBlue   = { glm::vec3(0.0f, 0.0f, 1.0f), 0.1f, 0.9f, 0.9f, 0.5f, 128 };
    Material phongGreen  = { glm::vec3(0.0f, 1.0f, 0.0f), 0.1f, 0.9f, 0.9f, 0.5f, 128 };
    Material phongPurple = { glm::vec3(1.0f, 0.0f, 1.0f), 0.1f, 0.9f, 0.9f, 0.5f, 128 };
    Material phongCyan   = { glm::vec3(0.0f, 1.0f, 1.0f), 0.1f, 0.9f, 0.9f, 0.5f, 128 };
    Material phongYellow = { glm::vec3(1.0f, 1.0f, 0.0f), 0.1f, 0.9f, 0.9f, 0.5f, 128 };

    Material blackMirror = { glm::vec3(0.0f, 0.0f, 0.0f), 0.1f, 0.9f, 0.9f, 0.9f, 128 };
    Material greyMirror = { glm::vec3(0.1f, 0.1f, 0.1f), 0.1f, 0.9f, 0.9f, 0.9f, 128 };
 
    scene->addObject(new Sphere(glm::vec3(0.0f, -5.0f, -50.0f),   5.0f, phongRed));
    scene->addObject(new Sphere(glm::vec3(-25.0f, -5.0f, -55.0f), 5.0f, phongGreen));
    scene->addObject(new Sphere(glm::vec3(-18.0f, -5.0f, -80.0f), 5.0f, phongBlue)); 
    scene->addObject(new Sphere(glm::vec3(20.0f, -5.0f, -20.0f),  5.0f, phongPurple));
    scene->addObject(new Sphere(glm::vec3(-25.0f, -5.0f, -30.0f), 5.0f, phongCyan));  
    scene->addObject(new Sphere(glm::vec3(20.0f, -5.0f, -50.0f),  5.0f, phongYellow));

    scene->addObject(new Triangle(
        glm::vec3(-35.0f, 0.0f, -100.0f),
        glm::vec3(0.0f, 50.0f, -80.0f),
        glm::vec3(35.0f, 0.0f, -100.0f),
        blackMirror
        ));  

    scene->addObject(new Plane(glm::vec3(0.0f, 1.0f, 0.0f), -10.0f, greyMirror));
    scene->addLight(new Light(glm::vec3(0.0f, 50.0f, -75.0f), 5000.0f));
    scene->addLight(new Light(glm::vec3(10.0f, -9.0f, -30.0f), 10.0f));
    
    /*
    scene->addLight(new Light(glm::vec3(0.0f, 1000.0f, 0.0f), 1000000.0f));
    scene->addLight(new Light(glm::vec3(0.0f, 9.0f, 6.8f), 500.0f));


    scene->addObject(new Sphere(glm::vec3(0.0f, 3.0f, 15.0f), 3.0f, phongRed));
    scene->addObject(new Sphere(glm::vec3(-20.0f, 10.0f, -15.0f), 10.0f, phongBlue)); 
    scene->addObject(new Sphere(glm::vec3(20.0f, 5.0f, 0.0f), 5.0f, phongGreen));
    scene->addObject(new Sphere(glm::vec3(0.0f, 20.0f, 40.0f), 20.0f, phongPurple));


    scene->addObject(new Plane(glm::vec3(0.0f, 1.0f, 0.0f), 0.0f, greyMirror));
    Mesh mesh("assets/mesh20.obj");
    scene->addObject(&mesh);
    */
    
    //scene->camera().setPosition(glm::vec3(30.0f, 10.0f, 30.0f));
    //scene->camera().rotate(3.141f / -4.0f);

    while (!m_window->closed()) { 
        m_window->poll();
        Renderer::clear();
        
        auto start = std::chrono::system_clock::now();
        
        Renderer::drawScene(scene);
        //scene->camera().rotate(3.141f / 15.0f);
        
        auto end = std::chrono::system_clock::now();
        auto timeElapsed = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
        std::cout << 1.0f / (timeElapsed.count() / 1e+6) << "\n";
        
        m_window->update(); 
    }

    scene->deleteScene();

}

Application::~Application() {
    delete m_window;
};