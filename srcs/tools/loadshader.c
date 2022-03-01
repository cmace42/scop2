/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loadshader.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmace <cmace@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/01 11:09:47 by cmace             #+#    #+#             */
/*   Updated: 2022/03/01 16:43:33 by cmace            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./incs/scop.h"

GLuint	loadShaders(const char *vertexSource, int vertexLen, const char *fragmentSource, int fragmentLen)
{
	GLuint	programId;
	GLuint	vertexShaderID;
	GLuint	fragmentShaderID;
	GLint	result;
	char	infoLog[512];

	// Crée les shaders
	fragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);
	vertexShaderID = glCreateShader(GL_VERTEX_SHADER);
	result = GL_FALSE;
	// Compile le vertex shader
	glShaderSource(vertexShaderID, 1, &vertexSource, &vertexLen);
	glCompileShader(vertexShaderID);
	// Vérifie le vertex shader
	glGetShaderiv(vertexShaderID, GL_COMPILE_STATUS, &result);
	if (!result)
	{
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
	programId = glCreateProgram();
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
	// suppression du vertex et fragment shader car elles sont dans le program donc elles ne servent plus a rien
	glDeleteShader(vertexShaderID);
	glDeleteShader(fragmentShaderID);
	return (programId);
}
