#version 330 core 
 
// Valeurs interpolées à partir du vertex shader
in vec2 UV; 
in vec3 fragmentColor;
 
// Données en sortie
out vec3 color; 
 
// Valeurs qui sont constantes pour l'ensemble du modèle.
uniform sampler2D myTextureSampler; 
 
void main(){ 
 
    // Couleur de sortie = couleur de la texture pour les coordonnées UV spécifiées
    //color = texture(myTextureSampler, UV ).rgb; 
    color = fragmentColor;
}