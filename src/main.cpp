
#define SDL_MAIN_USE_CALLBACKS 1 /* use the callbacks instead of main() */
#include <GL/glew.h>
#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "loadShader.h"
#include "loadDDS.h"
#include "Inputs.h"
#include "voxelBuffers.h"

static SDL_Window *window = NULL;
static SDL_GLContext glctx = NULL;
static Inputs *inputs = NULL;

int winWidth, winHeight;
GLuint elementbuffer;
GLuint VertexArrayID;
GLuint vertexbuffer;
GLuint uvsbuffer;
GLuint DiffuseTexture;
glm::mat4 Projection;
GLuint programID;
GLuint DiffuseTextureID;
GLuint MatrixID;
GLuint ModelMatrixID;
GLuint ViewMatrixID;
float lastTime = 0.0f;

/* This function runs once at startup. */
SDL_AppResult SDL_AppInit(void **appstate, int argc, char *argv[])
{
    /* Create the window */
    window = SDL_CreateWindow("Around The World", 1280, 720, SDL_WINDOW_OPENGL);

    if (!window)
    {
        SDL_Log("Couldn't create window and renderer: %s", SDL_GetError());
        return SDL_APP_FAILURE;
    }

    /* Manage OpenGL context*/
    glctx = SDL_GL_CreateContext(window);
    SDL_GL_MakeCurrent(window, glctx);

    if (glewInit() == GLEW_OK)
        std::cout << glGetString(GL_VERSION) << std::endl;

    inputs = new Inputs(window);

    SDL_GetWindowSize(window, &winWidth, &winHeight);

    // Enable depth test
    glEnable(GL_DEPTH_TEST);
    // Accept fragment if it is closer to the camera than the former one
    glDepthFunc(GL_LESS);

    glEnable(GL_CULL_FACE);

    glFrontFace(GL_CCW);
    glCullFace(GL_BACK);

    // Generate a buffer for the indices

    glGenBuffers(1, &elementbuffer);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elementbuffer);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(voxel_index_data), &voxel_index_data, GL_STATIC_DRAW);

    glGenVertexArrays(1, &VertexArrayID);
    glBindVertexArray(VertexArrayID);

    glGenBuffers(1, &vertexbuffer);
    glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(voxel_vertex_data), &voxel_vertex_data, GL_STATIC_DRAW);

    glGenBuffers(1, &uvsbuffer);
    glBindBuffer(GL_ARRAY_BUFFER, uvsbuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(voxel_uv_data), &voxel_uv_data, GL_STATIC_DRAW);

    DiffuseTexture = loadDDS("../res/diffuse.dds");

    // Camera Projections
    Projection = glm::perspective(glm::radians(45.0f), (float)winWidth / (float)winHeight, 0.1f, 100.0f);

    // Camera matrix
    glm::mat4 View = glm::lookAt(
        glm::vec3(4, 3, 3), // Camera is at (4,3,3), in World Space
        glm::vec3(0, 0, 0), // and looks at the origin
        glm::vec3(0, 1, 0)  // Head is up (set to 0,-1,0 to look upside-down)
    );

    // Create and compile our GLSL program from the shaders
    programID = LoadShaders("../res/shaders/TextureVertShader.vert", "../res/shaders/TextureFragShader.frag");

    // Get a handle for our uniforms
    DiffuseTextureID = glGetUniformLocation(programID, "DiffuseTextureSampler");

    MatrixID = glGetUniformLocation(programID, "MVP");
    ModelMatrixID = glGetUniformLocation(programID, "M");
    ViewMatrixID = glGetUniformLocation(programID, "V");

    return SDL_APP_CONTINUE;
}

/* This function runs when a new event (mouse input, keypresses, etc) occurs. */
SDL_AppResult SDL_AppEvent(void *appstate, SDL_Event *event)
{
    if (event->type == SDL_EVENT_QUIT)
    {
        return SDL_APP_SUCCESS; /* end the program, reporting success to the OS. */
    }
    return SDL_APP_CONTINUE;
}

/* This function runs once per frame, and is the heart of the program. */
SDL_AppResult SDL_AppIterate(void *appstate)
{
    //glClearColor(clear_color.x * clear_color.w, clear_color.y * clear_color.w, clear_color.z * clear_color.w, clear_color.w);

    const Uint64 currentTime = SDL_GetPerformanceCounter();
    float deltaTime = (float)(currentTime - lastTime) / (float)SDL_GetPerformanceFrequency();
    lastTime = currentTime;

    inputs->Update(deltaTime);

    //if (inputs.showUI)
    {
        // Start the Dear ImGui frame
        //ImGui_ImplOpenGL3_NewFrame();
        //ImGui_ImplGlfw_NewFrame();
        //ImGui::NewFrame();
    }

    //if (inputs.showUI)
    {

        static int counter = 0;

        //ImGui::Begin("Around The World"); // Create a window called "Hello, world!" and append into it.

        //ImGui::Text("This is some useful text."); // Display some text (you can use a format strings too)

        // ImGui::SliderFloat("float", nullptr, 0.0f, 1.0f);            // Edit 1 float using a slider from 0.0f to 1.0f
        //ImGui::ColorEdit3("clear color", (float *)&clear_color); // Edit 3 floats representing a colorwd

        //ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / io.Framerate, io.Framerate);
        //ImGui::End();
    }


    // Projection matrix : 45&deg; Field of View, 4:3 ratio, display range : 0.1 unit <-> 100 units
    Projection = glm::perspective(glm::radians(60.0f), 16.0f / 9.0f, 0.1f, 100.0f);
    // Camera matrix
    glm::mat4 View = glm::lookAt(
        inputs->position,                    // Camera is here
        inputs->position + inputs->direction, // and looks here : at the same position, plus "direction"
        inputs->up                           // Head is up (set to 0,-1,0 to look upside-down)
    );

    // ModelMatrix
    glm::mat4 Model = glm::mat4(1.0f);

    glm::mat4 mv = View * Model;
    glm::mat3 mv33 = glm::mat3(mv);
    glm::mat4 mvp = Projection * View * Model;

    /* Render here */
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glUseProgram(programID);

    // 1st attribute buffer : vertices
    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
    glVertexAttribPointer(
        0,        // attribute 0. No particular reason for 0, but must match the layout in the shader.
        3,        // size
        GL_FLOAT, // type
        GL_FALSE, // normalized?
        0,        // stride
        (void *)0 // array buffer offset
    );

    glEnableVertexAttribArray(1);
    glBindBuffer(GL_ARRAY_BUFFER, uvsbuffer);
    glVertexAttribPointer(
        1,        // attribute. No particular reason for 1, but must match the layout in the shader.
        2,        // size
        GL_FLOAT, // type
        GL_FALSE, // normalized?
        0,        // stride
        (void *)0 // array buffer offset
    );

    // This is done in the main loop since each model will have a different MVP matrix (At least for the M part)
    glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &mvp[0][0]);
    glUniformMatrix4fv(ModelMatrixID, 1, GL_FALSE, &Model[0][0]);
    glUniformMatrix4fv(ViewMatrixID, 1, GL_FALSE, &View[0][0]);

    // Bind our diffuse texture in Texture Unit 0
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, DiffuseTexture);
    glUniform1i(DiffuseTextureID, 0);

    // Draw the triangles !
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elementbuffer);
    glDrawElements(
        GL_TRIANGLES,             // mode
        sizeof(voxel_index_data), // count
        GL_UNSIGNED_INT,          // type
        (void *)0                 // element array buffer offset
    );

    glDisableVertexAttribArray(0);
    glDisableVertexAttribArray(1);

    //if (inputs.showUI)
    {
        // Rendering
        //ImGui::Render();
        //ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
    }

    SDL_GL_SwapWindow(window);

    return SDL_APP_CONTINUE;
}

/* This function runs once at shutdown. */
void SDL_AppQuit(void *appstate, SDL_AppResult result)
{

    SDL_DestroyWindow(window);
    window = nullptr;

    SDL_GL_DestroyContext(glctx);
    glctx = nullptr;

    delete (inputs);
    inputs = nullptr;

    glDeleteBuffers(1, &elementbuffer);
    glDeleteBuffers(1, &vertexbuffer);
    glDeleteBuffers(1, &uvsbuffer);
    glDeleteTextures(1, &DiffuseTexture);
    glDeleteVertexArrays(1, &VertexArrayID);
    glDeleteProgram(programID);
}