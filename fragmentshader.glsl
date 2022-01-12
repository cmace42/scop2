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
uniform float transition;
 
// Valeurs qui sont constantes pour l'ensemble du modèle.
uniform sampler2D myTextureSampler; 
 
void main(){ 
	if (showTexture)
	{
		if (test)
		{
			// Couleur de sortie = couleur de la texture pour les coordonnées UV spécifiées
			color = mix(fragmentColor * bidouille,(texture(myTextureSampler, UV ).rgb * bidouille),transition);
		}
		else
		{
			color = mix(fragmentColor, texture(myTextureSampler, UV ).rgb,transition);
		}
	}
	else
	{
		if (test)
		{
			color = mix((texture(myTextureSampler, UV ).rgb * bidouille), fragmentColor * bidouille, transition);
		}
		else
		{
			color = mix(texture(myTextureSampler, UV ).rgb, fragmentColor, transition);
		}
	}
}