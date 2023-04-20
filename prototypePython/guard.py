import pygame
from constants import PLAYER_SIZE,TILE_SIZE

def is_between(a, x, b):
    return min(a, b) <= x <= max(a, b)


class Guard(pygame.sprite.Sprite):
    #route = [ { "action":"go" , "time":1000 , "position" : [2,4]} , {"action":"wait", "time":2000}              ]
    def __init__(self,x,y,route:list[dict], *groups: pygame.sprite.AbstractGroup) -> None:
        super().__init__(*groups)
        self.surf = pygame.Surface((PLAYER_SIZE,PLAYER_SIZE))
        self.rect = self.surf.get_rect(topleft=(x*TILE_SIZE,y*TILE_SIZE))
        self.surf.fill((20,200,20))


        self.detector_surf = pygame.Surface((4*TILE_SIZE,2*TILE_SIZE),pygame.SRCALPHA)
        self.detector_surf.fill(pygame.Color(140,180,100,120))
        self.detector_rect = self.detector_surf.get_rect(midleft=self.rect.midright)
        self.route = route
        self.current_route_index = 0
        self.current_action = None
        self.current_route_data = None
        self.speed = 2
        self.truePos = [self.rect.x,self.rect.y]
        self.set_action(self.route[0])
    def set_action(self,route_action:dict):
        action = route_action['action']
        if action == "wait":
            self.current_route_data = {"cumulTime":0,"time":route_action['time']}
        elif action == "go":
            pos = [route_action["position"][0]*TILE_SIZE,route_action["position"][1]*TILE_SIZE]
            self.current_route_data = {"cumulTime":0,"time":route_action["time"],"position":pos,"initialPos":[self.rect.x,self.rect.y]}
            self.truePos = [self.rect.x,self.rect.y]
        else:
            print("error !")
            exit(1)
        self.current_action = action

    def next_action(self):
        self.current_route_index = (self.current_route_index + 1)% len(self.route)
        self.set_action(self.route[self.current_route_index])
        
    def update(self,dt:float):
        if self.current_action == "wait":
            self.current_route_data["cumulTime"] += dt
            if(self.current_route_data["cumulTime"]>self.current_route_data["time"]):
                self.next_action()
        elif self.current_action == "go":
            time_proportion = self.current_route_data["cumulTime"] / self.current_route_data["time"] 
            position_differenceX = self.current_route_data["position"][0] - self.current_route_data["initialPos"][0]
            position_differenceY = self.current_route_data["position"][1] - self.current_route_data["initialPos"][1]

            target = self.current_route_data["initialPos"][0] + (position_differenceX * time_proportion)

            self.truePos[0] = target if (is_between(self.rect.x,target,self.current_route_data["position"][0])) else self.current_route_data["position"][0]

            target = self.current_route_data["initialPos"][1] + (position_differenceY * time_proportion)

            self.truePos[1] = target if (is_between(self.rect.y,target,self.current_route_data["position"][1])) else self.current_route_data["position"][1]

 
            # if(int(self.truePos[0]) in range(self.rect.x,self.current_route_data["position"][0])):
            #     self.truePos[0] = self.current_route_data["position"][0]

            # if(int(self.truePos[1]) in range(self.rect.y,self.current_route_data["position"][1])):
            #     self.truePos[1] = self.current_route_data["position"][1]
            if(self.rect.x - self.truePos[0] != 0):
                if(self.rect.x < self.truePos[0]):
                    self.detector_rect.midleft=self.rect.midright
                elif(self.rect.x > self.truePos[0]):
                    self.detector_rect.midright=self.rect.midleft

            if(self.rect.y - self.truePos[1] != 0):
                if(self.rect.y < self.truePos[1]):
                    self.detector_rect.midtop=self.rect.midbottom
                elif(self.rect.y > self.truePos[1]):
                    self.detector_rect.midbottom=self.rect.midtop


            self.rect.x = self.truePos[0]
            self.rect.y = self.truePos[1]

            self.current_route_data["cumulTime"] += dt

            
            if (self.current_route_data["position"] == [self.rect.x,self.rect.y]):
                self.next_action()
        else:
            print("unknown action",self.current_action)
            exit(1)

    def render(self,surface:pygame.Surface):
        surface.blit(self.detector_surf,self.detector_rect)
        surface.blit(self.surf,self.rect)

