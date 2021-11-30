#include "scop.h"

extern char vertexshader_glsl[];
extern int vertexshader_glsl_len;
extern char fragmentshader_glsl[];
extern int fragmentshader_glsl_len;


void loop(t_vao vao, SDL_Window* window)
{
	GLuint Texture = loadBMP_custom("texturetest.bmp");
	GLuint programId = loadShaders(vertexshader_glsl, vertexshader_glsl_len, fragmentshader_glsl, fragmentshader_glsl_len);
	t_vec2 angleModel;
	t_camera camera;
	// angle horizontal : vers -Z 
	float horizontalAngle = 3.14f; 
	// angle vertical : 0, regarde l'horizon 
	float verticalAngle = 0.0f; 
	t_vec3 dir;
	t_vec3 right;

	angleModel.x = 0;
	angleModel.y = 0;
	camera.position= vec3_new(0.0f, 0.0f, 10.0f);
	camera.target = vec3_new(0.0f, 0.0f, 0.0f);
	camera.up = vec3_new(0.0f, 1.0f, 5.0f);
	int xMouse;
	int yMouse;
	SDL_GetRelativeMouseState(&xMouse, &yMouse);
	int lastxMouse = xMouse;
	int lastyMouse = yMouse;
	double currentTime;
	double lastTime;
	float deltaTime;
	int running = 1;
	glEnable(GL_CULL_FACE);
	while(running)
	{
		currentTime = SDL_GetTicks();
		deltaTime = (float)(currentTime - lastTime);
		lastTime = currentTime;
		SDL_GetRelativeMouseState(&xMouse, &yMouse);
		horizontalAngle += MOUSESPEED * deltaTime * (float)(xMouse);
		verticalAngle += MOUSESPEED * deltaTime * (float)(yMouse);

		dir = vec3_new(cosf(verticalAngle) * sinf(horizontalAngle),
				sinf(verticalAngle),
				cosf(verticalAngle) * cosf(horizontalAngle));
		right = vec3_new(sinf(horizontalAngle - 3.14f/2.0f),
				0,
				cosf(horizontalAngle - 3.14f/2.0f));
		camera.up = vec3_cross(right, dir);
		camera.target = vec3_add(camera.position, dir);
		running = event(&angleModel, &camera, right, deltaTime, dir);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glClearColor(0.0f, 0.0f, 0.4f, 0.0f);
		// premier tampon d'attributs : les sommets
		glEnableVertexAttribArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, vao.vertexBuffer);
		glVertexAttribPointer(
		0,                  //cela correspond au « layout » dans le shader 
		3,                  // taille
		GL_FLOAT,           // type 
		GL_FALSE,           // normalisé ? 
		0,                  // nombre d'octets séparant deux sommets dans le tampon
		(void*)0            // décalage du tableau de tampon
		);
		// premier tampon d'attributs : les couleurs
		glEnableVertexAttribArray(1);
		glBindBuffer(GL_ARRAY_BUFFER, vao.textureBuffer);
		glVertexAttribPointer(
		1,                  //cela correspond au « layout » dans le shader 
		2,                  // taille
		GL_FLOAT,           // type 
		GL_FALSE,           // normalisé ? 
		0,                  // nombre d'octets séparant deux sommets dans le tampon
		(void*)0            // décalage du tableau de tampon
		);
		glUseProgram(programId);
		printf("camera = x : %f, y : %f, z : %f\n\n",camera.position.x,camera.position.y,camera.position.z);
		applyPerspective(programId, angleModel.x, angleModel.y, camera);
		// // Dessine le triangle ! 
		glDrawArrays(GL_TRIANGLES, 0, 12 * 3); // Démarre à partir du sommet 0; 3 sommets au total -> 1 triangle 
		glDisableVertexAttribArray(0);
		SDL_GL_SwapWindow(window); // Sans ca pas d'image ?
		SDL_Delay(1000/60); // 1000 ms / nombre de fps (ici 60) = ms par seconde entre chaque frame
		//do some stuff
	}
	glDeleteTextures(1, &Texture);
	glDeleteProgram(programId);
	glDeleteVertexArrays(1, &vao.VertexArrayID);
	glDeleteBuffers(1, &vao.vertexBuffer);
	glDeleteBuffers(1, &vao.textureBuffer);
}