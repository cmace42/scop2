#include "scop.h"

GLuint loadShaders(const char *vertexSource, int vertexLen, const char *fragmentSource, int fragmentLen)
{
	// Crée les shaders
	GLuint vertexShaderID = glCreateShader(GL_VERTEX_SHADER);
	GLuint fragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);
	GLint result = GL_FALSE;

	// Compile le vertex shader
	glShaderSource(vertexShaderID, 1, &vertexSource, &vertexLen);
	glCompileShader(vertexShaderID);

	// Vérifie le vertex shader
	char infoLog[512];
	glGetShaderiv(vertexShaderID, GL_COMPILE_STATUS, &result);
	if (!result)
	{
		glGetShaderInfoLog(vertexShaderID, 512, NULL, infoLog);
		glGetShaderInfoLog(vertexShaderID, sizeof(infoLog), NULL, infoLog);
        write(STDERR_FILENO, "error shader compilation failed: ", sizeof("error shader compilation failed: "));
        write(STDERR_FILENO, infoLog, strlen(infoLog));
	}

	// Compile le fragment shader
	glShaderSource(fragmentShaderID, 1, &fragmentSource, &fragmentLen);
	glCompileShader(fragmentShaderID);

	// Vérifie le vertex shader
	glGetShaderiv(fragmentShaderID, GL_COMPILE_STATUS, &result);
	if (!result)
	{
		glGetShaderInfoLog(fragmentShaderID, 512, NULL, infoLog);
		printf("ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n%s\n", infoLog);
	}

	// Crée et lit le programme
	GLuint programId = glCreateProgram();
	glAttachShader(programId, vertexShaderID);
	glAttachShader(programId, fragmentShaderID);
	glLinkProgram(programId);
	// Vérifie le program
	glGetProgramiv(programId, GL_COMPILE_STATUS, &result);
	if (!result)
	{
		glGetProgramInfoLog(programId, 512, NULL, infoLog);
		printf("ERROR::PROGRAM::COMPILATION_FAILED\n%s\n", infoLog);
	}

	//suppression du vertex et fragment shader car elles sont dans le program donc elles ne servent plus a rien
	glDeleteShader(vertexShaderID);
	glDeleteShader(fragmentShaderID);

	return (programId);
}