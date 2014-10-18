#include "windows.h"
#include "SDL.h"
#include "SDL_opengl.h"

SDL_Surface* g_screen;

const int WIW = 400; //ウィンドウ-幅
const int WIH = 400; //ウィンドウ-高さ

static GLfloat arm0[8][3] =
{
	{ -5, -8, -5 }, { -5, 8, -5 },
	{ 45, 8, -5 }, { 45, -8, -5 },
	{ -5, -8, 5 }, { -5, 8, 5 },
	{ 45, 8, 5 }, { 45, -8, 5 }
};
static GLfloat arm1[8][3] =
{
	{ 35, -8, -45 }, { 35, 8, -45 },
	{ 45, 8, -45 }, { 45, -8, -45 },
	{ 35, -8, 5 }, { 35, 8, 5 },
	{ 45, 8, 5 }, { 45, -8, 5 }
};

void drawArm(GLfloat arm[8][3]){
	for (int i = 0; i < 2; ++i){
		glBegin(GL_LINE_STRIP);
		for (int j = 0; j < 4; ++j){

			int index = i * 4 + j;
			glVertex3f(arm[index][0], arm[index][1], arm[index][2]);
		}
		int index = 4 * i;
		glVertex3f(arm[index][0], arm[index][1], arm[index][2]);
		glEnd();
	}

	glBegin(GL_LINES);
	for (int i = 0; i < 4; ++i){
		glVertex3f(arm[i][0], arm[i][1], arm[i][2]);
		int index = i + 4;
		glVertex3f(arm[index][0],arm[index][1],arm[index][2]);
	}
	glEnd();
	
}

void ourDisplay(void){
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(1,1,1);
	glLoadIdentity();
	glTranslatef(0.0, 0.0, -150);
	glScalef(1.0, 1.0, 1.1);
	drawArm(arm0);
	drawArm(arm1);
	glFlush();
	SDL_GL_SwapBuffers();
}

void ourInit(){
	glShadeModel(GL_FLAT);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glFrustum(-20.0, 20.0, -20.0, 20.0, 50, 200.0);
	glMatrixMode(GL_MODELVIEW);
	glViewport(0, 0, 400, 400);

}

void init(){

	if (SDL_Init(SDL_INIT_VIDEO) < 0){
		exit(1);
	}
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

	unsigned int flags = SDL_OPENGL;

	g_screen = SDL_SetVideoMode(WIW, WIH, 0, flags);
	if (g_screen == NULL){
		exit(1);
	}
	SDL_WM_SetCaption("OpenGL Test Window", NULL);//windowの名前

	/*
	glEnable(GL_TEXTURE_2D);
	glShadeModel(GL_FLAT);
	glDisable(GL_CULL_FACE);
	glClearColor(0, 0, 0, 0);

	glViewport(0, 0, WIW, WIH);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-50.0 ,50.0 , -50.0 , 50.0, -50.0, 50.0);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

	glMatrixMode(GL_MODELVIEW);
	*/
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glFrustum(-20.0, 20.0, -20.0, 20.0, 50, 200.0);
	glMatrixMode(GL_MODELVIEW);
	glViewport(0, 0, 400, 400);
}

int Quit(){
	SDL_Event Event;

	if (SDL_PollEvent(&Event)){

		switch (Event.type){

		case SDL_KEYDOWN:
			switch (Event.key.keysym.sym){
			case SDLK_ESCAPE:
				return 0;
				break;

			}
			break;

		case SDL_QUIT:
			return 0;
			break;
		}
	}

	return 1;
}

int main(int argv, char** argc){
	static int cnt = 0;
	init();
	ourInit();

	while (Quit()){
		//glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		// 座標変換を「なし」にする
		//glMatrixMode(GL_MODELVIEW);
		//glLoadIdentity();

		ourDisplay();

		Sleep(20);
	}
		

	//}
	return 0;
}