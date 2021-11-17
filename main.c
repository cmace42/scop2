#include "scop.h"

int main(int argc, char **argv)
{
	t_info info;
	GLuint vertexBuffer;

	if (initWindow(info.window) == true)
	{
		info.context = SDL_GL_CreateContext(info.window);
		vertexBuffer = initOpenGL();
		loop(vertexBuffer);
		//do some stuff
	}
	else
	{
		printf("Failed to init window\n");
		SDL_GL_DeleteContext(info.context);
		SDL_DestroyWindow(info.window);
		SDL_Quit();
	}
	printf("hey");
	GLenum err;
    while ((err = glGetError()) != GL_NO_ERROR) {
        write(STDERR_FILENO, "OpenGL error: ", strlen("OpenGL error: "));
        printf("%d",err);
        write(STDERR_FILENO, "\n", 1); 
    }
}