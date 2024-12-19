#ifndef SERVICE_H_INCLUDED
#define SERVICE_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <gtk/gtk.h>
#define MAX_ID_LENGTH 100  // Définir la taille maximale pour l'ID du service


typedef struct {
    char type[20];              
    char bloc;                  
    int places_disponibles;     
} Place;

typedef struct {
    char nom[50];               
    int id_parking;             
    char adresse[100];          
    Place place;               
} Parking;

typedef struct {
    char type[10];              
    int matricule;              
} Vehicule;


typedef struct {
    char paiement[50];          
    char demande_service[50];  
} ServiceDemande;


typedef struct {
    int jour;                  
    int mois;                  
    int annee;                 
} Date;


typedef struct {
    int heure;                  
    int minute;               
} Heure;


typedef struct {
    int id_reservation;         
    Parking parking;           
    Place place;                
    Date date_reservation;     
    Heure heure_debut;          
    Heure heure_fin;            
    Vehicule vehicule;          
    ServiceDemande service;     
} ReservationDetails;

typedef struct {
    char id[100] ;                     
    char type[100];              
    char prix[100];                   
    char payment[100];           
    char heure[100];             
    char jj[100];                 
    char mm[100];                 
    char aa[100];                
    char confirmed[100]; 
     char id_reservation [100];  // Ajoutez ce champ pour stocker l'ID de la réservation
           
} service;
typedef struct {
    int id_reservation;       
    int id_service;             
} ReservationService;

typedef struct {
    int id_reservation;      
    Parking parking;           
    Place place;               
    Date dateReservation;       
    Heure heure_debut;         
    Heure heure_fin;            
    Vehicule vehicule;        
    ServiceDemande serviceComp; 
       int id;  // ou autre type si nécessaire

} Reservation;
int ajouter(char *filename, service s) ;
void modifier_service(service s, int *resultat) ;
int supprimer_Service(const char *filename, const char *id) ;
void afficher_service(GtkWidget *liste, char *noms); // Afficher dans treeview les userss
void chercher_service(service s , char text[100]);
/*int affecter(char *id_service, int id_reservation, char *filename) ;*/
int verifier_existence(const char *id, const char *filename);
int affecter(const char *id_service, int id_reservation, const char *service_file, const char *reservation_file, const char *affectation_file) ;
void afficher_affectations(GtkWidget *treeview, const char *filename);
int verifier_modif(const char *filename, const char *id, service *s);
#endif // SERVICE_H_INCLUDED

