
#ifndef HTOPNADR_HPP
#define HTOPNADR_HPP

/* ************************************************************************** */

#include "../hashtable.hpp"
#include "cstddef"

// #include ...

/* ************************************************************************** */

namespace lasd
{

  /* ************************************************************************** */

  template <typename Data>
  class HashTableOpnAdr : virtual public HashTable<Data>
  { // Must extend HashTable<Data>

  private:
    // ...

  protected:
    using HashTable<Data>::m;

    Vector<Data> table;

    Vector<char> flags;

  public:
    // Default constructor
    HashTableOpnAdr();

    /* ************************************************************************ */

    // Specific constructors
    HashTableOpnAdr(const ulong &);                                // A hash table of a given size
    HashTableOpnAdr(const LinearContainer<Data> &);                // A hash table obtained from a LinearContainer
    HashTableOpnAdr(const ulong &, const LinearContainer<Data> &); // A hash table of a given size obtained from a LinearContainer

    /* ************************************************************************ */

    // Copy constructor
    HashTableOpnAdr(const HashTableOpnAdr &);

    // Move constructor
    HashTableOpnAdr(HashTableOpnAdr &&) noexcept;

    /* ************************************************************************ */

    // Destructor
    ~HashTableOpnAdr() = default;

    /* ************************************************************************ */

    // Copy assignment
    HashTableOpnAdr<Data> &operator=(const HashTableOpnAdr<Data> &);

    // Move assignment
    HashTableOpnAdr<Data> &operator=(HashTableOpnAdr<Data> &&) noexcept;

    /* ************************************************************************ */

    // Comparison operators
    bool operator==(const HashTableOpnAdr<Data> &) const noexcept;
    bool operator!=(const HashTableOpnAdr<Data> &) const noexcept;

    /* ************************************************************************ */

    // Specific member functions (inherited from HashTable)

    void Resize(const ulong &); // Resize the hashtable to a given size

    /* ************************************************************************ */

    // Specific member functions (inherited from DictionaryContainer)

    bool Insert(const Data &) override; // Override DictionaryContainer member (Copy of the value)
    bool Insert(Data &&) override;      // Override DictionaryContainer member (Move of the value)
    bool Remove(const Data &) override; // Override DictionaryContainer member

    /* ************************************************************************ */

    // Specific member functions (inherited from TestableContainer)

    bool Exists(const Data &) const noexcept override; // Override TestableContainer member

    /* ************************************************************************ */

    // Specific member functions (inherited from MappableContainer)

    using typename MappableContainer<Data>::MapFunctor;

    void Map(MapFunctor, void *) override; // Override MappableContainer member

    /* ************************************************************************ */

    // Specific member functions (inherited from FoldableContainer)

    using typename FoldableContainer<Data>::FoldFunctor;

    void Fold(FoldFunctor, const void *, void *) const override; // Override FoldableContainer member

    /* ************************************************************************ */

    // Specific member functions (inherited from Container)

    void Clear() override; // Override Container member

  public:
    // Auxiliary member functions

    ulong HashKey(const Data &, const ulong &) const noexcept;
    // Dato un dato, controllare se nella sequenza di probing della chiave di quel dato c'è gia quel dato
    // in modo da sapere se ci sono duplicati o meno. Nel caso restituisca -1, vuol dire che il dato non c'è. Se
    // restituisce un indice, in quell'indice c'è il dato che sto cercando
    long Find(const Data &, const ulong & = 0) const;
    // Dato un dato, restituire il primo indice vuoto(vuoto vuoto oppure il cui dato è stato cancellato)
    long FindEmpty(const Data &, const ulong & = 0) const;
    // Dato un index, cancellare negli index successivi(tramite probing) un determinato Data
    // void Remove();
  };

  /* ************************************************************************** */

}

#include "htopnadr.cpp"

#endif
