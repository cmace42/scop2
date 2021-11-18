#include "scop.h"

int main(int argc, char **argv)
{
    t_info info;
    t_vao vao;

    if ((info.window = initWindow()) != NULL)
    {
        info.context = SDL_GL_CreateContext(info.window);
		printf("%p\n",info.context);
        vao = initOpenGL();
        loop(vao, info.window);
        //do some stuff
    }
    else
    {
        printf("Failed to init window\n");
        SDL_GL_DeleteContext(info.context);
        SDL_DestroyWindow(info.window);
        SDL_Quit();
    }
}