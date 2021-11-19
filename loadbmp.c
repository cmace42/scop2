#include "scop.h"

GLuint loadBMP_custom(const char *imagepath)
{
	// Données lues à partir de l'en-tête du fichier BMP
	unsigned char header[54]; // Chaque fichier BMP débute par un en-tête de 54 octets
	unsigned int dataPos;     // Position dans le fichier où les données débutent
	unsigned int width, height; 
	unsigned int imageSize;   // = width*height*3 
	// Ouverture du fichier
	FILE * file = fopen(imagepath,"rb"); 
	if (!file)
	{
		printf("Image could not be opened\n");
		return 0;
	}
	if (fread(header, 1, 54, file)!=54 )
	{ // S'il n'est pas possible de lire 54 octets : problème
   		 printf("Not a correct BMP file\n"); 
    	return 0; 
	}
	if ( header[0]!='B' || header[1]!='M' )
	{ 
		printf("Not a correct BMP file\n"); 
		return 0; 
	}
	// Lit des entiers à partir du tableau d'octets
	dataPos    = *(int*)&(header[0x0A]); 
	imageSize  = *(int*)&(header[0x22]); 
	width      = *(int*)&(header[0x12]); 
	height     = *(int*)&(header[0x16]);
	// Certains fichiers BMP sont mal formés, on devine les informations manquantes
	if (imageSize == 0)
		imageSize = width * height * 3; // 3 : un octet pour chaque composante rouge, vert et bleu
	if (dataPos == 0)
		dataPos = 54; // l'en-tête BMP est fait de cette façon
	// Crée un tampon
	unsigned char data[imageSize]; 
	
	// Lit les données à partir du fichier pour les mettre dans le tampon
	fread(data,1,imageSize,file); 
	
	// Tout est en mémoire maintenant, le fichier peut être fermé
	fclose(file);
	// Crée une texture OpenGL
	GLuint textureID; 
	glGenTextures(1, &textureID); 
	
	// "Lie" la nouvelle texture : toutes les fonctions agissant sur les textures suivantes vont modifier cette texture
	glBindTexture(GL_TEXTURE_2D, textureID); 
	
	// Donne l'image à OpenGL
	glTexImage2D(GL_TEXTURE_2D, 0,GL_RGB, width, height, 0, GL_BGR, GL_UNSIGNED_BYTE, data); 
	
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST); 
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	return (textureID);
}