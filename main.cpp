// ============================================================
//  Road Scene with Day / Night Transition + Rain
//  Keys: D = Day | N = Night
// ============================================================

#include <windows.h>
#include <GL/glut.h>
#define PI 3.141516
#include <math.h>
#include <cmath>
#include <stdlib.h>

// ── Day / Night ───────────────────────────────────────────────────────────────
bool isDay = true;

// ── Animation globals ─────────────────────────────────────────────────────────
float angle = 0.0f;

// ── Bird globals ──────────────────────────────────────────────────────────────
float birdX = 0.0f, birdY = 7.2f;
float birdWingY = -1.0f, birdDirection = 1.0f;

// ── Cloud globals ─────────────────────────────────────────────────────────────
float cloud1X = 0.0f,  cloud1Y = 7.0f;
float cloud2X = 3.5f,  cloud2Y = 7.4f;
float cloud3X = 6.5f,  cloud3Y = 7.1f;

// ── Rain globals ──────────────────────────────────────────────────────────────
#define MAX_DROPS 1000
float dropX[MAX_DROPS];
float dropY[MAX_DROPS];
int totalDrops = 0;
bool isRain = false;

// ── Car globals ───────────────────────────────────────────────────────────────
float angle1   = 0.0f;   // wheel rotation angle
float car1Move = 0.0f;   // car on bottom road  (moves left -> right)
float car2Move = 9.0f;   // car on upper road   (moves right -> left)

// ── Boat globals (from provided boat code) ────────────────────────────────────
float boatX = 0.0f;      // boat x position in scene coords (0..9)

// ── Draw a single circle blob (used for clouds) ───────────────────────────────
void drawCircleBlob(float cx, float cy, float r)
{
    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(cx, cy);
    for (int i = 0; i <= 30; ++i)
    {
        float theta = 2.0f * PI * float(i) / 30.0f;
        glVertex2f(cx + r * cosf(theta), cy + r * sinf(theta));
    }
    glEnd();
}

// ── Draw one cloud at world position (x, y) ───────────────────────────────────
void drawCloud(float x, float y, float s)
{
    glColor3f(1.0f, 1.0f, 1.0f);
    drawCircleBlob(x,          y,          0.28f * s);
    drawCircleBlob(x + 0.28f*s, y + 0.10f*s, 0.22f * s);
    drawCircleBlob(x - 0.28f*s, y + 0.08f*s, 0.20f * s);
    drawCircleBlob(x + 0.50f*s, y,          0.18f * s);
    drawCircleBlob(x - 0.48f*s, y,          0.16f * s);
}

// ── Cloud animation step ──────────────────────────────────────────────────────
void cloudAnimation()
{
    float speed = 0.008f;
    cloud1X += speed;
    cloud2X += speed * 0.7f;
    cloud3X += speed * 1.2f;

    if (cloud1X >  10.5f) cloud1X = -2.0f;
    if (cloud2X >  10.5f) cloud2X = -2.0f;
    if (cloud3X >  10.5f) cloud3X = -2.0f;
}

// ── Draw a filled polygon from a plain array ──────────────────────────────────
void polygon(float coords[][2], int count,
             int r, int g, int b,
             float Tx=0, float Ty=0, float s=1)
{
    glColor3ub(r, g, b);
    glBegin(GL_POLYGON);
    for (int i = 0; i < count; i++)
        glVertex2f(Tx + s * coords[i][0], Ty + s * coords[i][1]);
    glEnd();
}

// ── Draw one bird ─────────────────────────────────────────────────────────────
void bird(float Tx, float Ty, float direction, float wingY,
          int r=0, int g=0, int b=0, float s=1)
{
    float body[][2] = {
        {28.65f*direction,  2.99f},
        {31.98f*direction,  1.74f},
        {31.6f *direction,  0.23f},
        {31.93f*direction, -1.29f},
        {30.43f*direction, -0.38f},
        {28.77f*direction, -1.12f},
        {24.29f*direction, -4.59f},
        {16.47f*direction, -5.28f},
        {10.7f *direction, -4.96f},
        {2.95f *direction,-10.29f},
        {8.55f *direction, -3.22f},
        {0.18f *direction,  1.29f},
        {9.57f *direction, -0.31f},
        {11.02f*direction,  0.27f},
        {22.82f*direction,  1.86f},
        {28.65f*direction,  2.99f}
    };
    float wing[][2] = {
        {22.82f*direction, wingY*1.86f},
        {23.38f*direction, wingY*8.57f},
        {9.98f *direction, wingY*25.45f},
        {11.02f*direction, wingY*0.27f}
    };
    polygon(body, 16, r, g, b, Tx, Ty, s);
    polygon(wing,  4, r, g, b, Tx, Ty, s);
}

// ── Small animated roadside tree ──────────────────────────────────────────────
void drawTree(float x, float y)
{
    glColor3f(0.55f, 0.27f, 0.07f);
    glBegin(GL_QUADS);
        glVertex2f(x-0.03f, y);
        glVertex2f(x+0.03f, y);
        glVertex2f(x+0.03f, y+0.3f);
        glVertex2f(x-0.03f, y+0.3f);
    glEnd();
    glPushMatrix();
    glTranslatef(x, y+0.3f, 0);
    glRotatef(10*sin(angle), 0, 0, 1);
    glTranslatef(-x, -(y+0.3f), 0);

    // leaves darker at night
    if (isDay) glColor3f(0.0f, 0.6f, 0.0f);
    else        glColor3f(0.0f, 0.3f, 0.0f);

    for (float i = 0; i < 3; ++i) {
        glBegin(GL_TRIANGLE_FAN);
        glVertex2f(x, y+0.3f+i*0.05f);
        for (int j = 0; j <= 20; ++j) {
            float theta = 2.0f*3.1416f*float(j)/20.0f;
            glVertex2f(x+0.12f*cosf(theta), y+0.3f+i*0.05f+0.12f*sinf(theta));
        }
        glEnd();
    }
    glPopMatrix();
}

// ── Large animated upper-sky tree ─────────────────────────────────────────────
void drawBigTree(float x, float y, float trunkH, float trunkW, float canopyR, int numBlobs)
{
    glColor3ub(33, 23, 2);
    glBegin(GL_QUADS);
        glVertex2f(x-trunkW, y);
        glVertex2f(x+trunkW, y);
        glVertex2f(x+trunkW, y+trunkH);
        glVertex2f(x-trunkW, y+trunkH);
    glEnd();

    float pivotY = y + trunkH;
    glPushMatrix();
    glTranslatef(x, pivotY, 0);
    glRotatef(8*sinf(angle), 0, 0, 1);
    glTranslatef(-x, -pivotY, 0);

    // canopy darker at night
    if (isDay) glColor3ub(31,  92, 48);
    else        glColor3ub(10,  45, 20);

    float blobOffsets[][3] = {
        {  0.0f,  0.30f, 1.00f },
        { -0.50f,  0.50f, 0.92f },
        {  0.05f,  0.55f, 1.10f },
        {  0.50f,  0.20f, 0.75f },
        {  0.00f,  0.20f, 1.25f },
        { -0.25f, -0.05f, 0.60f },
        {  0.30f,  0.40f, 0.80f },
        {  0.30f,  0.30f, 0.85f },
    };
    int n = (numBlobs < 8) ? numBlobs : 8;
    for (int b = 0; b < n; ++b) {
        float bx = x + blobOffsets[b][0]*canopyR;
        float by = pivotY + blobOffsets[b][1]*canopyR;
        float br = blobOffsets[b][2]*canopyR;
        glBegin(GL_TRIANGLE_FAN);
        glVertex2f(bx, by);
        for (int j = 0; j <= 24; ++j) {
            float theta = 2.0f*3.1416f*float(j)/24.0f;
            glVertex2f(bx+br*cosf(theta), by+br*sinf(theta));
        }
        glEnd();
    }
    glPopMatrix();
}

// ── Moon + Stars (night only) ─────────────────────────────────────────────────
void drawMoonAndStars()
{
    // Moon (top-left area of sky)
    glColor3f(1.0f, 1.0f, 0.82f);
    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(1.5f, 7.5f);
    for (int i = 0; i <= 100; i++) {
        float a = 2.0f * 3.1416f * i / 100;
        glVertex2f(1.5f + 0.3f*cosf(a), 7.5f + 0.3f*sinf(a));
    }
    glEnd();

    // Stars
    glColor3f(1.0f, 1.0f, 1.0f);
    glPointSize(3.0f);
    glBegin(GL_POINTS);
    glVertex2f(3.0f, 7.7f);
    glVertex2f(4.5f, 7.3f);
    glVertex2f(5.8f, 7.8f);
    glVertex2f(6.5f, 7.1f);
    glVertex2f(2.5f, 6.8f);
    glVertex2f(7.2f, 7.5f);
    glVertex2f(8.0f, 6.9f);
    glVertex2f(0.8f, 7.2f);
    glEnd();
    glPointSize(1.0f);
}

// ── Rain: add one drop at a random x across the scene width ──────────────────
void addDrop()
{
    if (totalDrops < MAX_DROPS) {
        // scene x range is 0..9, y range is 0..8
        dropX[totalDrops] = static_cast<float>(rand()) / (RAND_MAX / 9.0f);
        dropY[totalDrops] = 8.0f;   // start at top of scene
        totalDrops++;
    }
}

// ── Rain: draw all drops ──────────────────────────────────────────────────────
void drawRaindrops()
{
    glColor3f(0.2f, 0.4f, 1.0f);
    glBegin(GL_LINES);
    for (int i = 0; i < totalDrops; i++) {
        glVertex2f(dropX[i], dropY[i]);
        glVertex2f(dropX[i], dropY[i] - 0.05f);
    }
    glEnd();
}

// ── Car: circle (from provided car code) ─────────────────────────────────────
void circle(float r, float g, float b, float radius, float xc, float yc)
{
    glBegin(GL_POINTS);
    for (int i = 0; i < 200; i++) {
        glColor3ub(r, g, b);
        float pi = 3.1416f;
        float A = (i * 2 * pi) / 200;
        float x = radius * cos(A);
        float y = radius * sin(A);
        glVertex2f(x + xc, y + yc);
    }
    glEnd();
}

// ── Car: box body (from provided car code) ────────────────────────────────────
void box(float r, float g, float b, float x1, float y1, float x2, float y2)
{
    glColor3ub(r, g, b);
    glBegin(GL_POLYGON);
    glVertex2f(x1,        y2);
    glVertex2f(x1,        y1);
    glVertex2f(x1 + x2,   y1);
    glVertex2f(x1 + x2,   y2);
    glEnd();
}

// ── Car: draw one full car at position (cx, cy) with given scale/direction ───
//   direction:  1 = facing right,  -1 = facing left
void drawCar(float cx, float cy, float s, float carAngle, int direction)
{
    float d = (float)direction;
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glTranslatef(cx, cy, 0);

    // -- main body (lower rectangle) ------------------------------------------
    glColor3ub(220, 30, 30);
    glBegin(GL_POLYGON);
        glVertex2f(d * 0.0f * s,  0.0f);
        glVertex2f(d * 0.7f * s,  0.0f);
        glVertex2f(d * 0.7f * s,  0.28f * s);
        glVertex2f(d * 0.0f * s,  0.28f * s);
    glEnd();

    // -- cabin roof (trapezoid on top of body) --------------------------------
    glColor3ub(180, 20, 20);
    glBegin(GL_POLYGON);
        glVertex2f(d * 0.12f * s,  0.28f * s);
        glVertex2f(d * 0.58f * s,  0.28f * s);
        glVertex2f(d * 0.50f * s,  0.48f * s);
        glVertex2f(d * 0.20f * s,  0.48f * s);
    glEnd();

    // -- windshield (front window) --------------------------------------------
    glColor3ub(180, 220, 255);
    glBegin(GL_POLYGON);
        glVertex2f(d * 0.50f * s,  0.29f * s);
        glVertex2f(d * 0.56f * s,  0.29f * s);
        glVertex2f(d * 0.49f * s,  0.46f * s);
        glVertex2f(d * 0.42f * s,  0.46f * s);
    glEnd();

    // -- rear window ----------------------------------------------------------
    glColor3ub(180, 220, 255);
    glBegin(GL_POLYGON);
        glVertex2f(d * 0.14f * s,  0.29f * s);
        glVertex2f(d * 0.20f * s,  0.29f * s);
        glVertex2f(d * 0.22f * s,  0.46f * s);
        glVertex2f(d * 0.15f * s,  0.46f * s);
    glEnd();

    // -- front bumper (small rectangle at front) ------------------------------
    glColor3ub(80, 80, 80);
    glBegin(GL_POLYGON);
        glVertex2f(d * 0.62f * s,  0.04f * s);
        glVertex2f(d * 0.72f * s,  0.04f * s);
        glVertex2f(d * 0.72f * s,  0.10f * s);
        glVertex2f(d * 0.62f * s,  0.10f * s);
    glEnd();

    // -- rear bumper ----------------------------------------------------------
    glColor3ub(80, 80, 80);
    glBegin(GL_POLYGON);
        glVertex2f(d * -0.02f * s,  0.04f * s);
        glVertex2f(d *  0.08f * s,  0.04f * s);
        glVertex2f(d *  0.08f * s,  0.10f * s);
        glVertex2f(d * -0.02f * s,  0.10f * s);
    glEnd();

    // -- headlight ------------------------------------------------------------
    glColor3ub(255, 255, 180);
    glBegin(GL_POLYGON);
        glVertex2f(d * 0.64f * s,  0.14f * s);
        glVertex2f(d * 0.70f * s,  0.14f * s);
        glVertex2f(d * 0.70f * s,  0.22f * s);
        glVertex2f(d * 0.64f * s,  0.22f * s);
    glEnd();

    // -- wheel 1 (rear) : dark tyre + rotating hub ----------------------------
    glPushMatrix();
    glTranslatef(d * 0.13f * s, 0.0f, 0);
    // tyre (dark filled circle)
    glColor3ub(30, 30, 30);
    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(0.0f, 0.0f);
    for (int j = 0; j <= 30; j++) {
        float a = 2.0f * 3.1416f * j / 30;
        glVertex2f(0.11f * s * cosf(a), 0.11f * s * sinf(a));
    }
    glEnd();
    // hub (white rotating spokes using LINES)
    glPushMatrix();
    glRotatef(carAngle * d, 0.0f, 0.0f, 1.0f);
    glColor3ub(200, 200, 200);
    glBegin(GL_LINES);
    for (int j = 0; j < 4; j++) {
        float a = 3.1416f * j / 4;
        glVertex2f( 0.09f * s * cosf(a),  0.09f * s * sinf(a));
        glVertex2f(-0.09f * s * cosf(a), -0.09f * s * sinf(a));
    }
    glEnd();
    glPopMatrix();
    glPopMatrix();

    // -- wheel 2 (front) : same -----------------------------------------------
    glPushMatrix();
    glTranslatef(d * 0.57f * s, 0.0f, 0);
    glColor3ub(30, 30, 30);
    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(0.0f, 0.0f);
    for (int j = 0; j <= 30; j++) {
        float a = 2.0f * 3.1416f * j / 30;
        glVertex2f(0.11f * s * cosf(a), 0.11f * s * sinf(a));
    }
    glEnd();
    glPushMatrix();
    glRotatef(carAngle * d, 0.0f, 0.0f, 1.0f);
    glColor3ub(200, 200, 200);
    glBegin(GL_LINES);
    for (int j = 0; j < 4; j++) {
        float a = 3.1416f * j / 4;
        glVertex2f( 0.09f * s * cosf(a),  0.09f * s * sinf(a));
        glVertex2f(-0.09f * s * cosf(a), -0.09f * s * sinf(a));
    }
    glEnd();
    glPopMatrix();
    glPopMatrix();

    glPopMatrix();
}

// ── Boat (from provided boat code, adapted to scene coords) ──────────────────
//   River sits in the lower grass strip  y ~ 2.2 to 3.0
//   boatX travels 0..9 in scene units
void drawBoat(float x)
{
    float y = 5.75f + sinf(x * 1.8f) * 0.04f;

    // hull
    glColor3f(0.50f, 0.15f, 0.07f);
    glBegin(GL_POLYGON);
        glVertex2f(x - 0.28f, y);
        glVertex2f(x + 0.30f, y);
        glVertex2f(x + 0.22f, y + 0.11f);
        glVertex2f(x - 0.20f, y + 0.11f);
    glEnd();

    // hull highlight stripe
    glColor3f(0.72f, 0.32f, 0.12f);
    glBegin(GL_QUADS);
        glVertex2f(x - 0.20f, y + 0.09f);
        glVertex2f(x + 0.22f, y + 0.09f);
        glVertex2f(x + 0.22f, y + 0.11f);
        glVertex2f(x - 0.20f, y + 0.11f);
    glEnd();

    // deck
    glColor3f(0.82f, 0.63f, 0.33f);
    glBegin(GL_QUADS);
        glVertex2f(x - 0.18f, y + 0.11f);
        glVertex2f(x + 0.20f, y + 0.11f);
        glVertex2f(x + 0.20f, y + 0.13f);
        glVertex2f(x - 0.18f, y + 0.13f);
    glEnd();

    // cabin body
    glColor3f(0.88f, 0.73f, 0.38f);
    glBegin(GL_QUADS);
        glVertex2f(x - 0.07f, y + 0.13f);
        glVertex2f(x + 0.10f, y + 0.13f);
        glVertex2f(x + 0.10f, y + 0.23f);
        glVertex2f(x - 0.07f, y + 0.23f);
    glEnd();

    // cabin roof
    glColor3f(0.58f, 0.12f, 0.09f);
    glBegin(GL_POLYGON);
        glVertex2f(x - 0.10f, y + 0.23f);
        glVertex2f(x + 0.13f, y + 0.23f);
        glVertex2f(x + 0.08f, y + 0.29f);
        glVertex2f(x - 0.05f, y + 0.29f);
    glEnd();

    // cabin window
    glColor3f(0.55f, 0.82f, 1.0f);
    glBegin(GL_QUADS);
        glVertex2f(x + 0.01f, y + 0.15f);
        glVertex2f(x + 0.08f, y + 0.15f);
        glVertex2f(x + 0.08f, y + 0.21f);
        glVertex2f(x + 0.01f, y + 0.21f);
    glEnd();

    // mast
    glColor3f(0.30f, 0.17f, 0.04f);
    glBegin(GL_QUADS);
        glVertex2f(x - 0.007f, y + 0.13f);
        glVertex2f(x + 0.007f, y + 0.13f);
        glVertex2f(x + 0.007f, y + 0.58f);
        glVertex2f(x - 0.007f, y + 0.58f);
    glEnd();

    // main sail (left)
    glColor3f(0.96f, 0.93f, 0.84f);
    glBegin(GL_TRIANGLES);
        glVertex2f(x,          y + 0.56f);
        glVertex2f(x,          y + 0.13f);
        glVertex2f(x - 0.24f,  y + 0.22f);
    glEnd();

    // fore sail (right)
    glColor3f(0.90f, 0.87f, 0.78f);
    glBegin(GL_TRIANGLES);
        glVertex2f(x,          y + 0.53f);
        glVertex2f(x,          y + 0.13f);
        glVertex2f(x + 0.19f,  y + 0.23f);
    glEnd();

    // flag
    glColor3f(0.88f, 0.10f, 0.10f);
    glBegin(GL_TRIANGLES);
        glVertex2f(x,          y + 0.58f);
        glVertex2f(x,          y + 0.50f);
        glVertex2f(x + 0.07f,  y + 0.54f);
    glEnd();
}

// ── Bird animation step ───────────────────────────────────────────────────────
void birdAnimation()
{
    birdX += 0.035f * birdDirection;
    birdWingY += 0.05f;
    if (birdWingY >  1.0f) birdWingY = -1.0f;
    if (birdX >  10.5f) birdDirection = -1.0f;
    if (birdX <  -1.5f) birdDirection =  1.0f;
}

// ── Master animation timer ────────────────────────────────────────────────────
void update(int value)
{
    angle += 0.08f;
    if (angle > 2*3.1416f) angle -= 2*3.1416f;
    birdAnimation();
    cloudAnimation();

    // Rain drop movement
    for (int i = 0; i < totalDrops; i++) {
        dropY[i] -= 0.03f;

        // remove drop once it falls off the bottom of the scene
        if (dropY[i] < 0.0f) {
            for (int j = i; j < totalDrops - 1; j++) {
                dropX[j] = dropX[j + 1];
                dropY[j] = dropY[j + 1];
            }
            totalDrops--;
            i--;
        }
    }

    // Add a few new drops each frame
    for (int i = 0; i < 5; i++) {
        addDrop();
    }

    // Car movement (from provided car code)
    angle1 += 2.0f;
    car1Move += 0.02f;
    if (car1Move > 10.0f) car1Move = -1.0f;
    car2Move -= 0.02f;
    if (car2Move < -1.0f) car2Move = 10.0f;

    // Boat movement (from provided boat code)
    boatX += 0.015f;
    if (boatX > 9.5f) boatX = -0.5f;

    glutPostRedisplay();
    glutTimerFunc(30, update, 0);
}

// ── Keyboard: D = Day, N = Night ──────────────────────────────────────────────
void keyboard(unsigned char key, int x, int y)
{
    if (key == 'd' || key == 'D') isDay = true;
    if (key == 'n' || key == 'N') isDay = false;
    if (key == 'r' || key == 'R') isRain = !isRain;
    glutPostRedisplay();
}

// ── Main display ──────────────────────────────────────────────────────────────
void display()
{
    glClear(GL_COLOR_BUFFER_BIT);

    // ── Road layer 1 (bottom) ─────────────────────────────────────────────────
    // road slightly darker at night
    if (isDay) glColor3ub(59, 60, 61);
    else        glColor3ub(30, 30, 32);
    glBegin(GL_QUADS);
        glVertex2f(0.0f,0.0f); glVertex2f(0.0f,2.0f);
        glVertex2f(9.0f,2.0f); glVertex2f(9.0f,0.0f);
    glEnd();

    glBegin(GL_QUADS); glColor3ub(250,251,252);
        glVertex2f(1.0f,1.0f); glVertex2f(2.0f,1.0f);
        glVertex2f(2.0f,0.9f); glVertex2f(1.0f,0.9f); glEnd();
    glBegin(GL_QUADS); glColor3ub(250,251,252);
        glVertex2f(3.0f,1.0f); glVertex2f(4.0f,1.0f);
        glVertex2f(4.0f,0.9f); glVertex2f(3.0f,0.9f); glEnd();
    glBegin(GL_QUADS); glColor3ub(250,251,252);
        glVertex2f(5.0f,1.0f); glVertex2f(6.0f,1.0f);
        glVertex2f(6.0f,0.9f); glVertex2f(5.0f,0.9f); glEnd();
    glBegin(GL_QUADS); glColor3ub(250,251,252);
        glVertex2f(7.0f,1.0f); glVertex2f(8.0f,1.0f);
        glVertex2f(8.0f,0.9f); glVertex2f(7.0f,0.9f); glEnd();

    // ── Kerb + grass strip ────────────────────────────────────────────────────
    glBegin(GL_QUADS); glColor3ub(162,165,168);
        glVertex2f(0.0f,2.0f); glVertex2f(0.0f,2.2f);
        glVertex2f(9.0f,2.2f); glVertex2f(9.0f,2.0f); glEnd();
    glBegin(GL_QUADS); glColor3ub(250,251,252);
        glVertex2f(1.0f,2.2f); glVertex2f(1.1f,2.2f);
        glVertex2f(1.1f,2.0f); glVertex2f(1.0f,2.0f); glEnd();
    glBegin(GL_QUADS); glColor3ub(250,251,252);
        glVertex2f(2.0f,2.2f); glVertex2f(2.1f,2.2f);
        glVertex2f(2.1f,2.0f); glVertex2f(2.0f,2.0f); glEnd();
    glBegin(GL_QUADS); glColor3ub(250,251,252);
        glVertex2f(3.0f,2.2f); glVertex2f(3.1f,2.2f);
        glVertex2f(3.1f,2.0f); glVertex2f(3.0f,2.0f); glEnd();
    glBegin(GL_QUADS); glColor3ub(250,251,252);
        glVertex2f(4.0f,2.2f); glVertex2f(4.1f,2.2f);
        glVertex2f(4.1f,2.0f); glVertex2f(4.0f,2.0f); glEnd();
    glBegin(GL_QUADS); glColor3ub(250,251,252);
        glVertex2f(5.0f,2.2f); glVertex2f(5.1f,2.2f);
        glVertex2f(5.1f,2.0f); glVertex2f(5.0f,2.0f); glEnd();
    glBegin(GL_QUADS); glColor3ub(250,251,252);
        glVertex2f(6.0f,2.2f); glVertex2f(6.1f,2.2f);
        glVertex2f(6.1f,2.0f); glVertex2f(6.0f,2.0f); glEnd();
    glBegin(GL_QUADS); glColor3ub(250,251,252);
        glVertex2f(7.0f,2.2f); glVertex2f(7.1f,2.2f);
        glVertex2f(7.1f,2.0f); glVertex2f(7.0f,2.0f); glEnd();
    glBegin(GL_QUADS); glColor3ub(250,251,252);
        glVertex2f(8.0f,2.2f); glVertex2f(8.1f,2.2f);
        glVertex2f(8.1f,2.0f); glVertex2f(8.0f,2.0f); glEnd();

    // lower grass  (darker at night)
    if (isDay) glColor3ub(20, 181, 33);
    else        glColor3ub( 5,  70, 10);
    glBegin(GL_QUADS);
        glVertex2f(0.0f,2.2f); glVertex2f(0.0f,3.0f);
        glVertex2f(9.3f,3.0f); glVertex2f(9.0f,2.2f);
    glEnd();

    // ── Road layer 2 (upper) ──────────────────────────────────────────────────
    if (isDay) glColor3ub(42, 42, 43);
    else        glColor3ub(18, 18, 20);
    glBegin(GL_QUADS);
        glVertex2f(0.0f,4.5f); glVertex2f(9.0f,4.5f);
        glVertex2f(9.0f,3.0f); glVertex2f(0.0f,3.0f);
    glEnd();

    glBegin(GL_QUADS); glColor3ub(175,175,179);
        glVertex2f(0.0f,4.5f); glVertex2f(0.0f,4.6f);
        glVertex2f(9.0f,4.6f); glVertex2f(9.0f,4.5f); glEnd();
    glBegin(GL_QUADS); glColor3ub(250,250,252);
        glVertex2f(1.0f,4.5f); glVertex2f(1.0f,4.6f);
        glVertex2f(1.1f,4.6f); glVertex2f(1.1f,4.5f); glEnd();
    glBegin(GL_QUADS); glColor3ub(250,250,252);
        glVertex2f(2.0f,4.5f); glVertex2f(2.0f,4.6f);
        glVertex2f(2.1f,4.6f); glVertex2f(2.1f,4.5f); glEnd();
    glBegin(GL_QUADS); glColor3ub(250,250,252);
        glVertex2f(3.0f,4.5f); glVertex2f(3.0f,4.6f);
        glVertex2f(3.1f,4.6f); glVertex2f(3.1f,4.5f); glEnd();
    glBegin(GL_QUADS); glColor3ub(250,250,252);
        glVertex2f(4.0f,4.5f); glVertex2f(4.0f,4.6f);
        glVertex2f(4.1f,4.6f); glVertex2f(4.1f,4.5f); glEnd();
    glBegin(GL_QUADS); glColor3ub(250,250,252);
        glVertex2f(5.0f,4.5f); glVertex2f(5.0f,4.6f);
        glVertex2f(5.1f,4.6f); glVertex2f(5.1f,4.5f); glEnd();
    glBegin(GL_QUADS); glColor3ub(250,250,252);
        glVertex2f(6.0f,4.5f); glVertex2f(6.0f,4.6f);
        glVertex2f(6.1f,4.6f); glVertex2f(6.1f,4.5f); glEnd();
    glBegin(GL_QUADS); glColor3ub(250,250,252);
        glVertex2f(7.0f,4.5f); glVertex2f(7.0f,4.6f);
        glVertex2f(7.1f,4.6f); glVertex2f(7.1f,4.5f); glEnd();
    glBegin(GL_QUADS); glColor3ub(250,250,252);
        glVertex2f(8.0f,4.5f); glVertex2f(8.0f,4.6f);
        glVertex2f(8.1f,4.6f); glVertex2f(8.1f,4.5f); glEnd();

    // centre lane markings
    glBegin(GL_QUADS); glColor3ub(250,250,252);
        glVertex2f(0.5f,3.6f); glVertex2f(0.5f,3.7f);
        glVertex2f(1.4f,3.7f); glVertex2f(1.4f,3.6f); glEnd();
    glBegin(GL_QUADS); glColor3ub(250,250,252);
        glVertex2f(2.5f,3.6f); glVertex2f(2.5f,3.7f);
        glVertex2f(3.5f,3.7f); glVertex2f(3.5f,3.6f); glEnd();
    glBegin(GL_QUADS); glColor3ub(250,250,252);
        glVertex2f(5.0f,3.6f); glVertex2f(5.0f,3.7f);
        glVertex2f(6.0f,3.7f); glVertex2f(6.0f,3.6f); glEnd();
    glBegin(GL_QUADS); glColor3ub(250,250,252);
        glVertex2f(7.0f,3.6f); glVertex2f(7.0f,3.7f);
        glVertex2f(8.0f,3.7f); glVertex2f(8.0f,3.6f); glEnd();

    // upper grass strip (darker at night)
    if (isDay) glColor3ub(38, 179, 25);
    else        glColor3ub( 8,  70,  8);
    glBegin(GL_QUADS);
        glVertex2f(0.0f,4.6f); glVertex2f(0.0f,5.2f);
        glVertex2f(9.0f,5.2f); glVertex2f(9.0f,4.6f);
    glEnd();

    // ── Sky bands ─────────────────────────────────────────────────────────────
    // lower sky band
    if (isDay) glColor3ub(40, 148, 250);   // day  = blue
    else        glColor3ub( 5,   5,  40);   // night = deep navy
    glBegin(GL_QUADS);
        glVertex2f(0.0f,5.2f); glVertex2f(0.0f,6.5f);
        glVertex2f(9.0f,6.5f); glVertex2f(9.0f,5.2f);
    glEnd();

    // upper sky band
    if (isDay) glColor3ub(247, 177,  96);   // day  = warm orange
    else        glColor3ub(  2,   2,  25);   // night = near black
    glBegin(GL_QUADS);
        glVertex2f(0.0f,6.5f); glVertex2f(0.0f,8.0f);
        glVertex2f(9.0f,8.0f); glVertex2f(9.0f,6.5f);
    glEnd();

    // ── Moon + stars (night only) | Sun (day only) ───────────────────────────
    if (!isDay)
        drawMoonAndStars();

    // ── Lamps ─────────────────────────────────────────────────────────────────
    glBegin(GL_QUADS); glColor3ub(250,180,17);
        glVertex2f(1.55f,2.2f); glVertex2f(1.55f,2.9f);
        glVertex2f(1.65f,2.9f); glVertex2f(1.65f,2.2f); glEnd();
    glBegin(GL_QUADS); glColor3ub(250,180,17);
        glVertex2f(4.4f,2.2f); glVertex2f(4.4f,3.2f);
        glVertex2f(4.6f,3.2f); glVertex2f(4.6f,2.2f); glEnd();
    glBegin(GL_QUADS); glColor3ub(250,180,17);
        glVertex2f(7.4f,2.2f); glVertex2f(7.4f,3.2f);
        glVertex2f(7.6f,3.2f); glVertex2f(7.6f,2.2f); glEnd();
    glBegin(GL_QUADS); glColor3ub(64,46,6);
        glVertex2f(1.575f,2.9f); glVertex2f(1.575f,3.725f);
        glVertex2f(1.625f,3.725f); glVertex2f(1.625f,2.9f); glEnd();
    glBegin(GL_QUADS); glColor3ub(64,46,6);
        glVertex2f(4.45f,3.2f); glVertex2f(4.45f,4.3f);
        glVertex2f(4.55f,4.3f); glVertex2f(4.55f,3.2f); glEnd();
    glBegin(GL_QUADS); glColor3ub(64,46,6);
        glVertex2f(7.45f,3.2f); glVertex2f(7.45f,4.3f);
        glVertex2f(7.55f,4.3f); glVertex2f(7.55f,3.2f); glEnd();
    // lamp arm triangles
    glBegin(GL_TRIANGLES); glColor3ub(64,46,6);
        glVertex2f(1.2f,4.1f); glVertex2f(1.2f,4.175f); glVertex2f(1.6f,3.725f); glEnd();
    glBegin(GL_TRIANGLES); glColor3ub(64,46,6);
        glVertex2f(2.0f,4.175f); glVertex2f(2.05f,4.175f); glVertex2f(1.6f,3.725f); glEnd();
    glBegin(GL_TRIANGLES); glColor3ub(64,46,6);
        glVertex2f(3.5f,4.8f); glVertex2f(3.5f,4.9f); glVertex2f(4.5f,4.3f); glEnd();
    glBegin(GL_TRIANGLES); glColor3ub(64,46,6);
        glVertex2f(5.5f,4.9f); glVertex2f(5.5f,4.8f); glVertex2f(4.5f,4.3f); glEnd();
    glBegin(GL_TRIANGLES); glColor3ub(64,46,6);
        glVertex2f(6.5f,4.9f); glVertex2f(6.5f,4.8f); glVertex2f(7.5f,4.3f); glEnd();
    glBegin(GL_TRIANGLES); glColor3ub(64,46,6);
        glVertex2f(8.5f,4.9f); glVertex2f(8.5f,4.8f); glVertex2f(7.5f,4.3f); glEnd();
    // upper lamp posts
    glBegin(GL_QUADS); glColor3ub(33,23,2);
        glVertex2f(0.9f,5.2f); glVertex2f(0.9f,6.1f);
        glVertex2f(1.0f,6.1f); glVertex2f(1.0f,5.2f); glEnd();
    glBegin(GL_QUADS); glColor3ub(33,23,2);
        glVertex2f(2.0f,5.2f); glVertex2f(2.0f,5.8f);
        glVertex2f(2.1f,5.8f); glVertex2f(2.1f,5.2f); glEnd();
    glBegin(GL_QUADS); glColor3ub(33,23,2);
        glVertex2f(6.1f,5.2f); glVertex2f(6.1f,5.8f);
        glVertex2f(6.2f,5.8f); glVertex2f(6.2f,5.2f); glEnd();
    glBegin(GL_QUADS); glColor3ub(33,23,2);
        glVertex2f(7.0f,5.2f); glVertex2f(7.0f,5.5f);
        glVertex2f(7.1f,5.5f); glVertex2f(7.1f,5.2f); glEnd();
    glBegin(GL_QUADS); glColor3ub(33,23,2);
        glVertex2f(7.7f,5.2f); glVertex2f(7.7f,5.5f);
        glVertex2f(7.8f,5.5f); glVertex2f(7.8f,5.2f); glEnd();
    // small pine triangles
    if (isDay) glColor3ub(47, 143, 23);
    else        glColor3ub(15,  60,  8);
    glBegin(GL_TRIANGLES);
        glVertex2f(6.8f,5.5f); glVertex2f(7.3f,5.5f); glVertex2f(7.05f,5.9f); glEnd();
    glBegin(GL_TRIANGLES);
        if (isDay) glColor3ub(47, 143, 23);
        else        glColor3ub(15,  60,  8);
        glVertex2f(7.6f,5.5f); glVertex2f(7.9f,5.5f); glVertex2f(7.7f,6.0f); glEnd();

    // ── Lamp head circles ─────────────────────────────────────────────────────
    // Day = white  |  Night = warm yellow glow
    int i;
    GLfloat p1=1.123f,q1=4.175f,r1=0.20f;    int tr2=100; GLfloat tp2=2.0f*PI;
    if (isDay) glColor3ub(252,252,252); else glColor3ub(255,220,80);
    glBegin(GL_TRIANGLE_FAN); glVertex2f(p1,q1);
    for(i=0;i<=tr2;i++) glVertex2f(p1+r1*cosf(i*tp2/tr2),q1+r1*sinf(i*tp2/tr2)); glEnd();

    GLfloat p2=2.0f,q2=4.175f,r2=0.2025f;    int tr3=100; GLfloat tp3=2.0f*PI;
    if (isDay) glColor3ub(252,252,252); else glColor3ub(255,220,80);
    glBegin(GL_TRIANGLE_FAN); glVertex2f(p2,q2);
    for(i=0;i<=tr3;i++) glVertex2f(p2+r2*cosf(i*tp3/tr3),q2+r2*sinf(i*tp3/tr3)); glEnd();

    GLfloat p3=3.4f,q3=4.95f,r3=0.27f;       int tr4=100; GLfloat tp4=2.0f*PI;
    if (isDay) glColor3ub(252,252,252); else glColor3ub(255,220,80);
    glBegin(GL_TRIANGLE_FAN); glVertex2f(p3,q3);
    for(i=0;i<=tr4;i++) glVertex2f(p3+r3*cosf(i*tp4/tr4),q3+r3*sinf(i*tp4/tr4)); glEnd();

    GLfloat p4=5.5f,q4=5.0f,r4=0.27f;        int tr5=100; GLfloat tp5=2.0f*PI;
    if (isDay) glColor3ub(252,252,252); else glColor3ub(255,220,80);
    glBegin(GL_TRIANGLE_FAN); glVertex2f(p4,q4);
    for(i=0;i<=tr5;i++) glVertex2f(p4+r4*cosf(i*tp5/tr5),q4+r4*sinf(i*tp5/tr5)); glEnd();

    GLfloat p5=6.45f,q5=4.95f,r5=0.27f;      int tr6=100; GLfloat tp6=2.0f*PI;
    if (isDay) glColor3ub(252,252,252); else glColor3ub(255,220,80);
    glBegin(GL_TRIANGLE_FAN); glVertex2f(p5,q5);
    for(i=0;i<=tr6;i++) glVertex2f(p5+r5*cosf(i*tp6/tr6),q5+r5*sinf(i*tp6/tr6)); glEnd();

    GLfloat p6=8.6f,q6=5.0f,r6=0.27f;        int tr7=100; GLfloat tp7=2.0f*PI;
    if (isDay) glColor3ub(252,252,252); else glColor3ub(255,220,80);
    glBegin(GL_TRIANGLE_FAN); glVertex2f(p6,q6);
    for(i=0;i<=tr7;i++) glVertex2f(p6+r6*cosf(i*tp7/tr7),q6+r6*sinf(i*tp7/tr7)); glEnd();

    // ── 4 small animated roadside trees ──────────────────────────────────────
    drawTree(0.55f, 2.2f);
    drawTree(2.95f, 2.2f);
    drawTree(5.95f, 2.2f);
    drawTree(8.45f, 2.2f);

    drawBoat(boatX);

    // ── Original static upper-sky circle clusters (preserved) ─────────────────
    GLfloat p7=0.6f,q7=6.0f,r7=0.3f;    int tr8=100;  GLfloat tp8=2.0f*PI;
    glBegin(GL_TRIANGLE_FAN); glColor3ub(31,92,48); glVertex2f(p7,q7);
    for(i=0;i<=tr8;i++)  glVertex2f(p7+r7*cosf(i*tp8/tr8),q7+r7*sinf(i*tp8/tr8));  glEnd();

    GLfloat p8=0.5f,q8=6.5f,r8=0.35f;   int tr9=100;  GLfloat tp9=2.0f*PI;
    glBegin(GL_TRIANGLE_FAN); glColor3ub(31,92,48); glVertex2f(p8,q8);
    for(i=0;i<=tr9;i++)  glVertex2f(p8+r8*cosf(i*tp9/tr9),q8+r8*sinf(i*tp9/tr9));  glEnd();

    GLfloat p9=1.05f,q9=6.55f,r9=0.38f; int tr10=100; GLfloat tp10=2.0f*PI;
    glBegin(GL_TRIANGLE_FAN); glColor3ub(31,92,48); glVertex2f(p9,q9);
    for(i=0;i<=tr10;i++) glVertex2f(p9+r9*cosf(i*tp10/tr10),q9+r9*sinf(i*tp10/tr10)); glEnd();

    GLfloat p10=1.5f,q10=6.2f,r10=0.26f; int tr11=100; GLfloat tp11=2.0f*PI;
    glBegin(GL_TRIANGLE_FAN); glColor3ub(31,92,48); glVertex2f(p10,q10);
    for(i=0;i<=tr11;i++) glVertex2f(p10+r10*cosf(i*tp11/tr11),q10+r10*sinf(i*tp11/tr11)); glEnd();

    GLfloat p11=1.0f,q11=6.2f,r11=0.43f; int tr12=100; GLfloat tp12=2.0f*PI;
    glBegin(GL_TRIANGLE_FAN); glColor3ub(31,92,48); glVertex2f(p11,q11);
    for(i=0;i<=tr12;i++) glVertex2f(p11+r11*cosf(i*tp12/tr12),q11+r11*sinf(i*tp12/tr12)); glEnd();

    GLfloat p12=1.8f,q12=5.75f,r12=0.2f; int tr13=100; GLfloat tp13=2.0f*PI;
    glBegin(GL_TRIANGLE_FAN); glColor3ub(31,92,48); glVertex2f(p12,q12);
    for(i=0;i<=tr13;i++) glVertex2f(p12+r12*cosf(i*tp13/tr13),q12+r12*sinf(i*tp13/tr13)); glEnd();

    GLfloat p13=2.1f,q13=5.9f,r13=0.32f; int tr14=100; GLfloat tp14=2.0f*PI;
    glBegin(GL_TRIANGLE_FAN); glColor3ub(31,92,48); glVertex2f(p13,q13);
    for(i=0;i<=tr14;i++) glVertex2f(p13+r13*cosf(i*tp14/tr14),q13+r13*sinf(i*tp14/tr14)); glEnd();

    GLfloat p14=2.3f,q14=5.8f,r14=0.28f; int tr15=100; GLfloat tp15=2.0f*PI;
    glBegin(GL_TRIANGLE_FAN); glColor3ub(31,92,48); glVertex2f(p14,q14);
    for(i=0;i<=tr15;i++) glVertex2f(p14+r14*cosf(i*tp15/tr15),q14+r14*sinf(i*tp15/tr15)); glEnd();

    GLfloat p15=6.0f,q15=5.8f,r15=0.29f; int tr16=100; GLfloat tp16=2.0f*PI;
    glBegin(GL_TRIANGLE_FAN); glColor3ub(31,92,48); glVertex2f(p15,q15);
    for(i=0;i<=tr16;i++) glVertex2f(p15+r15*cosf(i*tp16/tr16),q15+r15*sinf(i*tp16/tr16)); glEnd();

    GLfloat p16=6.2f,q16=6.0f,r16=0.32f; int tr17=100; GLfloat tp17=2.0f*PI;
    glBegin(GL_TRIANGLE_FAN); glColor3ub(31,92,48); glVertex2f(p16,q16);
    for(i=0;i<=tr17;i++) glVertex2f(p16+r16*cosf(i*tp17/tr17),q16+r16*sinf(i*tp17/tr17)); glEnd();

    GLfloat p17=6.4f,q17=5.8f,r17=0.25f; int tr18=100; GLfloat tp18=2.0f*PI;
    glBegin(GL_TRIANGLE_FAN); glColor3ub(31,92,48); glVertex2f(p17,q17);
    for(i=0;i<=tr18;i++) glVertex2f(p17+r17*cosf(i*tp18/tr18),q17+r17*sinf(i*tp18/tr18)); glEnd();

    // ── 2 animated big trees over static clusters ─────────────────────────────
    drawBigTree(1.0f, 5.2f, 0.85f, 0.055f, 0.43f, 8);
    drawBigTree(6.2f, 5.2f, 0.60f, 0.05f,  0.32f, 5);

    // ── Red sun (day only) ────────────────────────────────────────────────────
    if (isDay)
    {
        GLfloat p18=8.3f,q18=7.4f,r18=0.365f; int tr19=100; GLfloat tp19=2.0f*PI;
        glBegin(GL_TRIANGLE_FAN); glColor3ub(240,58,55); glVertex2f(p18,q18);
        for(i=0;i<=tr19;i++) glVertex2f(p18+r18*cosf(i*tp19/tr19),q18+r18*sinf(i*tp19/tr19));
        glEnd();
    }

    // ── 3 moving clouds ───────────────────────────────────────────────────────
    drawCloud(cloud1X, cloud1Y, 0.55f);
    drawCloud(cloud2X, cloud2Y, 0.42f);
    drawCloud(cloud3X, cloud3Y, 0.35f);

    // ── Cars ──────────────────────────────────────────────────────────────────
    // bottom road (y ~0.2 to 2.0): car moves left to right
    drawCar(car1Move, 0.35f, 1.0f, angle1,  1);
    // upper road  (y ~3.0 to 4.5): car moves right to left
    drawCar(car2Move, 3.55f, 1.0f, angle1, -1);

    // ── Boat (from provided boat code, on the grass strip between roads) ──────


    // ── Rain (drawn last, in front of everything) ─────────────────────────────
    if (isRain)
        drawRaindrops();

    // ── Flapping birds ────────────────────────────────────────────────────────
    bird(birdX,        birdY,        birdDirection,  birdWingY,  30,30,30, 0.008f);
    bird(birdX-0.25f,  birdY+0.18f,  birdDirection, -birdWingY,  30,30,30, 0.006f);
    bird(birdX-0.45f,  birdY+0.32f,  birdDirection,  birdWingY,  30,30,30, 0.005f);
    bird(birdX-0.60f,  birdY+0.44f,  birdDirection,  birdWingY,  30,30,30, 0.004f);
    bird(birdX-0.75f,  birdY+0.54f,  birdDirection,  birdWingY,  30,30,30, 0.003f);

    glutSwapBuffers();
}

int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(900, 800);
    glutCreateWindow("Road Scene  [D = Day | N = Night]");

    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
    gluOrtho2D(0, 9, 0, 8);

    glutDisplayFunc(display);
    glutKeyboardFunc(keyboard);
    glutTimerFunc(0, update, 0);
    glutMainLoop();
    return 0;
}
