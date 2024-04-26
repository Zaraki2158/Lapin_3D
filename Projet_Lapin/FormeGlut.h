

#include "FormePoint.h"



void Tete()
{
  glPushMatrix();
  glColor3f(0.95,0.95,0.95);
  glTranslatef(0,0.5,0);
  glRotatef(90,0,0,1);
  glScalef(0.8,0.65,0.60);
  glutSolidSphere(0.35,100,100);
  glPopMatrix();
}


void Corps()
{
  //Coprs Blanc
  glPushMatrix();
  glColor3f(0.95,0.95,0.95);
  glTranslatef(0,0.2,0);
  glRotatef(90,0,0,1);
  glScalef(1,0.75,0.55);
  glutSolidSphere(0.25,100,100);
  glPopMatrix();

  //ventre rose
  glPushMatrix();
  glColor3f(0.98,0.89,0.859);
  glTranslatef(0,0.18,0.01);
  glRotatef(90,0,0,1);
  glScalef(0.85,0.65,0.55);
  glutSolidSphere(0.25,100,100);
  glPopMatrix();
}

void Bouche()
{
  //bouche noir
  glPushMatrix();
  glColor3f(0,0,0);
  glTranslatef(0,0.48,0.190);
  glRotatef(180,0,4,9);
  glScalef(1,1,1);
  glutSolidTorus(0.006,0.05,100,100);
  glPopMatrix();

  //contour rose
  glPushMatrix();
  glColor3f(0.98,0.89,0.859);
  glTranslatef(0,0.455,0.17);
  glRotatef(90,0,0,1);
  glScalef(0.85,0.85,0.55);
  glutSolidSphere(0.1,100,100);
  glPopMatrix();
}


void Pieds()
{
  //pied droit
  glPushMatrix();
  glColor3f(0.95,0.95,0.95);
  glTranslatef(0.09,0.13,0);
  glRotatef(90,1,0,0);
  glScalef(0.8,1,1);
  Cylindre(0.07,0.22,100);
  glPopMatrix();

  glPushMatrix();
  glColor3f(0.98,0.89,0.859);
  glTranslatef(0.09,0.127,0);
  glRotatef(90,1,0,0);
  glScalef(0.8,1,1);
  Cylindre(0.05,0.22,100);
  glPopMatrix();


  //pied gauche
  glPushMatrix();
  glColor3f(0.95,0.95,0.95);
  glTranslatef(-0.09,0.13,0);
  glRotatef(90,1,0,0);
  glScalef(0.8,1,1);
  Cylindre(0.07,0.22,100);
  glPopMatrix();


  glPushMatrix();
  glColor3f(0.98,0.89,0.859);
  glTranslatef(-0.09,0.127,0);
  glRotatef(90,1,0,0);
  glScalef(0.8,1,1);
  Cylindre(0.05,0.22,100);
  glPopMatrix();
}


void Bras()
{
  //bras droit
  glPushMatrix();
  glColor3f(0.95,0.95,0.95);
  glTranslatef(0.245,0.12,0);
  glRotatef(90,0,0,1);
  glScalef(1,0.5,0.5);
  glutSolidSphere(0.08,100,100);
  glPopMatrix();

  glPushMatrix();
  glColor3f(0.95,0.95,0.95);
  glTranslatef(0.244,0.16,0);
  glRotatef(100,0,0,1);
  glScalef(1,0.5,0.5);
  glutSolidSphere(0.08,100,100);
  glPopMatrix();

  glPushMatrix();
  glColor3f(0.95,0.95,0.95);
  glTranslatef(0.239,0.19,0);
  glRotatef(110,0,0,1);
  glScalef(1,0.5,0.5);
  glutSolidSphere(0.08,100,100);
  glPopMatrix();

  glPushMatrix();
  glColor3f(0.95,0.95,0.95);
  glTranslatef(0.230,0.22,0);
  glRotatef(120,0,0,1);
  glScalef(1,0.5,0.5);
  glutSolidSphere(0.08,100,100);
  glPopMatrix();

  glPushMatrix();
  glColor3f(0.95,0.95,0.95);
  glTranslatef(0.22,0.24,0);
  glRotatef(125,0,0,1);
  glScalef(1,0.5,0.5);
  glutSolidSphere(0.08,100,100);
  glPopMatrix();

  glPushMatrix();
  glColor3f(0.95,0.95,0.95);
  glTranslatef(0.245,0.12,0);
  glRotatef(90,0,0,1);
  glScalef(1,0.5,0.5);
  glutSolidSphere(0.08,100,100);
  glPopMatrix();

  glPushMatrix();
  glColor3f(0.95,0.95,0.95);
  glTranslatef(0.244,0.16,0);
  glRotatef(100,0,0,1);
  glScalef(1,0.5,0.5);
  glutSolidSphere(0.08,100,100);
  glPopMatrix();

  glPushMatrix();
  glColor3f(0.95,0.95,0.95);
  glTranslatef(0.239,0.19,0);
  glRotatef(110,0,0,1);
  glScalef(1,0.5,0.5);
  glutSolidSphere(0.08,100,100);
  glPopMatrix();

  glPushMatrix();
  glColor3f(0.95,0.95,0.95);
  glTranslatef(0.230,0.22,0);
  glRotatef(120,0,0,1);
  glScalef(1,0.5,0.5);
  glutSolidSphere(0.08,100,100);
  glPopMatrix();

  glPushMatrix();
  glColor3f(0.95,0.95,0.95);
  glTranslatef(0.22,0.24,0);
  glRotatef(125,0,0,1);
  glScalef(1,0.5,0.5);
  glutSolidSphere(0.08,100,100);
  glPopMatrix();


  //bras gauche
  glPushMatrix();
  glColor3f(0.95,0.95,0.95);
  glTranslatef(-0.245,0.12,0);
  glRotatef(-270,0,0,1);
  glScalef(1,0.5,0.5);
  glutSolidSphere(0.08,100,100);
  glPopMatrix();

  glPushMatrix();
  glColor3f(0.95,0.95,0.95);
  glTranslatef(-0.244,0.16,0);
  glRotatef(-280,0,0,1);
  glScalef(1,0.5,0.5);
  glutSolidSphere(0.08,100,100);
  glPopMatrix();

  glPushMatrix();
  glColor3f(0.95,0.95,0.95);
  glTranslatef(-0.239,0.19,0);
  glRotatef(-290,0,0,1);
  glScalef(1,0.5,0.5);
  glutSolidSphere(0.08,100,100);
  glPopMatrix();

  glPushMatrix();
  glColor3f(0.95,0.95,0.95);
  glTranslatef(-0.230,0.22,0);
  glRotatef(-300,0,0,1);
  glScalef(1,0.5,0.5);
  glutSolidSphere(0.08,100,100);
  glPopMatrix();

  glPushMatrix();
  glColor3f(0.95,0.95,0.95);
  glTranslatef(-0.22,0.24,0);
  glRotatef(-305,0,0,1);
  glScalef(1,0.5,0.5);
  glutSolidSphere(0.08,100,100);
  glPopMatrix();
}


void Mains()
{
  //main droite
  glPushMatrix();
  glColor3f(0.95,0.95,0.95);
  glTranslatef(0.245,0.09,0);
  glRotatef(90,0,0,1);
  glScalef(1,0.5,0.5);
  glutSolidSphere(0.08,100,100);
  glPopMatrix();

  //main gauche
  glPushMatrix();
  glColor3f(0.95,0.95,0.95);
  glTranslatef(-0.245,0.09,0);
  glRotatef(90,0,0,1);
  glScalef(1,0.5,0.5);
  glutSolidSphere(0.08,100,100);
  glPopMatrix();
}
