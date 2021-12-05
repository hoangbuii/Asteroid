#include "Entity.h"

Entity::Entity()
{
	Tex = NULL;
	Frame.w = 0;
	Frame.h = 0;
	Frame.x = 0;
	Frame.y = 0;
}

bool Entity::Load_Image(const char* file_path, SDL_Renderer* G_Renderer)
{
	bool success = true;
	SDL_Surface* image = NULL;
	image = IMG_Load(file_path);
	if (image == NULL)
	{
		cout << "Failed to load Image: " << file_path << " - " << IMG_GetError() << endl;
		success = false;
	}
	else
	{
		Tex = SDL_CreateTextureFromSurface(G_Renderer, image);
		if (Tex == NULL)
		{
			cout << "Failed to create Texture: " << file_path << " - " << IMG_GetError() << endl;
			success = false;
		}
	}
	Frame.w = image->w;
	Frame.h = image->h;
	SDL_FreeSurface(image);
	image = NULL;
	return success;
}

void Entity::Render(SDL_Renderer* G_Renderer)
{
	SDL_RenderCopy(G_Renderer, Tex, NULL, &Frame);
}

void Entity::Free()
{
	if (Tex != NULL)
	{
		SDL_DestroyTexture(Tex);
		Tex = NULL;
	}
}