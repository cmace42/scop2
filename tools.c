#include "scop.h"

//Projection Matrice
t_mat4 initPerspective ( float fov, float zNear, float zFar)
{
	const float ar =  4.0f / 3.0f;
    const float zRange = zNear - zFar;
    const float tanHalfFOV = tanf(ToRadian(fov / 2.0));

	return ((t_mat4){
		.m = {
			{1.0f / (tanHalfFOV * ar), 0.0f, 0.0f, 0.0f},
			{0.0f, 1.0f / tanHalfFOV, 0.0f, 0.0f},
            {0.0, 0.0,  - (zFar + zNear) / (zFar - zNear), (-2 * zFar * zNear) / (zFar - zNear)},
			{0.0f, 0.0f, -1.0f, 0.0f}
		}
	});
}

// Camera Matrice
t_mat4 lookAt(t_vec3 cameraPosition, t_vec3 cameraTarget, t_vec3 upVector)
{
	t_vec3 cameraDir = vec3_normalisation(vec3_sub(cameraPosition, cameraTarget));
	t_vec3 cameraRight = vec3_normalisation(vec3_cross(upVector, cameraDir));
	t_vec3 cameraUp = vec3_cross(cameraDir, cameraRight);

	return (mat4_mult((t_mat4){
		.m = {
			{cameraRight.x, cameraRight.y, cameraRight.z, 0.0f},
			{cameraUp.x, cameraUp.y, cameraUp.z, 0.0f},
			{cameraDir.x, cameraDir.y, cameraDir.z, 0.0f},
			{0.0f, 0.0f , 0.0f, 1.0f}
		}
	}, mat4_translation((t_vec3){-cameraPosition.x, -cameraPosition.y, -cameraPosition.z})));
}

//Model Matrice
t_mat4 initModelMatrice(float xAngle, float yAngle)
{
	t_mat4 scale = mat4_identity();
	t_mat4 rotate = mat4_mult(mat4_identity(), mat4_mult(mat4_rotation_y(xAngle), mat4_rotation_x(yAngle)));
	t_mat4 translation = mat4_identity();
	t_mat4 modelMatrice = mat4_mult(mat4_mult(scale, rotate), translation);
	return (modelMatrice);
}