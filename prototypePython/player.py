import pygame

from typing import Callable
from constants import PLAYER_SIZE,TILE_SIZE

class Player(pygame.sprite.Sprite):
    def __init__(self,x,y,collisionCheckFunc:Callable, *groups: pygame.sprite.AbstractGroup) -> None:
        super().__init__(*groups)
        self.surf = pygame.Surface((PLAYER_SIZE,PLAYER_SIZE))
        self.rect = self.surf.get_rect(topleft=(x*TILE_SIZE,y*TILE_SIZE))
        self.surf.fill((200,20,20))
        self.vel = pygame.Vector2(0,0)
        self.speed = 3
        self.collisionCheckFunc = collisionCheckFunc

    def update(self,dt:float):
        keys = pygame.key.get_pressed()
        if keys[pygame.K_RIGHT]:
            self.vel.x += self.speed
        if keys[pygame.K_LEFT]:
            self.vel.x -= self.speed
        if keys[pygame.K_UP]:
            self.vel.y -= self.speed
        if keys[pygame.K_DOWN]:
            self.vel.y += self.speed


        self.rect.y += self.vel.y
        self.handleCollisionY(self.collisionCheckFunc(self))
        self.rect.x += self.vel.x
        self.handleCollisionX(self.collisionCheckFunc(self))
        self.vel.update(0,0)
        

    def handleCollisionX(self,collider):
        if(not collider):return
        if(self.vel.x != 0):
            if(self.vel.x > 0):
                self.rect.right = collider.rect.left
            else:
                self.rect.left = collider.rect.right

    def handleCollisionY(self,collider):
        if(not collider):return
        if (self.vel.y  != 0):
            if(self.vel.y > 0):
                self.rect.bottom = collider.rect.top
            else:
                self.rect.top = collider.rect.bottom

    def render(self,surface:pygame.Surface):
        surface.blit(self.surf,self.rect)
    
