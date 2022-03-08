/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loadbmp.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmace <cmace@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/01 11:09:53 by cmace             #+#    #+#             */
/*   Updated: 2022/03/08 14:00:43 by cmace            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

int	loadBMP_custom(const char *imagepath, t_bmp *bmp)
{
	// Données lues à partir de l'en-tête du fichier BMP
	unsigned char	header[54]; // Chaque fichier BMP débute par un en-tête de 54 octets
	unsigned int	dataPos; // Position dans le fichier où les données débutent
	unsigned int	imageSize; // = bmp.width*bmp.height*3
	FILE			*file;

	file = fopen(imagepath, "rb");
	if (!file)
	{
		printf("Image could not be opened\n");
		return (0);
	}
	if (fread(header, 1, 54, file) != 54)
	{ // S'il n'est pas possible de lire 54 octets : problème
		printf("Not a correct BMP file\n");
		return (0);
	}
	if (header[0] != 'B' || header[1] != 'M')
	{
		printf("Not a correct BMP file\n");
		return (0);
	}
	// Lit des entiers à partir du tableau d'octets
	dataPos = *(int *)&(header[0x0A]);
	imageSize = *(int *)&(header[0x22]);
	bmp->width = *(int *)&(header[0x12]);
	bmp->height = *(int *)&(header[0x16]);
	// Certains fichiers BMP sont mal formés, on devine les informations manquantes
	if (imageSize == 0)
		imageSize = bmp->width * bmp->height * 3; // 3 : un octet pour chaque composante rouge, vert et bleu
	if (dataPos == 0)
		dataPos = 54; // l'en-tête BMP est fait de cette façon
	// Crée un tampon
	if ((bmp->data = (char *)malloc(sizeof(char) * (imageSize))) == NULL)
	{
		return (RIP_MALLOC);
	}
	// Lit les données à partir du fichier pour les mettre dans le tampon
	fread(bmp->data, 1, imageSize, file);
	fclose(file);
	return (GET_RESULT);
}

GLuint	getTextureId(t_bmp bmp)
{
	GLuint	textureID;

	glGenTextures(1, &textureID);
	glBindTexture(GL_TEXTURE_2D, textureID);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, bmp.width, bmp.height, 0, GL_BGR, GL_UNSIGNED_BYTE, bmp.data);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glGenerateMipmap(GL_TEXTURE_2D);
	return (textureID);
}
