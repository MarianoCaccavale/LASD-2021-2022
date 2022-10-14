
#ifndef BST_HPP
#define BST_HPP

/* ************************************************************************** */

#include "../binarytree/lnk/binarytreelnk.hpp"

/* ************************************************************************** */

namespace lasd
{

  /* ************************************************************************** */

  template <typename Data>
  class BST : virtual public DictionaryContainer<Data>,
              virtual public BinaryTreeLnk<Data>
  { // Must extend BinaryTreeLnk<Data>

  private:
    // ...

  protected:
    using BinaryTreeLnk<Data>::size;
    using BinaryTreeLnk<Data>::root;

    // ...

  public:
    using typename BinaryTreeLnk<Data>::NodeLnk;

    // Default constructor
    BST() = default;

    /* ************************************************************************ */

    // Specific constructors
    BST(const LinearContainer<Data> &); // A bst obtained from a LinearContainer

    /* ************************************************************************ */

    // Copy constructor
    BST(const BST<Data> &);

    // Move constructor
    BST(BST<Data> &&) noexcept;

    /* ************************************************************************ */

    // Destructor
    ~BST() = default;

    /* ************************************************************************ */

    // Copy assignment
    BST<Data> &operator=(const BST<Data> &);

    // Move assignment
    BST<Data> &operator=(BST<Data> &&) noexcept;

    /* ************************************************************************ */

    // Comparison operators
    bool operator==(const BST<Data> &) const noexcept;
    bool operator!=(const BST<Data> &) const noexcept;

    /* ************************************************************************ */

    // Specific member functions

    const Data &Min() const; // (concrete function must throw std::length_error when empty)
    Data MinNRemove();       // (concrete function must throw std::length_error when empty)
    void RemoveMin();        // (concrete function must throw std::length_error when empty)

    const Data &Max() const; // (concrete function must throw std::length_error when empty)
    Data MaxNRemove();       // (concrete function must throw std::length_error when empty)
    void RemoveMax();        // (concrete function must throw std::length_error when empty)

    const Data &Predecessor(const Data &) const; // (concrete function must throw std::length_error when not found)
    Data PredecessorNRemove(const Data &);       // (concrete function must throw std::length_error when not found)
    void RemovePredecessor(const Data &);        // (concrete function must throw std::length_error when not found)

    const Data &Successor(const Data &) const; // (concrete function must throw std::length_error when not found)
    Data SuccessorNRemove(const Data &);       // (concrete function must throw std::length_error when not found)
    void RemoveSuccessor(const Data &);        // (concrete function must throw std::length_error when not found)

    /* ************************************************************************ */

    // Specific member functions (inherited from DictionaryContainer)

    bool Insert(const Data &) override; // Override DictionaryContainer member (Copy of the value)
    bool Insert(Data &&) override;      // Override DictionaryContainer member (Move of the value)
    bool Remove(const Data &) override; // Override DictionaryContainer member

    /* ************************************************************************ */

    // Specific member functions (inherited from TestableContainer)

    bool Exists(const Data &) const noexcept override; // Override TestableContainer member

  protected:
    // Auxiliary member functions

    Data DataNDelete(NodeLnk *);

    NodeLnk *Detach(NodeLnk *&) noexcept;

    NodeLnk *DetachMin(NodeLnk *&) noexcept;
    NodeLnk *DetachMax(NodeLnk *&) noexcept;

    NodeLnk *Skip2Left(NodeLnk *&);
    NodeLnk *Skip2Right(NodeLnk *&);

    NodeLnk *const &FindPointerToMin(NodeLnk *const &) const; // unmutable version
    NodeLnk *&FindPointerToMin(NodeLnk *&);                   // mutable versions

    NodeLnk *const &FindPointerToMax(NodeLnk *const &) const; // unmutable versions
    NodeLnk *&FindPointerToMax(NodeLnk *&);                   // mutable versions

    NodeLnk *const &FindPointerTo(NodeLnk *const &, const Data &) const; // unmutable versions
    NodeLnk *&FindPointerTo(NodeLnk *&, const Data &);                   // mutable versions

    NodeLnk *const *FindPointerToPredecessor(NodeLnk *const &, const Data &) const; // unmutable versions
    NodeLnk **FindPointerToPredecessor(NodeLnk *&, const Data &);                   // mutable versions

    NodeLnk *const *FindPointerToSuccessor(NodeLnk *const &, const Data &) const; // unmutable versions
    NodeLnk **FindPointerToSuccessor(NodeLnk *&, const Data &);                   // mutable versions
  };

  /* ************************************************************************** */

}

#include "bst.cpp"

#endif
