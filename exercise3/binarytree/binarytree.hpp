
#ifndef BINARYTREE_HPP
#define BINARYTREE_HPP

/* ************************************************************************** */

#include "../container/container.hpp"

#include "../iterator/iterator.hpp"

#include "../queue/lst/queuelst.hpp"

#include "../stack/lst/stacklst.hpp"

/* ************************************************************************** */

namespace lasd
{

  /* ************************************************************************** */

  template <typename Data>
  class BinaryTree : virtual public PreOrderMappableContainer<Data>,
                     virtual public PostOrderMappableContainer<Data>,
                     virtual public InOrderMappableContainer<Data>,
                     virtual public BreadthMappableContainer<Data>,
                     virtual public PreOrderFoldableContainer<Data>,
                     virtual public PostOrderFoldableContainer<Data>,
                     virtual public InOrderFoldableContainer<Data>,
                     virtual public BreadthFoldableContainer<Data>
  {
    // Must extend PreOrderMappableContainer<Data>,
    //             PostOrderMappableContainer<Data>,
    //             InOrderMappableContainer<Data>,
    //             BreadthMappableContainer<Data>,
    //             PreOrderFoldableContainer<Data>,
    //             PreOrderFoldableContainer<Data>,
    //             InOrderFoldableContainer<Data>,
    //             BreadthFoldableContainer<Data>

  private:
    // ...

  protected:
    // using InOrder/BreadthMappableContainer<Data>::size;
    using BreadthMappableContainer<Data>::size;

  public:
    struct Node
    {

    private:
    protected:
      // Comparison operators
      bool operator==(const Node &) const noexcept; // Comparison of abstract types is possible, but should not be visible.
      bool operator!=(const Node &) const noexcept; // Comparison of abstract types is possible, but should not be visible.

    public:
      friend class BinaryTree<Data>;

      /* ********************************************************************** */

      // Destructor
      virtual ~Node() = default;

      /* ********************************************************************** */

      // Copy assignment
      Node &operator=(const Node &) const = delete; // Copy assignment of abstract types should not be possible.

      // Move assignment
      Node &operator=(Node &&) = delete; // Move assignment of abstract types should not be possible.

      /* ********************************************************************** */

      // Specific member functions

      virtual Data &Element() noexcept = 0;             // Mutable access to the element (concrete function should not throw exceptions)
      virtual const Data &Element() const noexcept = 0; // Immutable access to the element (concrete function should not throw exceptions)

      inline bool IsLeaf() const noexcept;             // (concrete function should not throw exceptions)
      virtual bool HasLeftChild() const noexcept = 0;  // (concrete function should not throw exceptions)
      virtual bool HasRightChild() const noexcept = 0; // (concrete function should not throw exceptions)

      virtual Node &LeftChild() const = 0;  // (concrete function must throw std::out_of_range when not existent)
      virtual Node &RightChild() const = 0; // (concrete function must throw std::out_of_range when not existent)
    };

    /* ************************************************************************ */

    // Destructor
    virtual ~BinaryTree() = default;

    /* ************************************************************************ */

    // Copy assignment
    BinaryTree &operator=(const BinaryTree &) const = delete; // Copy assignment of abstract types should not be possible.

    // Move assignment
    BinaryTree &operator=(BinaryTree &&) = delete; // Move assignment of abstract types should not be possible.

    /* ************************************************************************ */

    // Comparison operators
    // implementa il confronto dei nodi in modo che controlli gli alberi radicati in quel nodo. In quel modo
    // questo confronto deve solo richiamare il confronto delle radici, al resto ci pensano i nodi
    bool operator==(const BinaryTree &) const noexcept; // Comparison of abstract binary tree is possible.
    bool operator!=(const BinaryTree &) const noexcept; // Comparison of abstract binary tree is possible.

    /* ************************************************************************ */

    // Specific member functions

    virtual Node &Root() const = 0; // (concrete function must throw std::length_error when empty)

    /* ************************************************************************ */

    // Specific member functions (inherited from MappableContainer)

    using typename MappableContainer<Data>::MapFunctor;

    void Map(MapFunctor, void *) override; // Override MappableContainer member

    /* ************************************************************************ */

    // Specific member functions (inherited from FoldableContainer)

    using typename FoldableContainer<Data>::FoldFunctor;

    void Fold(FoldFunctor, const void *, void *) const override; // Override FoldableContainer member

    /* ************************************************************************ */

    // Specific member functions (inherited from PreOrderMappableContainer)

    void MapPreOrder(MapFunctor, void *) override; // Override PreOrderMappableContainer member

    /* ************************************************************************ */

    // Specific member functions (inherited from PreOrderFoldableContainer)

    void FoldPreOrder(FoldFunctor, const void *, void *) const override; // Override PreOrderFoldableContainer member

    /* ************************************************************************ */

    // Specific member functions (inherited from PostOrderMappableContainer)

    void MapPostOrder(MapFunctor, void *) override; // Override PostOrderMappableContainer member

    /* ************************************************************************ */

    // Specific member functions (inherited from PostOrderFoldableContainer)

    void FoldPostOrder(FoldFunctor, const void *, void *) const override; // Override PostOrderFoldableContainer member

    /* ************************************************************************ */

    // Specific member functions (inherited from InOrderMappableContainer)

    void MapInOrder(MapFunctor, void *) override; // Override InOrderMappableContainer member

    /* ************************************************************************ */

    // Specific member functions (inherited from InOrderFoldableContainer)

    void FoldInOrder(FoldFunctor, const void *, void *) const override; // Override InOrderFoldableContainer member

    /* ************************************************************************ */

    // Specific member functions (inherited from BreadthMappableContainer)

    void MapBreadth(MapFunctor, void *) override; // Override BreadthMappableContainer member

    /* ************************************************************************ */

    // Specific member functions (inherited from BreadthFoldableContainer)
    void FoldBreadth(FoldFunctor, const void *, void *) const override; // Override BreadthFoldableContainer member

  protected:
    // Auxiliary member functions (for PreOrderMappableContainer)

    void MapPreOrder(MapFunctor, void *, Node *); // Accessory function executing from one node of the tree

    /* ************************************************************************ */

    // Auxiliary member functions (for PreOrderFoldableContainer)

    void FoldPreOrder(FoldFunctor, const void *, void *, const Node *) const; // Accessory function executing from one node of the tree

    /* ************************************************************************ */

    // Auxiliary member functions (for PostOrderMappableContainer)

    void MapPostOrder(MapFunctor, void *, Node *); // Accessory function executing from one node of the tree

    /* ************************************************************************ */

    // Auxiliary member functions (for PostOrderFoldableContainer)

    void FoldPostOrder(FoldFunctor, const void *, void *, const Node *) const; // Accessory function executing from one node of the tree

    /* ************************************************************************ */

    // Auxiliary member functions (for InOrderMappableContainer)

    void MapInOrder(MapFunctor, void *, Node *); // Accessory function executing from one node of the tree

    /* ************************************************************************ */

    // Auxiliary member functions (for InOrderFoldableContainer)

    void FoldInOrder(FoldFunctor, const void *, void *, const Node *) const; // Accessory function executing from one node of the tree

    /* ************************************************************************ */

    // Auxiliary member functions (for BreadthMappableContainer)

    void MapBreadth(MapFunctor, void *, Node *); // Accessory function executing from one node of the tree

    /* ************************************************************************ */

    // Auxiliary member functions (for BreadthFoldableContainer)

    void FoldBreadth(FoldFunctor, const void *, void *, const Node *) const; // Accessory function executing from one node of the tree
  };

  /* ************************************************************************** */

  template <typename Data>
  class BTPreOrderIterator : virtual public ForwardIterator<Data>,
                             virtual public ResettableIterator<Data>
  {
    // Must extend ForwardIterator<Data>,
    //             ResettableIterator<Data>

  private:
    // ...

  protected:
    typename BinaryTree<Data>::Node *currentNode = nullptr;

    StackLst<typename BinaryTree<Data>::Node *> *stack = new StackLst<typename BinaryTree<Data>::Node *>();

    typename BinaryTree<Data>::Node *root = nullptr;

  public:
    // Specific constructors
    BTPreOrderIterator(const BinaryTree<Data> &); // An iterator over a given binary tree

    /* ************************************************************************ */

    // Copy constructor
    BTPreOrderIterator(const BTPreOrderIterator &);

    // Move constructor
    BTPreOrderIterator(BTPreOrderIterator &&);

    /* ************************************************************************ */

    // Destructor
    ~BTPreOrderIterator();

    /* ************************************************************************ */

    // Copy assignment
    BTPreOrderIterator &operator=(const BTPreOrderIterator<Data> &);

    // Move assignment
    BTPreOrderIterator &operator=(BTPreOrderIterator<Data> &&);

    /* ************************************************************************ */

    // Comparison operators
    bool operator==(const BTPreOrderIterator<Data> &) const noexcept;
    bool operator!=(const BTPreOrderIterator<Data> &) const noexcept;

    /* ************************************************************************ */

    // Specific member functions (inherited from Iterator)

    Data &operator*() const override; // (throw std::out_of_range when terminated)

    bool Terminated() const noexcept override; // (should not throw exceptions)

    /* ************************************************************************ */

    // Specific member functions (inherited from ForwardIterator)

    void operator++() override; // (throw std::out_of_range when terminated)

    /* ************************************************************************ */

    // Specific member functions (inherited from ResettableIterator)

    void Reset() noexcept override; // (should not throw exceptions)
  };

  /* ************************************************************************** */

  template <typename Data>
  class BTPostOrderIterator : virtual public ForwardIterator<Data>,
                              virtual public ResettableIterator<Data>
  {
    // Must extend ForwardIterator<Data>,
    //             ResettableIterator<Data>

  private:
    // ...

    typename BinaryTree<Data>::Node *currentNode = nullptr;

    StackLst<typename BinaryTree<Data>::Node *> *stack= new StackLst<typename BinaryTree<Data>::Node *>();

    typename BinaryTree<Data>::Node *root = nullptr;

  protected:
    typename BinaryTree<Data>::Node &LeftMostLeaf(typename BinaryTree<Data>::Node &) const;

  public:
    // Specific constructors
    BTPostOrderIterator(const BinaryTree<Data> &); // An iterator over a given binary tree

    /* ************************************************************************ */

    // Copy constructor
    BTPostOrderIterator(const BTPostOrderIterator<Data> &);

    // Move constructor
    BTPostOrderIterator(BTPostOrderIterator<Data> &&);

    /* ************************************************************************ */

    // Destructor
    ~BTPostOrderIterator();

    /* ************************************************************************ */

    // Copy assignment
    BTPostOrderIterator<Data> &operator=(const BTPostOrderIterator<Data> &);

    // Move assignment
    BTPostOrderIterator<Data> &operator=(BTPostOrderIterator<Data> &&);

    /* ************************************************************************ */

    // Comparison operators
    bool operator==(const BTPostOrderIterator<Data> &) const noexcept;
    bool operator!=(const BTPostOrderIterator<Data> &) const noexcept;

    /* ************************************************************************ */

    // Specific member functions (inherited from Iterator)

    Data &operator*() const override; // (throw std::out_of_range when terminated)

    bool Terminated() const noexcept override; // (should not throw exceptions)

    /* ************************************************************************ */

    // Specific member functions (inherited from ForwardIterator)

    void operator++() override; // (throw std::out_of_range when terminated)
    // Essendo in postOrder, quando faccio ++ son sicuro di aver già visitato tutto ciò che c'è sotto. L'unica cosa
    // che devo fare è guardare allo stack e fare top. Del nodo che mi viene restituito posso essere o foglio destro
    // o figlio sinistro. Se sono figlio destro, avendo sicuramente già visitato il sottoalbero sinistro, posso visitarlo
    // Viceversa, se sono figlio sinistro devontro controllare il sottoalbero destra radicato in "mio padre" usando
    // la funzione protetta per trovare la minima foglia sinistra.
    /* ************************************************************************ */

    // Specific member functions (inherited from ResettableIterator)

    void Reset() noexcept override; // (should not throw exceptions)
  };

  /* ************************************************************************** */

  template <typename Data>
  class BTInOrderIterator : virtual public ForwardIterator<Data>,
                            virtual public ResettableIterator<Data>
  {
    // Must extend ForwardIterator<Data>,
    //             ResettableIterator<Data>

  private:
    // ...

    typename BinaryTree<Data>::Node *currentNode = nullptr;

    StackLst<typename BinaryTree<Data>::Node *> *stack= new StackLst<typename BinaryTree<Data>::Node *>();

    typename BinaryTree<Data>::Node *root = nullptr;

  protected:
    typename BinaryTree<Data>::Node &LeftMostNode(typename BinaryTree<Data>::Node &) const;

  public:
    // Specific constructors
    BTInOrderIterator(const BinaryTree<Data> &); // An iterator over a given binary tree

    /* ************************************************************************ */

    // Copy constructor
    BTInOrderIterator(const BTInOrderIterator &);

    // Move constructor
    BTInOrderIterator(BTInOrderIterator &&);

    /* ************************************************************************ */

    // Destructor
    ~BTInOrderIterator();

    /* ************************************************************************ */

    // Copy assignment
    BTInOrderIterator &operator=(const BTInOrderIterator &);

    // Move assignment
    BTInOrderIterator &operator=(BTInOrderIterator &&);

    /* ************************************************************************ */

    // Comparison operators
    bool operator==(const BTInOrderIterator &) const noexcept;
    bool operator!=(const BTInOrderIterator &) const noexcept;

    /* ************************************************************************ */

    // Specific member functions (inherited from Iterator)

    Data &operator*() const override; // (throw std::out_of_range when terminated)

    bool Terminated() const noexcept override; // (should not throw exceptions)

    /* ************************************************************************ */

    // Specific member functions (inherited from ForwardIterator)

    void operator++() override; // (throw std::out_of_range when terminated)

    /* ************************************************************************ */

    // Specific member functions (inherited from ResettableIterator)

    void Reset() noexcept override; // (should not throw exceptions)
  };

  /* ************************************************************************** */

  template <typename Data>
  class BTBreadthIterator : virtual public ForwardIterator<Data>,
                            virtual public ResettableIterator<Data>
  {
    // Must extend ForwardIterator<Data>,
    //             ResettableIterator<Data>

  private:
    // ...

    typename BinaryTree<Data>::Node *currentNode = nullptr;

    QueueLst<typename BinaryTree<Data>::Node *> *queue = new QueueLst<typename BinaryTree<Data>::Node *>();

    typename BinaryTree<Data>::Node *root = nullptr;

  protected:
    // ...

  public:
    // Specific constructors
    BTBreadthIterator(const BinaryTree<Data> &); // An iterator over a given binary tree
    /* ************************************************************************ */

    // Copy constructor
    BTBreadthIterator(const BTBreadthIterator &);

    // Move constructor
    BTBreadthIterator(BTBreadthIterator &&);

    /* ************************************************************************ */

    // Destructor
    ~BTBreadthIterator() = default;

    /* ************************************************************************ */

    // Copy assignment
    BTBreadthIterator &operator=(const BTBreadthIterator<Data> &);

    // Move assignment
    BTBreadthIterator &operator=(BTBreadthIterator<Data> &&);

    /* ************************************************************************ */

    // Comparison operators
    bool operator==(const BTBreadthIterator<Data> &) const noexcept;
    bool operator!=(const BTBreadthIterator<Data> &) const noexcept;

    /* ************************************************************************ */

    // Specific member functions (inherited from Iterator)

    Data &operator*() const override; // (throw std::out_of_range when terminated)

    bool Terminated() const noexcept override; // (should not throw exceptions)

    /* ************************************************************************ */

    // Specific member functions (inherited from ForwardIterator)

    void operator++() override; // (throw std::out_of_range when terminated)

    /* ************************************************************************ */

    // Specific member functions (inherited from ResettableIterator)

    void Reset() noexcept override; // (should not throw exceptions)
  };

  /* ************************************************************************** */

}

#include "binarytree.cpp"

#endif
