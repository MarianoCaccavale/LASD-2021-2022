
#ifndef ITERATOR_HPP
#define ITERATOR_HPP

/* ************************************************************************** */

namespace lasd
{

  /* ************************************************************************** */

  template <typename Data>
  class Iterator
  {

  private:
    // ...

  protected:
    // ...

  public:
    // Destructor
    virtual ~Iterator() = default;

    /* ************************************************************************ */

    // Copy assignment
    Iterator &operator=(const Iterator &) const = delete; // Copy assignment of abstract types should not be possible.

    // Move assignment
    Iterator &operator=(Iterator &&) = delete; // Move assignment of abstract types should not be possible.

    /* ************************************************************************ */

    // Comparison operators
    virtual bool operator==(const Iterator &) const noexcept = delete; // Comparison of abstract types might not be possible.
    virtual bool operator!=(const Iterator &) const noexcept = delete; // Comparison of abstract types might not be possible.

    /* ************************************************************************ */

    // Specific member functions

    virtual Data &operator*() const = 0; // (concrete function must throw std::out_of_range when terminated)

    virtual bool Terminated() const noexcept = 0; // (concrete function should not throw exceptions)
  };

  /* ************************************************************************** */

  template <typename Data>
  class ForwardIterator : public virtual Iterator<Data>
  { // Must extend Iterator<Data>

  private:
    // ...

  protected:
    // ...

  public:
    // Destructor
    virtual ~ForwardIterator() = default;

    /* ************************************************************************ */

    // Copy assignment
    ForwardIterator &operator=(const ForwardIterator &) const = delete; // Copy assignment of abstract types should not be possible.

    // Move assignment
    ForwardIterator &operator=(ForwardIterator &&) = delete; // Move assignment of abstract types should not be possible.

    /* ************************************************************************ */

    // Comparison operators
    virtual bool operator==(const ForwardIterator &) const noexcept = delete; // Comparison of abstract types might not be possible.
    virtual bool operator!=(const ForwardIterator &) const noexcept = delete; // Comparison of abstract types might not be possible.

    /* ************************************************************************ */

    // Specific member functions
    virtual void operator++() = 0; // (concrete function must throw std::out_of_range when terminated)
  };

  /* ************************************************************************** */

  template <typename Data>
  class BackwardIterator //: virtual public Iterator<Data>
  {                      // Must extend Iterator<Data>

  private:
    // ...

  protected:
    // ...

  public:
    // Destructor
    // virtual ~BackwardIterator() = default;

    /* ************************************************************************ */

    // Copy assignment
    // BackwardIterator &operator=(const BackwardIterator &) const = delete; // Copy assignment of abstract types should not be possible.

    // Move assignment
    // BackwardIterator &operator=(BackwardIterator &&) = delete; // Move assignment of abstract types should not be possible.

    /* ************************************************************************ */

    // Comparison operators
    // bool operator==(const BackwardIterator &) const noexcept = 0; // Comparison of abstract types might not be possible.
    // bool operator!=(const BackwardIterator &) const noexcept = 0; // Comparison of abstract types might not be possible.

    /* ************************************************************************ */

    // Specific member functions
    // type operator--() specifiers; // (concrete function must throw std::out_of_range when terminated)
  };

  /* ************************************************************************** */

  template <typename Data>
  class BidirectionalIterator //: virtual public ForwardIterator<Data>,
                              // virtual public BackwardIterator<Data>
  {
    // Must extend ForwardIterator<Data>,
    //             BackwardIterator<Data>

  private:
    // ...

  protected:
    // ...

  public:
    // Destructor
    // virtual ~BidirectionalIterator() = default;

    /* ************************************************************************ */

    // Copy assignment
    // BidirectionalIterator &operator=(const BidirectionalIterator &) const = delete; // Copy assignment of abstract types should not be possible.

    // Move assignment
    // BidirectionalIterator &operator=(BidirectionalIterator &&) = delete; // Move assignment of abstract types should not be possible.

    /* ************************************************************************ */

    // Comparison operators
    // bool operator==(const BidirectionalIterator &) const noexcept = 0; // Comparison of abstract types might not be possible.
    // bool operator!=(const BidirectionalIterator &) const noexcept = 0; // Comparison of abstract types might not be possible.

    /* ************************************************************************ */

    // Specific member functions

    // bool Terminated() const override; // Override Iterator member

    // bool ForwardTerminated() noexcept; // (concrete function should not throw exceptions)

    // bool BackwardTerminated() noexcept; // (concrete function should not throw exceptions)
  };

  /* ************************************************************************** */

  template <typename Data>
  class ResettableIterator : virtual public Iterator<Data>
  { // Must extend Iterator<Data>

  private:
  protected:
  public:
    // Destructor
    virtual ~ResettableIterator() = default;

    /* ************************************************************************ */

    // Copy assignment
    ResettableIterator &operator=(const ResettableIterator &) noexcept = delete; // Copy assignment of abstract types should not be possible.

    // Move assignment
    ResettableIterator &operator=(ResettableIterator &&) = delete; // Move assignment of abstract types should not be possible.

    /* ************************************************************************ */

    // Comparison operators
    virtual bool operator==(const ResettableIterator &) const noexcept = delete; // Comparison of abstract types might not be possible.
    virtual bool operator!=(const ResettableIterator &) const noexcept = delete; // Comparison of abstract types might not be possible.

    /* ************************************************************************ */

    // Specific member functions
    virtual void Reset() noexcept = 0; // (concrete function should not throw exceptions)
  };

  /* ************************************************************************** */

}

#endif
