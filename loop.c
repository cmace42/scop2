#include "scop.h"

void loop(t_env data)
{
	int running = 1;
	data.action.transition = 1.0f;
	while(running)
	{
		running = event(&data, data.time.deltaTime);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		// glClearColor(0.0f, 0.0f, 0.4f, 0.0f);
		data.time = getDataTime(data.time);
		if (data.action.rotate)
			doRotate(&data.model, (t_vec3){.y = 0.02f}, data.modelData.size_groupe);
		data.action = interact(data);
		render(data);
		SDL_Delay(1000/60); // 1000 ms / nombre de fps (ici 60) = ms par seconde entre chaque frame
	}
}