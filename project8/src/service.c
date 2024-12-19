#include "service.h"
#include <stdio.h>
#include <string.h>
#include <gtk/gtk.h>
#include <stdlib.h>

#define COLUMNS 9 // Nombre total de colonnes
service s;

enum {
    EID,
    ETYPE,
    EPRIX,
    EPAYMENT,
    EHEURE,
    EJJ,
    EMM,
    EAA,
    ECONFIRMED,
};    
enum {
    EID_SERVICE,
    EID_RESERVATION,
    N_COLUMNS
};


int ajouter(char *filename, service s) {
    FILE *f = fopen(filename, "a");
    if (f != NULL) {
        fprintf(f, " %s %s %s %s %s %s %s %s '%s'\n", s.id, s.type, s.prix, s.payment, s.heure ,s.jj, s.mm, s.aa, s.confirmed);
        fclose(f);
        return 1;  
    } else {
        return 0; 
    }
}


void afficher_service(GtkWidget *liste, char *noms) {
    GtkCellRenderer *renderer;
    GtkTreeViewColumn *column;
    GtkTreeIter iter;
    GtkListStore *store;

    char id[100];
    char type[100];
    char prix[100];
    char payment[100];
    char heure[100];
    char jj[100];
    char mm[100];
    char aa[100];
    char confirmed[100];

    store = gtk_tree_view_get_model(GTK_TREE_VIEW(liste));

    if (store == NULL) {
        // Configuration des colonnes du TreeView
        renderer = gtk_cell_renderer_text_new();
        column = gtk_tree_view_column_new_with_attributes("ID", renderer, "text", EID, NULL);
        gtk_tree_view_append_column(GTK_TREE_VIEW(liste), column);

        renderer = gtk_cell_renderer_text_new();
        column = gtk_tree_view_column_new_with_attributes("Type", renderer, "text", ETYPE, NULL);
        gtk_tree_view_append_column(GTK_TREE_VIEW(liste), column);

        renderer = gtk_cell_renderer_text_new();
        column = gtk_tree_view_column_new_with_attributes("Prix", renderer, "text", EPRIX, NULL);
        gtk_tree_view_append_column(GTK_TREE_VIEW(liste), column);

        renderer = gtk_cell_renderer_text_new();
        column = gtk_tree_view_column_new_with_attributes("Payment", renderer, "text", EPAYMENT, NULL);
        gtk_tree_view_append_column(GTK_TREE_VIEW(liste), column);

        renderer = gtk_cell_renderer_text_new();
        column = gtk_tree_view_column_new_with_attributes("Heure", renderer, "text", EHEURE, NULL);
        gtk_tree_view_append_column(GTK_TREE_VIEW(liste), column);

        renderer = gtk_cell_renderer_text_new();
        column = gtk_tree_view_column_new_with_attributes("JJ", renderer, "text", EJJ, NULL);
        gtk_tree_view_append_column(GTK_TREE_VIEW(liste), column);

        renderer = gtk_cell_renderer_text_new();
        column = gtk_tree_view_column_new_with_attributes("MM", renderer, "text", EMM, NULL);
        gtk_tree_view_append_column(GTK_TREE_VIEW(liste), column);

        renderer = gtk_cell_renderer_text_new();
        column = gtk_tree_view_column_new_with_attributes("AA", renderer, "text", EAA, NULL);
        gtk_tree_view_append_column(GTK_TREE_VIEW(liste), column);

        renderer = gtk_cell_renderer_text_new();
        column = gtk_tree_view_column_new_with_attributes("Confirmed", renderer, "text", ECONFIRMED, NULL);
        gtk_tree_view_append_column(GTK_TREE_VIEW(liste), column);
    }

    store = gtk_list_store_new(COLUMNS, 
                               G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING, 
                               G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING, 
                               G_TYPE_STRING);

    FILE *f = fopen(noms, "r");
    if (f == NULL) {
        printf("Erreur : impossible d'ouvrir le fichier %s\n", noms);
        return;
    }

    // Lecture des données depuis le fichier
    while (fscanf(f, " %s %s %s %s %s %s %s %s %s",
                  id, type, prix, payment, heure, jj, mm, aa, confirmed) == 9) {
    
        gtk_list_store_append(store, &iter);
        gtk_list_store_set(store, &iter,
                           EID, id,
                           ETYPE, type,
                           EPRIX, prix,
                           EPAYMENT, payment,
                           EHEURE, heure,
                           EJJ, jj,
                           EMM, mm,
                           EAA, aa,
                           ECONFIRMED, confirmed,
                           -1);
    }

    fclose(f);

    gtk_tree_view_set_model(GTK_TREE_VIEW(liste), GTK_TREE_MODEL(store));
    g_object_unref(store);
}
void modifier_service(service s, int *resultat) {
    char id[100];
    char type[100];
    char prix[100];
    char payment[100];
    char heure[100];
    char jj[100];
    char mm[100];
    char aa[100];
    char confirmed[100];

    FILE *f1 = NULL, *f2 = NULL;
    int id_trouve = 0;  // Variable pour vérifier si l'ID a été trouvé

    // Ouvrir le fichier en lecture
    f1 = fopen("service.txt", "r");
    if (f1 == NULL) {
        perror("Error opening service.txt");
        *resultat = 2; // Échec d'ouverture du fichier service.txt
        return;
    }

    // Ouvrir le fichier en écriture
    f2 = fopen("nouvservice.txt", "w");
    if (f2 == NULL) {
        perror("Error opening nouvservice.txt");
        fclose(f1);
        *resultat = 3; // Échec d'ouverture du fichier nouvservice.txt
        return;
    }

    // Lire le fichier ligne par ligne et modifier si nécessaire
    while (fscanf(f1, "%s %s %s %s %s %s %s %s %s\n", id, type, prix, payment, heure, jj, mm, aa, confirmed) != EOF) {
        if (strcmp(s.id, id) == 0) {
            // Si l'ID correspond, on écrit la nouvelle ligne
            fprintf(f2, "%s %s %s %s %s %s %s %s %s\n", s.id, s.type, s.prix, s.payment, s.heure, s.jj, s.mm, s.aa, s.confirmed);
            id_trouve = 1; // Marquer l'ID comme trouvé
        } else {
            // Sinon, on écrit la ligne actuelle
            fprintf(f2, "%s %s %s %s %s %s %s %s %s\n", id, type, prix, payment, heure, jj, mm, aa, confirmed);
        }
    }

    // Si l'ID n'a pas été trouvé, signaler l'erreur
    if (!id_trouve) {
        fclose(f1);
        fclose(f2);
        remove("nouvservice.txt");  // Supprimer le fichier temporaire
        *resultat = 6; // L'ID n'a pas été trouvé
        return;
    }

    // Fermeture des fichiers
    fclose(f1);
    fclose(f2);

    // Remplacer le fichier original par le nouveau
    if (remove("service.txt") != 0) {
        perror("Error deleting old service.txt");
        *resultat = 4; // Erreur lors de la suppression du fichier original
        return;
    }

    if (rename("nouvservice.txt", "service.txt") != 0) {
        perror("Error renaming nouvservice.txt to service.txt");
        *resultat = 5; // Erreur lors du renommage
        return;
    }

    *resultat = 1; // Succès de la modification
}

int supprimer_Service(const char *filename, const char *id) {
    FILE *file = fopen(filename, "r");
    FILE *temp = fopen("temp.txt", "w");
    
    if (file == NULL || temp == NULL) {
        perror("Erreur lors de l'ouverture des fichiers");
        if (file) fclose(file);
        if (temp) fclose(temp);
        return 0;
    }

    char id_buffer[100], type[100], prix[100], payment[100], heure[100];
    char jj[100], mm[100], aa[100], confirmed[100];
    int found = 0;

    while (fscanf(file, "%s %s %s %s %s %s %s %s %s\n", 
                  id_buffer, type, prix, payment, heure, 
                  jj, mm, aa, confirmed) != EOF) {
        if (strcmp(id_buffer, id) != 0) {
            // Écrire dans le fichier temporaire si l'ID ne correspond pas
            fprintf(temp, "%s %s %s %s %s %s %s %s %s\n", 
                    id_buffer, type, prix, payment, heure, 
                    jj, mm, aa, confirmed);
        } else {
            found = 1; // Indique que l'ID a été trouvé
        }
    }

    fclose(file);
    fclose(temp);

    if (found) {
        // Remplacer le fichier d'origine
        if (remove(filename) != 0 || rename("temp.txt", filename) != 0) {
            perror("Erreur lors de la mise à jour du fichier");
            return 0;
        }
        printf("Service avec l'ID %s supprimé avec succès.\n", id);
        return 1;
    } else {
        remove("temp.txt"); // Supprimer le fichier temporaire inutile
        printf("Erreur : Service avec l'ID %s introuvable.\n", id);
        return 0;
    }
}


/*void afficher(char *filename) {
    service s;
    FILE *f = fopen(filename, "r");

    if (f == NULL) {
        printf("Erreur lors de l'ouverture du fichier.\n");
        return;
    }

    while (fscanf(f, "%s %s %s %s %s %s %s %s %c\n", &s.id, s.type, s.prix, s.payment,s.heure , s.jj, s.mm, s.aa, &s.confirmed) != EOF) {
        printf("%s %s %s %s %s/%s/%s %s %c\n", s.id, s.type, s.prix, s.payment,s.heure , s.jj, s.mm, s.aa,  s.confirmed);
    }

    fclose(f);
}*/


void chercher_service(service s , char text[100])
{
  FILE *f4 = NULL;
  FILE *ff = NULL;
  remove("rechservice.txt");
  f4 = fopen("service.txt", "r");
  ff = fopen("rechservice.txt", "a+");

  if (f4 == NULL || ff == NULL)
  {
    return;
  }

  else
  {

    while (fscanf(f4, "%s %s %s %s %s %s %s %s %s\n",
                s.id, s.type, s.prix, s.payment, s.heure,
                s.jj, s.mm, s.aa, s.confirmed) != EOF)
    {
      if (strcmp(text, s.id) == 0 || strcmp(text, s.type) == 0 )

        fprintf(ff,"%s %s %s %s %s %s %s %s %s\n",
                s.id, s.type, s.prix, s.payment, s.heure,
                s.jj, s.mm, s.aa, s.confirmed);
    }

    fclose(f4);
    fclose(ff);
  }
}

// Fonction pour vérifier si un ID existe dans un fichier
// Fonction pour vérifier si un ID existe dans un fichier
int verifier_id_existe(const char *id, const char *filename, char delimiter) {
    FILE *f = fopen(filename, "r");
    if (f == NULL) {
        printf("Erreur d'ouverture du fichier %s\n", filename);
        return 0;
    }

    char ligne[500];
    char id_lu[100];

    // Formater l'ID recherché pour qu'il ait toujours 4 chiffres
    char id_formate_recherche[100];
    sprintf(id_formate_recherche, "%04d", atoi(id)); // Ajoute des zéros si nécessaire

    // Lire chaque ligne du fichier
    while (fgets(ligne, sizeof(ligne), f)) {
        ligne[strcspn(ligne, "\n")] = 0; // Nettoyer la ligne

        // Diviser la ligne en fonction des espaces multiples
        char *token = strtok(ligne, " "); // Le premier mot de la ligne correspond à l'ID
        if (token != NULL) {
            // Formater l'ID extrait pour comparaison
            char id_formate_lu[100];
            sprintf(id_formate_lu, "%04d", atoi(token));

            // Débogage : Afficher l'ID extrait et formaté
            printf("ID extrait de la ligne : '%s', ID recherché : '%s'\n", id_formate_lu, id_formate_recherche);

            if (strcmp(id_formate_recherche, id_formate_lu) == 0) {
                fclose(f);
                return 1; // ID trouvé
            }
        }
    }

    fclose(f);
    return 0; // ID non trouvé
}
int verifier_modif(const char *filename, const char *id, service *s) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        printf("Erreur d'ouverture du fichier %s\n", filename);
        return 0;
    }

    char line[256];
    while (fgets(line, sizeof(line), file)) {
        char temp[256];
        strncpy(temp, line, sizeof(temp));

        // Vérification de l'ID
        char *token = strtok(temp, " ");
        if (token && strcmp(token, id) == 0) {
            // ID trouvé, remplir la structure 'service'
            sscanf(line, "%s %s %s %s %s %s %s %s", 
                   s->id, s->type, s->prix, s->payment, 
                   s->heure, s->jj, s->mm, s->aa, s->confirmed);

            // Nettoyage de 'confirmed' pour enlever les apostrophes et espaces
            g_strstrip(s->confirmed);

            fclose(file);
            return 1; // ID trouvé
        }
    }

    fclose(file);
    return 0; // ID non trouvé
}
int affecter(const char *id_service, int id_reservation, const char *service_file, const char *reservation_file, const char *affectation_file) {
    // Vérifier si l'ID du service existe dans service.txt
    if (!verifier_id_existe(id_service, service_file, ' ')) {
        printf("Erreur d'affectation : L'ID du service %s n'existe pas dans %s\n", id_service, service_file);
        return 0;
    }

    // Formater l'ID de réservation pour qu'il ait 4 chiffres
    char id_reservation_str[100];
    sprintf(id_reservation_str, "%04d", id_reservation); // Formater avec 4 chiffres

    // Vérifier si l'ID de la réservation existe dans reservation.txt
    if (!verifier_id_existe(id_reservation_str, reservation_file, '|')) {
        printf("Erreur d'affectation : L'ID de la réservation %s n'existe pas dans %s\n", id_reservation_str, reservation_file);
        return 0;
    }

    // Si les deux ID existent, effectuer l'affectation
    FILE *f = fopen(affectation_file, "a");
    if (f != NULL) {
        fprintf(f, "Service %s affecté à la réservation %s\n", id_service, id_reservation_str);
        fclose(f);
        printf("Affectation réussie : Service %s affecté à la réservation %s\n", id_service, id_reservation_str);
        return 1;
    } else {
        printf("Erreur d'ouverture du fichier %s pour l'affectation\n", affectation_file);
        return 0;
    }
}

void afficher_affectations(GtkWidget *treeview, const char *filename) {
    FILE *file;
    char line[256];
    GtkListStore *store;
    GtkTreeIter iter;

    // Créer une nouvelle liste pour stocker les données
    store = gtk_list_store_new(1, G_TYPE_STRING); // Une seule colonne pour le texte complet

    // Ouvrir le fichier affectation.txt
    file = fopen(filename, "r");
    if (file == NULL) {
        perror("Erreur d'ouverture du fichier");
        return;
    }

    // Lire chaque ligne du fichier et ajouter au TreeView
    while (fgets(line, sizeof(line), file)) {
        // Supprimer le retour à la ligne à la fin de chaque ligne
        line[strcspn(line, "\n")] = '\0'; // Remplacer le \n par \0 pour éviter l'affichage du retour à la ligne

        // Ajouter la ligne lue dans le modèle de liste
        gtk_list_store_append(store, &iter);
        gtk_list_store_set(store, &iter, 0, line, -1); // Ajouter la ligne dans la première colonne
    }

    // Fermer le fichier
    fclose(file);

    // Affecter le modèle de données au TreeView
    gtk_tree_view_set_model(GTK_TREE_VIEW(treeview), GTK_TREE_MODEL(store));

    // Libérer la mémoire du modèle après l'utilisation
    g_object_unref(store);

    // Créer la colonne pour afficher le texte
    GtkCellRenderer *renderer;
    GtkTreeViewColumn *column;

    // Vérifier si la colonne existe déjà avant de l'ajouter
    if (gtk_tree_view_get_column(GTK_TREE_VIEW(treeview), 0) == NULL) {
        // Colonne unique pour afficher le texte complet
        renderer = gtk_cell_renderer_text_new();
        column = gtk_tree_view_column_new_with_attributes("Affectation", renderer, "text", 0, NULL);
        gtk_tree_view_append_column(GTK_TREE_VIEW(treeview), column);
    }
}


