/****************************************************************************************/
/*                     Lapin.cpp                    */
/****************************************************************************************/
/*         Affiche a l'ecran un cube en 3D         */
/****************************************************************************************/


#include <GL/glut.h>
#include <math.h>
#include "FormeGlut.h"
#include <cstdio>
#include <jpeglib.h>

//////////////////////////////////////////////
//////Tableaux Pour Créer le Baton
//////////////////////////////////////////////
Point pCube[8]={
    {-0.5,-0.5, 0.5,1.0,0.0,0.0},
    { 0.5, -0.5, 0.5,0.0,1.0,0.0},
    { 0.5, -0.5, -0.5,0.0,0.0,1.0},
    { -0.5, -0.5, -0.5,1.0,1.0,1.0},
    { -0.5,0.5, 0.5,1.0,0.0,0.0},
    { 0.5, 0.5, 0.5,0.0,1.0,0.0},
    { 0.5, 0.5, -0.5,0.0,0.0,1.0},
    { -0.5, 0.5, -0.5,1.0,1.0,1.0}};

//Tableau pour stocker les indices des sommets par face pour le cube
int fCube[6][4]={
  {0,3,2,1},
  {0,1,5,4},
  {1,2,6,5},
  {2,3,7,6},
  {0,4,7,3},
  {4,5,6,7}};

//////////////////////////////
//////////////////////////////



//////////////////////////////
//////Variable de base
//////////////////////////////

//image
const int largimg=256;
const int hautimg=256;
unsigned char image[largimg*hautimg*3];
unsigned char texture[256][256][3];
unsigned char texture2[512][512][3];

// Angle d'ouverture oeil
float angleOuvert =2*M_PI/3;

//Pour gestion camera et souris
char presse;
int anglex,angley,x,y,xold,yold;
float cameraZoom = 1.5f;

//Pour animation du baton
bool boolBaton=true;
double angleanime=360;

//variables pour animation oreille
bool animation = false; // Contrôle si l'animation est activée ou non
bool mouvement = true; // Contrôle la direction du mouvement de l'oreille
float TranslationX = 0.0; // Translation actuelle de l'oreille sur l'axe X
const float maxTranslation = 0.03; // Plage de translation maximale pour l'oreille
const float vitesse = 0.001; // Vitesse du mouvement de l'oreille

//////////////////////////////
//////////////////////////////


/* Prototype des fonctions */
void affichage();
void clavier(unsigned char touche,int x,int y);
void Fleches(int key, int x, int y);
void reshape(int x,int y);
void mouse(int bouton,int etat,int x,int y);
void mousemotion(int x,int y);
void loadJpegImage(char *fichier);

//////////////////////////
//////Fonctions d'animations
//////////////////////////

void animeBaton()
{
    // Si le booléen boolBaton est vrai
    if (boolBaton == true)
    {
        // Si l'angle animé est inférieur à 360 degrés
        if (angleanime < 360)
        {
            angleanime += 5; // Augmente l'angle animé de 5 degrés
            glutPostRedisplay(); // Demande le redessin de la scène pour refléter le changement d'angle
        }
    }

    // Si le booléen boolBaton est faux
    if (boolBaton == false)
    {
        // Si l'angle animé est supérieur à 180 degrés
        if (angleanime > 180)
        {
            angleanime -= 5; // Diminue l'angle animé de 5 degrés
            glutPostRedisplay(); // Demande le redessin de la scène pour refléter le changement d'angle
        }
    }
}


void animationOeil(int value)
{
    if (angleOuvert <= (2*M_PI/3) || angleOuvert >= M_PI )
    {
        value *= -1; // Change la direction de l'animation

    }
    angleOuvert += value * (M_PI / 150); // Ajuste l'angle progressivement

    glutPostRedisplay(); // Redessine la sphère avec le nouvel angle
    glutTimerFunc(16, animationOeil, value); // Déclenche une nouvelle mise à jour après 16ms (environ 60 FPS)
}



// Fonction pour animer le mouvement de l'oreille
void animationOreilles()
{
    if (animation)
    { // Vérifie si l'animation est activée
        if (mouvement)
        { // Vérifie la direction du mouvement
            TranslationX += vitesse; // Augmente la translation vers la droite
            if (TranslationX >= maxTranslation) { // Vérifie si l'oreille a atteint la limite droite
                mouvement = false; // Change la direction du mouvement vers la gauche
            }
        } else
        {
            TranslationX -= vitesse; // Diminue la translation vers la gauche
            if (TranslationX <= -maxTranslation)
            { // Vérifie si l'oreille a atteint la limite gauche
                mouvement = true; // Change la direction du mouvement vers la droite
            }
        }

        glutPostRedisplay(); // Demande de redessiner la fenêtre pour refléter les changements de l'oreille
    }
}



///////////////////////
///////////////////////


 //oreilles//
void oreilleMove()
{

  //oreille droite
  glPushMatrix();
  glColor3f(0.95,0.95,0.95);
  glTranslatef(0.15 -TranslationX,0.84,0);
  glRotatef(65,0,0,1);
  glScalef(1,0.4,0.2);
  glutSolidSphere(0.21,100,100);
  glPopMatrix();

  glPushMatrix();
  glColor3f(0.98,0.89,0.859);
  glTranslatef(0.15-TranslationX,0.84,0.02);
  glRotatef(65,0,0,1);
  glScalef(0.9,0.4,0.15);
  glutSolidSphere(0.18,100,100);
  glPopMatrix();


  //oreille gauche
  glPushMatrix();
  glColor3f(0.95,0.95,0.95);
  glTranslatef(-0.15+TranslationX,0.84,0);
  glRotatef(-65,0,0,1);
  glScalef(1,0.4,0.2);
  glutSolidSphere(0.21,100,100);
  glPopMatrix();

  glPushMatrix();
  glColor3f(0.98,0.89,0.859);
  glTranslatef(-0.15+TranslationX,0.84,0.02);
  glRotatef(-65,0,0,1);
  glScalef(0.9,0.4,0.15);
  glutSolidSphere(0.18,100,100);
  glPopMatrix();

}


///////////////////////
//////Fonction d'affichage
///////////////////////

void loadJpegImage(char *fichier) {
    struct jpeg_decompress_struct cinfo;
    struct jpeg_error_mgr jerr;
    FILE *file;

    cinfo.err = jpeg_std_error(&jerr);
    jpeg_create_decompress(&cinfo);

  unsigned char *ligne;

  cinfo.err = jpeg_std_error(&jerr);
  jpeg_create_decompress(&cinfo);
#ifdef __WIN32
  if (fopen_s(&file,fichier,"rb") != 0)
    {
      fprintf(stderr,"Erreur : impossible d'ouvrir le fichier texture.jpg\n");
      exit(1);
    }
#elif __GNUC__
  if ((file = fopen(fichier,"rb")) == 0)
    {
      fprintf(stderr,"Erreur : impossible d'ouvrir le fichier texture.jpg\n");
      exit(1);
    }
#endif
  jpeg_stdio_src(&cinfo, file);
  jpeg_read_header(&cinfo, TRUE);

  if ((cinfo.image_width!=largimg)||(cinfo.image_height!=hautimg)) {
    fprintf(stdout,"Erreur : l'image doit etre de taille 256x256\n");
    exit(1);
  }
  if (cinfo.jpeg_color_space==JCS_GRAYSCALE) {
    fprintf(stdout,"Erreur : l'image doit etre de type RGB\n");
    exit(1);
  }

  jpeg_start_decompress(&cinfo);
  ligne=image;
  while (cinfo.output_scanline<cinfo.output_height)
    {
      ligne=image+3*largimg*cinfo.output_scanline;
      jpeg_read_scanlines(&cinfo,&ligne,1);
    }
  jpeg_finish_decompress(&cinfo);
  jpeg_destroy_decompress(&cinfo);

  for(int i = 0 ;i<256; i++){
        for(int j=0 ; j<256;j++){
            texture[i][j][0]=image[i*256*3+j*3];
            texture[i][j][1]=image[i*256*3+j*3+1];
            texture[i][j][2]=image[i*256*3+j*3+2];

        }
    }

    for(int i = 0 ;i<512; i++){
        for(int j=0 ; j<512 ;j++){
            if(i<256 && j<256){
                texture2[i][j][0]=texture[i][j][0];
                texture2[i][j][1]=texture[i][j][1];
                texture2[i][j][2]=texture[i][j][2];
                }
            if(i>256 && j>256){
                texture2[i][j][0]=texture[i%256][j%256][0];
                texture2[i][j][1]=texture[i%256][j%256][1];
                texture2[i][j][2]=texture[i%256][j%256][2];
            }
            else{
                texture2[i][j][0]=255;
                texture2[i][j][1]=255;
                texture2[i][j][2]=255;
            }
        }
    }
}


void affichage()
{
  /* effacement de l'image avec la couleur de fond */
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glShadeModel(GL_SMOOTH);
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  glOrtho(-1*cameraZoom,1*cameraZoom,-1*cameraZoom,1*cameraZoom,-1,1);
  glRotatef(angley,1.0,0.0,0.0);
  glRotatef(anglex,0.0,1.0,0.0);
  gluLookAt(0.0, 0.5, 0.1, 0.0, 0.5, 0.0, 0.0, 0.5, 0.0);
  glEnable(GL_DEPTH_TEST);
  glEnable(GL_COLOR_MATERIAL);
  glEnable(GL_LIGHTING);
  glEnable(GL_NORMALIZE);

  //spot avant, lumiere diffuse
  glPushMatrix();
  GLfloat posLight1[] = {-0.8, 0.8, 0.8, 1};
  glLightfv(GL_LIGHT0, GL_POSITION, posLight1);
  glEnable(GL_LIGHT0);
  glPopMatrix();

  //spot arriere, lumiere diffuse
  glPushMatrix();
  GLfloat posLight2[] = {1, 1, -1, 1};
  GLfloat ColorDiffuse[] = {1, 1, 1, 1};
  glLightfv(GL_LIGHT1, GL_POSITION, posLight2);
  glLightfv(GL_LIGHT1, GL_DIFFUSE, ColorDiffuse);
  glEnable(GL_LIGHT1);
  glPopMatrix();

  //spot sous les pieds, lumiere diffuse
  glPushMatrix();
  GLfloat posLight3[] = {0, -1, 0, 1};
  GLfloat ColorDiffuse2[] = {0.4, 0.4, 0.4, 0.4};
  glLightfv(GL_LIGHT2, GL_POSITION, posLight3);
  glLightfv(GL_LIGHT2, GL_DIFFUSE, ColorDiffuse2);
  glEnable(GL_LIGHT2);
  glPopMatrix();

  //lumiere ambiante
  glPushMatrix();
  GLfloat ColorAmbiant[] = {1, 0, 0, 1};
  glLightfv(GL_LIGHT3, GL_AMBIENT, ColorAmbiant);
  glPopMatrix();


  //Tête//
  Tete();

  //Oreilles//
  oreilleMove();

  //Oeil//
  //oeil droit
  glPushMatrix();
  glColor3f(0.98,0.89,0.859);
  glTranslatef(0.12,0.6,0.18);
  glRotatef(90,-90,0,1);
  createSphere(30,30,0.055,angleOuvert);
  glPopMatrix();

  glPushMatrix();
  glEnable(GL_TEXTURE_2D);
  glColor3f(1,1,1);
  glTranslatef(0.12,0.6,0.18);
  glRotated(0.12,1.0,0.18,0.12);
  createSphereOeil(30,30,0.05);
  glDisable(GL_TEXTURE_2D);
  glPopMatrix();

  //oeil gauche
  glPushMatrix();
  glColor3f(0.98,0.89,0.859);
  glTranslatef(-0.12,0.6,0.18);
  glRotatef(90,-90,0,1);
  createSphere(30,30,0.055,angleOuvert);
  glPopMatrix();

  glPushMatrix();
 glEnable(GL_TEXTURE_2D);
  glColor3f(1,1,1);
  glTranslatef(-0.12,0.6,0.18);
  createSphereOeil(100,100,0.05);
  glDisable(GL_TEXTURE_2D);
  glPopMatrix();


  //Corps//
  Corps();


  //Bouche//
  Bouche();


  //Pieds//
  Pieds();


  //Bras//
  Bras();


  //Mains
  Mains();


  ////Baton////
  glPushMatrix();
   /* // en commentaire car la texture ferme la fenetre toute seule au bout dune 10ene de secondes
  loadJpegImage("./wood.jpg");
           //Parametrage du placage de textures
  glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);
  glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);
  glTexImage2D(GL_TEXTURE_2D,0,GL_RGB,256,256,0,GL_RGB,GL_UNSIGNED_BYTE,image);
  glEnable(GL_TEXTURE_2D); */
  glRotatef(angleanime,0,1,0);
  glColor3f(0.67,0.52,0.32);
  glTranslatef(0.24,0.01,0);
  glScalef(1,1,10);

for (int i = 0; i < 6; i++) {
    glBegin(GL_QUADS);
    // Pour chaque sommet de la face
    for (int j = 0; j < 4; j++) {
        glTexCoord3f(pCube[fCube[i][j]].r, pCube[fCube[i][j]].g, pCube[fCube[i][j]].b);
        glVertex3f(pCube[fCube[i][j]].x*0.05, pCube[fCube[i][j]].y*0.05, pCube[fCube[i][j]].z*0.05);
    }
    glEnd();
}
  //glDisable(GL_TEXTURE_2D);
  glPopMatrix();


  //On echange les buffers
  glutSwapBuffers();
}

void clavier(unsigned char touche,int x,int y)
{
  switch (touche)
    {
    case 'T': // allume lumiere ambiante
      glEnable(GL_LIGHT3);
      break;
    case 't': // eteint lumiere ambiante
      glDisable(GL_LIGHT3);
      break;
    case 'p': /* affichage du carre plein */
      glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
      glutPostRedisplay();
      break;
    case 'g':
      boolBaton=!boolBaton;
      glutIdleFunc(animeBaton);
      break;
    case 'f': /* affichage en mode fil de fer */
      glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);
      glutPostRedisplay();
      break;
    case 's' : /* Affichage en mode sommets seuls */
      glPolygonMode(GL_FRONT_AND_BACK,GL_POINT);
      glutPostRedisplay();
      break;
    case 'd':
      glEnable(GL_DEPTH_TEST);
      glutPostRedisplay();
      break;
    case 'D':
      glDisable(GL_DEPTH_TEST);
      glutPostRedisplay();
      break;
    case 'a'://Les faces à l'envers s'affichent en fil de fer
      glPolygonMode(GL_FRONT,GL_FILL);
      glPolygonMode(GL_FRONT,GL_LINE);
      glutPostRedisplay();
      break;
    case 'z': //dezoom la camera
      cameraZoom+=0.1f;
      glutPostRedisplay();
      break;
    case 'Z': //zoom la camera
      cameraZoom-=0.1f;
      glutPostRedisplay();
      break;
    case 'c': //animation du lapin
      animation = !animation;
    glutIdleFunc(animationOreilles);
      break;
    case 'q' : /*la touche 'q' permet de quitter le programme */
      exit(0);
    }
}

void Fleches(int key, int x, int y)
{
    switch (key)
    {
        case GLUT_KEY_UP:
            angley+=2;
            glutPostRedisplay();
            break;
        case GLUT_KEY_DOWN :
            angley-=2;
            glutPostRedisplay();
            break;
        case GLUT_KEY_LEFT:
            anglex+=2;
            glutPostRedisplay();
            break;
        case GLUT_KEY_RIGHT:
            anglex-=2   ;
            glutPostRedisplay();
            break;
    }
}


void reshape(int x,int y)
{
  if (x<y)
    glViewport(0,(y-x)/2,x,x);
  else
    glViewport((x-y)/2,0,y,y);
}


void mouse(int button, int state,int x,int y)
{
  /* si on appuie sur le bouton gauche */
  if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
  {
    presse = 1; /* le booleen presse passe a 1 (vrai) */
    xold = x; /* on sauvegarde la position de la souris */
    yold=y;
  }
  /* si on relache le bouton gauche */
  if (button == GLUT_LEFT_BUTTON && state == GLUT_UP)
    presse=0; /* le booleen presse passe a 0 (faux) */
}


void mousemotion(int x,int y)
  {
    if (presse) /* si le bouton gauche est presse */
    {
      /* on modifie les angles de rotation de l'objet
	 en fonction de la position actuelle de la souris et de la derniere
	 position sauvegardee */
      anglex=anglex+(x-xold);
      angley=angley+(y-yold);
      glutPostRedisplay(); /* on demande un rafraichissement de l'affichage */
    }

    xold=x; /* sauvegarde des valeurs courante de le position de la souris */
    yold=y;
  }


  int main(int argc,char **argv)
{
  loadJpegImage("./yeux.jpg");

  /* initialisation de glut et creation
     de la fenetre */
  glutInit(&argc,argv);

  glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
  glutInitWindowPosition(200,200);
  glutInitWindowSize(1000,1000);
  glutCreateWindow("LapinCretin");

  /* Initialisation d'OpenGL */
  glClearColor(0.5,0.5,0.5,0.5);
  glColor3f(1.0,1.0,1.0);
  glPointSize(2.0);
  glEnable(GL_DEPTH_TEST);
  glutTimerFunc(16, animationOeil, 1);

  /* Parametrage du placage de textures */
  glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);
  glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);
  glTexImage2D(GL_TEXTURE_2D,0,GL_RGB,256,256,0,GL_RGB,GL_UNSIGNED_BYTE,image);

  /* enregistrement des fonctions de rappel */
  glutDisplayFunc(affichage);
  glutKeyboardFunc(clavier);
  glutSpecialFunc(Fleches);
  glutReshapeFunc(reshape);
  glutMouseFunc(mouse);
  glutMotionFunc(mousemotion);

  /* Entree dans la boucle principale glut */
  glutMainLoop();
  return 0;
}
