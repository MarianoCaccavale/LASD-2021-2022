
#include <iostream>

namespace lasd
{

    /* ************************************************************************** */

    template <typename Data>
    QueueVec<Data>::QueueVec()
    {
        this->size = 2;
        this->Elementi = new Data[this->size];
        this->head = 0;
        this->tail = 0;
    }

    template <typename Data>
    QueueVec<Data>::QueueVec(const LinearContainer<Data> &container)
    {

        this->size = container.Size();
        this->tail = 0;
        this->Elementi = new Data[container.Size()];

        for (ulong i = 0; i < container.Size(); i++)
        {
            this->Enqueue(container[i]);
            //this->Elementi[i] = container[i];
            //this->head++;
        }
    }

    template <typename Data>
    QueueVec<Data>::QueueVec(const QueueVec<Data> &otherQueue)
    {
        this->size = otherQueue.size;
        this->head = otherQueue.head;
        this->tail = otherQueue.tail;
        this->Elementi = new Data[otherQueue.size];
        std::copy(otherQueue.Elementi, otherQueue.Elementi + otherQueue.size, this->Elementi);
    }

    template <typename Data>
    QueueVec<Data>::QueueVec(QueueVec<Data> &&otherQueue)
    {
        std::swap(this->size, otherQueue.size);
        std::swap(this->Elementi, otherQueue.Elementi);
        std::swap(this->head, otherQueue.head);
        std::swap(this->tail, otherQueue.tail);
    }

    template <typename Data>
    QueueVec<Data>::~QueueVec()
    {
        this->size = 0;
        this->head = 0;
        this->tail = 0;
    }

    template <typename Data>
    QueueVec<Data> &QueueVec<Data>::operator=(const QueueVec<Data> &otherQueue)
    {

        QueueVec<Data>* queueTmp = new QueueVec<Data>(otherQueue);
        std::swap(*this, *queueTmp);
        delete queueTmp;
        return *this;
    }

    template <typename Data>
    QueueVec<Data> &QueueVec<Data>::operator=(QueueVec<Data> &&otherQueue)
    {
        std::swap(this->size, otherQueue.size);
        std::swap(this->Elementi, otherQueue.Elementi);
        std::swap(this->head, otherQueue.head);
        std::swap(this->tail, otherQueue.tail);
        return *this;
    }

    template <typename Data>
    bool QueueVec<Data>::operator==(const QueueVec<Data> &otherQueue) const noexcept
    {

        if (this->size != otherQueue.size || this->head != otherQueue.head || this->tail != otherQueue.tail)
            return false;

        for (ulong i = 0; i < this->Size(); i++)
        {
            if (this->Elementi[(this->tail + i) % this->size] != otherQueue.Elementi[(otherQueue.tail + i) % otherQueue.size])
                return false;
        }

        return true;
    }

    template <typename Data>
    bool QueueVec<Data>::operator!=(const QueueVec<Data> &otherQueue) const noexcept
    {
        return !(*this == otherQueue);
    }

    template <typename Data>
    const Data &QueueVec<Data>::Head() const
    {
        if (this->Empty())
            throw std::length_error("Queue vuota!");

        return this->Elementi[this->tail];
    }

    template <typename Data>
    Data &QueueVec<Data>::Head()
    {
        if (this->Empty())
            throw std::length_error("Queue vuota!");

        return this->Elementi[this->tail];
    }

    template <typename Data>
    void QueueVec<Data>::Dequeue()
    {

        if (this->Empty())
            throw std::length_error("Queue vuota!");

        this->tail = (++this->tail) % this->size;
        if (this->Size() <= (this->size * 0.5))
            this->Reduce();
    }

    template <typename Data>
    Data QueueVec<Data>::HeadNDequeue()
    {
        if (this->Empty())
            throw std::length_error("Queue vuota!");

        Data dataToReturn = this->Head();
        this->Dequeue();
        return dataToReturn;
    }

    template <typename Data>
    void QueueVec<Data>::Enqueue(const Data &dataToAdd)
    {

        if (this->Size() + 1 >= this->size)
            this->Expand();

        this->Elementi[this->head] = dataToAdd;
        this->head = (this->head + 1) % this->size;
    }

    template <typename Data>
    void QueueVec<Data>::Enqueue(Data &&dataToAdd)
    {
        if (this->Size() + 1 >= this->size)
            this->Expand();

        this->Elementi[this->head] = dataToAdd;
        this->head = (this->head + 1) % this->size;
    }

    /* ************************************************************************** */

    // Specific member functions

    template <typename Data>
    bool QueueVec<Data>::Empty() const noexcept
    {
        return head == tail;
    }

    template <typename Data>
    ulong QueueVec<Data>::Size() const noexcept
    {
        if (this->tail > this->head)
        {

            return (this->size - (this->tail - this->head));
        }
        else
        {

            return (this->head - this->tail);
        }
    }

    template <typename Data>
    void QueueVec<Data>::Clear()
    {
        this->size = 2;
        this->head = 0;
        this->tail = 0;
    }

    /* ************************************************************************** */

    // Auxiliary member functions
    template <typename Data>
    void QueueVec<Data>::Expand()
    {

        ulong new_size = (this->size * 2);
        this->SwapVectors(new_size);
        this->size = new_size;

        // this->Resize(this->size * 2);
    }

    template <typename Data>
    void QueueVec<Data>::Reduce()
    {

        unsigned long new_size = (this->size * (0.5));

        if (new_size < 2)
        {
            new_size = 2;
        }

        this->SwapVectors(new_size);
        this->size = new_size;

        // this->Resize(this->size * 0.5);
    }

    template <typename Data>
    void QueueVec<Data>::SwapVectors(const ulong newSize) noexcept
    {

        Data *nuovo = new Data[newSize];

        for (ulong index = 0; index < this->Size(); ++index)
        {
            nuovo[index] = this->Elementi[(this->tail + index) % this->size];
        }

        std::swap(this->Elementi, nuovo);
        this->head = this->Size();
        this->tail = 0;

        delete[] nuovo;
        // std::swap(this->Elementi, otherVector.Elementi);
    }

}
