import OpenGL.GL as GL              # standard Python OpenGL wrapper
import numpy as np                  # all matrix manipulations & OpenGL args
import glfw

class Pyramid:

    def __init__(self, shader):
        self.shader = shader

        # pyramid position buffer, Numpy array of our 3D coordinates
        position = np.array(((-0.5, -0.5, -0.5), (-0.5, 0.5, -0.5), (0.5, 0.5, -0.5), (0.5, -0.5, -0.5), (0, 0, 0.5)),'f')

        indices = np.array(((0, 1, 2), (0, 2, 3), (0, 1, 4), (1, 2, 4), (2, 3, 4), (0, 3, 4)), dtype=np.int8)

        self.glid = GL.glGenVertexArrays(1)  # create OpenGL vertex array id
        GL.glBindVertexArray(self.glid)      # activate to receive state below
        #self.buffers = [GL.glGenBuffers(2)]  # create buffer for position attrib
        self.buffers = GL.glGenBuffers(2)	 # if n > 1, use this instead
        # GL.glGenBuffers(n) with n > 1 directly returns a list and not an index

        # create position attribute, send to GPU, declare type & per-vertex size
        loc = GL.glGetAttribLocation(shader.glid, 'position')
        GL.glEnableVertexAttribArray(loc)    # assign to position attribute
        GL.glBindBuffer(GL.GL_ARRAY_BUFFER, self.buffers[0])
        GL.glBufferData(GL.GL_ARRAY_BUFFER, position, GL.GL_STATIC_DRAW)
        GL.glVertexAttribPointer(loc, 3, GL.GL_FLOAT, False, 0, None)
        GL.glBindBuffer(GL.GL_ARRAY_BUFFER, self.buffers[1])
        GL.glBufferData(GL.GL_ARRAY_BUFFER, indices, GL.GL_STATIC_DRAW)


    def draw(self):
        # use shader, draw triangle as GL_TRIANGLE vertex array, draw array call
        GL.glUseProgram(self.shader.glid)
        GL.glBindVertexArray(self.glid)
        GL.glDrawArrays(GL.GL_TRIANGLES, 0, 18)

        # perspective

        rotation = np.radians(45.0 + glfw.get_time())
        scale_vector = np.array([1.0, 1.0, 1.0])


    def __del__(self):
        GL.glDeleteVertexArrays(1, [self.glid])
        GL.glDeleteBuffers(1, self.buffers)