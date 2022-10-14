
#include "test.hpp"

#include "../zlasdtest/test.hpp"

#include "../zlasdtest/container/container.hpp"

#include <random>

#include <iomanip>

void menu(){

    unsigned int scelta;
    char scelta_struttura;
    char scelta_tipo;
    unsigned long scelta_dim;


    while (true){

        std::cout << "Lasd Libraries 2022" << std::endl;
        std::cout << "Menù:" << std::endl;
        std::cout << "1) Test semplice" << std::endl;
        std::cout << "2) Test completo del docente" << std::endl;
        std::cout << "3) Uscita" << std::endl;


        std::cin >> scelta;

        switch (scelta){
        case 1:

            std::cout << "Scelta della struttura dati da testare( (V)ector, (L)ist )" << std::endl;
            std::cin >> scelta_struttura;

            if (scelta_struttura == 'V'){

                std::cout << "Di che tipo vuoi che sia la struttura? ( (I)nt, (D)ouble, (S)tring )" << std::endl;
                std::cin >> scelta_tipo;

                switch (scelta_tipo){
                case 'I':

                    std::cout << "Di che dimensione vuoi la struttura?" << std::endl;
                    std::cin >> scelta_dim;
                    VectorTest<int>(scelta_dim, scelta_tipo);    //Vector di interi di dimensione n
                    
                    break;
                
                case 'D':

                    std::cout << "Di che dimensione vuoi la struttura?" << std::endl;
                    std::cin >> scelta_dim;
                    VectorTest<double>(scelta_dim, scelta_tipo);   //Vector di long di dimensione n

                    break;

                case 'S':

                    std::cout << "Di che dimensione vuoi la struttura?" << std::endl;
                    std::cin >> scelta_dim;
                    VectorTest<std::string>(scelta_dim, scelta_tipo);   //Vector di stringhe di dimensione n

                    break;

                default:

                    std::cout << "Scelta non riconosciuta" << std::endl;
                    
                    break;
                }
                
            }else if (scelta_struttura == 'L'){

                std::cout << "Di che tipo vuoi che sia la struttura? ( (I)nt, (D)ouble, (S)tring )" << std::endl;
                std::cin >> scelta_tipo;

                switch (scelta_tipo){
                case 'I':

                    std::cout << "Di che dimensione vuoi la struttura?" << std::endl;
                    std::cin >> scelta_dim;
                    ListTest<int>(scelta_dim, scelta_tipo);
                                        
                    break;
                
                case 'D':

                    std::cout << "Di che dimensione vuoi la struttura?" << std::endl;
                    std::cin >> scelta_dim;
                    ListTest<double>(scelta_dim, scelta_tipo);
                    
                    break;

                case 'S':

                    std::cout << "Di che dimensione vuoi la struttura?" << std::endl;
                    std::cin >> scelta_dim;
                    ListTest<std::string>(scelta_dim, scelta_tipo);
                    
                    break;

                default:

                    std::cout << "Scelta non riconosciuta" << std::endl;
                    
                    break;
                }
                
                break;
            
        case 2:

            lasdtest(); // To call in the menu of your library test!

        break;

        case 3:

            return;

        default:

            std::cout << "Scelta non riconosciuta";

        break;

        }

        std::cout << std::endl << std::endl << std::endl;

        }
    }
}

template <typename Data>
void elemTest(lasd::LinearContainer<Data>& struttura){

    unsigned long scelta_indice;
    std::cout << "Quale elemento vuoi visualizzare?( (1)Front, (" << struttura.Size() <<")Back, (2...n-1)Indice)" <<std::endl;
    std::cin >> scelta_indice;

    if(scelta_indice == 1){

        std::cout<< "L'elemento in testa alla struttura è:" << struttura.Front() << std::endl;

    }else if (scelta_indice == struttura.Size()){

        std::cout<< "L'elemento in coda alla struttura è:" << struttura.Back() << std::endl;

    }else{

        std::cout << "L'elemento all'indice " << scelta_indice << " è " << struttura[scelta_indice-1] << std::endl;

    }

}

template <typename Data>
void exitsTest(lasd::FoldableContainer<Data>& struttura){

    Data elemento;
        
    std::cout << "Inserire l'elemento che vuoi cercare:" << std::endl;
    std::cin >> elemento;

    if (struttura.Exists(elemento)){

        std::cout << "L'elemento è presente nella struttura" << std::endl;

    }else{

        std::cout << "L'elemento non è presente nella struttura" << std::endl;

    }
}

// Map Test
template <typename Data>
void mapPrintDouble(Data& dato, void* parametro){

    std::cout << std::setprecision(22) << dato << std::endl;

}

void mapDouble(int& dato, void* parametro){

    std::cout << dato * 2 << std::endl;

}

void specificTest(lasd::PreOrderMappableContainer<int>& struttura){

    struttura.MapPreOrder(&mapDouble, 0);

}

void mapPow(double& dato, void* parametro){

    std::cout << dato * dato << std::endl;

}

void specificTest(lasd::PreOrderMappableContainer<double>& struttura){

    struttura.MapPreOrder(&mapPow, 0);

}

void mapUpperCase(std::string& dato, void* parametro){

    for(unsigned int index = 0; index < dato.size(); index++){

        std::cout << static_cast<char>(std::toupper(dato[index]));

    }

    std::cout << std::endl;
}

void specificTest(lasd::PreOrderMappableContainer<std::string>& struttura){

    struttura.MapPreOrder(&mapUpperCase, 0);

}

// Fold Test

void foldSum(const int& dato, const void* parametro, void* accumulatore){

    if(dato < *((int*)parametro)){

        *((int*)accumulatore) += dato;

    }
}

void foldTest(lasd::PreOrderFoldableContainer<int>& struttura){

    unsigned int n, ris;

    std::cout << "Inserire la grandezza n:" <<std::endl;
    std::cin >> n;

    struttura.FoldPreOrder(&foldSum, &n, &ris);
    std::cout << "Il risultato è:" << ris << std::endl;

}

void foldProd(const double& dato, const void* parametro, void* accumulatore){

    if (dato < *((double*)parametro)){

        *((double*)accumulatore) *= dato;

    }
}

void foldTest(lasd::PreOrderFoldableContainer<double>& struttura){

    double n, ris = 1;

    std::cout << "Inserire la grandezza n:" <<std::endl;
    std::cin >> n;

    struttura.FoldPreOrder(&foldProd, &n, &ris);
    std::cout << "Il risultato è:" << ris << std::endl;

}

void foldConcat(const std::string& dato, const void* parametro, void* accumulatore){

    if (dato.size() < *((int*)parametro)){

        *((std::string*)accumulatore) += dato;

    }

}

void foldTest(lasd::PreOrderFoldableContainer<std::string>& struttura){

    int n;
    std::string stringa_finale = "";

    std::cout << "Inserire la grandezza n:" <<std::endl;
    std::cin >> n;

    struttura.FoldPreOrder(&foldConcat, &n, &stringa_finale);
    std::cout << "Il risultato è:" << stringa_finale << std::endl;

}

template <typename Data>
void specificVecTest(lasd::Vector<Data>& vettore){

    unsigned long new_size;

    std::cout << "Scegliere la nuova dimensione della struttura:" << std::endl;
    std::cin >> new_size;

    vettore.Resize(new_size);
    vettore.MapPreOrder(&mapPrintDouble<Data>, 0);
    std::cout << std::endl;
    std::cout << "Struttura ridimensionata!";

}

template <typename Data>
void specificListTest(lasd::List<Data>& lista){

    unsigned int scelta;
    char scelta_testa_coda;
    Data dato;

    std::cout << "1) Inserimento:" << std::endl;
    std::cout << "2) Rimozione:" << std::endl;
    std::cout << "3) Rimozione con lettura:" << std::endl;
    std::cin >> scelta;

    switch (scelta){
    case 1:
        
        std::cout << "Inserimento in (T)esta o in (C)oda?" << std::endl;
        std::cin >> scelta_testa_coda;

        switch (scelta_testa_coda){
        case 'T':
            
            std::cout << "Che elemento vuoi inserire?" << std::endl;
            std::cin >> dato;

            lista.InsertAtFront(dato);
            lista.MapPreOrder(&mapPrintDouble<Data>, 0);
            std::cout << std::endl;

            break;
        
        case 'C':

            std::cout << "Che elemento vuoi inserire?" << std::endl;
            std::cin >> dato;

            lista.InsertAtBack(dato);
            lista.MapPreOrder(&mapPrintDouble<Data>, 0);
            std::cout << std::endl;

            break;

        default:

            std::cout << "Sceta non riconosciuta" << std::endl;

            break;
        }

        break;
    case 2:
        
        lista.RemoveFromFront();
        std::cout << std::endl;

        break;
    case 3:
        
        std::cout << lista.FrontNRemove() << std::endl;

        break;
    default:

        std::cout << "Scelta non riconosciuta" << std::endl;

        break;
    }


}



template<typename Data>
void vecTestMenu(lasd::Vector<Data>& vettore){
    
    unsigned int scelta = 0;

    while (true){

        std::cout << "Scelta delle operazioni:" << std::endl;
        std::cout << "1)Visualizza un elemento specifico:" << std::endl;
        std::cout << "2)Visualizza tutta la struttura:" << std::endl;
        std::cout << "3)Controllo d'esistenza di un valore:" << std::endl;
        std::cout << "4)FoldFunction:" << std::endl;
        std::cout << "5)Applicazione di una funzione in base al tipo di elementi:" << std::endl;
        std::cout << "6)Resize struttura:" << std::endl;
        std::cout << "7)Uscita:" << std::endl;

        std::cin >> scelta;

        switch (scelta){
        case 1:
            
            elemTest(vettore);

            break;
        
        case 2:

            vettore.MapPreOrder(&mapPrintDouble<Data>, 0);
            std::cout << std::endl;

            break;

        case 3:

            exitsTest<Data>(vettore);

            break;

        case 4:

            foldTest(vettore);

            break;

        case 5:

            specificTest(vettore);

            break;
        
        case 6:

            specificVecTest(vettore);

            break;
        
        case 7:

            return;

            break;

        default:

            std::cout << "Scelta non valida!" << std::endl;

            break;
        }

    }
    
}

// Rand generator per i Vector

template <typename Data>
void intRandGenVect(lasd::Vector<Data>& struttura){

    std::default_random_engine gen(std::random_device{}());
    std::uniform_int_distribution<int> distributore(0, 100);


    for (unsigned long index = 0 ; index < struttura.Size(); index++){

        struttura[index] = distributore(gen);
        std::cout <<struttura[index]<<std::endl;

    }

    std::cout<<"Struttura riempita!"<<std::endl;
}

template <typename Data>
void floatRandGenVect(lasd::Vector<Data>& struttura){

    std::default_random_engine gen(std::random_device{}());
    std::uniform_real_distribution<float> distributore(0.0, 100.0);


    for (unsigned long index = 0 ; index < struttura.Size(); index++){

        struttura[index] = distributore(gen);
        std::cout <<struttura[index]<<std::endl;

    }

    std::cout<<"Struttura riempita!"<<std::endl;
}

template <typename Data>
void stringRandGenVect(lasd::Vector<Data>& struttura){

    std::string string_tmp;
    const char lookup_table[] = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";

    std::default_random_engine gen(std::random_device{}());
    std::uniform_int_distribution<int> distributore(0, 62);
    std::uniform_int_distribution<int> distributore_grandezza(0, 10);


    for (unsigned long index = 0 ; index < struttura.Size(); index++){

        unsigned int len = distributore_grandezza(gen);

        for (unsigned int i = 0; i < len; i++){
            
            string_tmp += lookup_table[distributore(gen)];
            
        }

        struttura[index] = string_tmp;
        string_tmp = "";
        std::cout <<struttura[index]<<std::endl;       

    }

    std::cout<<"Struttura riempita!"<<std::endl;
}

// Rand generator per le List

template <typename Data>
void intRandGenList(lasd::List<Data>& lista, unsigned long dimensione){

    std::default_random_engine gen(std::random_device{}());
    std::uniform_int_distribution<int> distributore(0, 100);

    for (unsigned long index = 0; index < dimensione; index++){

        lista.InsertAtFront(distributore(gen));

    }

    std::cout << "Struttura riempita!" << std::endl;

}

template <typename Data>
void floatRandGenList(lasd::List<Data>& lista, unsigned long dimensione){

    std::default_random_engine gen(std::random_device{}());
    std::uniform_real_distribution<float> distributore(0.0, 100.0);

    for (unsigned long index = 0; index < dimensione; index++){

        lista.InsertAtFront(distributore(gen));

    }

    std::cout << "Struttura riempita!" << std::endl;

}

template <typename Data>
void stringRandGenList(lasd::List<Data>& lista, unsigned long dimensione){

    std::string string_tmp;
    const char lookup_table[] = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";

    std::default_random_engine gen(std::random_device{}());
    std::uniform_int_distribution<int> distributore(0, 62);
    std::uniform_int_distribution<int> distributore_grandezza(0, 10);

    for (unsigned long index = 0 ; index < dimensione; index++){

        unsigned int len = distributore_grandezza(gen);

        for (unsigned int i = 0; i < len; i++){
            
            string_tmp += lookup_table[distributore(gen)];
            
        }

        lista.InsertAtFront(string_tmp);
        string_tmp = "";
    }

    std::cout<<"Struttura riempita!"<<std::endl;
}


template <typename Data>
void VectorTest(unsigned long dimensione, char tipo){

    switch (tipo)    {
    case 'I':{

        lasd::Vector<int> vettore = lasd::Vector<int>(dimensione);
        intRandGenVect<int>(vettore);
        vecTestMenu(vettore);

        break;
        
    }
    case 'D':{

        lasd::Vector<double> vettore = lasd::Vector<double>(dimensione);
        floatRandGenVect<double>(vettore);
        vecTestMenu(vettore);

        break;
    }
    case 'S':{

        lasd::Vector<std::string> vettore = lasd::Vector<std::string>(dimensione);
        stringRandGenVect<std::string>(vettore);
        vecTestMenu(vettore);

        break;
    }
    default:

        std::cout << "Scelta non riconosciuta" << std::endl;

        break;
    }  

            
    return;

}

template <typename Data>
void ListTest(unsigned long dimensione, char tipo){

    switch (tipo){
    case 'I':{

        lasd::List<int> lista = lasd::List<int>();
        intRandGenList<int>(lista, dimensione);
        listTestMenu(lista);

        break;
    }
    case 'D':{

        lasd::List<double> lista = lasd::List<double>();
        floatRandGenList<double>(lista, dimensione);
        listTestMenu(lista);

        break;
    }
    case 'S':{

        lasd::List<std::string> lista = lasd::List<std::string>();
        stringRandGenList<std::string>(lista, dimensione);
        listTestMenu(lista);


        break;
    }
    default:

        break;
    }


}

template <typename Data>
void listTestMenu(lasd::List<Data>& lista){

    unsigned int scelta = 0;

    while (true){

        std::cout << "Scelta delle operazioni:" << std::endl;
        std::cout << "1)Visualizza un elemento specifico:" << std::endl;
        std::cout << "2)Visualizza tutta la struttura:" << std::endl;
        std::cout << "3)Controllo d'esistenza di un valore:" << std::endl;
        std::cout << "4)FoldFunction:" << std::endl;
        std::cout << "5)Applicazione di una funzione in base al tipo di elementi:" << std::endl;
        std::cout << "6)funzioni specifiche sulla struttura:" << std::endl;
        std::cout << "7)Uscita" << std::endl;

        std::cin >> scelta;

        switch (scelta){
        case 1:
            
            elemTest(lista);

            break;
        
        case 2:

            lista.MapPreOrder(&mapPrintDouble<Data>, 0);
            std::cout << std::endl;
            
            break;

        case 3:

            exitsTest(lista);
            
            break;

        case 4:

            foldTest(lista);

            break;

        case 5:

            specificTest(lista);

            break;

        case 6:

            specificListTest(lista);

            break;

        case 7:

            return;

            break;

        default:

            std::cout << "Scelta non valida!" << std::endl;

            break;
        }
    
    }
            
    return;

}