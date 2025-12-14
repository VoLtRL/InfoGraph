#include "pyramid.h"

#include <iostream>
#include <GLFW/glfw3.h>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

Pyramid::Pyramid(Shader *shader_program) : shader_program_(shader_program->get_id()) {

// Définition des points de la pyramide
GLfloat vertex_buffer_data[] = {
    -0.5f, 0.0f,  0.5f,
     0.5f, 0.0f,  0.5f,
     0.5f, 0.0f, -0.5f,
    -0.5f, 0.0f, -0.5f,
     0.0f, 1.0f, 0.0f
};

// Définition des indices pour les faces de la pyramide
GLint indices[] = {
    0, 1, 2,
    0, 2, 3,
    0, 1, 4,
    1, 2, 4,
    2, 3, 4,
    3, 0, 4

};

    // Génération et liaison des buffers
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertex_buffer_data), vertex_buffer_data, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);    
    
}

Pyramid::~Pyramid() {
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
}

void Pyramid::draw() {

    // Utilise le shader
    glUseProgram(this->shader_program_);
    // Lie le VAO
    glBindVertexArray(VAO);


    // Applique les transformations
    glm::mat4 rotation = glm::rotate(glm::mat4(1.0f), (float) glm::radians(50.0f * glfwGetTime()),glm::vec3(0.0f,1.0f,0.2f));
    glm::mat4 translation = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f,-0.3f,-3.0f));
    glm::mat4 scale = glm::scale(glm::mat4(1.0f),glm::vec3(1.0f,1.0f,1.0f));

    // Combine les transformations
    glm::mat4 view = translation * rotation * scale;

    // Matrice de projection
    glm::mat4 projection = glm::perspective(glm::radians(45.0f),800.0f / 600.0f,0.1f,100.0f);

    // Envoie les matrices au shader
    GLint view_loc = glGetUniformLocation(this->shader_program_, "view");
    glUniformMatrix4fv(view_loc, 1, GL_FALSE, glm::value_ptr(view));
    GLint proj_loc = glGetUniformLocation(this->shader_program_, "projection");
    glUniformMatrix4fv(proj_loc, 1, GL_FALSE, glm::value_ptr(projection));

    // Dessine la pyramide
    glDrawElements(GL_TRIANGLES, 18, GL_UNSIGNED_INT, 0);
}

void Pyramid::key_handler(int key) {
    return;
}



