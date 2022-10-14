
#ifndef BINARYTREEVEC_HPP
#define BINARYTREEVEC_HPP

/* ************************************************************************** */

#include "../binarytree.hpp"
#include "../../vector/vector.hpp"

/* ************************************************************************** */

namespace lasd
{

  /* ************************************************************************** */

  template <typename Data>
  class BinaryTreeVec : virtual public BinaryTree<Data>
  {
    // Must extend BinaryTree<Data>

  private:
    // ...

  protected:
    using BinaryTree<Data>::size;

    // ...

    struct NodeVec : virtual public BinaryTree<Data>::Node
    { // Must extend Node

    private:
      // ...

    protected:
      Data data;
      ulong index;
      Vector<NodeVec *> *vecAppartenenza = new Vector<NodeVec*>();

    public:
      // Default constructor
      NodeVec() = default;

      // Specifc Constructor
      NodeVec(const Data &, ulong, Vector<NodeVec *> *);

      // Copy Constructor
      NodeVec(const NodeVec &);

      // Move Constructor
      NodeVec(NodeVec &&);

      // Copy operator
      NodeVec &operator=(const NodeVec &);

      // Move operator
      NodeVec &operator=(NodeVec &&) noexcept;

      // Destructor
      ~NodeVec() = default;

      Data &Element() noexcept override;
      const Data &Element() const noexcept override;

      bool HasLeftChild() const noexcept override;
      bool HasRightChild() const noexcept override;

      NodeVec &LeftChild() const override;
      NodeVec &RightChild() const override;
    };

    Vector<NodeVec*> *vector = nullptr;

  public:
    // Default constructor
    BinaryTreeVec();

    /* ************************************************************************ */

    // Specific constructors
    BinaryTreeVec(const LinearContainer<Data> &); // A binary tree obtained from a LinearContainer

    /* ************************************************************************ */

    // Copy constructor
    BinaryTreeVec(const BinaryTreeVec<Data> &);

    // Move constructor
    BinaryTreeVec(BinaryTreeVec<Data> &&);

    /* ************************************************************************ */

    // Destructor
    ~BinaryTreeVec();

    /* ************************************************************************ */

    // Copy assignment
    BinaryTreeVec<Data> &operator=(const BinaryTreeVec<Data> &);

    // Move assignment
    BinaryTreeVec<Data> &operator=(BinaryTreeVec<Data> &&);

    /* ************************************************************************ */

    // Comparison operators
    bool operator==(const BinaryTreeVec<Data> &) const noexcept;
    bool operator!=(const BinaryTreeVec<Data> &) const noexcept;

    /* ************************************************************************ */

    // Specific member functions (inherited from BinaryTree)
    NodeVec &Root() const override; // Override BinaryTree member (throw std::length_error when empty)

    /* ************************************************************************ */

    // Specific member functions (inherited from Container)

    void Clear() override; // Override Container member

    /* ************************************************************************ */

    // Specific member functions (inherited from BreadthMappableContainer)

    using typename MappableContainer<Data>::MapFunctor;
    void MapBreadth(MapFunctor, void *) override; // Override BreadthMappableContainer member

    /* ************************************************************************ */

    // Specific member functions (inherited from BreadthFoldableContainer)

    using typename FoldableContainer<Data>::FoldFunctor;
    void FoldBreadth(FoldFunctor, const void *, void *); // Override BreadthFoldableContainer member
  };

  /* ************************************************************************** */

}

#include "binarytreevec.cpp"

#endif
