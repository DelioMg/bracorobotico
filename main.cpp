//Delio de Macedo Gonçalves

#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/freeglut.h>
#include <cmath>
#include <stdio.h>

// Definição das estruturas para segmentos do braço e garra
struct SegmentoRobo {
    float comprimento, largura, altura; 
    float anguloZ; 
    float cor[3]; 
};

struct Garra {
    float abertura; 
    float comprimento, largura; 
    float cor[3]; 
};

// Variáveis globais
float tx = 0; // Posição horizontal da base
float cameraAnguloY = 0.0f; // Ângulo da câmera
float cameraAltura = 10.0f; // Altura da câmera
float cameraDistancia = 30.0f; // Distância da câmera
int mouseXAnterior = 0; 
int mouseYAnterior = 0;
bool arrastando = false;
float rotacaoVertical = 0; // Rotação vertical do braço
float corbraco[3] = {0.0f, 1.0f, 0.0f}; // Cor padrão para os braços e garra

// Definição dos segmentos e da garra
SegmentoRobo braco1 = {4.0, 0.8, 0.5, -45, {0, 1, 0}};
SegmentoRobo braco2 = {3.0, 0.8, 0.5, 45, {0, 1, 0}};
SegmentoRobo braco3 = {2.5, 0.8, 0.5, -30, {0, 1, 0}};
Garra garra = {9.5, 1.2, 0.2, {0, 1, 0}};

// Função para desenhar cada segmento do braço
void DesenhaSegmento(SegmentoRobo seg) {
    glColor3fv(corbraco);
    glPushMatrix();
        glTranslatef(0, seg.comprimento / 2.0f, 0); 
        glScalef(seg.largura, seg.comprimento, seg.altura); 
        glutSolidCube(1); 
    glPopMatrix();
}

// Função para desenhar a garra
void DesenhaGarra(Garra g) {
    glColor3fv(corbraco);

    // Desenha a garra à esquerda
    glPushMatrix();
        glTranslatef(-g.largura * 1.5f, 0, 0);
        glRotatef(-g.abertura, 0, 0, 1);
        glTranslatef(0, g.comprimento / 2, 0);
        glScalef(g.largura, g.comprimento, 0.2);
        glutSolidCube(1);
    glPopMatrix();

    // Desenha a garra à direita
    glPushMatrix();
        glTranslatef(g.largura * 1.5f, 0, 0);
        glRotatef(g.abertura, 0, 0, 1);
        glTranslatef(0, g.comprimento / 2, 0);
        glScalef(g.largura, g.comprimento, 0.2);
        glutSolidCube(1);
    glPopMatrix();
}

// Função para desenhar o braço completo
void DesenhaBraco() {
    glTranslatef(0, 0.5, 0); 
    glRotatef(rotacaoVertical, 1, 0, 0); 

    // Articulação entre Base e 1
    glPushMatrix();
        glColor3fv(corbraco);
        GLUquadric* joint0 = gluNewQuadric();
        glTranslatef(0, 0, -0.3);
        gluCylinder(joint0, 0.5, 0.5, 0.6, 16, 2); 
        gluDisk(joint0, 0, 0.5, 16, 1); 
        glTranslatef(0, 0, 0.6); 
        gluDisk(joint0, 0, 0.5, 16, 1); 
        gluDeleteQuadric(joint0);
    glPopMatrix();

    // Segmento 1
    glRotatef(braco1.anguloZ, 0, 0, 1);
    DesenhaSegmento(braco1);
    glTranslatef(0, braco1.comprimento, 0);

    // Articulação entre 1 e 2
    glPushMatrix();
        glColor3fv(corbraco);
        GLUquadric* joint1 = gluNewQuadric();
        glTranslatef(0, 0, -0.3);
        gluCylinder(joint1, 0.5, 0.5, 0.6, 16, 2); 
        gluDisk(joint1, 0, 0.5, 16, 1); 
        glTranslatef(0, 0, 0.6); 
        gluDisk(joint1, 0, 0.5, 16, 1); 
        gluDeleteQuadric(joint1);
    glPopMatrix();

    // Segmento 2
    glRotatef(braco2.anguloZ, 0, 0, 1);
    DesenhaSegmento(braco2);
    glTranslatef(0, braco2.comprimento, 0);

    // Articulação entre 2 e 3
    glPushMatrix();
        glColor3fv(corbraco);
        GLUquadric* joint2 = gluNewQuadric();
        glTranslatef(0, 0, -0.3);
        gluCylinder(joint2, 0.5, 0.5, 0.6, 16, 2); 
        gluDisk(joint2, 0, 0.5, 16, 1); 
        glTranslatef(0, 0, 0.6); 
        gluDisk(joint2, 0, 0.5, 16, 1); 
        gluDeleteQuadric(joint2);
    glPopMatrix();

    // Segmento 3
    glRotatef(braco3.anguloZ, 0, 0, 1);
    DesenhaSegmento(braco3);
    glTranslatef(0, braco3.comprimento, 0);

    // Articulação entre 3 e garra
    glPushMatrix();
        glColor3fv(corbraco);
        GLUquadric* joint3 = gluNewQuadric();
        glTranslatef(0, 0, -0.3);
        gluCylinder(joint3, 0.5, 0.5, 0.6, 16, 2); 
        gluDisk(joint3, 0, 0.5, 16, 1); 
        glTranslatef(0, 0, 0.6); 
        gluDisk(joint3, 0, 0.5, 16, 1); 
        gluDeleteQuadric(joint3);
    glPopMatrix();

    // Desenha a garra
    glTranslatef(0, 0.3, 0); 
    DesenhaGarra(garra); 
}


// Função para desenhar o texto da HUD (informações de controle)
void DesenhaTexto(float x, float y, const char* texto) {
    glRasterPos2f(x, y);
    while (*texto) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, *texto++);
    }
}

// Função para desenhar a HUD
void DesenhaHUD() {
    glDisable(GL_LIGHTING);
    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();
    gluOrtho2D(0, 100, 0, 100); 
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glLoadIdentity();

    // Desenha os controles na tela
    glColor3f(1, 1, 1);
    DesenhaTexto(2, 95, "Controles:");
    DesenhaTexto(2, 90, "A/Z - Rotacao Braco 1");
    DesenhaTexto(2, 85, "S/X - Rotacao Braco 2");
    DesenhaTexto(2, 80, "D/C - Rotacao Braco 3");
    DesenhaTexto(2, 75, "Q/W - Abrir/Fechar Garra");
    DesenhaTexto(2, 70, "Setas Cima/Baixo - Rotacao Braco");
    DesenhaTexto(2, 65, "Setas Esquerda/Direita - Mover base");
    DesenhaTexto(2, 60, "Mouse : Esquerdo - Rotacionar | Direito - Reset");
    DesenhaTexto(2, 55, "Mouse : Scroll - Zoom");

    glPopMatrix();
    glMatrixMode(GL_PROJECTION);
    glPopMatrix();
    glMatrixMode(GL_MODELVIEW);
    glEnable(GL_LIGHTING);
}

// Função para desenhar a cena (base, chão e braço)
void Desenha(void) {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); 
    glLoadIdentity();

    // Define a posição da câmera
    float rad = cameraAnguloY * 3.1415926f / 180.0f;
    float camX = cameraDistancia * sin(rad);
    float camZ = cameraDistancia * cos(rad);
    gluLookAt(camX, cameraAltura, camZ, 0, 10, 0, 0, 1, 0);

    // Desenha o chão
    glPushMatrix();
        glColor3f(0.01, 0.01, 0.01); 
        glTranslatef(0, -0.01f, 0);
        glScalef(50, 0.01f, 50); // Ajusta o tamanho do chão
        glutSolidCube(1); 
    glPopMatrix();

    // Base + braço
    glPushMatrix();
        glTranslatef(tx, 0, 0);

        // Desenha a base (cilindro)
        glPushMatrix();
            glColor3fv(corbraco);
            GLUquadric* quad = gluNewQuadric();
            glRotatef(-90, 1, 0, 0);
            gluCylinder(quad, 2.5, 2.5, 1, 32, 1);
            gluDisk(quad, 0, 2.5, 32, 1);
            glTranslatef(0, 0, 1);
            gluDisk(quad, 0, 2.5, 32, 1);
            gluDeleteQuadric(quad);
        glPopMatrix();

        // Desenha o braço sobre a base
        glPushMatrix();
            glTranslatef(0, 0.5, 0);
            DesenhaBraco();
        glPopMatrix();

    glPopMatrix();

    DesenhaHUD(); // Desenha a HUD
    glutSwapBuffers(); // Troca os buffers para exibir a cena
}

// Função para ajustar o tamanho da janela
void AlteraTamanhoJanela(int w, int h) {
    if (h == 0) h = 1;
    float aspecto = (float)w / h;
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45, aspecto, 1.0, 100.0);
    glMatrixMode(GL_MODELVIEW);
}

// Função para responder a teclas do teclado
void Teclado(unsigned char key, int x, int y) {
    switch (key) {
        case 'a': if (braco1.anguloZ < 40) braco1.anguloZ += 5; break;
        case 'z': if (braco1.anguloZ > -40) braco1.anguloZ -= 5; break;
        case 's': if (braco2.anguloZ < 80) braco2.anguloZ += 5; break;
        case 'x': if (braco2.anguloZ > -80) braco2.anguloZ -= 5; break;
        case 'd': if (braco3.anguloZ < 80) braco3.anguloZ += 5; break;
        case 'c': if (braco3.anguloZ > -80) braco3.anguloZ -= 5; break;
        case 'q': if (garra.abertura < 8) garra.abertura += 2; break;
        case 'w': if (garra.abertura > -20) garra.abertura -= 2; break;
        case 27: exit(0); break;
    }
    glutPostRedisplay();
}

// Função para responder a teclas especiais (setas)
void TeclasEspeciais(int key, int x, int y) {
    switch (key) {
        case GLUT_KEY_LEFT:  if (tx > -20) tx -= 1; break;
        case GLUT_KEY_RIGHT: if (tx < 20)  tx += 1; break;
        case GLUT_KEY_UP:
             if (braco1.anguloZ > -30) braco1.anguloZ -= 10;
             if (braco2.anguloZ > -60) braco2.anguloZ -= 10;
             if (braco3.anguloZ > -60) braco3.anguloZ -= 10;
             break;
        case GLUT_KEY_DOWN:
             if (braco1.anguloZ < 30) braco1.anguloZ += 10;
             if (braco2.anguloZ < 60) braco2.anguloZ += 10;
             if (braco3.anguloZ < 60) braco3.anguloZ += 10;
             break;

    }
    glutPostRedisplay();
}

// Funções do mouse para controle da câmera
void Mouse(int button, int state, int x, int y) {
    if (button == GLUT_LEFT_BUTTON) {
        if (state == GLUT_DOWN) {
            arrastando = true;
            mouseXAnterior = x;
            mouseYAnterior = y;
        } else {
            arrastando = false;
        }
    } else if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN) {
        // Reset da câmera
        cameraAnguloY = 0;
        cameraAltura = 10;
        cameraDistancia = 30;
        glutPostRedisplay();
    }

    if (button == 3) { // Scroll para cima
        cameraDistancia -= 1.0f;
        if (cameraDistancia < 5.0f) cameraDistancia = 5.0f;
        glutPostRedisplay();
    } else if (button == 4) { // Scroll para baixo
        cameraDistancia += 1.0f;
        glutPostRedisplay();
    }
}

void MovimentoMouse(int x, int y) {
    if (arrastando) {
        int dx = x - mouseXAnterior;
        int dy = y - mouseYAnterior;

        cameraAnguloY += dx * 0.5f;
        cameraAltura += dy * 0.1f;

        if (cameraAltura < 2.0f) cameraAltura = 2.0f;
        if (cameraAltura > 50.0f) cameraAltura = 50.0f;

        mouseXAnterior = x;
        mouseYAnterior = y;

        glutPostRedisplay();
    }
}

// Inicialização das configurações do OpenGL
void Inicializa() {
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_COLOR_MATERIAL);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);

    GLfloat luzPosicional[] = {0.0f, 50.0f, 50.0f, 1.0f};
    glLightfv(GL_LIGHT0, GL_POSITION, luzPosicional);

    glClearColor(0.0f, 0.0f, 0.0f, 1.0f); 
}

// Função principal
int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(1366, 768);
    glutCreateWindow("Braco Robotico");

    Inicializa();

    glutDisplayFunc(Desenha);
    glutReshapeFunc(AlteraTamanhoJanela);
    glutKeyboardFunc(Teclado);
    glutSpecialFunc(TeclasEspeciais);
    glutMouseFunc(Mouse);
    glutMotionFunc(MovimentoMouse);

    glutMainLoop();
    return 0;
}
