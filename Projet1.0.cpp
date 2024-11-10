// Projet1.0.cpp : Ce fichier contient la fonction 'main'. L'exécution du programme commence et se termine à cet endroit.
//

#include <iostream>

#include "Option.h"
#include "CallOption.h"
#include "PutOption.h"
#include "BlackScholesPricer.h"
#include "EuropeanVanillaOption.h"
#include "optionType.h"
#include "BinaryTree.h"

int main()
{
    std::cout << "Hello World!\n";

    std::cout << "test eloi";

    std::cout << "test lou";

    #pragma region PARTIE 1 TEST
    // TEST CALLOPTION
    double maturity = 1.0;            
    double strikePrice = 100.0;      
    double spotPriceAtMaturity = 105.0;
    
    // Création de l'option avec la maturité d'abord, puis le strike
    CallOption callOption(maturity, strikePrice);
    
    double payoff = callOption.payoff(spotPriceAtMaturity);
    std::cout << "Le payoff de l'option Call est : " << payoff << std::endl;
    
    // Vérification pour afficher un message de succès ou d'erreur
    if (payoff == std::max(spotPriceAtMaturity - strikePrice, 0.0)) {
        std::cout << "Le calcul du payoff est correct." << std::endl;
    }
    else {
        std::cout << "Erreur dans le calcul du payoff." << std::endl;
    }
    
    
    // TEST PUTOPTION
    double expiry = 1.0;          // Maturité (en années)
    double strike = 100.0;        // Prix d'exercice
    double spotPrice1 = 95.0;     // Prix du sous-jacent < strike
    double spotPrice2 = 105.0;    // Prix du sous-jacent > strike
    
    // Création de l'option Put
    PutOption putOption(expiry, strike);
    
    // Test du payoff pour un prix du sous-jacent inférieur au strike
    double payoff1 = putOption.payoff(spotPrice1);
    std::cout << "Payoff pour spotPrice = 95 : " << payoff1 << " (attendu : 5)" << std::endl;
    
    // Test du payoff pour un prix du sous-jacent supérieur au strike
    double payoff2 = putOption.payoff(spotPrice2);
    std::cout << "Payoff pour spotPrice = 105 : " << payoff2 << " (attendu : 0)" << std::endl;
    
    // TEST BLACKSCHOLES PRICER
    
    // Paramètres pour l'option et le modèle Black-Scholes
    double testExpiry = 1.0;           // Maturité (en années)
    double testStrike = 100.0;         // Prix d'exercice
    double assetPrice = 100.0;       // Prix de l'actif sous-jacent
    double interestRate = 0.05;      // Taux sans risque (5%)
    double volatility = 0.2;         // Volatilité (20%)
    
    // Création d'une option Call avec un nom unique pour éviter les redéfinitions
    CallOption testCallOption(expiry, strike);
    
    // Initialisation de BlackScholesPricer avec un pointeur vers l'option
    BlackScholesPricer pricer(&testCallOption, assetPrice, interestRate, volatility);
    
    // Calcul du prix de l'option avec le paramètre requis par operator()
    double optionPrice = pricer(pricer);
    std::cout << "Prix de l'option Call avec Black-Scholes : " << optionPrice << " (valeur attendue : environ 10.45)" << std::endl;
    
    // Calcul du Delta de l'option
    double delta = pricer.delta();
    std::cout << "Delta de l'option Call : " << delta << " (valeur attendue : environ 0.6368)" << std::endl;
    
    #pragma endregion

    #pragma region PARTIE 2 TEST
    // Crée un arbre binaire de profondeur 4
    BinaryTree<int> arbre(4);

    // Ajoute des valeurs dans l'arbre
    arbre.setNode(0, 0, 10);
    arbre.setNode(1, 0, 20);
    arbre.setNode(1, 1, 30);
    arbre.setNode(2, 0, 40);
    arbre.setNode(2, 1, 50);
    arbre.setNode(2, 2, 60);

    // Affiche l'arbre
    std::cout << "Affichage de l'arbre binaire :\n";
    arbre.display();

    // Récupère une valeur spécifique
    int valeur = arbre.getNode(1, 1);
    std::cout << "\nValeur au niveau 1, position 1 : " << valeur << std::endl;
    #pragma endregion



    return 0;
}

// Exécuter le programme : Ctrl+F5 ou menu Déboguer > Exécuter sans débogage
// Déboguer le programme : F5 ou menu Déboguer > Démarrer le débogage

// Astuces pour bien démarrer : 
//   1. Utilisez la fenêtre Explorateur de solutions pour ajouter des fichiers et les gérer.
//   2. Utilisez la fenêtre Team Explorer pour vous connecter au contrôle de code source.
//   3. Utilisez la fenêtre Sortie pour voir la sortie de la génération et d'autres messages.
//   4. Utilisez la fenêtre Liste d'erreurs pour voir les erreurs.
//   5. Accédez à Projet > Ajouter un nouvel élément pour créer des fichiers de code, ou à Projet > Ajouter un élément existant pour ajouter des fichiers de code existants au projet.
//   6. Pour rouvrir ce projet plus tard, accédez à Fichier > Ouvrir > Projet et sélectionnez le fichier .sln.
