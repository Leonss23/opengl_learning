#include "config.h"

int main() {
    GLFWwindow* window = windowInit();

    // Vertex Data
    GLfloat vertices[] = {
            -0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f, // left
            0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f, // right
            0.0f, 0.5f, 0.0f, 0.0f, 0.0f, 1.0f, // top
        };
    GLuint indices[] = {
        0, 1, 2
        };
    GLuint indicesCount = sizeof(indices) / sizeof(indices[0]);

    ShaderProgram ShaderProgram("default.vert", "default.frag");

    VAO VAO1;
    VAO1.Bind();

    BufferObject VBO1(GL_ARRAY_BUFFER, vertices, sizeof(vertices));
    BufferObject EBO1(GL_ELEMENT_ARRAY_BUFFER, indices, sizeof(indices));

    VAO1.LinkAttrib(VBO1, 0, 3, GL_FLOAT, 6 * sizeof(GLfloat), 0);
    VAO1.LinkAttrib(VBO1, 1, 3, GL_FLOAT, 6 * sizeof(GLfloat), (void*)(3 * sizeof(GLfloat)));

    VBO1.Unbind();
    VAO1.Unbind();
    EBO1.Unbind();

    GLuint scaleUniform = glGetUniformLocation(ShaderProgram.ID, "scale");

    // Drawing settings
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

    while (!glfwWindowShouldClose(window)) {
        // logic
        processInput(window);

        // rendering
        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        ShaderProgram.Use();
        glUniform1f(scaleUniform, 1.0f);
        VAO1.Bind();
        glDrawElements(GL_TRIANGLES, indicesCount, GL_UNSIGNED_INT, 0);

        // submit
        glfwSwapBuffers(window);
        glfwPollEvents();
        }

    VAO1.Delete();
    VBO1.Delete();
    EBO1.Delete();
    ShaderProgram.Delete();

    cleanupGlfw(window);
    return 0;
    };
