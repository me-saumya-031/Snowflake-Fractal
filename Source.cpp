#include <GL/glut.h>
#include <cmath>
#include <vector>

int depth = 0; 
float scale = 0.1f; 
float growthSpeed = 0.01f; 

// Function to draw a Koch curve
void kochCurve(float x1, float y1, float x2, float y2, int depth) {
    if (depth == 0) {
        glVertex2f(x1, y1);
        glVertex2f(x2, y2);
    }
    else {
        float x3 = (2 * x1 + x2) / 3;
        float y3 = (2 * y1 + y2) / 3;
        float x4 = (x1 + 2 * x2) / 3;
        float y4 = (y1 + 2 * y2) / 3;

        float x5 = (x1 + x2) / 2 + (sqrt(3) / 6) * (y2 - y1);
        float y5 = (y1 + y2) / 2 + (sqrt(3) / 6) * (x1 - x2);

        kochCurve(x1, y1, x3, y3, depth - 1);
        kochCurve(x3, y3, x5, y5, depth - 1);
        kochCurve(x5, y5, x4, y4, depth - 1);
        kochCurve(x4, y4, x2, y2, depth - 1);
    }
}

void drawSnowflake(int depth) {
    glBegin(GL_LINES);
    kochCurve(-0.5f, -0.288675f, 0.5f, -0.288675f, depth); // Bottom edge
    kochCurve(0.5f, -0.288675f, 0.0f, 0.57735f, depth); // Right edge
    kochCurve(0.0f, 0.57735f, -0.5f, -0.288675f, depth); // Left edge
    glEnd();
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    glLoadIdentity();
    glScalef(scale, scale, 1.0f); 

    drawSnowflake(depth);

    glutSwapBuffers();
}

void update(int value) {
    scale += growthSpeed;
    if (scale > 1.0f) {
        scale = 0.1f; 
        depth++;
        if (depth > 5) {
            depth = 0; 
        }
    }

    glutPostRedisplay();

    glutTimerFunc(16, update, 0);
}

void init() {
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f); // Black background
    glColor3f(1.0f, 1.0f, 1.0f); // White snowflake
    glLineWidth(2.0f); // Set line width
    glOrtho(-1.0f, 1.0f, -1.0f, 1.0f, -1.0f, 1.0f); // Set orthographic projection
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(500, 500);
    glutCreateWindow("Animated Koch Snowflake");

    init();

    glutDisplayFunc(display);
    glutTimerFunc(0, update, 0); // Start the update loop
    glutMainLoop();

    return 0;
}