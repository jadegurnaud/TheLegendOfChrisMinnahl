#include <iostream>
#include "manager.h"
#include <gf/RenderWindow.h>

//Include local headers

int main(){
	Manager m("The Legend Of Chris Minnahl");
	gf::Window &win = m.getWindow();
	gf::RenderTarget &renderer= m.getRenderer(); 
	m.run();
	return 0;
}
