#ifndef CHUFFMAN_H
#define CHUFFMAN_H
#include <iostream>
#include <queue>
#include <vector>

using namespace std;

class cHuffman
{
    //!Creatinon de la structure sNoeud
    struct sNoeud
    {
        char mdonnee;       // code
        double mfreq;       // fréquence du code
        sNoeud *mgauche;    // fils gauche
        sNoeud *mdroit;     // fils droit

        sNoeud(char d, double f)
        {
            mgauche = nullptr;
            mdroit = nullptr;
            this->mdonnee = d;
            this->mfreq = f;
        }
    };

    sNoeud *racine;
    char *mtrame;
    double *freq;
    int mLongueur;

    public:
        struct compare
        {
            bool operator()(sNoeud* gauche, sNoeud* droit)
            {
                return ( (gauche->mfreq) > (droit->mfreq) );
            }
        };

        //! Constructeur de la classe
        /**@brief
        *   Cette fonction permet de creer un objet cHuffman a partir des parametres suivants
        *
        *@param[in] L
        *   double avec le valeur de la longeur de la trame
        *@param[in] trame
        *   tableau de char
        *@param[in] nb
        *   tableau contenant la frequence de chaque char
        */
        cHuffman(double L, char *trame, double *nb)
        {
            priority_queue <sNoeud*, vector <sNoeud*>, compare> q;
            mtrame = trame;
            mLongueur = L;
            freq = new double[mLongueur];
            for(int k=0; k<mLongueur; k++)
            {
                freq[k] = nb[k];
            }
            racine = nullptr;
            double somme = 0.0;
            for(int i=0; i< mLongueur; i++)
            {
                sNoeud N(mtrame[i], freq[i]);
                q.push(N);
            }
            for(int j=0; j<mLongueur; j++)
            {
                sNoeud *Gauche = q.top();
                q.pop(Gauche);
                sNoeud *Droit = q.top();
                q.pop(Droit);
                somme = Gauche->mfreq + Droit->mfreq;
                sNoeud *NParent('#', somme);
                q.push(NParent);
                NParent->mgauche = Gauche;
                NParent->mdroit = Droit;
            }
        }

        //! Destructeur de la classe cHuffman
        /**@brief
        *   Cette fonction permet de supprimer une variable de cHuffman
        */
        virtual ~cHuffman(){}

};

#endif // CHUFFMAN_H
