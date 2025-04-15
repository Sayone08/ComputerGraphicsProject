#include<windows.h>
#include <GL/glut.h>
#include <stdio.h>
#include <GL/gl.h>
#include <math.h>

float p = 480.0, q = 620.0, cloud1X=80.0, cloud2X=620.0, cloud3X=1030.0;
bool movingUpB1 = true;
bool movingUpB2 = true;
float ferrisWheelAngle = 0.0f;
float rotationSpeed = 0.05f;
float busX = 1280.0f;
float busSpeed = 0.09f;
float wheelAngle = 0.0f;
float wheelRotationSpeed = 5.0f;


void init(void)
{
    glClearColor(0.98, 0.96, 0.99,0.0); //GLfloat red,green,blue,alpha initial value 0 alpha values used by glclear to clear the color buffers
    glMatrixMode(GL_PROJECTION);  // To specify which matrix is the current matrix & projection applies subsequent matrix to projecton matrix stack
    glLoadIdentity();
    glOrtho(0.0, 1280.0, 0.0, 720.0, -1.0, 1.0);
    //gluOrtho2D(0.0,300.0,0.0,300.0); // Orthographic representation; multiply the current matrix by an orthographic matrix 2D= left right,bottom,top equivalent near=-1,far=1
}

void stripes(int p, int q,int n, int gapWidth, int startX)
{
    int stripeWidth = 5;

    for (int i = 0; i < n; i++)
    {
        glColor3f(0.36, 0.20, 0.10);
        glBegin(GL_POLYGON);
        glVertex2i(startX, p);
        glVertex2i(startX + stripeWidth, p);
        glVertex2i(startX + stripeWidth, q);
        glVertex2i(startX, q);
        glEnd();

        startX += stripeWidth + gapWidth;
    }
}

void HouseStripes(int p, int q,int n, int gapWidth, int startX, int stripeWidth)
{

    for (int i = 0; i < n; i++)
    {
        glColor3f(0.9, 1, 1);
        glBegin(GL_POLYGON);
        glVertex2i(startX, p);
        glVertex2i(startX + stripeWidth, p);
        glVertex2i(startX + stripeWidth, q);
        glVertex2i(startX, q);
        glEnd();

        startX += stripeWidth + gapWidth;
    }
}

void BusStripes(int p, int q,int n, int gapWidth, int startX, int stripeWidth)
{

    for (int i = 0; i < n; i++)
    {
        glColor3f(0.11, 0.15, 0.17);
        glBegin(GL_POLYGON);
        glVertex2i(startX, p);
        glVertex2i(startX + stripeWidth, p);
        glVertex2i(startX + stripeWidth, q);
        glVertex2i(startX, q);
        glEnd();

        startX += stripeWidth + gapWidth;
    }
}

void RallingStripes(int p, int q,int n, int gapWidth, int startX, int stripeWidth)
{

    for (int i = 0; i < n; i++)
    {
        glColor3f(0.56, 0.28, 0);
        glBegin(GL_POLYGON);
        glVertex2i(startX, p);
        glVertex2i(startX + stripeWidth, p);
        glVertex2i(startX + stripeWidth, q);
        glVertex2i(startX, q);
        glEnd();

        startX += stripeWidth + gapWidth;
    }
}

void sculpture1()
{
    float stripeHeight = 6.5;
    float totalHeight = 670 - 60;
    float bottomLeftX = 1090;
    float bottomRightX = 1130;
    float bottomWidth = bottomRightX - bottomLeftX;


    float stripeWidth = bottomWidth - 10;

    for (int i = 1; i < 25; i++)
    {
        float stripeBottomY = 60 + i * (stripeHeight + 15);
        float stripeTopY = stripeBottomY + stripeHeight;

        float stripeLeftXBottom = 1080 + 10;
        float stripeRightXBottom = 1140 - 10;

        float stripeLeftXTop = stripeLeftXBottom;
        float stripeRightXTop = stripeRightXBottom;

        glColor3f(0.9, 1, 1);
        glBegin(GL_POLYGON);
        glVertex2f(stripeLeftXBottom, stripeBottomY);
        glVertex2f(stripeRightXBottom, stripeBottomY);
        glVertex2f(stripeRightXTop, stripeTopY);
        glVertex2f(stripeLeftXTop, stripeTopY);
        glEnd();
    }

}

void circle(GLfloat rx, GLfloat ry, GLfloat cx, GLfloat cy, GLfloat n)
{
    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(cx,cy);

    for(int i=0; i<=100; i++)
    {
        float angle = 2*3.14*i/n;
        float x = rx*cosf(angle);
        float y = ry*sinf(angle);
        glVertex2f(x+cx,y+cy);
    }
    glEnd();
}


void BorderedCircle(GLfloat rx, GLfloat ry, GLfloat cx, GLfloat cy, GLfloat n)
{
    glBegin(GL_LINE_LOOP);
    for (int i = 0; i <= 100; i++)
    {
        float angle = 2 * 3.14 * i / n;
        float x = rx * cosf(angle);
        float y = ry * sinf(angle);
        glVertex2f(x + cx, y + cy);
    }
    glEnd();
}


void DrawLinesFromMiniCircle(GLfloat miniRadius, GLfloat filledRadius, GLfloat cx, GLfloat cy, GLfloat n)
{
    for (int i = 0; i <= 100; i++)
    {
        float angle = 2 * 3.14 * i / n;

        // Mini Circle (small radius)
        GLfloat miniCircleX = miniRadius * cosf(angle) + cx;
        GLfloat miniCircleY = miniRadius * sinf(angle) + cy;

        // Filled Circle (larger radius)
        GLfloat filledCircleX = filledRadius * cosf(angle) + cx;
        GLfloat filledCircleY = filledRadius * sinf(angle) + cy;

        // Draw line from the mini circle to the filled border
        glBegin(GL_LINES);
        glVertex2f(miniCircleX, miniCircleY);
        glVertex2f(filledCircleX, filledCircleY);
        glEnd();
    }
}

void drawCloud(float startX, float startY)
{
    glColor3f(0.78, 0.87, 1);

    circle(17, 17, startX, startY, 100);
    circle(18, 18, startX + 20, startY - 10, 100);
    circle(18, 18, startX + 20, startY + 20, 100);
    circle(21, 21, startX + 40, startY + 30, 100);
    circle(21, 21, startX + 40, startY - 10, 100);
    circle(23, 23, startX + 70, startY, 100);
    circle(23, 23, startX + 70, startY + 25, 100);
    circle(17, 17, startX + 95, startY + 10, 100);
}

void DrawRotatingFerrisWheel() {
    glPushMatrix();
    glTranslatef(860, 380, 0);
    glRotatef(ferrisWheelAngle, 0, 0, 1);
    glTranslatef(-860, -380, 0);

    glColor3f(0, 0.7, 0.99);
    BorderedCircle(180, 180, 860, 380, 100); // Outer border

    circle(170, 170, 860, 380, 100); // Filled border
    glColor3f(0.98, 0.96, 0.99);
    circle(160, 160, 860, 380, 100); // Inner circle

    glColor3f(0.49, 0.87, 1);
    circle(24, 24, 860, 380, 100); // Inner mini circle
    glColor3f(0, 0.7, 0.99);
    circle(20, 20, 860, 380, 100); // Inner mini circle

    DrawLinesFromMiniCircle(20, 160, 860, 380, 40);


    for (int i = 0; i < 12; i++) {
        float angle = 2 * 3.14f * i / 12;
        float x = 185 * cosf(angle) + 860;
        float y = 185 * sinf(angle) + 380;
        glColor3f(1, 0.58, 0.01);
        circle(11, 11, x, y, 100);
    }

    glPopMatrix();

    // Update rotation angle
    ferrisWheelAngle += rotationSpeed;
    if(ferrisWheelAngle > 360)
        ferrisWheelAngle -= 360;
}



void drawStripes()
{
    float startX = 1140 + 10; // 5px left gap
    float endX = 1190 - 10;   // 5px right gap
    float totalHeight = 580 - 60; // full height of the area
    int stripeCount = 20;
    float gap = 15;

    float stripeHeight = (totalHeight - (stripeCount - 1) * gap) / stripeCount;

    for (int i = 1; i < stripeCount; i++)
    {
        float yBottom = 60 + i * (stripeHeight + gap);
        float yTop = yBottom + stripeHeight;

        glColor3f(0.9, 1, 1);
        glBegin(GL_POLYGON);
        glVertex2f(startX, yBottom);
        glVertex2f(endX, yBottom);
        glVertex2f(endX, yTop);
        glVertex2f(startX, yTop);
        glEnd();
    }
}


void drawStripedGridInEllipse(GLfloat rx, GLfloat ry, GLfloat cx, GLfloat cy, int stripeW, int stripeH, int spacing)
{

    for (int x = cx - rx; x <= cx + rx - stripeW; x += stripeW + spacing)
    {
        for (int y = cy - ry; y <= cy + ry - 1; y++)
        {
            float dx = (x + stripeW / 2.0) - cx;
            float dy = (y + stripeH / 2.0) - cy;
            if ((dx * dx) / (rx * rx) + (dy * dy) / (ry * ry) <= 1.0f)
            {
                glColor3f(0.9, 1, 1);
                glBegin(GL_POLYGON);
                glVertex2i(x, y);
                glVertex2i(x + stripeW, y);
                glVertex2i(x + stripeW, y + stripeH);
                glVertex2i(x, y + stripeH);
                glEnd();
            }
        }
    }

    for (int y = cy - ry; y <= cy + ry - stripeH; y += stripeH + spacing)
    {
        for (int x = cx - rx; x <= cx + rx - 1; x++)
        {
            float dx = (x + stripeW / 2.0) - cx;
            float dy = (y + stripeH / 2.0) - cy;
            if ((dx * dx) / (rx * rx) + (dy * dy) / (ry * ry) <= 1.0f)
            {
                glColor3f(0.9, 1, 1);
                glBegin(GL_POLYGON);
                glVertex2i(x, y);
                glVertex2i(x + stripeW, y);
                glVertex2i(x + stripeW, y + stripeH);
                glVertex2i(x, y + stripeH);
                glEnd();
            }
        }
    }
}



void Draw()
{
    glClear(GL_COLOR_BUFFER_BIT);


    ////////////////////////////////////////////////////////Cloud//////////////////////////////////
    if(cloud1X<=1280)
        cloud1X+=0.09;
    else
        cloud1X=0.0;
    glutPostRedisplay();
    drawCloud(cloud1X, 640);

    if(cloud2X<=1280)
        cloud2X+=0.09;
    else
        cloud2X=0.0;
    glutPostRedisplay();
    drawCloud(cloud2X, 640);

    if(cloud3X<=1280)
        cloud3X+=0.09;
    else
        cloud3X=0.0;
    glutPostRedisplay();
    drawCloud(cloud3X, 640);




    ////////////////////////////////////////////////////////Sculpture//////////////////////////////////
    glColor3f(0.38, 0.82, 1); //left part
    glBegin(GL_POLYGON);
    glVertex2i(1080,60);
    glVertex2i(1080,670);
    glVertex2i(1140,640);
    glVertex2i(1140,60);
    glEnd();
    sculpture1();

    glColor3f(0.38, 0.82, 1);
    circle(100, 230, 1240, 200, 100);

    drawStripedGridInEllipse(100, 220, 1240, 200, 5, 5, 30);

    glColor3f(0, 0.7, 0.99);
    glBegin(GL_POLYGON); //right part
    glVertex2i(1140,60);
    glVertex2i(1140,620);
    glVertex2i(1190,630);
    glVertex2i(1200,60);
    glEnd();
    drawStripes();



    ///////////////////////////////////////////Road///////////////////////////////
    glColor3f( 0.44, 0.34, 0.24);
    glBegin(GL_POLYGON);
    glVertex2i(0,0);
    glVertex2i(0,40);
    glVertex2i(1280,40);
    glVertex2i(1280,0);
    glEnd();
    glColor3f( 0.25, 0.17, 0.09);
    glBegin(GL_POLYGON);
    glVertex2i(0,40);
    glVertex2i(0,60);
    glVertex2i(1280,60);
    glVertex2i(1280,40);
    glEnd();


    //////////////////////////////////////////////////pilar-1///////////////////////////////////////////////////
    glColor3f( 0.37, 0.17, 0.04); //base
    glBegin(GL_POLYGON);
    glVertex2i(80,60);
    glVertex2i(80,100);
    glVertex2i(160,100);
    glVertex2i(160,60);
    glEnd();
    glColor3f( 0.79, 0.59, 0.46); //main part
    glBegin(GL_POLYGON);
    glVertex2i(85,100);
    glVertex2i(85,280);
    glVertex2i(155,280);
    glVertex2i(155,100);
    glEnd();
    glColor3f(0.64, 0.34, 0.05); //main upper part
    glBegin(GL_POLYGON);
    glVertex2i(85,265);
    glVertex2i(85,280);
    glVertex2i(155,280);
    glVertex2i(155,265);
    glEnd();
    glColor3f(0.36, 0.20, 0.10);// First Horizontal Stripe
    glBegin(GL_POLYGON);
    glVertex2i(85, 220);
    glVertex2i(155, 220);
    glVertex2i(155, 225);
    glVertex2i(85, 225);
    glEnd();
    glBegin(GL_POLYGON); // Second Horizontal Stripe
    glVertex2i(85, 145);
    glVertex2i(155, 145);
    glVertex2i(155, 150);
    glVertex2i(85, 150);
    glEnd();

    // middle vertical stripes
    stripes(155,215,6,4,95);

    // upper vertical stripes
    stripes(230,260,6,4,95);

    // lower vertical stripes
    stripes(105,140,6,4,95);

    glColor3f(0.56, 0.28, 0); //Upper big triangles
    glBegin(GL_TRIANGLES);
    glVertex2i(90,280);
    glVertex2i(120,400);
    glVertex2i(150,280);
    glEnd();
    glColor3f(0.37, 0.17, 0.04); //Upper small triangles
    glBegin(GL_TRIANGLES);
    glVertex2i(85,280);
    glVertex2i(95,325);
    glVertex2i(105,280);
    glEnd();
    glColor3f(0.37, 0.17, 0.04); //Upper  small triangles
    glBegin(GL_TRIANGLES);
    glVertex2i(135,280);
    glVertex2i(145,325);
    glVertex2i(155,280);
    glEnd();


    //////////////////////////////////////////////////pilar-3 small///////////////////////////////////////////////////
    glColor3f( 0.79, 0.59, 0.46); //main part
    glBegin(GL_POLYGON);
    glVertex2i(460,210);
    glVertex2i(460,280);
    glVertex2i(530,280);
    glVertex2i(530,210);
    glEnd();
    glColor3f(0.64, 0.34, 0.05); //main upper part
    glBegin(GL_POLYGON);
    glVertex2i(460,265);
    glVertex2i(460,280);
    glVertex2i(530,280);
    glVertex2i(530,265);
    glEnd();

    stripes(230,260,6,4,470);// upper vertical stripes

    glColor3f(0.56, 0.28, 0); //Upper big triangles
    glBegin(GL_TRIANGLES);
    glVertex2i(465,280);
    glVertex2i(495,400);
    glVertex2i(525,280);
    glEnd();
    glColor3f(0.37, 0.17, 0.04); //Upper small triangles
    glBegin(GL_TRIANGLES);
    glVertex2i(460,280);
    glVertex2i(470,325);
    glVertex2i(480,280);
    glEnd();
    glColor3f(0.37, 0.17, 0.04); //Upper  small triangles
    glBegin(GL_TRIANGLES);
    glVertex2i(510,280);
    glVertex2i(520,325);
    glVertex2i(530,280);
    glEnd();



    ///////////////////////////////////////////////////////Bridge///////////////////////////////////////////////////////
    glColor3f( 0.36, 0.53, 0.71); //main base left part
    glBegin(GL_POLYGON);
    glVertex2i(0,100);
    glVertex2i(0,110);
    glVertex2i(85,110);
    glVertex2i(85,100);
    glEnd();
    glBegin(GL_POLYGON); //main base right part
    glVertex2i(155,100);
    glVertex2i(155,110);
    glVertex2i(205,110);
    glVertex2i(205,100);
    glEnd();
    glBegin(GL_POLYGON); //main base upper right part
    glVertex2i(155,225);
    glVertex2i(155,230);
    glVertex2i(255,230);
    glVertex2i(255,225);
    glEnd();
    glBegin(GL_LINES); //bridge upper line part
    glVertex2i(155,220);
    glVertex2i(255,220);
    glEnd();
    glBegin(GL_POLYGON); //main base right part
    glVertex2i(240,100);
    glVertex2i(240,110);
    glVertex2i(255,110);
    glVertex2i(255,100);
    glEnd();
    glBegin(GL_POLYGON); //main base right part
    glVertex2i(335,100);
    glVertex2i(335,110);
    glVertex2i(445,110);
    glVertex2i(445,100);
    glEnd();
    glBegin(GL_POLYGON); //main base upper right part
    glVertex2i(335,225);
    glVertex2i(335,230);
    glVertex2i(445,230);
    glVertex2i(445,225);
    glEnd();
    glBegin(GL_LINES); //bridge upper line part
    glVertex2i(335,220);
    glVertex2i(445,220);
    glEnd();
    glBegin(GL_LINES);
    glVertex2i(0,160);
    glVertex2i(85,220);
    glEnd();
    glBegin(GL_POLYGON); //bridge upper part
    glVertex2i(0,165);
    glVertex2i(0,170);
    glVertex2i(85,230);
    glVertex2i(85,225);
    glEnd();
    glBegin(GL_POLYGON); //bridge side part
    glVertex2i(80,110);
    glVertex2i(80,225);
    glVertex2i(85,225);
    glVertex2i(85,110);
    glEnd();
    glBegin(GL_LINES); //bridge front part
    glVertex2i(10,110);
    glVertex2i(10,175);
    glEnd();
    glBegin(GL_LINES); //bridge back part
    glVertex2i(15,110);
    glVertex2i(15,170);
    glEnd();
    glColor3f(0.36, 0.53, 0.71); //bridge front part
    glBegin(GL_LINES);
    glVertex2i(30,110);
    glVertex2i(30,190);
    glEnd();
    glBegin(GL_LINES); //bridge back part
    glVertex2i(35,110);
    glVertex2i(35,185);
    glEnd();
    glBegin(GL_LINES); //bridge front part
    glVertex2i(50,110);
    glVertex2i(50,205);
    glEnd();
    glBegin(GL_LINES); //bridge back part
    glVertex2i(55,110);
    glVertex2i(55,200);
    glEnd();


    /////////////////////////////////////////////////Postbox///////////////////////////
    glColor3f( 0, 0, 0); //Postbox base
    glBegin(GL_POLYGON);
    glVertex2i(200,60);
    glVertex2i(200,70);
    glVertex2i(245,70);
    glVertex2i(245,60);
    glEnd();
    glColor3f( 1, 0, 0); //Postbox main
    glBegin(GL_POLYGON);
    glVertex2i(205,70);
    glVertex2i(205,180);
    glVertex2i(240,180);
    glVertex2i(240,70);
    glEnd();
    glColor3f( 0.94, 0.08, 0.08); //Postbox upper
    glBegin(GL_POLYGON);
    glVertex2i(200,180);
    glVertex2i(205,200);
    glVertex2i(240,200);
    glVertex2i(245,180);
    glEnd();
    glColor3f( 1, 1, 1); //Postbox white part
    glBegin(GL_POLYGON);
    glVertex2i(210,165);
    glVertex2i(210,170);
    glVertex2i(235,170);
    glVertex2i(235,165);
    glEnd();
    glColor3f( 1, 0, 0); //Postbox main part
    glBegin(GL_POLYGON);
    glVertex2i(210,80);
    glVertex2i(210,155);
    glVertex2i(235,155);
    glVertex2i(235,80);
    glEnd();

    glColor3f(0, 0, 0);  // postbox black part
    for(int i = 0; i < 3; i++)    // Columns
    {
        for(int j = 0; j < 4; j++)    // Rows
        {
            int x1 = 210 + i * (7 + 2);
            int y1 = 80 + j * (17.25 + 2);
            int x2 = x1 + 7;
            int y2 = y1 + 17.25;

            glBegin(GL_POLYGON);  // Filled black rectangles
            glVertex2i(x1, y1);
            glVertex2i(x2, y1);
            glVertex2i(x2, y2);
            glVertex2i(x1, y2);
            glEnd();
        }
    }



    ////////////////////////////////////////////////////////Pillar-2//////////////////////////////////////////
    glColor3f(0.37, 0.17, 0.04); //Pillar base
    glBegin(GL_POLYGON);
    glVertex2i(245,60);
    glVertex2i(245,70);
    glVertex2i(345,70);
    glVertex2i(345,60);
    glEnd();
    glColor3f(0.79, 0.59, 0.46); //Pillar main-1
    glBegin(GL_POLYGON);
    glVertex2i(250,70);
    glVertex2i(250,245);
    glVertex2i(340,245);
    glVertex2i(340,70);
    glEnd();
    //lower stripes
    stripes(85,230,7,5,262);

    glColor3f(0.36, 0.20, 0.10);// First Horizontal Stripe
    glBegin(GL_POLYGON);
    glVertex2i(255, 245);
    glVertex2i(255, 255);
    glVertex2i(335, 255);
    glVertex2i(335, 245);
    glEnd();
    glColor3f(0.79, 0.59, 0.46); //Pillar main-2
    glBegin(GL_POLYGON);
    glVertex2i(250,255);
    glVertex2i(250,340);
    glVertex2i(340,340);
    glVertex2i(340,255);
    glEnd();
    //middle stripes
    stripes(265,325,7,5,262);

    glColor3f(0.36, 0.20, 0.10);// second Horizontal Stripe
    glBegin(GL_POLYGON);
    glVertex2i(255, 340);
    glVertex2i(255, 350);
    glVertex2i(335, 350);
    glVertex2i(335, 340);
    glEnd();
    glColor3f(0.79, 0.59, 0.46); //Pillar main-3
    glBegin(GL_POLYGON);
    glVertex2i(250,350);
    glVertex2i(250,460);
    glVertex2i(340,460);
    glVertex2i(340,350);
    glEnd();
    //upper stripes
    stripes(355,375,7,5,262);


    glColor3f(0.36, 0.20, 0.10);// third Horizontal Stripe
    glBegin(GL_POLYGON);
    glVertex2i(255, 460);
    glVertex2i(255, 470);
    glVertex2i(335, 470);
    glVertex2i(335, 460);
    glEnd();
    glColor3f(0.79, 0.59, 0.46); //Pillar main-4
    glBegin(GL_POLYGON);
    glVertex2i(265,470);
    glVertex2i(265,500);
    glVertex2i(325,500);
    glVertex2i(325,470);
    glEnd();
    //above upper stripes
    stripes(475,495,5,4,275);

    glColor3f(0.56, 0.28, 0); //upper parts
    glBegin(GL_POLYGON);
    glVertex2i(265,500);
    glVertex2i(275,520);
    glVertex2i(315,520);
    glVertex2i(325,500);
    glEnd();
    glColor3f(0.36, 0.20, 0.10); //upper border parts
    glBegin(GL_POLYGON);
    glVertex2i(275,520);
    glVertex2i(275,525);
    glVertex2i(315,525);
    glVertex2i(315,520);
    glEnd();
    glColor3f(0.36, 0.20, 0.10); //upper border parts
    glBegin(GL_POLYGON);
    glVertex2i(265,500);
    glVertex2i(265,505);
    glVertex2i(325,505);
    glVertex2i(325,500);
    glEnd();
    glColor3f(0.79, 0.59, 0.46); //Pillar main-4
    glBegin(GL_POLYGON);
    glVertex2i(275,525);
    glVertex2i(275,545);
    glVertex2i(315,545);
    glVertex2i(315,525);
    glEnd();
    //above upper stripes
    stripes(530,540,4,4,280);

    glColor3f(0.56, 0.28, 0); //Upper big triangles
    glBegin(GL_TRIANGLES);
    glVertex2i(275,545);
    glVertex2i(295,620);
    glVertex2i(315,545);
    glEnd();

    glColor3f(0.36, 0.20, 0.10); //Watch
    glBegin(GL_POLYGON);
    glVertex2i(262,385);
    glVertex2i(262,450);
    glVertex2i(328,450);
    glVertex2i(328,385);
    glEnd();
    glColor3f(1.0, 1.0, 1.0);
    circle(26, 26, 295, 417.5,100);
    glColor3f(0.0, 0.0, 0.0);
    circle(3, 3, 295, 417.5,100);

    // Hour Hand (Short, to the right)
    glBegin(GL_LINES);
    glVertex2i(295, 417.5);  // Center
    glVertex2i(315, 417.5);  // Right (3 o'clock)
    glEnd();

    // Minute Hand (Long, Upwards)
    glBegin(GL_LINES);
    glVertex2i(295, 417.5);  // Center
    glVertex2i(295, 439);    // Up (12 o'clock)
    glEnd();




    ////////////////////////////////////////////////////////Ferris wheel//////////////////////////////////
    DrawRotatingFerrisWheel();




    ////////////////////////////////////////////////////////house1//////////////////////////////////
    glColor3f(0.91, 0.59, 0.46); //house base
    glBegin(GL_POLYGON);
    glVertex2i(350,60);
    glVertex2i(350,245);
    glVertex2i(445,245);
    glVertex2i(445,60);
    glEnd();
    glColor3f(0.56, 0.28, 0); //house stripe1
    glBegin(GL_POLYGON);
    glVertex2i(350,115);
    glVertex2i(350,120);
    glVertex2i(445,120);
    glVertex2i(445,115);
    glEnd();
    glColor3f(0.56, 0.28, 0); //house stripe2
    glBegin(GL_POLYGON);
    glVertex2i(350,180);
    glVertex2i(350,185);
    glVertex2i(445,185);
    glVertex2i(445,180);
    glEnd();
    glColor3f(0.56, 0.28, 0); //house stripe3
    glBegin(GL_POLYGON);
    glVertex2i(350,230);
    glVertex2i(350,235);
    glVertex2i(445,235);
    glVertex2i(445,230);
    glEnd();
    glColor3f(0.97, 0.81, 0.74); //house triangle
    glBegin(GL_POLYGON);
    glVertex2i(350,185);
    glVertex2i(398,225);
    glVertex2i(445,185);
    glEnd();

    HouseStripes(130,170,4,6,359,15); //house stripes

    glColor3f(0.36, 0.20, 0.10); //house door
    glBegin(GL_POLYGON);
    glVertex2i(380,60);
    glVertex2i(380,95);
    glVertex2i(415,95);
    glVertex2i(415,60);
    glEnd();
    circle(17.5, 10, 397.5, 95, 50); // draw semi-circle top of the door


    ////////////////////////////////////////////////////house2/////////////////////////////////////////
    glColor3f(0.91, 0.59, 0.46); //house base
    glBegin(GL_POLYGON);
    glVertex2i(665,60);
    glVertex2i(665,290);
    glVertex2i(785,290);
    glVertex2i(785,60);
    glEnd();
    glColor3f(00.56, 0.28, 0); //house stripe1
    glBegin(GL_POLYGON);
    glVertex2i(665,115);
    glVertex2i(665,120);
    glVertex2i(785,120);
    glVertex2i(785,115);
    glEnd();
    glColor3f(0.56, 0.28, 0); //house stripe2
    glBegin(GL_POLYGON);
    glVertex2i(665,200);
    glVertex2i(665,205);
    glVertex2i(785,205);
    glVertex2i(785,200);
    glEnd();
    glColor3f(0.56, 0.28, 0); //house stripe3
    glBegin(GL_POLYGON);
    glVertex2i(665,275);
    glVertex2i(665,280);
    glVertex2i(785,280);
    glVertex2i(785,275);
    glEnd();
    glColor3f(0.97, 0.81, 0.74); //house triangle
    glBegin(GL_POLYGON);
    glVertex2i(665,205);
    glVertex2i(725,270);
    glVertex2i(785,205);
    glEnd();

    HouseStripes(130,190,4,8,678,18); //house stripes

    glColor3f(0.36, 0.20, 0.10); //house door
    glBegin(GL_POLYGON);
    glVertex2i(710,60);
    glVertex2i(710,95);
    glVertex2i(740,95);
    glVertex2i(740,60);
    glEnd();
    circle(15, 10, 725, 95,50); // draw semi-circle top of the door


    ////////////////////////////////////////////////////////house3//////////////////////////////////
    glColor3f(0.91, 0.59, 0.46); //house base
    glBegin(GL_POLYGON);
    glVertex2i(1005,60);
    glVertex2i(1005,245);
    glVertex2i(1100,245);
    glVertex2i(1100,60);
    glEnd();
    glColor3f(0.56, 0.28, 0); //house stripe1
    glBegin(GL_POLYGON);
    glVertex2i(1005,115);
    glVertex2i(1005,120);
    glVertex2i(1100,120);
    glVertex2i(1100,115);
    glEnd();
    glColor3f(0.56, 0.28, 0); //house stripe2
    glBegin(GL_POLYGON);
    glVertex2i(1005,180);
    glVertex2i(1005,185);
    glVertex2i(1100,185);
    glVertex2i(1100,180);
    glEnd();
    glColor3f(0.56, 0.28, 0); //house stripe3
    glBegin(GL_POLYGON);
    glVertex2i(1005,230);
    glVertex2i(1005,235);
    glVertex2i(1100,235);
    glVertex2i(1100,230);
    glEnd();
    glColor3f(0.97, 0.81, 0.74); //house triangle
    glBegin(GL_POLYGON);
    glVertex2i(1005,185);
    glVertex2i(1053,225);
    glVertex2i(1100,185);
    glEnd();

    HouseStripes(130,170,4,6,1015,15); //house stripes

    glColor3f(0.36, 0.20, 0.10); //house door
    glBegin(GL_POLYGON);
    glVertex2i(1035,60);
    glVertex2i(1035,95);
    glVertex2i(1070,95);
    glVertex2i(1070,60);
    glEnd();
    circle(17.5, 10, 1052.5, 95, 50); // draw semi-circle top of the door



    ////////////////////////////////////////////////////////Big house1//////////////////////////////////
    glColor3f(1, 0.69, 0.55); //house base
    glBegin(GL_POLYGON);
    glVertex2i(445,60);
    glVertex2i(445,210);
    glVertex2i(665,210);
    glVertex2i(665,60);
    glEnd();
    glColor3f(0.56, 0.28, 0); //house stripe1
    glBegin(GL_POLYGON);
    glVertex2i(445,125);
    glVertex2i(445,130);
    glVertex2i(665,130);
    glVertex2i(665,125);
    glEnd();
    glColor3f(0.56, 0.28, 0); //house stripe2
    glBegin(GL_POLYGON);
    glVertex2i(445,190);
    glVertex2i(445,195);
    glVertex2i(665,195);
    glVertex2i(665,190);
    glEnd();
    glColor3f(0.56, 0.28, 0); //house stripe3
    glBegin(GL_POLYGON);
    glVertex2i(445,220);
    glVertex2i(445,225);
    glVertex2i(665,225);
    glVertex2i(665,220);
    glEnd();

    HouseStripes(140,180,6,12,460,22); //house stripes middle
    HouseStripes(70,115,2,12,460,22); //house stripes bottom-left
    HouseStripes(70,115,2,12,595,22); //house stripes bottom-right

    RallingStripes(210,220,27,5,450,3); //house roof ralling

    glColor3f(0.36, 0.20, 0.10); //house door
    glBegin(GL_POLYGON);
    glVertex2i(535,60);
    glVertex2i(535,95);
    glVertex2i(577,95);
    glVertex2i(577,60);
    glEnd();
    circle(21, 13, 556, 95, 50); // draw semi-circle top of the door


    ////////////////////////////////////////////////////////Big house2//////////////////////////////////
    glColor3f(1, 0.69, 0.55); //house base
    glBegin(GL_POLYGON);
    glVertex2i(785,60);
    glVertex2i(785,210);
    glVertex2i(1005,210);
    glVertex2i(1005,60);
    glEnd();
    glColor3f(0.56, 0.28, 0); //house stripe1
    glBegin(GL_POLYGON);
    glVertex2i(785,125);
    glVertex2i(785,130);
    glVertex2i(1005,130);
    glVertex2i(1005,125);
    glEnd();
    glColor3f(0.56, 0.28, 0); //house stripe2
    glBegin(GL_POLYGON);
    glVertex2i(785,190);
    glVertex2i(785,195);
    glVertex2i(1005,195);
    glVertex2i(1005,190);
    glEnd();
    glColor3f(0.56, 0.28, 0); //house stripe3
    glBegin(GL_POLYGON);
    glVertex2i(785,220);
    glVertex2i(785,225);
    glVertex2i(1005,225);
    glVertex2i(1005,220);
    glEnd();

    HouseStripes(140,180,6,12,800,22); //house stripes middle
    HouseStripes(70,115,2,12,800,22); //house stripes bottom-left
    HouseStripes(70,115,2,12,935,22); //house stripes bottom-right

    RallingStripes(210,220,27,5,790,3); //house roof ralling

    glColor3f(0.36, 0.20, 0.10); //house door
    glBegin(GL_POLYGON);
    glVertex2i(875,60);
    glVertex2i(875,95);
    glVertex2i(917,95);
    glVertex2i(917,60);
    glEnd();
    circle(21, 13, 896, 95, 50); // draw semi-circle top of the door



    //////////////////////////////////////////////Hot Air Ballon-1//////////////////////////////////
    if (movingUpB1) {
        p += 0.05; // Move up
        if (p >= 720.0) {
            movingUpB1 = false; // Change direction
        }
    } else {
        p -= 0.05; // Move down
        if (p <= 480.0) {
            movingUpB1 = true; // Change direction
        }
    }

    glutPostRedisplay();
    //parasoot base
    glColor3f(0.56, 0.28, 0);
    circle(20, 30, 580, p-100, -200);
    glBegin(GL_LINES);
    glVertex2f(595, p-115);
    glVertex2f(620, p);
    glEnd();
    glBegin(GL_LINES);
    glVertex2f(565, p-115);
    glVertex2f(540, p);
    glEnd();
    glBegin(GL_LINES);
    glVertex2f(580, p-115);
    glVertex2f(580, p);
    glEnd();
    glBegin(GL_POLYGON);
    glVertex2i(565, p-135);
    glVertex2i(565, p-115);
    glVertex2i(595, p-115);
    glVertex2i(595, p-135);
    glEnd();

    //parasoot baloon
    glColor3f(0.99, 0.71, 0.63);
    circle(70, 85, 580, p, 50);
    glColor3f(1, 0.48, 0.33);
    circle(50, 85, 580, p, 50);
    glColor3f(0.99, 0.71, 0.63);
    circle(35, 85, 580, p, 50);
    glColor3f(1, 0.48, 0.33);
    circle(5, 85, 580, p, 50);


    //////////////////////////////////////////////Hot Air Ballon-2//////////////////////////////////
    if (movingUpB2) {
        q += 0.05; // Move up
        if (q >= 720.0) {
            movingUpB2 = false; // Change direction
        }
    } else {
        q -= 0.05; // Move down
        if (q <= 620.0) {
            movingUpB2 = true; // Change direction
        }
    }

    glutPostRedisplay();
    // Big parasoot base
    glColor3f(0.56, 0.28, 0);
    circle(20, 30, 180, q-100, -200);
    glBegin(GL_LINES);
    glVertex2f(195, q-115);
    glVertex2f(220, q);
    glEnd();
    glBegin(GL_LINES);
    glVertex2f(165, q-115);
    glVertex2f(140, q);
    glEnd();
    glBegin(GL_LINES);
    glVertex2f(180, q-115);
    glVertex2f(180, q);
    glEnd();
    glBegin(GL_POLYGON);
    glVertex2f(165, q-135);
    glVertex2f(165, q-115);
    glVertex2f(195, q-115);
    glVertex2f(195, q-135);
    glEnd();

    // Big parasoot balloon
    glColor3f(0.99, 0.71, 0.63);
    circle(70, 85, 180, q, 50);
    glColor3f(1, 0.48, 0.33);
    circle(50, 85, 180, q, 50);
    glColor3f(0.99, 0.71, 0.63);
    circle(35, 85, 180, q, 50);
    glColor3f(1, 0.48, 0.33);
    circle(5, 85, 180, q, 50);


    //////////////////////////////////////////////Bus//////////////////////////////////
    busX -= busSpeed;
    wheelAngle += wheelRotationSpeed;
    if(wheelAngle > 360) wheelAngle -= 360;
    if(busX < -170)
        busX = 1280;

     float offsetX = busX - 1280;

    // Bus base (bottom part)
    glColor3f(1, 0.18, 0.33);
    glBegin(GL_POLYGON);
    glVertex2f(1103 + offsetX, 20);
    glVertex2f(1103 + offsetX, 50);
    glVertex2f(1270 + offsetX, 50);
    glVertex2f(1270 + offsetX, 20);
    glEnd();

    // Bus main body
    glColor3f(1, 0.18, 0.33);
    glBegin(GL_POLYGON);
    glVertex2f(1110 + offsetX, 50);
    glVertex2f(1110 + offsetX, 130);
    glVertex2f(1270 + offsetX, 130);
    glVertex2f(1270 + offsetX, 50);
    glEnd();

    // Horizontal decorative stripe
    glColor3f(1, 1, 0.01);
    glBegin(GL_POLYGON);
    glVertex2f(1110 + offsetX, 86);
    glVertex2f(1110 + offsetX, 90);
    glVertex2f(1270 + offsetX, 90);
    glVertex2f(1270 + offsetX, 86);
    glEnd();

    // Bottom trim lines
    glBegin(GL_LINES);
    glVertex2f(1150 + offsetX, 45);
    glVertex2f(1230 + offsetX, 45);
    glEnd();
    glBegin(GL_LINES);
    glVertex2f(1120 + offsetX, 38);
    glVertex2f(1230 + offsetX, 38);
    glEnd();

    // Windows and doors (using your BusStripes function)
    BusStripes(118, 100, 5, 4, 1120 + offsetX, 25);  // Upper windows
    BusStripes(78, 58, 3, 4, 1150 + offsetX, 25);    // Lower windows
    BusStripes(78, 25, 1, 4, 1240 + offsetX, 25);    // Door
    BusStripes(78, 45, 1, 4, 1120 + offsetX, 25);    // Driver window

    // Front wheel (with rotation)
    glPushMatrix();
    glTranslatef(1135 + offsetX, 18, 0);
    glRotatef(wheelAngle, 0, 0, 1);
    glColor3f(0.11, 0.15, 0.17);
    circle(18, 18, 0, 0, 50);
    glColor3f(0.98, 0.96, 0.99);
    circle(8, 8, 0, 0, 50);
    glPopMatrix();

    // Rear wheel (with rotation)
    glPushMatrix();
    glTranslatef(1220 + offsetX, 18, 0);
    glRotatef(wheelAngle, 0, 0, 1);
    glColor3f(0.11, 0.15, 0.17);
    circle(18, 18, 0, 0, 50);
    glColor3f(0.98, 0.96, 0.99);
    circle(8, 8, 0, 0, 50);
    glPopMatrix();

    glutPostRedisplay();



    glutSwapBuffers();
}

int main(int argc,char **argv)
{
    glutInit(&argc,argv);
    glutInitDisplayMode ( GLUT_RGB | GLUT_DOUBLE );
    glutInitWindowPosition(0,0);
    glutInitWindowSize(500,500);
    glutCreateWindow("Lab Final");
    init();
    glutDisplayFunc(Draw);
    glutMainLoop();
    return 0;
}
