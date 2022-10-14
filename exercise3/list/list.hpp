
#ifndef LIST_HPP
#define LIST_HPP

/* ************************************************************************** */

#include "../container/container.hpp"

/* ************************************************************************** */

namespace lasd {

/* ************************************************************************** */

template <typename Data>
class List :   virtual public LinearContainer<Data>,
               virtual public PreOrderMappableContainer<Data>,
               virtual public PostOrderMappableContainer<Data>,
               virtual public PreOrderFoldableContainer<Data>,
               virtual public PostOrderFoldableContainer<Data>
               {

private:

  // ...

protected:

  using LinearContainer<Data>::size;

  struct Node {

    // Data
    Data elem;
    struct Node* next = nullptr;    

    /* ********************************************************************** */

    Node() = default;

    // Specific constructors

    Node(const Data&);
    Node(Data&&) noexcept;

    /* ********************************************************************** */

    // Copy constructor
    
    Node(const Node&);

    // Move constructor
    
    Node(Node&&) noexcept;

    // Destructor

    ~Node() = default;


    /* ********************************************************************** */

    // Assignment

    Node& operator=(const Node&);

    Node& operator=(Node&&);

    /* ********************************************************************** */
    

    // Comparison operators
    
    inline bool operator==(const Node&) const noexcept;
    bool operator!=(const Node&) const noexcept;

    /* ********************************************************************** */

    // Specific member functions

    // ...

  };

  struct Node* head = nullptr;

  // ...

public:

  // Default constructor
  List();

  /* ************************************************************************ */

  // Specific constructor
  List(const LinearContainer<Data>&);

  /* ************************************************************************ */

  // Copy constructor
  List(const List<Data>&);

  // Move constructor
  List(List<Data>&&);

  /* ************************************************************************ */

  // Destructor
  ~List();

  /* ************************************************************************ */

  // Copy assignment
  List& operator=(const List<Data>&);

  // Move assignment
  List& operator=(List&&) noexcept;

  /* ************************************************************************ */

  // Comparison operators
  bool operator==(const List<Data>&) const noexcept;
  bool operator!=(const List<Data>&) const noexcept;

  /* ************************************************************************ */

  // Specific member functions

  void InsertAtFront(const Data&); // Copy of the value
  void InsertAtFront(Data&&) noexcept; // Move of the value
  void RemoveFromFront();
  Data FrontNRemove();

  void InsertAtBack(const Data&); // Copy of the value
  void InsertAtBack(Data&&) noexcept; // Move of the value

  /* ************************************************************************ */

  // Specific member functions (inherited from Container)

  void Clear() override;

  /* ************************************************************************ */

  // Specific member functions (inherited from LinearContainer)

  Data& Front() const override; // Override LinearContainer member (must throw std::length_error when empty)
  Data& Back() const override; // Override LinearContainer member (must throw std::length_error when empty)

  Data& operator[](const unsigned long) const override; // Override LinearContainer member (must throw std::out_of_range when out of range)

  /* ************************************************************************ */

  // Specific member functions (inherited from MappableContainer)

  using typename MappableContainer<Data>::MapFunctor;
  void Map(MapFunctor, void*) override; // Override MappableContainer member

  /* ************************************************************************ */

  // Specific member functions (inherited from PreOrderMappableContainer)

  void MapPreOrder(const MapFunctor, void*) override; // Override PreOrderMappableContainer member

  /* ************************************************************************ */

  // Specific member functions (inherited from PostOrderMappableContainer)

  void MapPostOrder(const MapFunctor, void*) override; // Override PostOrderMappableContainer member

  /* ************************************************************************ */

  // Specific member functions (inherited from FoldableContainer)

  using typename FoldableContainer<Data>::FoldFunctor;
  void Fold(FoldFunctor, const void*, void*) const override; // Override FoldableContainer member

  /* ************************************************************************ */

  // Specific member functions (inherited from PreOrderFoldableContainer)

  void FoldPreOrder(const FoldFunctor, const void*, void*) const override; // Override FoldableContainer member

  /* ************************************************************************ */

  // Specific member functions (inherited from PostOrderFoldableContainer)

  void FoldPostOrder(const FoldFunctor, const void*, void*) const override; // Override FoldableContainer member

protected:

  // Auxiliary member functions (for PreOrderMappableContainer & PostOrderMappableContainer)

  void MapPreOrder(const MapFunctor, void*, unsigned long); // Accessory function executing from one point of the list onwards
  void MapPostOrder(const MapFunctor, void*, unsigned long); // Accessory function executing from one point of the list onwards

  /* ************************************************************************ */

  // Auxiliary member functions (for PreOrderFoldableContainer & PostOrderFoldableContainer)

  void FoldPreOrder(const FoldFunctor, const void*, void*, unsigned long); // Accessory function executing from one point of the list onwards
  void FoldPostOrder(const FoldFunctor, const void*, void*, unsigned long); // Accessory function executing from one point of the list onwards

};

/* ************************************************************************** */

}

#include "list.cpp"

#endif
