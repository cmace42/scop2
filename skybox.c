#include "scop.h"

int loadSkyBox(char **file, GLuint *textureId)
{
	size_t i;
	t_bmp bmp;

	i = 0;
	glGenTextures(1, &(*textureId));
	glBindTexture(GL_TEXTURE_CUBE_MAP, *textureId);
	while (i < 6)
	{
		if (loadBMP_custom(file[i], &bmp) != GET_RESULT)
			return (-1);
		glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i,
			0, GL_RGB, bmp.width, bmp.height, 0, GL_RGB, GL_UNSIGNED_BYTE, bmp.data);
		free(bmp.data);
		i++;
	}
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
	return (1);
}