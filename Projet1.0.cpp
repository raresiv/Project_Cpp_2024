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
#include "CRRPricer.h"
#include "AsianCallOption.h"
#include "AsianPutOption.h"
#include "AsianOption.h"
#include "EuropeanDigitalCallOption.h"
#include "EuropeanDigitalPutOption.h"

#include <vector>
#include "BlackScholesMCPricer.h"


int main()
{
    /*
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
    double optionPrice = pricer();
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

    #pragma region Partie VRAI TEST 1
    {

        double S0(95.), K(100.), T(0.5), r(0.02), sigma(0.2);
        CallOption opt1(T, K);
        PutOption opt2(T, K);


        std::cout << "European options 1" << std::endl << std::endl;

        {
            BlackScholesPricer pricer1(&opt1, S0, r, sigma);
            std::cout << "BlackScholesPricer price=" << pricer1() << ", delta=" << pricer1.delta() << std::endl;

            BlackScholesPricer pricer2(&opt2, S0, r, sigma);
            std::cout << "BlackScholesPricer price=" << pricer2() << ", delta=" << pricer2.delta() << std::endl;
            std::cout << std::endl;

            int N(150);
            double U = exp(sigma * sqrt(T / N)) - 1.0;
            double D = exp(-sigma * sqrt(T / N)) - 1.0;
            double R = exp(r * T / N) - 1.0;

            CRRPricer crr_pricer1(&opt1, N, S0, U, D, R);
            std::cout << "Calling CRR pricer with depth=" << N << std::endl;
            std::cout << std::endl;
            std::cout << "CRR pricer computed price=" << crr_pricer1() << std::endl;
            std::cout << "CRR pricer explicit formula price=" << crr_pricer1(true) << std::endl;
            std::cout << std::endl;

            CRRPricer crr_pricer2(&opt2, N, S0, U, D, R);
            std::cout << "Calling CRR pricer with depth=" << N << std::endl;
            std::cout << std::endl;
            std::cout << "CRR pricer computed price=" << crr_pricer2() << std::endl;
            std::cout << "CRR pricer explicit formula price=" << crr_pricer2(true) << std::endl;
        }
        std::cout << std::endl << "*********************************************************" << std::endl;
    }

    {
        std::cout << "Binary Tree" << std::endl << std::endl;
        BinaryTree<bool> t1;
        t1.setDepth(3);
        t1.setNode(1, 1, true);
        t1.display();
        t1.setDepth(5);
        t1.display();
        t1.setDepth(3);
        t1.display();


        BinaryTree<double> t2;
        t2.setDepth(2);
        t2.setNode(2, 1, 3.14);
        t2.display();
        t2.setDepth(4);
        t2.display();
        t2.setDepth(3);
        t2.display();

        BinaryTree<int> t3;
        t3.setDepth(4);
        t3.setNode(3, 0, 8);
        t3.display();
        t3.setDepth(2);
        t3.display();
        t3.setDepth(4);
        t3.display();

        std::cout << std::endl << "*********************************************************" << std::endl;
    }

    #pragma endregion

    #pragma region Test Partie 3

    //
    //std::vector<double> path1 = { 100,105,110,115 };//moy 107.5
    //std::vector<double> path2 = { 90,85,70,60 };//moy 76.25
    //double strikeAsian = 100;
    //double e = 1.0;
    //AsianCallOption callOptionA(e,strikeAsian, { 0.25, 0.5, 0.75, 1 });
    //AsianPutOption putOptionA(e,strikeAsian, { 0.25, 0.5, 0.75, 1 });
    //
    //// Calcul des payoffs pour chaque trajectoire 
    //double callPayoff1 = callOptionA.payoffPath(path1);
    //double callPayoff2 = callOptionA.payoffPath(path2);
    //double putPayoff1 = putOptionA.payoffPath(path1);
    //double putPayoff2 = putOptionA.payoffPath(path2); // Affichage des résultats 
    //std::cout << "Call Option Payoffs:\n"; 
    //std::cout << "Path 1: "<< callPayoff1 << "\n"; // Attendu : 7.5 
    //std::cout << "Path 2: "<< callPayoff2 << "\n"; // Attendu : 0 
    //std::cout << "\nPut Option Payoffs:\n"; 
    //std::cout << "Path 1: "<< putPayoff1 << "\n"; // Attendu : 0 
    //std::cout << "Path 2: "<< putPayoff2 << "\n"; // Attendu : 7.5 
    //// Test de l'obtention des timesteps 
    //std::cout << "\nTime steps for the options:\n"; 
    //for (double t : callOptionA.getTimeSteps())
    //{ std::cout << t << " "; } 
    //std::cout << "\n"; for (double t : putOptionA.getTimeSteps())
    //{ std::cout << t << " "; }
    //#pragma endregion


    #pragma region Vrai Test partie 3

    double S0(95.), K(100.), T(0.5), r(0.02), sigma(0.2);
    std::vector<Option*> opt_ptrs;
    opt_ptrs.push_back(new CallOption(T, K));
    opt_ptrs.push_back(new PutOption(T, K));

    std::vector<double> fixing_dates;
    for (int i = 1; i <= 5; i++) {
        fixing_dates.push_back(0.1 * i);
    }
    opt_ptrs.push_back(new AsianCallOption(fixing_dates, K));
    opt_ptrs.push_back(new AsianPutOption(fixing_dates, K));

    std::vector<double> ci;
    BlackScholesMCPricer* pricer3;

    for (auto& opt_ptr : opt_ptrs) {
        pricer3 = new BlackScholesMCPricer(opt_ptr, S0, r, sigma);
        do {
            pricer3->generate(10000);
            ci = pricer3->confidenceInterval();
            std::cout << ci[1] << "  ";
            std::cout << ci[0];
       } while (ci[1] - ci[0] > 0.1);
        std::cout << " nb samples: " << pricer3->getNbPaths() << std::endl;
        std::cout << "price: " << (*pricer3)() << std::endl << std::endl;
        delete pricer3;
        delete opt_ptr;
    }
=======
    {
    std::vector<double> path1 = { 100,105,110,115 };//moy 107.5
    std::vector<double> path2 = { 90,85,70,60 };//moy 76.25
    double strikeAsian = 100;
    double e = 1.0;
    AsianCallOption callOptionA(e,strikeAsian, { 0.25, 0.5, 0.75, 1 });
    AsianPutOption putOptionA(e,strikeAsian, { 0.25, 0.5, 0.75, 1 });
    
    // Calcul des payoffs pour chaque trajectoire 
    double callPayoff1 = callOptionA.payoffPath(path1);
    double callPayoff2 = callOptionA.payoffPath(path2);
    double putPayoff1 = putOptionA.payoffPath(path1);
    double putPayoff2 = putOptionA.payoffPath(path2); // Affichage des résultats 
    std::cout << "Call Option Payoffs:\n"; 
    std::cout << "Path 1: "<< callPayoff1 << "\n"; // Attendu : 7.5 
    std::cout << "Path 2: "<< callPayoff2 << "\n"; // Attendu : 0 
    std::cout << "\nPut Option Payoffs:\n"; 
    std::cout << "Path 1: "<< putPayoff1 << "\n"; // Attendu : 0 
    std::cout << "Path 2: "<< putPayoff2 << "\n"; // Attendu : 7.5 
    // Test de l'obtention des timesteps 
    std::cout << "\nTime steps for the options:\n"; 
    for (double t : callOptionA.getTimeSteps())
    { std::cout << t << " "; } 
    std::cout << "\n"; for (double t : putOptionA.getTimeSteps())
    { std::cout << t << " "; }
    }
    #pragma endregion

    #pragma region Test Partie salle 17
    {
        std::cout << std::endl << "*********************************************************" << std::endl;
        double S0(95.), K(100.), T(0.5), r(0.02), sigma(0.2);
        EuropeanDigitalCallOption opt1(T, K);
        EuropeanDigitalPutOption opt2(T, K);


        std::cout << "European options 2" << std::endl << std::endl;

        {
            BlackScholesPricer pricer1(&opt1, S0, r, sigma);
            std::cout << "BlackScholesPricer price=" << pricer1() << ", delta=" << pricer1.delta() << std::endl;

            BlackScholesPricer pricer2(&opt2, S0, r, sigma);
            std::cout << "BlackScholesPricer price=" << pricer2() << ", delta=" << pricer2.delta() << std::endl;

        }
        std::cout << std::endl << "*********************************************************" << std::endl;
    }
    #pragma endregion
*/
    #pragma region testExcel

    // Paramètres pour l'option et le modèle Black-Scholes
    double testExpiry = 5.0;           // Maturité (en années)
    double testStrike = 101.0;         // Prix d'exercice
    double assetPrice = 100.0;       // Prix de l'actif sous-jacent
    double interestRate = 0.01;      // Taux sans risque (5%)
    double volatility = 0.1;         // Volatilité (20%)

    // Création d'une option Call avec un nom unique pour éviter les redéfinitions
    CallOption testCallOption(testExpiry, testStrike);
    
    // Initialisation de BlackScholesPricer avec un pointeur vers l'option
    BlackScholesPricer pricer1(&testCallOption, assetPrice, interestRate, volatility);
    
    // Calcul du prix de l'option avec le paramètre requis par operator()
    double optionCall = pricer1();
    std::cout << "Prix de l'option Call avec Black-Scholes : " << optionCall << std::endl;
    
    // Création d'une option Call avec un nom unique pour éviter les redéfinitions
    PutOption testPutOption(testExpiry, testStrike);
    
    // Initialisation de BlackScholesPricer avec un pointeur vers l'option
    BlackScholesPricer pricer2(&testPutOption, assetPrice, interestRate, volatility);
    
    // Calcul du prix de l'option avec le paramètre requis par operator()
    double optionPut = pricer2();
    std::cout << "Prix de l'option Put avec Black-Scholes : " << optionPut << std::endl;
    
    EuropeanDigitalCallOption opt1(testExpiry, testStrike);
    EuropeanDigitalPutOption opt2(testExpiry, testStrike);


    std::cout << "European options 2" << std::endl << std::endl;

    BlackScholesPricer pricer3(&opt1, assetPrice, interestRate, volatility);
    std::cout << "BlackScholesPricer digital call price=" << pricer3() << ", delta=" << pricer3.delta() << std::endl;

    BlackScholesPricer pricer4(&opt2, assetPrice, interestRate, volatility);
    std::cout << "BlackScholesPricer digital put price=" << pricer4() << ", delta=" << pricer4.delta() << std::endl;

    // CRR Params
    double R = 0.01;
    double U = 0.05;
    double D = -0.045;
    double N = 5;

    CRRPricer crr_pricer_CallOption(&testCallOption, N, assetPrice, U, D, R);
    std::cout << "CRR pricer computed price=" << crr_pricer_CallOption() << std::endl;
    std::cout << std::endl;

    CRRPricer crr_pricer_PutOption(&testPutOption, N, assetPrice, U, D, R);
    std::cout << "CRR pricer computed price=" << crr_pricer_PutOption() << std::endl;
    std::cout << std::endl;

    CRRPricer crr_pricer_DigitalCallOption(&opt1, N, assetPrice, U, D, R);
    std::cout << "CRR pricer computed price=" << crr_pricer_DigitalCallOption() << std::endl;
    std::cout << std::endl;

    CRRPricer crr_pricer_DigitalPutOption(&opt2, N, assetPrice, U, D, R);
    std::cout << "CRR pricer computed price=" << crr_pricer_DigitalPutOption() << std::endl;
    std::cout << std::endl;

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
