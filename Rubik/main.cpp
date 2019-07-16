#include <GL/gl.h>
#include <GL/glut.h>
#include <vector>

using namespace std;

struct cube_rotate
{
    GLfloat angle, x, y, z;
};

// Variabel Float
GLfloat angle, fAspect, cube_size;

// Variabel Int
GLint rot_x, rot_y, crement, x_0, x_k, y_0, y_k, z_0, z_k, gap, gap_crement;

//cube_rotate cube_rotations[3][3][3];
vector<cube_rotate> cube_rotations[3][3][3];

void load_visualization_parameters(void);

// Untuk menjalankan rotasi
void apply_rotation(GLfloat angle)
{
    vector<cube_rotate> face[4][3];
    int index;
    cube_rotate rotation;

    // Menyalin muka yang akan diputar
    // Menerapkan rotasi ke muka
    for(int i = 0; i < 3; ++i)
        for(int j = 0; j < 3; ++j)
        {

            index = 2 - j%3;

            if(x_0 == x_k)
            {
                rotation = {angle, 1.0, 0.0, 0.0};
                face[index][i] = cube_rotations[x_k][i][j];
            }

            if(y_0 == y_k)
            {
                rotation = {angle, 0.0, 1.0, 0.0};
                face[index][i] = cube_rotations[j][y_k][i];
            }

            if(z_0 == z_k)
            {
                rotation = {-1 * angle, 0.0, 0.0, 1.0};
                face[index][i] = cube_rotations[j][i][z_k];
            }

            face[index][i].push_back(rotation);

        }

    // Menyalin kembali muka yang diputar
    for(int i = 0; i < 3; ++i)
        for(int j = 0; j < 3; ++j)
        {

            if(x_0 == x_k)
                cube_rotations[x_k][i][j] = face[i][j];

            if(y_0 == y_k)
                cube_rotations[j][y_k][i] = face[i][j];

            if(z_0 == z_k)
                cube_rotations[j][i][z_k] = face[i][j];
        }

}

// Mengatur ulang parameter pemilihan muka
void reset_selected_face()
{

    x_0 = 0;
    x_k = 2;
    y_0 = 0;
    y_k = 2;
    z_0 = 0;
    z_k = 2;

}

void set_camera()
{
    // titik awal
    // Muka/Tengah/Atas
    //gluLookAt(0,80,200, 0,0,0, 0,1,0);
    gluLookAt(200,200,200, 0,0,0, 0,1,0);
}

// Membuat polygon
void draw_cube(int x, int y, int z)
{
    vector<cube_rotate> lrot = cube_rotations[x][y][z];
    glPushMatrix();

    // Menetapkan posisi akhir
    glTranslatef((x - 1) * cube_size + x * gap, (y - 1) * cube_size + y * gap, (z - 1) * cube_size + z * gap);

    // Memutar kubus untuk memperbaiki posisi
    for(int i = lrot.size() - 1; i >= 0; --i)
        glRotatef(lrot[i].angle, lrot[i].x, lrot[i].y, lrot[i].z);

    glColor3f(1.0f, 0.0f, 0.0f); // memberi warna di titik polygon
    glBegin(GL_QUADS);  // depan
    glNormal3f(0.0, 0.0, 1.0);  // face normal
    glVertex3f(cube_size/2, cube_size/2, cube_size/2); // atas kiri
    glVertex3f(-cube_size/2, cube_size/2, cube_size/2); // atas kanan
    glVertex3f(-cube_size/2, -cube_size/2, cube_size/2); // bawah kanan
    glVertex3f(cube_size/2, -cube_size/2, cube_size/2); // bawah kiri
    glEnd();

    glColor3f(1.0f, 0.5f, 0.0f); // memberi warna di titik polygon
    glBegin(GL_QUADS);  // belakang
    glNormal3f(0.0, 0.0, -1.0);  // face normal
    glVertex3f(cube_size/2, cube_size/2, -cube_size/2); // atas kiri
    glVertex3f(cube_size/2, -cube_size/2, -cube_size/2); // atas kanan
    glVertex3f(-cube_size/2, -cube_size/2, -cube_size/2); // bawah kanan
    glVertex3f(-cube_size/2, cube_size/2, -cube_size/2); // bawah kiri
    glEnd();

    glColor3f(0.0f, 0.0f, 1.0f); // memberi warna di titik polygon
    glBegin(GL_QUADS);  // kiri
    glNormal3f(-1.0, 0.0, 0.0);  // face normal
    glVertex3f(-cube_size/2, cube_size/2, cube_size/2); // atas kiri
    glVertex3f(-cube_size/2, cube_size/2, -cube_size/2); // atas kanan
    glVertex3f(-cube_size/2, -cube_size/2, -cube_size/2); // bawah kanan
    glVertex3f(-cube_size/2, -cube_size/2, cube_size/2); // bawah kiri
    glEnd();

    glColor3f(0.0f, 1.0f, 0.0f); // memberi warna di titik polygon
    glBegin(GL_QUADS);  // kanan
    glNormal3f(1.0, 0.0, 0.0);  // face normal
    glVertex3f(cube_size/2, cube_size/2, cube_size/2); // atas kiri
    glVertex3f(cube_size/2, -cube_size/2, cube_size/2); // atas kanan
    glVertex3f(cube_size/2, -cube_size/2, -cube_size/2); // bawah kanan
    glVertex3f(cube_size/2, cube_size/2, -cube_size/2); // bawah kiri
    glEnd();

    glColor3f(1.0f, 1.0f, 1.0f); // memberi warna di titik polygon
    glBegin(GL_QUADS);  // atas
    glNormal3f(0.0, 1.0, 0.0);  // face normal
    glVertex3f(-cube_size/2, cube_size/2, -cube_size/2); // atas kiri
    glVertex3f(-cube_size/2, cube_size/2, cube_size/2); // atas kanan
    glVertex3f(cube_size/2, cube_size/2, cube_size/2); // bawah kanan
    glVertex3f(cube_size/2, cube_size/2, -cube_size/2); // bawah kiri
    glEnd();

    glColor3f(1.0f, 1.0f, 0.0f); // memberi warna di titik polygon
    glBegin(GL_QUADS);  // bawah
    glNormal3f(0.0, -1.0, 0.0);  // face normal
    glVertex3f(-cube_size/2, -cube_size/2, -cube_size/2); // atas kiri
    glVertex3f(cube_size/2, -cube_size/2, -cube_size/2); // atas kanan
    glVertex3f(cube_size/2, -cube_size/2, cube_size/2); // bawah kanan
    glVertex3f(-cube_size/2, -cube_size/2, cube_size/2); // bawah kiri
    glEnd();

    glPopMatrix();

}

void display(void)
{

    int x = -cube_size, y = -cube_size, z = -cube_size;

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Mengatur ulang transformasi
    glLoadIdentity();

    // Mengatur posisi kamera
    set_camera();

    // Menerapkan transformasi visual
    glRotatef(rot_x, 1.0, 0.0, 0.0); // memutar polygon angle Y
    glRotatef(rot_y, 0.0, 1.0, 0.0); // memutar polygon angle X

    for(int i = 0; i < 3; ++i) // Melalui sumbu x
        for(int j = 0; j < 3; ++j) // Melalui sumbu y
            for(int k = 0; k < 3; ++k)   // Melalui sumbu z
            {
                // Membuat kubus tunggal
                draw_cube(i, j, k);
            }
    glutSwapBuffers(); // Untuk menukar layar belakang menjadi layar depan
}

void initGL(void)
{
    cube_size = 25.0; // ukuran size per kubus
    rot_x = 0.0; // Melihat rotasi x
    rot_y = 0.0; // Melihat rotasi y
    crement = 5; // Rotasi increment(+) dan decrement(-)
    gap = 5;
    gap_crement = 3;

    // Mengaktifkan merubah warna
    glEnable(GL_COLOR_MATERIAL);

    // Mengaktifkan kedalaman kubus
    glEnable(GL_DEPTH_TEST);

    angle=45;
}

// Menentukan apa yang akan ditampilkan
void load_visualization_parameters(void)
{
    // Koordinat proyeksi
    glMatrixMode(GL_PROJECTION); // Menerapkan operasi matriks selanjutnya ke tumpukan matriks proyeksi
    glLoadIdentity();

    // Perspektif proyeksi
    gluPerspective(angle,fAspect,0.4,500);

    // Sistem koordinat model
    glMatrixMode(GL_MODELVIEW); // Menerapkan operasi matriks selanjutkan ke tumpukan matriks modelview
    glLoadIdentity();

    // Posisi camera
    set_camera();
}

// Membentuk kembali
void reshape(GLsizei w, GLsizei h)
{
    // Mencegah pembagian dengan nol
    if ( h == 0 )
        h = 1;

    glViewport(0, 0, w, h); // Menentukan lebar,tinggi dimensi window

    // Ratio
    fAspect = (GLfloat)w/(GLfloat)h;

    load_visualization_parameters();
}

// Fungsi Keyboard
void keyFunction(unsigned char key, int x, int y)
{

    switch(key)
    {

    case '+':
        gap += gap_crement;
        break;

    case '-':
        gap -= gap_crement;
        break;

/********************************************/
    // Rotasi kubus
    // INcrement or DEcrement
    case 'J': // right
    case 'j':
        rot_y = (rot_y + crement) % 360;
        break;

    case 'L': // left
    case 'l':
        rot_y = (rot_y - crement) % 360;
        break;
/********************************************/
    case 'K': // up
    case 'k':
        rot_x = (rot_x - crement) % 360;
        break;

    case 'I': // down
    case 'i':
        rot_x = (rot_x + crement) % 360;
        break;
/********************************************/
    // Pergerakkan kubus
    // Sumbu X
    case 'A':
    case 'a':
        reset_selected_face();
        y_0 = 0;
        y_k = 0;
        break;

    case 'S':
    case 's':
        reset_selected_face();
        y_0 = 1;
        y_k = 1;
        break;

    case 'D':
    case 'd':
        reset_selected_face();
        y_0 = 2;
        y_k = 2;
        break;
/********************************************/
    // Sumbu Y
    case 'Q':
    case 'q':
        reset_selected_face();
        x_0 = 0;
        x_k = 0;
        break;

    case 'W':
    case 'w':
        reset_selected_face();
        x_0 = 1;
        x_k = 1;
        break;

    case 'E':
    case 'e':
        reset_selected_face();
        x_0 = 2;
        x_k = 2;
        break;
/********************************************/
    // Sumbu Z
    case 'C':
    case 'c':
        reset_selected_face();
        z_0 = 0;
        z_k = 0;
        break;

    case 'X':
    case 'x':
        reset_selected_face();
        z_0 = 1;
        z_k = 1;
        break;

    case 'Z':
    case 'z':
        reset_selected_face();
        z_0 = 2;
        z_k = 2;
        break;
/********************************************/
    // Memindahkan muka yang dipilih
    case 'O': // Searah jarum jam
    case 'o':
        apply_rotation(90);
        break;

    case 'U': // Berlawanan arah jam
    case 'u':
        apply_rotation(-90);
        break;

    default:
        break;
    }
    glutPostRedisplay(); // Menampilkan layar kembali
}

// Fungsi mouse
void mouseFunction(int button, int state, int x, int y)
{
    if (button == GLUT_LEFT_BUTTON)
        if (state == GLUT_DOWN)    // Perbesar
        {
            if (angle >= 25)
                angle -= 5;
        }
    if (button == GLUT_RIGHT_BUTTON)
        if (state == GLUT_DOWN)    // Perkecil
        {
            if (angle <= 125)
                angle += 5;
        }
    load_visualization_parameters();
    glutPostRedisplay();
}

void timer(int value)
{
    glutPostRedisplay();
    glutTimerFunc(15, timer, 0);
}

int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(400,350);
    glutInitWindowPosition(0, 0);
    glutCreateWindow("Graphic Project");
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    initGL();
    glutTimerFunc(0, timer, 0);
    glutMouseFunc(mouseFunction);
    glutKeyboardFunc(keyFunction);
    glutMainLoop();
}
