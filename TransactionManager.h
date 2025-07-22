#ifndef TRANSACTION_MANAGER_H
#define TRANSACTION_MANAGER_H

#include "Transaction.h"
#include <vector>
#include <map>
#include <string>

class TransactionManager {
private:
    std::vector<Client> clients;
    std::vector<Transaction> historique;
    std::string fichierDonnees;

public:
    TransactionManager(const std::string& fichier = "donnees.txt");
    
    // Gestion des clients
    void ajouterClient(int id, const std::string& nom, const std::string& email = "", const std::string& telephone = "");
    bool supprimerClient(int id);
    Client* trouverClient(int id);
    void afficherClients() const;
    std::vector<Client> rechercherClients(const std::string& critere) const;
    
    // Gestion des transactions
    void enregistrerTransaction(int idClient, const std::vector<Commande>& commandes);
    void afficherHistorique() const;
    void afficherHistoriqueDetaille() const;
    Transaction* trouverTransaction(int idTransaction);
    std::vector<Transaction> rechercherTransactions(int idClient) const;
    
    // Modification des commandes
    bool annulerCommandeDansTransaction(int idTrans, const std::string& desc);
    bool modifierCommandeDansTransaction(int idTrans, const std::string& desc, double nouveauMontant);
    bool changerStatutTransaction(int idTrans, StatutTransaction nouveauStatut);
    
    // Rapports et statistiques
    void genererRapportVentes() const;
    void genererRapportClients() const;
    double calculerChiffreAffaires() const;
    std::map<std::string, int> getStatistiquesCommandes() const;
    
    // Sauvegarde et chargement
    bool sauvegarderDonnees() const;
    bool chargerDonnees();
    
    // Utilitaires
    int getNombreClients() const;
    int getNombreTransactions() const;
};

#endif
