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
        // structure permettant de trier la liste dans l'ordre croissant
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
        *   tableau de char, les individus
        *@param[in] nb
        *   tableau contenant la frequence de chaque char
        */
        cHuffman(double L, char *trame, double *nb)
        {
            mLongueur = L;
            racine = nullptr;
            priority_queue <sNoeud*, vector <sNoeud*>, compare> q;

            mtrame = new char[mLongueur];
            freq = new double[mLongueur];
            for(int k=0; k<mLongueur; k++)
            {
                mtrame[k] = trame[k];
                freq[k] = nb[k];
            }
            for(int i=0; i<mLongueur; i++)
            {       // Création de la liste pour créer l'arbre
                sNoeud* racine = new sNoeud(mtrame[i], freq[i]);    // création de noeud pour chaque individus
                q.push(racine);                                     // Ajout de ce noeud dans la liste
            }
            for(int j=0; j<mLongueur-1; j++)
            {
                sNoeud *Gauche = q.top();       // recup plus petit de la liste
                q.pop();                        // suppression du plus petit de la liste
                sNoeud *Droit = q.top();        // recup nouveau plus petit de la liste
                q.pop();                        // suppression du nouveau plus petit de la liste
                // création du noeud parent des deux plus petits récupérés précédemment
                sNoeud *NParent = new sNoeud('#', (Gauche->mfreq + Droit->mfreq));  // '#' permet de repérer les noeuds parents et donc de les séparer de la liste originale
                q.push(NParent);                // Ajout du noeud parent créé
                NParent->mgauche = Gauche;      // Assignation du fils gauche du noeud parent
                NParent->mdroit = Droit;        // Assignation du fils droit du noeud parent
            }
            AfficherHuffman(q.top(), "");
        }

        //! Destructeur de la classe cHuffman
        /**@brief
        *   Cette fonction permet de supprimer une variable de cHuffman
        */
        virtual ~cHuffman(){}

        void AfficherHuffman(struct sNoeud *Racine, string str)
        {
            if(Racine != NULL)
            {
                if(Racine->mdonnee != '#')      // Si c'est un noeud de la liste originale
                {   // Affichage du code binaire associé
                    cout << Racine->mdonnee << " = " << str << " avec une freq de " << Racine->mfreq << endl << endl;
                }
                AfficherHuffman(Racine->mgauche, str + "0");    // 0 si gauche
                AfficherHuffman(Racine->mdroit, str + "1");     // 1 si droite
            }
        }
};

#endif // CHUFFMAN_H
