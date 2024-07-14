#include "AssetManager.h"
#include "ECS/Components.h"

AssetManager::AssetManager(Manager* man) : manager(man)
{

}

AssetManager::~AssetManager()
{

}

void AssetManager::CreateVisual(Vector2D pos, int width, int height, int scale, std::string id)
{
	auto& pVisual(manager->addEntity());
	pVisual.addComponent<TransformComponent>(pos.x, pos.y, width, height, scale);
	pVisual.addComponent<SpriteComponent>(id, true);
	pVisual.addGroup(Game::groupVisuals);
}

void AssetManager::CreateEnemy(Vector2D pos, int width, int height, int scale, std::string id, int speed)
{
	auto& enemy(manager->addEntity());
	
	enemy.addComponent<TransformComponent>(pos.x, pos.y, width, height, scale);
	enemy.getComponent<TransformComponent>().speed = speed;
	enemy.addComponent<SpriteComponent>(id, true);
	enemy.addComponent<ColliderComponent>("enemy");
	enemy.addComponent<EntityStatusComponent>(5, 10);
	enemy.addGroup(Game::groupEnemies);
}

void AssetManager::CreateProjectile(Vector2D pos, Vector2D vel, int range, int speed, std::string id, SDL_RendererFlip flip)
{
	auto& projectile(manager->addEntity());
	projectile.addComponent<TransformComponent>(pos.x, pos.y, 16, 16, 2);
	projectile.addComponent<SpriteComponent>(id, false);
	projectile.getComponent<SpriteComponent>().spriteFlip = flip;
	/*
	if (flip == "Left")
	{
		projectile.getComponent<SpriteComponent>().spriteFlip = SDL_FLIP_NONE;
	}
	if (flip == "Right")
	{
		projectile.getComponent<SpriteComponent>().spriteFlip = SDL_FLIP_HORIZONTAL;
	}
	if (flip == "Up")
	{
		projectile.getComponent<SpriteComponent>().spriteFlip = SDL_FLIP_NONE;
	}
	if (flip == "Down")
	{
		projectile.getComponent<SpriteComponent>().spriteFlip = SDL_FLIP_VERTICAL;
	}
	*/
	

	projectile.addComponent<ProjectileComponent>(range, speed, vel);
	projectile.addComponent<ColliderComponent>("projectile");
	projectile.addGroup(Game::groupProjectiles);
}

void AssetManager::AddTexture(std::string id, const char* path)
{
	textures.emplace(id, TextureManager::LoadTexture(path));

}

SDL_Texture* AssetManager::GetTexture(std::string id)
{
	return textures[id];
}

