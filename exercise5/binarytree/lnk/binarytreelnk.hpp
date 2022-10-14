
#ifndef BINARYTREELNK_HPP
#define BINARYTREELNK_HPP

/* ************************************************************************** */

#include "../binarytree.hpp"

/* ************************************************************************** */

namespace lasd
{

  /* ************************************************************************** */

  template <typename Data>
  class BinaryTreeLnk : virtual public BinaryTree<Data>
  {
    // Must extend BinaryTree<Data>

  private:
    // ...

  protected:
    using BinaryTree<Data>::size;

    // ...

    struct NodeLnk : virtual public BinaryTree<Data>::Node
    { // Must extend Node

    private:
      // ...

    protected:
      // ...

    public:
      Data data;
      NodeLnk *leftChild = nullptr;
      NodeLnk *rightChild = nullptr;

      // Constructor
      NodeLnk() = default;

      // Specific constructor
      NodeLnk(const Data &);

      // Copy constructor
      NodeLnk(const NodeLnk &);

      // Move constructor
      NodeLnk(NodeLnk &&);

      bool operator==(const NodeLnk&) const noexcept;
      bool operator!=(const NodeLnk&) const noexcept;

      // Copy operator
      NodeLnk &operator=(const NodeLnk &);

      // Move operator
      NodeLnk &operator=(NodeLnk &&);

      // Destructor
      ~NodeLnk();

      Data &Element() noexcept override;
      const Data &Element() const noexcept override;

      bool HasLeftChild() const noexcept override;
      bool HasRightChild() const noexcept override;

      NodeLnk &LeftChild() const override;
      NodeLnk &RightChild() const override;
    };

    NodeLnk *root = nullptr;

  public:
    // Default constructor
    BinaryTreeLnk() = default;

    /* ************************************************************************ */

    // Specific constructors
    BinaryTreeLnk(const LinearContainer<Data> &); // A binary tree obtained from a LinearContainer

    /* ************************************************************************ */

    // Copy constructor
    BinaryTreeLnk(const BinaryTreeLnk &);

    // Move constructor
    BinaryTreeLnk(BinaryTreeLnk &&) noexcept;

    /* ************************************************************************ */

    // Destructor
    ~BinaryTreeLnk() = default;

    /* ************************************************************************ */

    // Copy assignment
    BinaryTreeLnk<Data> &operator=(const BinaryTreeLnk &);

    // Move assignment
    BinaryTreeLnk<Data> &operator=(BinaryTreeLnk &&);

    /* ************************************************************************ */

    // Comparison operators
    bool operator==(const BinaryTreeLnk &) const noexcept;
    bool operator!=(const BinaryTreeLnk &) const noexcept;

    /* ************************************************************************ */

    // Specific member functions (inherited from BinaryTree)

    NodeLnk &Root() const; // Override BinaryTree member (throw std::length_error when empty)

    /* ************************************************************************ */

    // Specific member functions (inherited from Container)

    void Clear(); // Override Container member

  };

  /* ************************************************************************** */

}

#include "binarytreelnk.cpp"

#endif
