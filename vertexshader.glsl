#version 330 core 
 
// Données d'entrée du sommet, diffèrent pour chaque exécution de ce shader. 
layout(location = 0) in vec3 vertexPosition_modelspace; 
//layout(location = 1) in vec3 vertexColor;
layout(location = 1) in vec2 vertexUV; 
 
// Données de sortie ; vont être interpolées pour chaque fragment. 
out vec2 UV; 
//out vec3 fragmentColor; 
 
// Valeurs constantes pour l'ensemble du modèle. 
uniform mat4 MVP; 
 
void main(){ 
 
    // Position de sortie du sommet, dans l'espace de découpe : MVP * position
    gl_Position = MVP * vec4(vertexPosition_modelspace, 1); 
 
    // Coordonnées UV du sommet. Pas d'espace spécifique de coordonnées pour celles-ci. 
    UV = vertexUV; 
    //fragmentColor = vertexColor; 
}