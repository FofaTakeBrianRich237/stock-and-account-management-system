#include "Transaction.h"
#include <iostream>
#include <iomanip>
#include <cstring>
#include <vector>
#include <string>
#include <ctime>

int Transaction::compteur = 0;

Transaction::Transaction(int id) : idClient(id), statut(EN_COURS) {
    time(&date);
    idTransaction = ++compteur;
}

void Transaction::ajouterCommande(const Commande& cmd) {
    commandes.push_back(cmd);
}

bool Transaction::annulerCommande(const std::string& desc) {
    for (auto it = commandes.begin(); it != commandes.end(); ++it) {
        if (it->getDescription() == desc) {
            commandes.erase(it);
            return true;
        }
    }
    return false;
}

bool Transaction::modifierCommande(const std::string& desc, double nouveauMontant) {
    for (auto& cmd : commandes) {
        if (cmd.getDescription() == desc) {
            cmd.setMontant(nouveauMontant);
            return true;
        }
    }
    return false;
}

double Transaction::getTotal() const {
    double total = 0;
    for (const auto& cmd : commandes) {
        total += cmd.getMontantTotal();
    }
    return total;
}

time_t Transaction::getDate() const {
    return date;
}

const std::vector<Commande>& Transaction::getCommandes() const {
    return commandes;
}

int Transaction::getIdClient() const {
    return idClient;
}

int Transaction::getIdTransaction() const {
    return idTransaction;
}

StatutTransaction Transaction::getStatut() const {
    return statut;
}

std::string Transaction::getCommentaire() const {
    return commentaire;
}

void Transaction::setStatut(StatutTransaction statut) {
    this->statut = statut;
}

void Transaction::setCommentaire(const std::string& commentaire) {
    this->commentaire = commentaire;
}

void Transaction::afficher() const {
    std::cout << "Transaction ID: " << idTransaction
              << " | Client ID: " << idClient
              << " | Total: " << std::fixed << std::setprecision(2) << getTotal() << " FCFA"
              << " | Date: " << getDateString()
              << " | Statut: " << getStatutString() << std::endl;
}

std::string Transaction::getStatutString() const {
    switch(statut) {
        case EN_COURS: return "En cours";
        case VALIDEE: return "Validee";
        case ANNULEE: return "Annulee";
        case REMBOURSEE: return "Remboursee";
        default: return "Inconnu";
    }
}

std::string Transaction::getDateString() const {
    char buffer[80];
    struct tm* timeinfo = localtime(&date);
    strftime(buffer, 80, "%d/%m/%Y %H:%M:%S", timeinfo);
    return std::string(buffer);
}
