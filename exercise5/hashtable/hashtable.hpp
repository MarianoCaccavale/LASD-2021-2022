
#ifndef HASHTABLE_HPP
#define HASHTABLE_HPP

/* ************************************************************************** */

#include <random>

/* ************************************************************************** */

#include "../container/container.hpp"

/* ************************************************************************** */

namespace lasd
{

  /* ************************************************************************** */

  template <typename Data>
  class Hash
  {

  public:
    ulong operator()(const Data &) const noexcept; // (concrete function should not throw exceptions)
  };

  /* ************************************************************************** */

  template <typename Data>
  class HashTable : virtual public DictionaryContainer<Data>,
                    virtual public MappableContainer<Data>,
                    virtual public FoldableContainer<Data>
  { // Must extend DictionaryContainer<Data>,
    //             MappableContainer<Data>,
    //             FoldableContainer<Data>

  private:
    // ...

  protected:
    using DictionaryContainer<Data>::size;

    Hash<Data> trasformationHash = Hash<Data>();

    // P della funzione completa di indirizzamento
    //ulong bigPrimeNumber = 69697;
    ulong bigPrimeNumber = 2147483647;
    // a della funzione completa di indirizzamento
    ulong a;
    // b della funzione completa di indirizzamento
    ulong b;
    // m della funzione completa di indirizzamento, ha valore default 2048
    ulong m = 2048;

    /* ************************************************************************ */

    HashTable(const HashTable &);

    HashTable(HashTable &);

    // Copy assignment
    HashTable<Data> &operator=(const HashTable &); // Copy assignment of abstract types should not be possible.

    // Move assignment
    HashTable<Data> &operator=(HashTable &&) noexcept; // Move assignment of abstract types should not be possible.

    /* ************************************************************************ */

  public:
    // Constructor
    HashTable();

    // Destructor
    ~HashTable() = default;

    // Comparison operators
    bool operator==(const HashTable &) const noexcept = delete; // Comparison of abstract binary tree is possible.
    bool operator!=(const HashTable &) const noexcept = delete; // Comparison of abstract binary tree is possible.

    /* ************************************************************************ */

    // Specific member function

    virtual void Resize(const ulong &) = 0; // Resize the hashtable to a given size

    // Auxiliary member functions

    ulong HashKey(const Data &) const noexcept;
  };

  /* ************************************************************************** */

}

#include "hashtable.cpp"

#endif
