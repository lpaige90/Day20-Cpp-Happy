#include "D:/GLFW/include/GLFW/glfw3.h"
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "D:/Google Drive/Programming/Simple OpenGL Image Library/src/SOIL.h"

static void error_callback(int error, const char* description)
{
    fputs(description, stderr);
}
static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GL_TRUE);
}

int main(void)
{
    GLFWwindow* window;

    glfwSetErrorCallback(error_callback);
    if (!glfwInit()) {
        exit(EXIT_FAILURE);
    }

    window = glfwCreateWindow(1280, 680, "Happy", NULL, NULL);

    if (!window)
    {
        glfwTerminate();
        exit(EXIT_FAILURE);
    }

    glfwMakeContextCurrent(window);
    glfwSetKeyCallback(window, key_callback);
    glClearColor(1.0f,1.0f,1.0f,0.0f);
    while (!glfwWindowShouldClose(window))
    {
        float ratio;
        int width, height;

        glfwGetFramebufferSize(window, &width, &height);

        glViewport(0, 0, width, height);
        glClear(GL_COLOR_BUFFER_BIT);//Buffer enabled for color writing

        glMatrixMode(GL_PROJECTION);//Projection matrix stack
        glLoadIdentity();
        glOrtho(-ratio, ratio, -1.0f, 1.0f, 1.0f, -1.0f);//Projection

        glMatrixMode(GL_MODELVIEW);//Modelview matrix stack
        glLoadIdentity();

        /* load an image file directly as a new OpenGL texture */
        GLuint happy = SOIL_load_OGL_texture
        (
            "happy.png",
            SOIL_LOAD_AUTO,
            SOIL_CREATE_NEW_ID,
            SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT
        );
    
        /* check for an error during the load process */
        if( 0 == happy ) {
            printf( "SOIL loading error: '%s'\n", SOIL_last_result() );
        }

        glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, happy);
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        glBegin(GL_QUADS);
        glTexCoord2f(0.0f, 0.0f); 
        glVertex2f(-0.200f, -0.254f);
        glTexCoord2f(1.0f, 0.0f); 
        glVertex2f( 0.200f, -0.254f);
        glTexCoord2f(1.0f, 1.0f); 
        glVertex2f( 0.200f,  0.254f);
        glTexCoord2f(0.0f, 1.0f); 
        glVertex2f(-0.200f, 0.254f);
        glEnd();

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwDestroyWindow(window);
    glfwTerminate();
    exit(EXIT_SUCCESS);
}