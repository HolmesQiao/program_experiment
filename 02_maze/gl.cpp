#include "data.h"
#include <math.h>

#define TIMES 5 
#define HIGH width / 20 
#define A i - real_width / 2 , (j + 1) - real_high / 2, HIGH 
#define B i - real_width / 2, j - real_high / 2, HIGH 
#define C (i + 1) - real_width / 2, j - real_high / 2, HIGH
#define D (i + 1) - real_width / 2, (j + 1) - real_high / 2, HIGH
#define A_ i - real_width / 2, (j + 1) - real_high / 2, -3 
#define B_ i - real_width / 2, j - real_high / 2, -3 
#define C_ (i + 1) - real_width / 2, j - real_high / 2, -3
#define D_ (i + 1) - real_width / 2, (j + 1) - real_high / 2, -3
#define DRAW(type, i, j) do{\
    glBegin(type);\
    glEnd();\
}while(0)
#define DRAW_QUAD(i, j, m, n) do{\
    glBegin(GL_QUADS);\
	glVertex3f(i);\
	glVertex3f(j);\
	glVertex3f(m);\
	glVertex3f(n);\
    glEnd();\
}while(0)

typedef GLfloat vertex3[3];

GLfloat window_width = 500;
GLfloat window_high = 500;
GLfloat x_angle = 0, y_angle = 0, z_angle = 0;
GLfloat LightAmbient[]= { 0, 0, 1, 1.0f };
GLfloat LightDiffuse[]= { 1, 1, 1, 1.0f };
GLfloat LightPosition[]= {-5, -5, -1, 1};
GLint position = map_began;
//GLfloat LightPosition[]= {position / width + 1, position % width + 1, -2.0f, 1.0f };
bool should_draw_road = false;

void init_gl_data(void){
    window_width = 500;
    window_high = 500;
    x_angle = 0, y_angle = 0, z_angle = 0;
    position = map_began;
    should_draw_road = false;
    LightPosition[0] = LightPosition[1]= -width / 2 ;
}
void spinMap(void){glutPostRedisplay();}
void keyboard(unsigned char key, int x, int y){
    switch(key){
	case 'r': should_draw_road = true; break;
	case 'x': x_angle -= 2; break;
	case 'y': y_angle -= 2; break;
	case 'z': z_angle -= 2; break;
	case 'a':
	    if (position / width != 0 &&
		    real_map[position / width + 1][position % width + 1] != 0){
		position -= width;
		if (real_map[position / width + 1][position % width + 1] == 0){
		    position += width;
		}else {
		    should_draw_road = false;
		    LightPosition[0]--;
		}
	    }
	    break;
	case 'd':
	    if (position / width !=  high - 1&&
		    real_map[position / width + 1][position % width + 1] != 0){
		position += width;
		if (real_map[position / width + 1][position % width + 1] == 0){
		    position -= width;
		}else {
		    should_draw_road = false;
		    LightPosition[0]++;
		}
	    }
	    break;
	case 's':
	    if (position % width != 0 &&
		    real_map[position / width + 1][position % width + 1] != 0){
		position--;
		if (real_map[position / width + 1][position % width + 1] == 0){
		    position++;
		}else {
		    should_draw_road = false;
		    LightPosition[1]--;
		}
	    }
	    break;
	case 'w':
	    if (position % width != width - 1 &&
		    real_map[position / width + 1][position % width + 1] != 0){
		position++;
		if (real_map[position / width + 1][position % width + 1] == 0){
		    position--;
		}else {
		    should_draw_road = false;
		    LightPosition[1]++;
		}
	    }
	    break;
	case 'q': exit(1);
    }
    glutPostRedisplay();
}

void reshape(GLsizei w, GLsizei h){
    window_width = w, window_high = h;
    glLoadIdentity();
    if (h == 0) h = 1;
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);

    glLoadIdentity();
    if(w <= h){
        glOrtho(-real_width * 0.6, real_width * 0.6, -real_high * h / w * 0.6, real_high * h / w * 0.6, 3, -3);
    }else{
        glOrtho(-real_width * w / h * 0.6, real_width * w / h * 0.6, -real_high * 0.6, real_high * 0.6, 3, -3);
    }
    /*
    if(w <= h){
        glOrtho(-real_width, real_width, -real_high * h / w, real_high * h / w, 2, -2);
    }else{
        glOrtho(-real_width * w / h, real_width * w / h, -real_high, real_high, 2, -2);
    }
    */
    glMatrixMode(GL_MODELVIEW);
}

void init_gl(void){
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH | GLUT_ALPHA | GLUT_MULTISAMPLE);
    glutInitWindowSize(window_width, window_high);
    glutInitWindowPosition(300, 300);
    glutCreateWindow("Maze");
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);

    glMatrixMode(GL_MODELVIEW);
    glClearColor(0, 0, 0, 0.0);
    
    //glMatrixMode(GL_PROJECTION);
    glOrtho(-real_width * 0.5, real_width * 0.5, -real_high * 0.5, real_high * 0.5, 3, -3);
    glViewport(0, 0, window_width, window_high);
    //Texture[0] = LoadTexture("person.bmp");
}

void display(void){
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glColorMaterial(GL_FRONT/*_AND_BACK*/,GL_AMBIENT_AND_DIFFUSE);
    glEnable(GL_COLOR_MATERIAL);

    //draw map
    glRotatef(2, 1, 0, 0);
    glRotatef(2, 0, 1, 0);
    glRotatef(-30, 0, 0, 1);
    glLightfv(GL_LIGHT0, GL_AMBIENT, LightAmbient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, LightDiffuse);
    glLightfv(GL_LIGHT0, GL_POSITION, LightPosition);
    glLoadIdentity();
    glScaled(4.5, 4.5, 1);
    glRotatef(2, 1, 0, 0);
    glRotatef(2, 0, 1, 0);
    glRotatef(-30, 0, 0, 1);
    glRotatef(x_angle, 1, 0, 0);
    glRotatef(y_angle, 0, 1, 0);
    glRotatef(z_angle, 0, 0, 1);
    if (position == width * high - 1){
	/*if (Map_type == by_algorithm) new_game();
	else exit(1);*/
	new_game();
    }
    x_angle += 0.02;
    y_angle += 0.02;
    z_angle += 0.02;

    glViewport(0, 0, window_width, window_high);
    glOrtho(-real_width * 0.5, real_width * 0.5, -real_high * 0.5, real_high * 0.5, 2, -2);
    for (int i = 0; i < real_high; i++){
	for (int j = 0; j < real_width; j++){
	    if (real_map[i][j] == 0){
		glColor3f(0.5, 1, 0);
		    DRAW_QUAD(A, B, C, D);
		    DRAW_QUAD(A_, B_, C_, D_);
		glColor3f(1, 0.5, 0);
		    DRAW_QUAD(D, C, C_, D_);
		glColor3f(1, 1, 0);
		    DRAW_QUAD(A, B, B_, A_);
		glColor3f(0, 0, 1);
		    DRAW_QUAD(C, B, B_, C_);
		glColor3f(1, 0, 1);
		    DRAW_QUAD(D, A, A_, D_);
	    }/*else if (real_map[i][j] == 1){
		glColor3f(0, 0.5, 1);
		    DRAW_QUAD(A_, B_, C_, D_);
	    }*/else if (real_map[i][j] == 2){
		glColor3f(1, 0, 0);
		DRAW_QUAD(A, B, C, D);
		DRAW_QUAD(A_, B_, C_, D_);
	    }else if(real_map[i][j] == 3){
		glColor3f(0, 0, 0);
		DRAW_QUAD(A, B, C, D);
		DRAW_QUAD(A_, B_, C_, D_);
	    }
	}
    }
    //draw road
    if (should_draw_road){
	for (int k = 0; k < path_length; k++){
	    //int i = k / width + 1, j = k % width + 1;
	    int a = path[k] / width + 1, b = path[k] % width + 1;
	    GLfloat i = a, j = b;
	    glColor3f(1, 0, 0);
	    glBegin(GL_QUADS);
		DRAW_QUAD(A_, B_, C_, D_);
	    glEnd();
	}
	glutPostRedisplay();
    }
    //draw person
    //glLoadIdentity();
    //glRotatef(x_angle * 3, 0, 0, 1);
    //glScaled(0.7, 0.7, 1);
    glTranslatef(0, 0, sin(x_angle * 1.5));
    int i = position / width + 1, j = position % width + 1;
    glColor3f(0, 0, 0);
	DRAW_QUAD(A + 0.01, B + 0.01, C + 0.01, D + 0.01);
    glColor3f(1, 1, 1);{
	DRAW_QUAD(A_ - 0.01, B_ - 0.01, C_ - 0.01, D_ - 0.01);
    glColor3f(0.8, 0.8, 0.6);
	DRAW_QUAD(D, C, C_, D_);
	DRAW_QUAD(A, B, B_, A_);
	DRAW_QUAD(C, B, B_, C_);
	DRAW_QUAD(D, A, A_, D_);
    }
    
    glFlush();
    glutSwapBuffers();
}
