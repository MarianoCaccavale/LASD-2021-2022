
namespace lasd {

/* ************************************************************************** */

template<typename Data>
Vector<Data>::Vector(const unsigned long new_size){

    Elementi = new Data[new_size] {};
    size = new_size;
}

template<typename Data>
Vector<Data>::Vector(const LinearContainer<Data>& contenitore){

    size = contenitore.Size();
    Elementi = new Data[size];
    for(unsigned long i = 0; i < size; ++i){

        Elementi[i] = contenitore[i];

    }
}

/* ************************************************************************** */

//Copy contructor
template <typename Data>
Vector<Data>::Vector(const Vector<Data>& vettore){

    Elementi = new Data[vettore.size];
    std::copy(vettore.Elementi, vettore.Elementi + vettore.size, Elementi);
    size = vettore.size;
}

//Move constructor
template <typename Data>
Vector<Data>::Vector(Vector<Data>&& vettore) noexcept{

    std::swap(Elementi, vettore.Elementi);
    std::swap(size, vettore.size);
}

/* ************************************************************************** */

//Destructor
template<typename Data>
Vector<Data>::~Vector(){

    size = 0;
    delete[] Elementi;
}

/* ************************************************************************** */

//Copy assignment
template <typename Data>
Vector<Data>& Vector<Data>::operator=(const Vector<Data>& vettore){

    Vector<Data>* vettore_temp = new Vector<Data>(vettore);
    std::swap(*vettore_temp, *this);
    delete vettore_temp;
    return *this;
}

template <typename Data>
Vector<Data>& Vector<Data>::operator=(Vector<Data>&& vettore) noexcept{

    std::swap(Elementi, vettore.Elementi);
    std::swap(size, vettore.size);
    return *this;
}

template <typename Data>
bool Vector<Data>::operator==(const Vector<Data>& vettore) const noexcept{

    if (size == vettore.size){

        for(unsigned long i = 0; i < size; ++i){

            if (Elementi[i] != vettore.Elementi[i]){

                return false;

            }
        }

        return true;
    }else{

        return false;
    }
}

template <typename Data>
inline bool Vector<Data>::operator!=(const Vector<Data>& vettore) const noexcept{

    return !(*this == vettore);

}

/* ************************************************************************** */

template <typename Data>
void Vector<Data>::Resize(const unsigned long new_size){

    if (new_size == 0){
        Clear();
    }else if (size != new_size){

        Data* TempElement = new Data[new_size] {};

        unsigned long limit = 0;

        if (size < new_size)
            limit = size;
        else
            limit = new_size;

        for(unsigned long i = 0; i < limit; ++i){
            std::swap(Elementi[i], TempElement[i]);
        }
        std::swap (Elementi, TempElement);
        size = new_size;
        delete[] TempElement;

    }
}

template <typename Data>
void Vector<Data>::Clear(){

    delete[] Elementi;
    Elementi = nullptr;
    size = 0; 
    
}

template <typename Data>
Data& Vector<Data>::Front() const{

    if (size != 0){

        return Elementi[0];

    }else{

        throw std::length_error("Il vettore è vuoto, impossibile restituire il primo elemento");

    }
}

template <typename Data>
Data& Vector<Data>::Back() const{

    if (size != 0){

        return Elementi[size-1];

    }else{

        throw std::length_error("Il vettore è vuoto, impossibile restituire l'ultimo elemento");

    }
}

template <typename Data>
Data& Vector<Data>::operator[](const unsigned long index) const{

    if (index <= size){

        return Elementi[index];

    }else{

        throw std::out_of_range("Elemento di indice" + std::to_string(index) + "fuori range");
    }
}

template <typename Data>
void Vector<Data>::Map(MapFunctor funzione, void* parametro){
    
    MapPreOrder(funzione, parametro);

}

template <typename Data>
void Vector<Data>::MapPreOrder(const MapFunctor funzione, void* parametro){

    for (unsigned long index = 0; index < size; ++index){

        funzione(Elementi[index], parametro);
    }
}

template <typename Data>
void Vector<Data>::MapPostOrder(const MapFunctor funzione, void* parametro){

    unsigned long index = size;
    while (index > 0){

        funzione(Elementi[--index], parametro);
    }
}

template <typename Data>
void Vector<Data>::Fold(FoldFunctor funzione, const void* parametro, void* accumulatore) const{

    FoldPreOrder(funzione, parametro, accumulatore);

}

template <typename Data>
void Vector<Data>::FoldPreOrder(FoldFunctor funzione, const void* parametro, void* accumulatore) const{

    for (unsigned long index = 0; index < size; ++index){

        funzione(Elementi[index], parametro, accumulatore);

    }
}

template <typename Data>
void Vector<Data>::FoldPostOrder(FoldFunctor funzione, const void* parametro, void* accumulatore) const{

    unsigned long index = size;
    while (index > 0){

        funzione(Elementi[--index], parametro, accumulatore);

    }
}


}
