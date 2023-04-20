import pygame
from wall import Wall
from player import Player
class World():
    def __init__(self,size:int) -> None:
        self.size = size
        self.matrix : list[list[Wall]] = [[None for _ in range(size)] for i in range(size)]
        self.wallGroup = pygame.sprite.Group()

    def addWall(self,x:int,y:int,width:int,height:int) -> bool:
        if (not (x in range(0,self.size))) or (not (y in range(0,self.size))):
            return False
        for row in range(y,y+height):
            for col in range(x,x+width):
               if (not (col in range(0,self.size))) or (not (row in range(0,self.size))): continue
               self.matrix[row][col] = Wall(col,row,self.wallGroup)
        return True
    def removeWall(self,x:int,y:int):
        if (not (x in range(0,self.size))) or (not (y in range(0,self.size))): return False
        if(self.matrix[y][x] == None): return False
        self.matrix[y][x].kill()
        self.matrix[y][x] = None

    def prettyPrint(self) ->  None:
        print("---- Output ----")
        for y in range(self.size):
            for x in range(self.size):
                print(self.matrix[y][x],end=' |')
            print("")

    def checkCollisions(self,player:Player) -> pygame.sprite.Sprite:
        return pygame.sprite.spritecollideany(player,self.wallGroup)

    def render(self,surface:pygame.Surface) -> None:
        for y in range(self.size):
            for x in range(self.size):
                if(self.matrix[y][x] != None):
                    self.matrix[y][x].render(surface)
