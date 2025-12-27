#pragma once

#include <GL/glew.h>
#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

class Inputs
{
private:
    // window reference
    SDL_Window *win;

    // win size
    int winWidth, winHeight;

    // mouse Pos
    float xpos, ypos;
    // mouse Scroll
    double scrollY = 0.0;
    // horizontal angle : toward -Z
    float horizontalAngle = 3.14f;
    // vertical angle : 0, look at the horizon
    float verticalAngle = 0.0f;
    // Initial Field of View
    float initialFoV = 45.0f;

    float speed = 3.0f;
    float mouseSpeed = 0.05f;

    bool tabWasDown;

public:
    Inputs(SDL_Window *mainWindow);
    ~Inputs();
    void Update(float dt);

    // directions
    glm::vec3 direction, right, up;

    // position
    glm::vec3 position = glm::vec3(0, 0, 5);

    bool showUI = false;

    // field of view
    float FoV;
};

Inputs::Inputs(SDL_Window *mainWindow)
{
    win = mainWindow;

    // glfwGetWindowSize(win, &winWidth, &winHeight);
    // glfwSetCursorPos(win, winWidth / 2, winHeight / 2);

    SDL_GetWindowSize(win, &winWidth, &winHeight);
    SDL_WarpMouseInWindow(win, winWidth / 2.0f, winHeight / 2.0f);
}

Inputs::~Inputs()
{
}

void Inputs::Update(float dt)
{
    const bool *key_states = SDL_GetKeyboardState(NULL);

    if (!showUI)
    {
        Uint32 mouseInputs = SDL_GetMouseState(&xpos, &ypos);
        SDL_WarpMouseInWindow(win, winWidth / 2.0f, winHeight / 2.0f);
    }

    horizontalAngle += mouseSpeed * dt * float(winWidth / 2 - xpos);
    verticalAngle += mouseSpeed * dt * float(winHeight / 2 - ypos);

    // Direction : Spherical coordinates to Cartesian coordinates conversion
    direction = glm::vec3(
        cos(verticalAngle) * sin(horizontalAngle),
        sin(verticalAngle),
        cos(verticalAngle) * cos(horizontalAngle));

    // Right vector
    right = glm::vec3(
        sin(horizontalAngle - 3.14f / 2.0f),
        0,
        cos(horizontalAngle - 3.14f / 2.0f));

    // Up vector : perpendicular to both direction and right
    up = glm::cross(right, direction);

    {
        // Move forward
        if (key_states[SDL_SCANCODE_W])
        {
            position += direction * dt * speed;
        }
        // Move backward
        if (key_states[SDL_SCANCODE_S])
        {
            position -= direction * dt * speed;
        }
        // Strafe right
        if (key_states[SDL_SCANCODE_D])
        {
            position += right * dt * speed;
        }
        // Strafe left
        if (key_states[SDL_SCANCODE_A])
        {
            position -= right * dt * speed;
        }
        if (key_states[SDL_SCANCODE_TAB])
        {
            showUI = !showUI;
            // glfwSetInputMode(win, GLFW_CURSOR, (showUI ? GLFW_CURSOR_NORMAL : GLFW_CURSOR_HIDDEN));
            // glfwSetCursorPos(win, winWidth / 2, winHeight / 2);
        }
        if (key_states[SDL_SCANCODE_ESCAPE])
        {
            // glfwSetWindowShouldClose(win, GLFW_TRUE);
            SDL_Event e; 
            e.type = SDL_EVENT_QUIT;
            SDL_PushEvent(&e);
        }
    }
}
