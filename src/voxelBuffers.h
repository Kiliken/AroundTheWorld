#pragma once

#include <GL/glew.h>
#include <vector>

// Voxel Vertices
static const GLfloat voxel_vertex_data[] = {
    0.0f, 0.0f, 0.0f, // 0 bottom-left
    1.0f, 0.0f, 0.0f, // 1 bottom-right
    0.0f, 1.0f, 0.0f, // 2 top-left
    1.0f, 1.0f, 0.0f, // 3 top-right

    0.0f, 0.0f, 1.0f, // 4 bottom-left
    1.0f, 0.0f, 1.0f, // 5 bottom-right
    0.0f, 1.0f, 1.0f, // 6 top-left
    1.0f, 1.0f, 1.0f  // 7 top-right
};



// Voxel Uvs
static const GLfloat voxel_uv_data[] = {
    // Front face (0,1,2,3)
    0.0f, 0.0f,
    1.0f, 0.0f,
    0.0f, 1.0f,
    1.0f, 1.0f,

    // Back face (4,5,6,7)
    0.0f, 0.0f,
    1.0f, 0.0f,
    0.0f, 1.0f,
    1.0f, 1.0f,

    // Left face (0,2,4,6)
    0.0f, 0.0f,
    1.0f, 0.0f,
    0.0f, 1.0f,
    1.0f, 1.0f,

    // Right face (1,3,5,7)
    0.0f, 0.0f,
    1.0f, 0.0f,
    0.0f, 1.0f,
    1.0f, 1.0f,

    // Bottom face (0,1,4,5)
    0.0f, 0.0f,
    1.0f, 0.0f,
    0.0f, 1.0f,
    1.0f, 1.0f,

    // Top face (2,3,6,7)
    0.0f, 0.0f,
    1.0f, 0.0f,
    0.0f, 1.0f,
    1.0f, 1.0f
};


// Voxel indicies 
static const GLint voxel_index_data[] = {
    // Front face (z = 0)
    0, 2, 1,
    2, 3, 1,

    // Back face (z = 1)
    4, 5, 6,
    5, 7, 6,

    // Left face (x = 0)
    0, 4, 2,
    4, 6, 2,

    // Right face (x = 1)
    1, 3, 5,
    3, 7, 5,

    // Bottom face (y = 0)
    0, 1, 4,
    1, 5, 4,

    // Top face (y = 1)
    2, 6, 3,
    6, 7, 3
};
