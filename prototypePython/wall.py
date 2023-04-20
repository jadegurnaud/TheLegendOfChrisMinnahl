import pygame
from constants import TILE_SIZE
from player import Player

class Wall(pygame.sprite.Sprite):
    def __init__(self,x,y, *groups: pygame.sprite.AbstractGroup) -> None:
        super().__init__(*groups)
        self.rect = pygame.Rect(x*TILE_SIZE,y*TILE_SIZE,TILE_SIZE,TILE_SIZE)
        self.surf = pygame.Surface((TILE_SIZE,TILE_SIZE)) 
        self.surf.fill((200,200,200))
    def render(self,surface:pygame.Surface):
        surface.blit(self.surf,self.rect)
            
