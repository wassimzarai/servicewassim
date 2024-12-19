#ifdef HAVE_CONFIG_H
#  include <config.h>
#endif
#include <gtk/gtk.h>
#include <string.h>
#include <gtk/gtk.h>
#include "service.h"
#include "callbacks.h"
#include "interface.h"
#include "support.h"

service s1;
 Reservation r1 ;
int carte;
int heure;
int confirm;
int espece;

void
on_ajouter_button1__clicked            (GtkButton       *button,
                                        gpointer         user_data)
{
gtk_notebook_next_page(GTK_NOTEBOOK(lookup_widget(button, "notebook1")));
}


void
on_modifier_button2_clicked            (GtkButton       *button,
                                        gpointer         user_data)
{
gtk_entry_set_text(GTK_ENTRY(lookup_widget(button, "idmod_entry3")), s1.id);
gtk_entry_set_text(GTK_ENTRY(lookup_widget(button,"comboboxentry1")), s1.type);

    gtk_notebook_next_page(GTK_NOTEBOOK(lookup_widget(button, "notebook1")));
    gtk_notebook_next_page(GTK_NOTEBOOK(lookup_widget(button, "notebook1")));

}


void
on_supprimer_button3_clicked           (GtkButton       *button,
                                        gpointer         user_data)
{
gtk_notebook_next_page(GTK_NOTEBOOK(lookup_widget(button, "notebook1")));
gtk_notebook_next_page(GTK_NOTEBOOK(lookup_widget(button, "notebook1")));
gtk_notebook_next_page(GTK_NOTEBOOK(lookup_widget(button, "notebook1")));


}


void
on_actualiser_button4_clicked          (GtkButton       *button,
                                        gpointer         user_data)
{
GtkWidget *treeview1;
    treeview1 = lookup_widget(button, "treeview1");
    afficher_service(treeview1, "service.txt");
}



void
on_rechercher_button5_clicked          (GtkButton       *button,
                                        gpointer         user_data)
{service s ;
    char text[100];
    GtkWidget *treeview1;
    GtkWidget *input;

    input = lookup_widget(button, "idrechercher_entry1");
    strcpy(text, gtk_entry_get_text(GTK_ENTRY(input)));
    treeview1 = lookup_widget(button, "treeview1");
    chercher_service(s, text);
    afficher_service(treeview1, "rechservice.txt");

}


void
on_carte_radiobutton1_toggled          (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{
if (gtk_toggle_button_get_active(togglebutton))

        carte = 1;

}


void
on_carte_radiobutton2_toggled          (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{
if (gtk_toggle_button_get_active(togglebutton))

        carte = 2;


}


void
on_checkbutton1_toggled                (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{

}


void
on_annuler_button7_clicked             (GtkButton       *button,
                                        gpointer         user_data)
{
gtk_notebook_prev_page(GTK_NOTEBOOK(lookup_widget(button, "notebook1")));

}


void
on_ajouter_button6_clicked             (GtkButton       *button,
                                        gpointer         user_data)
{
service s;
int   jj, mm, aa , id, prix  ;
GtkWidget *idservices_entry2, *typesajou_comboboxentry1, *prix_spinbutton1, *carte_radiobutton1, *carte_radiobutton2, *jj_spinbutton2,*mm_spinbutton3,*aa_spinbutton4,*matin_radiobutton3,*apresmidi_radiobutton4,*checkbutton1;


      idservices_entry2  = lookup_widget(button, "idservices_entry2");
   typesajou_comboboxentry1 = lookup_widget(button, "typesajou_comboboxentry1");
    jj_spinbutton2 = lookup_widget(button, "jj_spinbutton2");
    mm_spinbutton3 = lookup_widget(button, "mm_spinbutton3");
    aa_spinbutton4 = lookup_widget(button, "aa_spinbutton4");
prix_spinbutton1 = lookup_widget(button, "prix_spinbutton1");
    jj = gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(jj_spinbutton2));
    mm = gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(mm_spinbutton3));
    aa = gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(aa_spinbutton4));   
    prix=gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(prix_spinbutton1));
	
strcpy(s.id, gtk_entry_get_text(GTK_ENTRY(idservices_entry2)));

strcpy(s.type, gtk_combo_box_get_active_text(GTK_COMBO_BOX(typesajou_comboboxentry1)));
sprintf(s.jj, "%d", jj);
sprintf(s.mm, "%d", mm);
sprintf(s.aa, "%d", aa);
sprintf(s.prix, "%d", prix);
if (carte == 1)
strcpy(s.payment, "carte");
else
strcpy(s.payment, "espece");

if (heure == 3)
strcpy(s.heure, "matin");
else
strcpy(s.heure, "apres-midi");
if (confirm == 5)
strcpy(s.confirmed, "No");
else
strcpy(s.confirmed, "YEs");

 if (ajouter("service.txt", s)) {
        GtkWidget *success_dialog = gtk_message_dialog_new(GTK_WINDOW(gtk_widget_get_toplevel(GTK_WIDGET(button))),
                                                          GTK_DIALOG_MODAL,
                                                          GTK_MESSAGE_INFO,
                                                          GTK_BUTTONS_OK,
                                                          "service ajouté avec succès !");
        gtk_dialog_run(GTK_DIALOG(success_dialog));
        gtk_widget_destroy(success_dialog);
    } else {
        GtkWidget *error_dialog = gtk_message_dialog_new(GTK_WINDOW(gtk_widget_get_toplevel(GTK_WIDGET(button))),
                                                        GTK_DIALOG_MODAL,
                                                        GTK_MESSAGE_ERROR,
                                                        GTK_BUTTONS_OK,
                                                        "Erreur lors de l'ajout du service !");
        gtk_dialog_run(GTK_DIALOG(error_dialog));
        gtk_widget_destroy(error_dialog);
    }
}



void
on_cartemod_radiobutton5_toggled       (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{
if (gtk_toggle_button_get_active(togglebutton))

        carte = 3;


}


void
on_especesmod_radiobutton6_toggled     (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{
if (gtk_toggle_button_get_active(togglebutton))

        carte = 4;

}


void
on_matinmod_radiobutton7_toggled       (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{
if (gtk_toggle_button_get_active(togglebutton))

        carte = 5;

}


void
on_apresmidi_radiobutton8_toggled      (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{
if (gtk_toggle_button_get_active(togglebutton))

        carte = 6;

}


void
on_checkbutton2_toggled                (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{

}


void
on_anuller_button9_clicked             (GtkButton       *button,
                                        gpointer         user_data)
{
gtk_notebook_prev_page(GTK_NOTEBOOK(lookup_widget(button, "notebook1")));
gtk_notebook_prev_page(GTK_NOTEBOOK(lookup_widget(button, "notebook1")));

}

void on_modifier_button8_clicked(GtkButton *button, gpointer user_data) {
    service s;
    int jj, mm, aa, prix;
    int resultat = 0; // Variable pour stocker le résultat de la modification
    GtkWidget *idmod_entry3, *typemod_comboboxentry2, *prixmod_spinbutton5;
    GtkWidget *jj_spinbutton6, *mm_spinbutton7, *aa_spinbutton8;
    GtkWidget *matinmod_radiobutton7, *apresmidi_radiobutton8;
    GtkWidget *cartemod_radiobutton5, *especesmod_radiobutton6;
    GtkWidget *checkbutton2;

    // Récupérer les widgets
    idmod_entry3 = lookup_widget(button, "idmod_entry3");
    typemod_comboboxentry2 = lookup_widget(button, "typemod_comboboxentry2");
    prixmod_spinbutton5 = lookup_widget(button, "prixmod_spinbutton5");
    jj_spinbutton6 = lookup_widget(button, "jj_spinbutton6");
    mm_spinbutton7 = lookup_widget(button, "mm_spinbutton7");
    aa_spinbutton8 = lookup_widget(button, "aa_spinbutton8");
    cartemod_radiobutton5 = lookup_widget(button, "cartemod_radiobutton5");
    especesmod_radiobutton6 = lookup_widget(button, "especesmod_radiobutton6");
    matinmod_radiobutton7 = lookup_widget(button, "matinmod_radiobutton7");
    apresmidi_radiobutton8 = lookup_widget(button, "apresmidi_radiobutton8");
    checkbutton2 = lookup_widget(button, "checkbutton2");

    // Récupération des valeurs
    jj = gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(jj_spinbutton6));
    mm = gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(mm_spinbutton7));
    aa = gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(aa_spinbutton8));
    prix = gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(prixmod_spinbutton5));

    // Remplir la structure
    strcpy(s.id, gtk_entry_get_text(GTK_ENTRY(idmod_entry3)));
    strcpy(s.type, gtk_combo_box_get_active_text(GTK_COMBO_BOX(typemod_comboboxentry2)));

    sprintf(s.jj, "%d", jj);
    sprintf(s.mm, "%d", mm);
    sprintf(s.aa, "%d", aa);
    sprintf(s.prix, "%d", prix);

    if (gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(cartemod_radiobutton5)))
        strcpy(s.payment, "carte");
    else
        strcpy(s.payment, "espece");

    if (gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(matinmod_radiobutton7)))
        strcpy(s.heure, "matin");
    else
        strcpy(s.heure, "apres-midi");

    if (gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(checkbutton2)))
        strcpy(s.confirmed, "Yes");
    else
        strcpy(s.confirmed, "No");

    // Appeler la fonction de modification avec passage par référence pour 'resultat'
    modifier_service(s, &resultat);

    // Vérifier le résultat de la modification
    if (resultat == 1) {
        GtkWidget *success_dialog = gtk_message_dialog_new(
            GTK_WINDOW(gtk_widget_get_toplevel(GTK_WIDGET(button))),
            GTK_DIALOG_MODAL,
            GTK_MESSAGE_INFO,
            GTK_BUTTONS_OK,
            "Service modifié avec succès !");
        gtk_dialog_run(GTK_DIALOG(success_dialog));
        gtk_widget_destroy(success_dialog);
    } else if (resultat == 6) {
        // Si l'ID n'a pas été trouvé, afficher un message d'erreur spécifique
        GtkWidget *error_dialog = gtk_message_dialog_new(
            GTK_WINDOW(gtk_widget_get_toplevel(GTK_WIDGET(button))),
            GTK_DIALOG_MODAL,
            GTK_MESSAGE_ERROR,
            GTK_BUTTONS_OK,
            "Erreur : L'ID spécifié n'a pas été trouvé !");
        gtk_dialog_run(GTK_DIALOG(error_dialog));
        gtk_widget_destroy(error_dialog);
    } else {
        GtkWidget *error_dialog = gtk_message_dialog_new(
            GTK_WINDOW(gtk_widget_get_toplevel(GTK_WIDGET(button))),
            GTK_DIALOG_MODAL,
            GTK_MESSAGE_ERROR,
            GTK_BUTTONS_OK,
            "Erreur : La modification du service a échoué !");
        gtk_dialog_run(GTK_DIALOG(error_dialog));
        gtk_widget_destroy(error_dialog);
    }
}

void on_supprimer_button10_clicked(GtkButton *button, gpointer user_data) {
    GtkWidget *idservicessup_entry4;
    char id[50];

    // Récupérer le champ de saisie pour l'ID
    idservicessup_entry4 = lookup_widget(GTK_WIDGET(button), "idservicessup_entry4");
    strcpy(id, gtk_entry_get_text(GTK_ENTRY(idservicessup_entry4)));

    // Vérifier si l'ID est vide
    if (strlen(id) == 0) {
        g_print("Erreur : Veuillez entrer un ID valide.\n");
        return;
    }

    // Appeler la fonction de suppression et vérifier le résultat
    if (supprimer_Service("service.txt", id)) {
     GtkWidget *success_dialog = gtk_message_dialog_new(GTK_WINDOW(gtk_widget_get_toplevel(GTK_WIDGET(button))),
                                                          GTK_DIALOG_MODAL,
                                                          GTK_MESSAGE_INFO,
                                                          GTK_BUTTONS_OK,
                                                          "service supprimer  avec succès !");
        gtk_dialog_run(GTK_DIALOG(success_dialog));
        gtk_widget_destroy(success_dialog);

    } else {
 GtkWidget *error_dialog = gtk_message_dialog_new(GTK_WINDOW(gtk_widget_get_toplevel(GTK_WIDGET(button))),
                                                        GTK_DIALOG_MODAL,
                                                        GTK_MESSAGE_ERROR,
                                                        GTK_BUTTONS_OK,
                                                        "Erreur lors de  supprimer du service !");
        gtk_dialog_run(GTK_DIALOG(error_dialog));
        gtk_widget_destroy(error_dialog);

      
    }
}


void
on_annuleraff_button13_clicked         (GtkButton       *button,
                                        gpointer         user_data)
{

}


void
on_affecter_button12_clicked           (GtkButton       *button,
                                        gpointer         user_data)
{  service s;
    Reservation r;

    // Récupérer les valeurs des champs de texte GTK
    GtkWidget *idaffecter_entry5, *idparking_entry6;
    idaffecter_entry5 = lookup_widget(button, "idaffecter_entry5");
    idparking_entry6 = lookup_widget(button, "idparking_entry6");

    // Vérifier si les widgets sont valides avant de récupérer les textes
    if (idaffecter_entry5 != NULL && idparking_entry6 != NULL) {
        // Récupérer l'ID du service (chaîne de caractères)
        const char *service_id_text = gtk_entry_get_text(GTK_ENTRY(idaffecter_entry5));
        if (service_id_text != NULL && strlen(service_id_text) > 0) {
            strcpy(s.id, service_id_text);  // Assurez-vous que s.id est un tableau de caractères
            printf("ID du service : %s\n", s.id);
        } else {
            printf("Erreur : L'ID du service est vide ou invalide\n");
            return;  // Quitter si l'ID du service est invalide
        }

        // Récupérer l'ID de la réservation (convertir en entier)
        const char *reservation_id_text = gtk_entry_get_text(GTK_ENTRY(idparking_entry6));
        r.id = atoi(reservation_id_text);  // Assurez-vous que r.id est un entier valide
        printf("ID de la réservation : %d\n", r.id);

        // Appeler la fonction d'affectation
    if (affecter(s.id, r.id, "service.txt", "reservation.txt", "affectation.txt")) {
  GtkWidget *success_dialog = gtk_message_dialog_new(GTK_WINDOW(gtk_widget_get_toplevel(GTK_WIDGET(button))),
                                                          GTK_DIALOG_MODAL,
                                                          GTK_MESSAGE_INFO,
                                                          GTK_BUTTONS_OK,
                                                          "service affecté avec succès !");
        gtk_dialog_run(GTK_DIALOG(success_dialog));
        gtk_widget_destroy(success_dialog);
    } else {
        GtkWidget *error_dialog = gtk_message_dialog_new(GTK_WINDOW(gtk_widget_get_toplevel(GTK_WIDGET(button))),
                                                        GTK_DIALOG_MODAL,
                                                        GTK_MESSAGE_ERROR,
                                                        GTK_BUTTONS_OK,
                                                        "Erreur lors de l'affecté du service !");
        gtk_dialog_run(GTK_DIALOG(error_dialog));
        gtk_widget_destroy(error_dialog);
    }
}
}
void
on_treeview1_row_activated             (GtkTreeView     *treeview,
                                        GtkTreePath     *path,
                                        GtkTreeViewColumn *column,
                                        gpointer         user_data)
{  GtkTreeIter iter;
    gchar *id;
    gchar *type;
    gchar *prix;
    gchar *payment;
    gchar *heure;
    gchar *jj;
    gchar *mm;
    gchar *aa;
    gchar *confirmed;

    service s ;

    GtkTreeModel *model = gtk_tree_view_get_model(treeview);

    if (gtk_tree_model_get_iter(model, &iter, path))
    {
        gtk_tree_model_get(GTK_TREE_MODEL(model), &iter, 0, &id, 1, &type, 2, &prix, 3, &payment,  4,&heure, 5, &jj, 6, &mm, 7, &aa, 8, &confirmed, -1);

        strcpy(s.id, id);
        strcpy(s.type, type);

        strcpy(s.prix, prix);
        strcpy(s.payment, payment);
        strcpy(s.heure, heure);
        strcpy(s.jj, jj);
        strcpy(s.mm, mm);
        strcpy(s.aa, aa);
	strcpy(s.confirmed, confirmed);
        s1 = s;
    }
}



void
on_treeviewaffecter_row_activated      (GtkTreeView     *treeview,
                                        GtkTreePath     *path,
                                        GtkTreeViewColumn *column,
                                        gpointer         user_data)
{   GtkTreeModel *model;
    GtkTreeIter iter;
    int service_id, reservation_id;  // Service ID et Reservation ID doivent être de type int

    // Récupérer le modèle de données du TreeView
    model = gtk_tree_view_get_model(treeview);

    // Accéder à l'itérateur de la ligne activée
    if (gtk_tree_model_get_iter(model, &iter, path)) {
        // Extraire les données des colonnes
        gtk_tree_model_get(model, &iter, &service_id, 0, &reservation_id , 1, -1);

        // Afficher les informations dans la console
        printf("Service ID: %d\n", service_id);
        printf("Reservation ID: %d\n", reservation_id);

        // Afficher les informations dans une boîte de dialogue
        char message[256];
        snprintf(message, sizeof(message), "Service  d ' id %d affecté à la réservation  d 'id %d", service_id, reservation_id);
        GtkWidget *dialog = gtk_message_dialog_new(NULL, GTK_DIALOG_MODAL, GTK_MESSAGE_INFO, GTK_BUTTONS_OK, "%s", message);
        gtk_dialog_run(GTK_DIALOG(dialog));
        gtk_widget_destroy(dialog);
    }
}
void
on_button1_clicked                     (GtkButton       *button,
                                        gpointer         user_data)
{ GtkWidget *treeviewaffecter;
    treeviewaffecter = lookup_widget(button, "treeviewaffecter");
    afficher_affectations(treeviewaffecter, "affectation.txt");  
}


void
on_verifier_clicked                    (GtkButton       *button,
                                        gpointer         user_data)
{
  GtkWidget *idmod_entry3, *typemod_comboboxentry2, *prixmod_spinbutton5;
    GtkWidget *jj_spinbutton6, *mm_spinbutton7, *aa_spinbutton8;
    GtkWidget *cartemod_radiobutton5, *especesmod_radiobutton6;
    GtkWidget *matinmod_radiobutton7, *apresmidi_radiobutton8, *checkbutton2;
    char id[100];
    service s;

    // Récupération des widgets
    idmod_entry3 = lookup_widget(GTK_WIDGET(button), "idmod_entry3");
    typemod_comboboxentry2 = lookup_widget(GTK_WIDGET(button), "typemod_comboboxentry2");
    prixmod_spinbutton5 = lookup_widget(GTK_WIDGET(button), "prixmod_spinbutton5");
    jj_spinbutton6 = lookup_widget(GTK_WIDGET(button), "jj_spinbutton6");
    mm_spinbutton7 = lookup_widget(GTK_WIDGET(button), "mm_spinbutton7");
    aa_spinbutton8 = lookup_widget(GTK_WIDGET(button), "aa_spinbutton8");
    cartemod_radiobutton5 = lookup_widget(GTK_WIDGET(button), "cartemod_radiobutton5");
    especesmod_radiobutton6 = lookup_widget(GTK_WIDGET(button), "especesmod_radiobutton6");
    matinmod_radiobutton7 = lookup_widget(GTK_WIDGET(button), "matinmod_radiobutton7");
    apresmidi_radiobutton8 = lookup_widget(GTK_WIDGET(button), "apresmidi_radiobutton8");
    checkbutton2 = lookup_widget(GTK_WIDGET(button), "checkbutton2");

    // Récupérer l'ID entré par l'utilisateur
    strcpy(id, gtk_entry_get_text(GTK_ENTRY(idmod_entry3)));

    // Vérification de l'existence de l'ID dans le fichier
    if (!verifier_modif("service.txt", id, &s)) {
        
    }

    // Pré-remplir le champ ID
    gtk_entry_set_text(GTK_ENTRY(idmod_entry3), s.id);

    // Pré-remplir le type dans le combobox
    GtkTreeModel *model = gtk_combo_box_get_model(GTK_COMBO_BOX(typemod_comboboxentry2));
    GtkTreeIter iter;
    gboolean valid = gtk_tree_model_get_iter_first(model, &iter);

    while (valid) {
        gchar *current_text;
        gtk_tree_model_get(model, &iter, 0, &current_text, -1);

        // Comparaison du type
        if (g_strcmp0(g_strstrip(current_text), g_strstrip(s.type)) == 0) {
            gtk_combo_box_set_active_iter(GTK_COMBO_BOX(typemod_comboboxentry2), &iter);
            g_free(current_text);
            break;
        }
        g_free(current_text);
        valid = gtk_tree_model_iter_next(model, &iter);
    }

    // Remplir les autres champs
    gtk_spin_button_set_value(GTK_SPIN_BUTTON(prixmod_spinbutton5), atof(s.prix));  // Prix
    gtk_spin_button_set_value(GTK_SPIN_BUTTON(jj_spinbutton6), atoi(s.jj)); // Jour
    gtk_spin_button_set_value(GTK_SPIN_BUTTON(mm_spinbutton7), atoi(s.mm)); // Mois
    gtk_spin_button_set_value(GTK_SPIN_BUTTON(aa_spinbutton8), atoi(s.aa)); // Année

    // Mettre à jour les boutons radio pour le mode de paiement
    if (strcmp(s.payment, "carte") == 0) {
        gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(cartemod_radiobutton5), TRUE);
        gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(especesmod_radiobutton6), FALSE);
    } else {
        gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(cartemod_radiobutton5), FALSE);
        gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(especesmod_radiobutton6), TRUE);
    }

    // Mettre à jour les boutons radio pour l'heure
    if (strcmp(s.heure, "matin") == 0) {
        gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(matinmod_radiobutton7), TRUE);
        gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(apresmidi_radiobutton8), FALSE);
    } else {
        gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(matinmod_radiobutton7), FALSE);
        gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(apresmidi_radiobutton8), TRUE);
    }

    // Mettre à jour la case de confirmation (checkbutton)
    g_strstrip(s.confirmed);
    gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(checkbutton2), strcmp(s.confirmed, "YEs") == 0);

    printf("Données pré-remplies pour l'ID : %s\n", s.id);
}
/*
void
on_ajs_button2_clicked                 (GtkButton       *button,
                                        gpointer         user_data)
{

}


void
on_mdfsbutton3_clicked                 (GtkButton       *button,
                                        gpointer         user_data)
{

}


void
on_mdfebutton4_clicked                 (GtkButton       *button,
                                        gpointer         user_data)
{


}


void
on_sups_button5_clicked                (GtkButton       *button,
                                        gpointer         user_data)
{
}


void
on_supebutton6_clicked                 (GtkButton       *button,
                                        gpointer         user_data)
{g
}


void
on_affsbutton7_clicked                 (GtkButton       *button,
                                        gpointer         user_data)
{



}


void
on_echecaffbutton8_clicked             (GtkButton       *button,
                                        gpointer         user_data)
{

}
*/

void
on_affecterservicebutton2_clicked      (GtkButton       *button,
                                        gpointer         user_data)
{gtk_notebook_next_page(GTK_NOTEBOOK(lookup_widget(button, "notebook1")));
gtk_notebook_next_page(GTK_NOTEBOOK(lookup_widget(button, "notebook1")));
gtk_notebook_next_page(GTK_NOTEBOOK(lookup_widget(button, "notebook1")));
gtk_notebook_next_page(GTK_NOTEBOOK(lookup_widget(button, "notebook1")));


}


void
on_acceuiservicebutton2_clicked        (GtkButton       *button,
                                        gpointer         user_data)
{gtk_notebook_prev_page(GTK_NOTEBOOK(lookup_widget(button, "notebook1")));

}


void
on_modfierservicebutton3_clicked       (GtkButton       *button,
                                        gpointer         user_data)
{
gtk_notebook_prev_page(GTK_NOTEBOOK(lookup_widget(button, "notebook1")));
gtk_notebook_prev_page(GTK_NOTEBOOK(lookup_widget(button, "notebook1")));
}


void
on_button4_clicked                     (GtkButton       *button,
                                        gpointer         user_data)
{gtk_notebook_prev_page(GTK_NOTEBOOK(lookup_widget(button, "notebook1")));
gtk_notebook_prev_page(GTK_NOTEBOOK(lookup_widget(button, "notebook1")));

}


void
on_affservicebutton5_clicked           (GtkButton       *button,
                                        gpointer         user_data)
{
gtk_notebook_prev_page(GTK_NOTEBOOK(lookup_widget(button, "notebook1")));
gtk_notebook_prev_page(GTK_NOTEBOOK(lookup_widget(button, "notebook1")));
gtk_notebook_prev_page(GTK_NOTEBOOK(lookup_widget(button, "notebook1")));
}

