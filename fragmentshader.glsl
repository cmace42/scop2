#version 330 core 
 
// Valeurs interpolées à partir du vertex shader
in vec2 UV; 
in vec3 fragmentColor;
 
// Données en sortie
out vec3 color;

uniform bool showTexture;
uniform bool test;
uniform int colortest;
uniform vec3 bidouille;
 
// Valeurs qui sont constantes pour l'ensemble du modèle.
uniform sampler2D myTextureSampler; 
 
void main(){ 
 
	if (showTexture)
	{
		if (test)
		{
			// Couleur de sortie = couleur de la texture pour les coordonnées UV spécifiées
			color = (texture(myTextureSampler, UV ).rgb * bidouille);
		}
		else
		{
			color = texture(myTextureSampler, UV ).rgb;
		}
	}
	else
	{
		if (test)
		{
			color = fragmentColor * bidouille;
		}
		else
		{
			color = fragmentColor;
		}
	}
}