/* C4-2.c */
#include <stdio.h>
#include <stdlib.h>
#include <GL/glut.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <math.h>
#define KEY_ESC 27
#define PAI 3.1415926536

float dist=0.0; /*視点の移動量*/
float distx=0.0;
float theta =0.0; /*物体の回転角度*/
float install=4.0;/*木の位置を設定*/
float balloc=0;
float ballxloc[3];
float hole[5][2];
float viewX=0;
float viewY=0;
void display(void)
{
	int i;
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
	
	glPushMatrix();
	gluLookAt(0.0,2.0,dist,0.0+viewX,1.2,dist+1.0,0.0,1.0,0.0);
	/*ビューイング変換　視点をz軸方向に動かす*/
	

	glPushMatrix();//人間の頭部分を再現
		glTranslatef(distx,0.9,1.0+dist);
		glColor3f(0.0,0.0,0.0);
		glutSolidSphere(0.2,15,15); 
	glPopMatrix();
	glPushMatrix();//人間の身体部分を再現
		glTranslatef(distx,0.3,1.0+dist);
		glColor3f(0.0,1.0,1.0);
		glScalef(1.0,2.0,0.5);
		glutSolidCube(0.4);
	glPopMatrix();
	glPushMatrix();//人間の左腕部分を再現
		glTranslatef(0.3+distx,0.4,1.0+dist);
		glRotatef(45,0.0,0.0,1.0);
		glColor3f(0.0,0.0,0.0);
		glScalef(0.35,1.5,0.2);
		glutSolidCube(0.4);
	glPopMatrix();
	glPushMatrix();//人間の右腕部分を再現
		glTranslatef(-0.3+distx,0.4,1.0+dist);
		glRotatef(-45,0.0,0.0,1.0);
		glColor3f(0.0,0.0,0.0);
		glScalef(0.35,1.5,0.2);
		glutSolidCube(0.4);
	glPopMatrix();
	glPushMatrix();//人間の左足部分を再現
		glTranslatef(0.1+distx,-0.2,1.0+dist);
		glScalef(0.3,1.0,0.3);
		glutSolidCube(0.4);
	glPopMatrix();
	glPushMatrix();//人間の右足部分を再現
		glTranslatef(-0.1+distx,-0.2,1.0+dist);
		glScalef(0.3,1.0,0.3);
		glutSolidCube(0.4);
	glPopMatrix();
	glColor3f(1.0,0.0,0.0);
	
	for(i=0;i<3;i++){
		glPushMatrix();//当たるとアウトなボールをモデリング
			glTranslatef(balloc-10,0.0,10.0*(i+1));
			//glTranslatef(0,0.0,10.0*(i+1));
			glutSolidSphere(1.0,20,20);
		glPopMatrix();
	}
	for(int i=0;i<6;i++){
		glPushMatrix();//右側の木(幹部分)をモデリング
			glColor3f(0.53,0.184,0.1);
			glTranslatef(-3.4,0.0,(install*i));
			glScalef(0.6,1.5,1.0);
			glutSolidCube(0.5);
		glPopMatrix();
		glPushMatrix();//左側の木(幹部分)をモデリング
			glTranslatef(3.4,0.0,5+(install*i));
			glScalef(0.6,1.5,1.0);
			glutSolidCube(0.5);
		glPopMatrix();
		glPushMatrix();//右側の木(葉部分)をモデリング
			glColor3f(0.0,0.616,0.357);
			glTranslatef(-3.4,1.0,(install*i));
			glScalef(1.0,1.5,1.5);
			glutSolidCube(1.0);
		glPopMatrix();
		glPushMatrix();//左側の木(葉部分)をモデリング
			glTranslatef(3.4,1.0,5+(install*i));
			glScalef(0.6,1.5,1.0);
			glutSolidCube(1.0);
		glPopMatrix();
	}
	glColor3f(0.0,0.0,0.0);
	for(int i=0;i<5;i++){
		glPushMatrix();
			glTranslatef(hole[i][0],-0.50,hole[i][1]);
			glutSolidCube(1.0);
		glPopMatrix();
	}
	glColor3f(0.0,1.0,0.0);
	for(int i=-50;i<50;i++){
		if((i>-3)&&(i<3)){
			glColor3f(0.72,0.5,0.3);
		}
		else{
			glColor3f(0.0,1.0,0.0);
		}
		glBegin(GL_POLYGON);//草原を再現
    		glVertex3f(i+1, -0.5, 35.0);
    		glVertex3f(i, -0.5, 35.0);
    		glVertex3f(i, -0.5, -35.0);
    		glVertex3f(i+1, -0.5, -35.0);
    	glEnd();
	}
	glPopMatrix();
	glutSwapBuffers();
}

void idle(void)/*イベントがなければidleが常に実行される*/
{
	//dist =fmod(dist+0.005,32.0);
	balloc=fmod(balloc+0.001,20);//当たるとアウトなボールを動かす
	glutPostRedisplay();/*ディスプレイコールバック関数(display)を実行*/
	//distx-1.0<=balloc+ballxloc[i]-10<=distx+1.0
	//10*i-2<=dist<=10*i
	for(int i=0;i<3;i++){
		if((distx-1.0<=balloc-10)&&(balloc+-10<=distx+1.0)&&((10*(i+1))-2<=dist)&&(dist<=10*(i+1))){
			printf("ゲームオーバー:ボールにぶつかりました");
			exit(0);
		}
	}
	for(int i=0;i<5;i++){
		if((hole[i][0]>=distx-0.5)&&(hole[i][0]<=distx+0.5)&&(hole[i][1]>=dist+0.5)&&(hole[i][1]<=dist+1.5)){
			printf("ゲームオーバー:落とし穴にはまりました");
			exit(0);
		}
	}
}

void myKbd(unsigned char key,int x,int y)
{
	if(key == KEY_ESC){ exit(0);}
	if(key=='f'){
		dist=fmod(dist+0.05,32.0);
	}
	if(key=='b'&& dist>-2){
		dist=fmod(dist-0.05,32.0);
	}
	if(key=='r'){
		distx=distx-0.05;
		//printf("右に動きます");
	}
	if(key=='l'){
		distx=distx+0.05;
		//printf("左に動きます");
	}
}

void myInit(char *progname)
{
	int width=640,height=480;
	float aspect =(float)width/(float)height;
	
	glutInitWindowPosition(0,0);
	glutInitWindowSize(width,height);
	glutInitDisplayMode(GLUT_DOUBLE|GLUT_RGBA);
	glutCreateWindow(progname);
	glClearColor(0.5,0.8,0.8,1.0);
	glutKeyboardFunc(myKbd);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(60.0,aspect,0.1,40.0);/*view volume ????*/
	glMatrixMode(GL_MODELVIEW);
	glEnable(GL_DEPTH_TEST);
}
int main (int argc, char** argv)
{
	int i;
	srand((unsigned)time(NULL));
	for(i=0;i<5;i++){
		hole[i][0]=rand()%6-2;
		hole[i][1]=rand()%20+10;
	}
	glutInit(&argc,argv);
	myInit(argv[0]);
	glutDisplayFunc(display);
	glutIdleFunc(idle);
	glutMainLoop();
	return(0);
}