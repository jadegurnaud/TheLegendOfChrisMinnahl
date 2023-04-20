#ifndef LOCAL_PLAYER_H
#define LOCAL_PLAYER_H
#include <gf/Entity.h>
#include <gf/Math.h>
#include <gf/Shapes.h>
#include <gf/Action.h>
#include <gf/Event.h>
#include <gf/RenderWindow.h>
#include <gf/ResourceManager.h>
#include <gf/Texture.h>
#include <gf/Time.h>
#include <gf/Sprite.h>
#include "wall.h"

constexpr gf::Vector2f PLAYER_SIZE = {26.0,16.0};


class Player: public gf::Entity{
	private:
	gf::Vector2f position;
	gf::Vector2f velocity;
	gf::ResourceManager& resources;
	gf::Sprite sprite;
	gf::Texture& textureRight;
	gf::Texture& textureLeft;
	gf::Texture& textureUp;
	gf::Texture& textureDown;
	gf::Texture& textureStatue;

	float speed = 200.0;
	bool isStatue, wantToStatue,statueSprite;
	int dirPlayer;
	public :
		Player(gf::ResourceManager& resources);

		void init();
		void setPosition(gf::Vector2f position);
		gf::Vector2f getPosition();
		void setVelocity(gf::Vector2f vel);
		gf::Vector2f getVelocity();
		void addVelocity(gf::Vector2f vel);
		
		void setWantToStatue(bool val);
		bool isWantToStatue();
		void setStatueSprite(bool var);
		void setStatue(bool val);
		void setdirectionPlayer(int var);
		//check if player is currently a statue
        bool isAStatue();
		void applyXMotion(gf::Time time);
		void applyYMotion(gf::Time time);
		virtual void render(gf::RenderTarget & target,
		const gf::RenderStates & states);
		int getGridPosY()const;
		
};
#endif
