




#include "Autres.h"



////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//Creation d'une sphère de n nombre de rayon, m nombre de meridien, radius le rayon, et angle l'angle de l'objet
////////////////////////////////////////////////////////////////////////////////////////////////////////////////


void createSphere(int n, int m, float rayon, float angle)
{
    // Calcul du nombre de points et de faces
    int numPoints = n * m;
    int numFaces = (n - 1) * (m - 1);

    // Alloue de la mémoire pour les points de la sphère et les faces
    Point* sphere = new Point[numPoints];
    Face* face_sphere = new Face[numFaces];

    // Générer les points de la sphère
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            double theta = ((double)j / (double)(m - 1.0)) * angle;
            double phi = ((double)i / (double)n) * (2 * M_PI);

            // Coordonnées cartésiennes en fonction de theta et phi
            sphere[j + (i * m)].x = rayon * sin(theta) * cos(phi);
            sphere[j + (i * m)].z = rayon * sin(theta) * sin(phi);
            sphere[j + (i * m)].y = rayon * cos(theta);
        }
    }

    // Calcule les normales pour chaque point de la sphère
    Point* normals = new Point[numPoints];
    for (int i = 0; i < numPoints; ++i)
    {
        // Normaliser les coordonnées pour obtenir les normales
        normals[i].x = sphere[i].x / rayon;
        normals[i].y = sphere[i].y / rayon;
        normals[i].z = sphere[i].z / rayon;
    }

    // Génére les faces de la sphère en utilisant les indices des points
    int index = 0;
    for (int i = 0; i < n - 1; i++)
    {
        for (int j = 0; j < m - 1; j++)
        {
            Face f{ 0, 0, 0, 0 };

            f.i = (i * m) + j;
            f.l = (i * m) + j + 1;

            if (i != n - 2) {
                f.j = ((i + 1) * m) + j;
                f.k = ((i + 1) * m) + j + 1;
            } else {
                f.j = j;
                f.k = j + 1;
            }

            face_sphere[index++] = f;
        }
    }

    // Dessine la sphère en utilisant les points, les normales et les faces
    glBegin(GL_QUADS);
    for (int i = 0; i < numFaces; i++)
    {
        // Dessine les faces avec les normales et les points correspondants
        glNormal3f(normals[face_sphere[i].i].x, normals[face_sphere[i].i].y, normals[face_sphere[i].i].z);
        glVertex3f(sphere[face_sphere[i].i].x, sphere[face_sphere[i].i].y, sphere[face_sphere[i].i].z);

        glNormal3f(normals[face_sphere[i].j].x, normals[face_sphere[i].j].y, normals[face_sphere[i].j].z);
        glVertex3f(sphere[face_sphere[i].j].x, sphere[face_sphere[i].j].y, sphere[face_sphere[i].j].z);

        glNormal3f(normals[face_sphere[i].k].x, normals[face_sphere[i].k].y, normals[face_sphere[i].k].z);
        glVertex3f(sphere[face_sphere[i].k].x, sphere[face_sphere[i].k].y, sphere[face_sphere[i].k].z);

        glNormal3f(normals[face_sphere[i].l].x, normals[face_sphere[i].l].y, normals[face_sphere[i].l].z);
        glVertex3f(sphere[face_sphere[i].l].x, sphere[face_sphere[i].l].y, sphere[face_sphere[i].l].z);
    }
    glEnd();

    // Libére la mémoire allouée
    delete[] sphere;
    delete[] face_sphere;
    delete[] normals;
}


void createSphereOeil(int n, int m, float rayon)
{
    // Calcul du nombre de points et de faces
    int numPoints = n * m;
    int numFaces = (n - 1) * (m - 1);

    // Alloue de la mémoire pour les points de la sphère
    Point* sphere = new Point[numPoints];

    // Génére les points de la sphère
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            // Calcul des angles theta et phi pour les coordonnées sphériques
            double theta = ((double)j / (double)(m - 1.0)) * 2 * M_PI;
            double phi = ((double)i / (double)(n - 1.0)) * M_PI;

            // Conversion des coordonnées sphériques en coordonnées cartésiennes
            sphere[j + (i * m)].x = rayon * sin(phi) * cos(theta);
            sphere[j + (i * m)].z = rayon * sin(phi) * sin(theta);
            sphere[j + (i * m)].y = rayon * cos(phi);
        }
    }

    // Dessine la sphère en utilisant des quadrilatères texturés
    glBegin(GL_QUADS);
    for (int i = 0; i < n - 1; i++)
    {
        for (int j = 0; j < m - 1; j++)
        {
            // Défini les coordonnées de texture et les sommets des quadrilatères
            glTexCoord2f(static_cast<float>(j) / (m - 1), static_cast<float>(i) / (n - 1));
            glVertex3f(sphere[j + (i * m)].x, sphere[j + (i * m)].y, sphere[j + (i * m)].z);

            glTexCoord2f(static_cast<float>(j + 1) / (m - 1), static_cast<float>(i) / (n - 1));
            glVertex3f(sphere[j + 1 + (i * m)].x, sphere[j + 1 + (i * m)].y, sphere[j + 1 + (i * m)].z);

            glTexCoord2f(static_cast<float>(j + 1) / (m - 1), static_cast<float>(i + 1) / (n - 1));
            glVertex3f(sphere[j + 1 + ((i + 1) * m)].x, sphere[j + 1 + ((i + 1) * m)].y, sphere[j + 1 + ((i + 1) * m)].z);

            glTexCoord2f(static_cast<float>(j) / (m - 1), static_cast<float>(i + 1) / (n - 1));
            glVertex3f(sphere[j + ((i + 1) * m)].x, sphere[j + ((i + 1) * m)].y, sphere[j + ((i + 1) * m)].z);
        }
    }
    glEnd();

    // Libére la mémoire allouée
    delete[] sphere;
}



void Cylindre(float rayon, float haut, int meridien)
{
    int i;
    float angle;
    float x, y;

    glBegin(GL_QUAD_STRIP);
    for (i = 0; i <= meridien; ++i)
    {
        angle = 2.0 * M_PI * i / meridien;
        x = rayon * cos(angle);
        y = rayon * sin(angle);

        // Normale pour le côté du cylindre
        float nx = cos(angle);
        float ny = sin(angle);
        float nz = 0.0f;
        glNormal3f(nx, ny, nz);

        glVertex3f(x, y, 0.0); // Point de la base du cylindre
        glVertex3f(x, y, haut); // Point du haut du cylindre
    }
    glEnd();

    glBegin(GL_TRIANGLE_FAN);
    glNormal3f(0.0f, 0.0f, -1.0f); // Normale pour la base inférieure (orientée vers le bas)
    glVertex3f(0.0, 0.0, 0.0); // Centre de la base inférieure
    for (i = 0; i <= meridien; ++i)
    {
        angle = 2.0 * M_PI * i / meridien;
        x = rayon * cos(angle);
        y = rayon * sin(angle);
        glVertex3f(x, y, 0.0); // Points de la base inférieure
    }
    glEnd();

    glBegin(GL_TRIANGLE_FAN);
    glNormal3f(0.0f, 0.0f, 1.0f); // Normale pour la base supérieure (orientée vers le haut)
    glVertex3f(0.0, 0.0, haut); // Centre de la base supérieure
    for (i = 0; i <= meridien; ++i)
    {
        angle = 2.0 * M_PI * i / meridien;
        x = rayon * cos(angle);
        y = rayon * sin(angle);
        glVertex3f(x, y, haut); // Points de la base supérieure
    }
    glEnd();
     glNormal3f(0.0, 0.0, 1.0);
}
