#version 330 core
// Valeurs interpolées à partir du vertex shader
in vec3 fragmentColor;
// Données de sortie
out vec3 color; 
 
void main(){ 
    // Output color = color spécifié dans le vertex shader
    // interpolé entre les trois sommets alentours
    color = fragmentColor; 
}