#include "scop.h"

//Projection Matrice
t_mat4 initPerspective (float fov, float zNear, float zFar)
{
	const float ar =  4.0f / 3.0f;
	// const float zRange = zNear - zFar;
	const float tanHalfFOV = tanf(ToRadian(fov / 2.0));

	return ((t_mat4){
		.m = {
			{1.0f / (tanHalfFOV * ar), 0.0f, 0.0f, 0.0f},
			{0.0f, 1.0f / tanHalfFOV, 0.0f, 0.0f},
			{0.0, 0.0, - (zFar + zNear) / (zFar - zNear), (-2 * zFar * zNear) / (zFar - zNear)},
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
t_mat4 initModelMatrice(t_vec3 angle, t_vec3 whl, t_vec3 pos)
{
	t_mat4 scale = mat4_identity();
	t_mat4 rotate = mat4_mult(mat4_translation((t_vec3){-whl.x + pos.x, -whl.y + pos.y ,-whl.z + pos.z }), mat4_identity());
	rotate = mat4_mult(mat4_mult(mat4_mult(mat4_rotation_y(angle.y), mat4_rotation_x(angle.x)),mat4_rotation_z(angle.z)), rotate);
	rotate = mat4_mult(mat4_translation((t_vec3){whl.x + pos.x, whl.y + pos.y ,whl.z + pos.z}),rotate);
	t_mat4 translation = mat4_translation((t_vec3){-pos.x, -pos.y, -pos.z});
	t_mat4 modelMatrice = mat4_mult(mat4_mult(scale, rotate), translation);
	return (modelMatrice);
}

t_vec3 initAllWhl(t_objectInWorld *model, size_t size_groupe)
{
	t_vec3 whltotal = (t_vec3){0.0,0.0,0.0};
	size_t i;

	i = 0;
	while (i < size_groupe)
	{
		whltotal.x += fabs(model[i].whl.x);
		whltotal.y += fabs(model[i].whl.y);
		whltotal.z += fabs(model[i].whl.z);
		i++;
	}
	return (whltotal);
}

void freeAll(t_env *env)
{
	size_t y;
	y = 0;
	while (y < env->modelData.size_groupe)
	{
		if (env->modelData.vertex[y].buffer_data)
			free(env->modelData.vertex[y].buffer_data);
		if (env->modelData.uv[y].buffer_data)
			free(env->modelData.uv[y].buffer_data);
		if (env->modelData.normal[y].buffer_data)
			free(env->modelData.normal[y].buffer_data);
		if (env->modelData.colorTriangles[y].buffer_data)
			free(env->modelData.colorTriangles[y].buffer_data);
		if (env->modelData.colorFaces[y].buffer_data)
			free(env->modelData.colorFaces[y].buffer_data);
		if (env->modelData.vertex[y].name)
			free(env->modelData.vertex[y].name);
		y++;
	}
	if (env->bmp1.data)
		free(env->bmp1.data);
	if (env->bmp2.data)
		free(env->bmp2.data);
	if (env->model)
		free(env->model);
	if (env->modelData.colorTriangles)
		free(env->modelData.colorTriangles);
	if (env->modelData.colorFaces)
		free(env->modelData.colorFaces);
	if (env->modelData.vertex)
		free(env->modelData.vertex);
	if (env->modelData.uv)
		free(env->modelData.uv);
	if (env->modelData.normal)
		free(env->modelData.normal);
	if (env->vao)
		free(env->vao);
}