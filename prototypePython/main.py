import pygame
pygame.init()
from constants import WORLD_SIZE,TILE_SIZE
from player import Player
from guard import Guard
from world import World
class Game:
    def __init__(self) -> None:
        self.window = pygame.display.set_mode((1280,720))
        self.clock = pygame.time.Clock()
        
        self.world = World(WORLD_SIZE)
        self.world.addWall(0,0,1,WORLD_SIZE)
        self.world.addWall(WORLD_SIZE-1,0,1,WORLD_SIZE)

        self.world.addWall(0,0,WORLD_SIZE,1)
        self.world.addWall(0,WORLD_SIZE-1,WORLD_SIZE,1)
        self.world.addWall(3,3,6,2)

        self.world.addWall(1,7,4,1)
        self.player = Player(10,10,self.world.checkCollisions)

        self.guardGroup:list[Guard] = pygame.sprite.Group()


        Guard(1,1,[
                {"action":"go","time":1000,"position":[10,1]},
                {"action":"wait","time":1000},
                {"action":"go","time":2000,"position":[1,1]},
                {"action":"wait","time":1000}
            ],self.guardGroup)
        Guard(3,10,[
                {"action":"go","time":1000,"position":[3,15]},
                {"action":"wait","time":1000},
                {"action":"go","time":2000,"position":[3,10]},
                {"action":"wait","time":1000}
            ],self.guardGroup)
        Guard(13,10,[
                {"action":"go","time":1000,"position":[18,10]},
                {"action":"wait","time":2000},
                {"action":"go","time":2000,"position":[13,10]},
                {"action":"wait","time":1000}
            ],self.guardGroup)



        font = pygame.font.SysFont(None, 64)
        self.gameOverText = font.render('GAME OVER', True, (200,5,5))
        self.gameOverText_rect = self.gameOverText.get_rect()
        self.gameOverText_rect.center = self.window.get_rect().center

        self.gameLoop()
    def playerCollidesWithDetector(self):
        for sprite in self.guardGroup:
            if(sprite.detector_rect.colliderect(self.player.rect)):
                return True
        return False
    def gameLoop(self):
        loop = True
        dt = 1
        gameOver = False
        while(loop):
            self.window.fill((10,0,20))
            for event in pygame.event.get():
                if event.type == pygame.QUIT:
                    loop = False
                if event.type == pygame.MOUSEBUTTONDOWN:
                    if event.button == 1:
                        self.world.addWall(*[int(i/TILE_SIZE) for i in event.pos],1,1)
                    if event.button == 3:
                        self.world.removeWall(*[int(i/TILE_SIZE) for i in event.pos])

            #update
            if(not gameOver):
                self.player.update(dt)

                self.guardGroup.update(dt)

                if(self.playerCollidesWithDetector()):
                    gameOver = True


            #render

            self.world.render(self.window)
            for sprite in self.guardGroup:
                sprite.render(self.window)


            self.player.render(self.window)

            if(gameOver):
                self.window.blit(self.gameOverText,self.gameOverText_rect)

            pygame.display.flip()
            dt = self.clock.tick(60)


if __name__ == "__main__":
    Game()