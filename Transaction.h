#ifndef TRANSACTION_H
#define TRANSACTION_H

#include <vector>
#include <string>
#include <ctime>

// Définition de l'énumération StatutTransaction
enum StatutTransaction {
    EN_COURS,
    VALIDEE,
    ANNULEE,
    REMBOURSEE
};

// Classe Commande
class Commande {
private:
    std::string description;
    double montant;
    int quantite;

public:
    Commande(const std::string& desc, double mont, int qty = 1) 
        : description(desc), montant(mont), quantite(qty) {}
    
    std::string getDescription() const { return description; }
    double getMontant() const { return montant; }
    void setMontant(double nouveauMontant) { montant = nouveauMontant; }
    double getMontantTotal() const { return montant * quantite; }
    int getQuantite() const { return quantite; }
};

class Transaction {
private:
    static int compteur;
    int idTransaction;
    int idClient;
    time_t date;
    StatutTransaction statut;
    std::string commentaire;
    std::vector<Commande> commandes;

public:
    Transaction(int id);
    
    void ajouterCommande(const Commande& cmd);
    bool annulerCommande(const std::string& desc);
    bool modifierCommande(const std::string& desc, double nouveauMontant);
    void changerStatut(const );
    void afficherToutesTransactions(const);
    void afficherTransactionSpecifique(const);
    void StatistiquesDesTransaction(const);


    double getTotal() const;
    time_t getDate() const;
    const std::vector<Commande>& getCommandes() const;
    int getIdClient() const;
    int getIdTransaction() const;
    StatutTransaction getStatut() const;
    std::string getCommentaire() const;
    
    void setStatut(StatutTransaction statut);
    void setCommentaire(const std::string& commentaire);
    
    void afficher() const;
    std::string getStatutString() const;
    std::string getDateString() const;
};

#endif
