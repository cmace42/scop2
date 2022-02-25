#include "scop.h"

int main(int argc, char **argv)
{
	t_env env;
	size_t i;
	int ret;

	if (argc != 2)
	{
		printf("fais l'usage\n");
		return (0);
	}
	if ((ret = init(&env, argv[1])) == GET_RESULT)
	{
		printf("+---------------+-------------------------------------------------------------------+\n\
| Scop control  |                                                                   |\n\
+---------------+-------------------------------------------------------------------+\n\
| WASD          | Déplacement de la caméra                                          |\n\
| Numpad 824679 | fais tourner ou déplacer l'objet en fonction du mode              |\n\
| L             | Change le mode(Rotation/Translation) du model                     |\n\
| zxc           | Change la couleur sur un R, G ou B                                |\n\
| o             | Change la couleur constamment                                     |\n\
| u             | Active/Desactive le mode gris                                     |\n\
| p             | Transition entre mode texture/sans texture                        |\n\
| i             | Change le type d'affectation de couleur(Par face ou par triangle) |\n\
| k             | Active/Desactive le GL_CULL_FACE                                  |\n\
| pageUp        | Active/Desactive le GL_DEPTH_TEST                                 |\n\
| delete        | Affiche sommets/trait intersommet/faces                           |\n\
+---------------+-------------------------------------------------------------------+\n");
		loop(env);
	}
	if (ret != WRONG_CHAR && ret != RIP_READ && ret != RIP_OPEN && ret != NO_VERTEX)
		freeAll(&env);
	glDeleteTextures(1, &env.texture);
	glDeleteProgram(env.programId);
	i = 0;
	while(i < env.modelData.size_groupe)
	{
		glDeleteVertexArrays(1, &env.vao[i].VertexArrayID);
		glDeleteBuffers(1, &env.vao[i].vertexBuffer);
		glDeleteBuffers(1, &env.vao[i].textureBuffer);
		i++;
	}
	if (env.context)
		SDL_GL_DeleteContext(env.context);
	SDL_DestroyWindow(env.window);
	SDL_Quit();
}