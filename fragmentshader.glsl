#version 330 core 
 
// Valeurs interpolées à partir du vertex shader
in vec2 UV; 
in vec3 fragmentColor;
 
// Données en sortie
out vec3 color;

uniform bool showTexture;
uniform bool test;
uniform int colortest;
 
// Valeurs qui sont constantes pour l'ensemble du modèle.
uniform sampler2D myTextureSampler; 
 
void main(){ 
 
	if (showTexture)
	{
		// Couleur de sortie = couleur de la texture pour les coordonnées UV spécifiées
		color = texture(myTextureSampler, UV ).rgb;
	}
	else
	{
		if (test)
		{
			color = fragmentColor * (colortest/100);
		}
		else
		{
			color = fragmentColor;
		}
	}
}