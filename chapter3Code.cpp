#include<stdio.h> 
#include<GL/glut.h> 
#include<math.h> 
#include<iostream>

// global declaration 
float i, j; 
const double pi = acos(-1);

using namespace std;
// Initialization function 
void myInit (void) 
{ 
    // Reset background color with black (since all three argument is 0.0) 
    glClearColor(0.0, 0.0, 0.0, 1.0); 
      
    // Set picture color to green (in RGB model) 
    // as only argument corresponding to G (Green) is 1.0 and rest are 0.0 
    glColor3f(1.0, 1.0, 1.0); 
      
    // Set width of point to one unit 
    glPointSize(1.0); 
    glMatrixMode(GL_PROJECTION); 
    glLoadIdentity(); 
      
    // Set window size in X- and Y- direction 
    gluOrtho2D(-780, 780, -420, 420); 
} 

void rotatePoints(double  X[], double Y[] , double cx , double cy , double angle ,int sz)
{
    double cos1 = cos(angle);
    double sin1 = sin(angle);
    double temp;
    for( int n=0; n<sz; n++ ){
        temp = ((X[n]-cx)*cos1 - (Y[n]-cy)*sin1) + cx;  
        Y[n] = ((X[n]-cx)*sin1 + (Y[n]-cy)*cos1) + cy;
        X[n] = temp;
    }
    return;
}

void drawPerson(int x , int y , bool is, bool isSecond) {

    glBegin(GL_POINTS); 
        
        // the angle to flip is 90 and the point is (x , cos(180)*11.0+y-45)
        
        if(j <= 500 || j>=800 || isSecond) {
            // head
            glVertex2i(x-5, y);
            glVertex2i(x+5, y);
            for(i=0;i<360;++i)
                glVertex2f(11.0*sin(i)+x , cos(i)*11.0+y);
        } else {
            double eyesX[2] = {x-5 , x+5};
            double eyesY[2] = {y   , y  };
            rotatePoints(eyesX , eyesY , x ,  cos(180)*11.0+y-45 , 270.0*pi/180 , 2);
            glVertex2i(eyesX[0], eyesY[0]);
            glVertex2i(eyesX[1], eyesY[1]);

            // head fliped
            double X[360];
            double Y[360];
            for(i=0;i<360;++i) {
                X[(int)i] = 11.0*sin(i)+x;
                Y[(int)i] = cos(i)*11.0+y;
            }

            rotatePoints(X , Y , x ,  cos(180)*11.0+y-45 , 270.0*pi/180 , 360);
            for(i=0;i<360;++i) {
                glVertex2f(X[(int)i] , Y[(int)i]);
            }
        }

        if(j <= 500 || j>=800 || isSecond) {
            // body
            for (i = 60; i>6 ; --i)
                glVertex2f(x, cos(180)*11.0+y-i);
        } else {
            // body fliped
            double X[49];
            double Y[49];
            for(i=55;i>6;--i) {
                int index = i;
                X[index] = x;
                Y[index] = cos(180)*11.0+y-i;
            }

            rotatePoints(X , Y , x ,  cos(180)*11.0+y-45 , 270.0*pi/180 , 49);
            for (i = 45; i>6 ; --i) {
                int index = i;
                glVertex2f(X[index], Y[index]);
            }
            for (i = 60; i>44 ; --i)
                glVertex2f(x, cos(180)*11.0+y-i);
        }

    glEnd();

    glBegin(GL_LINES);
        if(j <= 500 || j>=800 || isSecond) {
            // first hand
            glVertex2f(x, cos(180)*11.0+y-35);
            glVertex2f(x-20, cos(180)*11.0+y-35);

            // second hand
            glVertex2f(x, cos(180)*11.0+y-35);
            glVertex2f(x+20, cos(180)*11.0+y-35);
        } else {
            double X[4] = {x , x-20 , x , x+20};
            double Y[4] = {cos(180)*11.0+y-35 , cos(180)*11.0+y-35 , cos(180)*11.0+y-35 , cos(180)*11.0+y-35};
            rotatePoints(X , Y , x ,  cos(180)*11.0+y-45 , 270.0*pi/180 , 4);

            // first hand rotated
            glVertex2f(X[0] , Y[0]);
            glVertex2f(X[1] , Y[1]);
            
            // second hand rotated
            glVertex2f(X[2] , Y[2]);
            glVertex2f(X[3] , Y[3]);
        }

        // weapon
        if(is) {
            glVertex2f(x+20, cos(180)*11.0+y-35);
            glVertex2f(x+20, cos(180)*11.0+y-25);
            glVertex2f(x+20, cos(180)*11.0+y-25);
            glVertex2f(x+26, cos(180)*11.0+y-17);
        }

        // first leg
        glVertex2f(x, cos(180)*11.0+y-60);
        glVertex2f(x-20, cos(180)*11.0+y-80);

        // second leg
        glVertex2f(x, cos(180)*11.0+y-60);
        glVertex2f(x+20, cos(180)*11.0+y-80);
    glEnd();
}

void drawBoomerange(int x, int y){
    float offset = j-200;
    if(x+20+offset <= 300) {
        glBegin(GL_LINES);
            double X[2] = {x+20+offset , x+26+offset};
            double Y[2] = {y-35 , y-17};
            rotatePoints(X , Y , x+20+offset ,  y-25 , j , 2);
            glVertex2f(X[0], Y[0]); // here it will rotate 
            //glVertex2f(x+20+offset, y-35); no thing done
            glVertex2f(x+20+offset, y-25);
            glVertex2f(x+20+offset, y-25);
            //glVertex2f(x+26+offset, y-17); no thing done
            glVertex2f(X[1], Y[1]); // also the same thing
        glEnd();
    } else {
        glColor3f(1.0, 0.0, 0.0);   
        glBegin(GL_LINES);    
            glVertex2f(300, cos(180)*11.0+y-35);
            glVertex2f(300, cos(180)*11.0+y-25);
            glVertex2f(300, cos(180)*11.0+y-25);
            glVertex2f(306, cos(180)*11.0+y-17);
        glEnd();
        glBegin(GL_POINTS);
            for(i=1;i<=7;++i)
                glVertex2f(306, cos(180)*11.0+y-17-i);
        glEnd();
        glColor3f(1.0, 1.0, 1.0);
    }
}

void drawQuestionMark(int x , int y) {
    glBegin(GL_LINE_STRIP);
        glVertex2f(100+x , 50+y);
        glVertex2f(100+x , 75+y);
        glVertex2f(98+x , 77+y);
        glVertex2f(95+x , 79+y);
        glVertex2f(90+x , 81+y);
        glVertex2f(87+x , 83+y);
        glVertex2f(84+x , 86+y);
        glVertex2f(82+x , 89+y);
        glVertex2f(80+x , 91+y);
        glVertex2f(80+x , 97+y);
        glVertex2f(82+x , 99+y);
        glVertex2f(84+x , 101+y);
        glVertex2f(87+x , 103+y);
        glVertex2f(90+x , 106+y);
        glVertex2f(95+x , 108+y);
        glVertex2f(98+x , 111+y);
        glVertex2f(100+x , 111+y);
    glEnd();

    glPointSize(4);
    glBegin(GL_POINTS);
        glVertex2f(100+x , 43+y);
    glEnd();
    glPointSize(1);
}

// Function to display animation 
void display (void) 
{ 
    for (j = 0; j < 10000; j += 0.12) 
    {
        glClear(GL_COLOR_BUFFER_BIT);

            if(j<200) {
                drawPerson(-400 , -300 , 1 , 0);
                drawPerson(300 , -300 , 0 , 0);
            } else {
                drawPerson(-400 , -300 , 0 , 1);
                drawPerson(300 , -300 , 0 , 0);
                drawBoomerange(-400 , -300);
                if(j>=780) {
                    drawQuestionMark(190 , -300);
                }
            }
        glFlush(); 
    } 
} 
  
// Driver Program 
int main (int argc, char** argv) 
{ 
    glutInit(&argc, argv); 
      
    // Display mode which is of RGB (Red Green Blue) type 
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB); 
      
    // Declares window size 
    glutInitWindowSize(1360, 768); 
      
    // Declares window position which is (0, 0) 
    // means lower left corner will indicate position (0, 0) 
    glutInitWindowPosition(0, 0); 
  
    // Name to window 
    glutCreateWindow("Revolution"); 
  
    // Call to myInit() 
    myInit(); 
    glutDisplayFunc(display); 
    glutMainLoop(); 
} 
/*
#include<stdio.h>
#include<GL/gl.h>
#include<GL/glu.h>
#include<GL/glut.h>

static void draw();

int main(int argc, char** argv)
{
    //Initialize
    glutInit(&argc, argv);                  // initialization the glut lib
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB); // defining memories to use in program
    //Windows position
    glutInitWindowPosition(0, 0);           // according to your screen upper left corner
    //Windows Size
    glutInitWindowSize(400, 400);           // defining window size 
    glutCreateWindow("laithian project");   // you are creating the window and naming it laithian project
    glClearColor(1.0f, 1.0f, 1.0f, 0.0f);   // defining the color for painting the background
    glClear(GL_COLOR_BUFFER_BIT);           // clearing the background with the color we defined
    glMatrixMode(GL_PROJECTION);            // i don't know
    gluOrtho2D(-500, 500, -500, 500);       //  you are defining the window you have , what indexes does it covers
    glutDisplayFunc(draw);                  // here all the stuff will be done
    glutMainLoop();                         // to make sure that the painting continue to show 
}

void draw()
{
    glColor3f(0.0 , 0.0 , 0.0);

    glPointSize(10);
    glBegin(GL_POINTS);
        glVertex2d(-200, 200);
        glVertex2d(-100, 200);       
    glEnd();

    glBegin(GL_LINES);
        glVertex2d(-200, 100);
        glVertex2d(-100, 100);       
    glEnd();
*/
/*
    glBegin(GL_QUAD_STRIP); // it will draw two points two points --> a line then it will attach as folow

        glVertex2d(-200, 200);  // 1
        glVertex2d(-200, -200); // 2

        glVertex2d(200,  200);  // 1
        glVertex2d(200,  -200); // 2

        glVertex2d(300, 100);   // 1
        glVertex2d(300, 000);   // 2

        glVertex2d(400, 100);   // 1
        glVertex2d(400, 000);   // 2
        
    glEnd();
*/
/*
    glBegin(GL_POLYGON);
        glVertex2d(-200, 200);
        glVertex2d(-200, 100);
        glVertex2d(-100, 100);
        glVertex2d(-100, 200);
    glEnd();

    glBegin(GL_POLYGON);
        glVertex2d(200, 200);
        glVertex2d(200, 100);
        glVertex2d(100, 100);
        glVertex2d(100, 200);
    glEnd();

    glBegin(GL_POLYGON);
        glVertex2d(-150, -100);
        glVertex2d(150,  -100);
        glVertex2d(0,    -200);
    glEnd();

    glFlush();
}
*/
