#version 330 core 
 
// Valeurs interpolées à partir du vertex shader
in vec2 UV; 
in vec3 fragmentColor;
 
// Données en sortie
out vec3 color;

uniform bool showTexture;
uniform bool autoColorMode;
uniform vec3 colorMode;
uniform float transition;
uniform bool greymode;
 
// Valeurs qui sont constantes pour l'ensemble du modèle.
uniform sampler2D myTextureSampler; 
 
void main(){
	vec3 cTexture;
	if (greymode)
	{
		cTexture = texture(myTextureSampler, UV ).rgb;
		cTexture = vec3(cTexture.r + cTexture.g + cTexture.b) / 3.0;
	}
	else
		cTexture = texture(myTextureSampler, UV ).rgb;
	vec3 cNoTexture;
	if (greymode)
	{
		cNoTexture = vec3((fragmentColor.r + fragmentColor.g + fragmentColor.b) / 3.0);
	}
	else
		cNoTexture = fragmentColor;
	if (showTexture)
	{
		if (autoColorMode && !greymode)
		{
			// Couleur de sortie = couleur de la texture pour les coordonnées UV spécifiées
			color = mix(cNoTexture * colorMode,(texture(myTextureSampler, UV ).rgb * colorMode),transition);
		}
		else
		{
			
			color = mix(cNoTexture * colorMode,(texture(myTextureSampler, UV ).rgb * colorMode),transition);
		}
	}
	else
	{
		if (autoColorMode && !greymode)
		{
			color = mix((texture(myTextureSampler, UV ).rgb * colorMode), cNoTexture * colorMode, transition);
		}
		else
		{
			color = mix((texture(myTextureSampler, UV ).rgb * colorMode), cNoTexture * colorMode, transition);
		}
	}
}