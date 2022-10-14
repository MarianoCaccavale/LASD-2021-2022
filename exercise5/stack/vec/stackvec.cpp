
namespace lasd
{

    /* ************************************************************************** */

    template <typename Data>
    StackVec<Data>::StackVec()
    {
        this->size = 2;
        this->Elementi = new Data[this->size];
        this->head = 0;
    }

    template <typename Data>
    StackVec<Data>::StackVec(const LinearContainer<Data> &container)
    {

        this->size = container.Size();
        this->head = 0;

        this->Elementi = new Data[container.Size()];
        for (unsigned long i = 0; i < container.Size(); i++)
        {
            std::cout << i << std::endl;
            this->Push(container[i]);
        }
    }

    template <typename Data>
    StackVec<Data>::StackVec(const StackVec<Data> &otherStack)
    {
        this->size = otherStack.size;
        this->head = otherStack.head;
        this->Elementi = new Data[this->size];
        std::copy(otherStack.Elementi, otherStack.Elementi + otherStack.size, this->Elementi);
    }

    template <typename Data>
    StackVec<Data>::StackVec(StackVec<Data> &&otherStack)
    {
        std::swap(this->size, otherStack.size);
        std::swap(this->Elementi, otherStack.Elementi);
        std::swap(this->head, otherStack.head);
    }

    template <typename Data>
    StackVec<Data>::~StackVec()
    {
        this->size = 0;
        // delete[] this->Elementi;
        this->head = 0;
    }

    template <typename Data>
    StackVec<Data> &StackVec<Data>::operator=(const StackVec<Data> &otherStack)
    {
        StackVec<Data> *temp_StackVec = new StackVec<Data>(otherStack);
        std::swap(*temp_StackVec, *this);
        delete temp_StackVec;
        return *this;
    }

    template <typename Data>
    StackVec<Data> &StackVec<Data>::operator=(StackVec<Data> &&otherStack)
    {
        std::swap(this->size, otherStack.size);
        std::swap(this->Elementi, otherStack.Elementi);
        std::swap(this->head, otherStack.head);
        return *this;
    }

    template <typename Data>
    bool StackVec<Data>::operator==(const StackVec<Data> &otherStack) const noexcept
    {
        if (this->size != otherStack.size || this->head != otherStack.head)
        {

            return false;
        }

        for (ulong i = 0; i < this->head; i++)
        {
            if (this->Elementi[i] != otherStack.Elementi[i])
                return false;
        }

        return true;
    }

    template <typename Data>
    bool StackVec<Data>::operator!=(const StackVec<Data> &otherStack) const noexcept
    {

        return !(*this == otherStack);
    }

    template <typename Data>
    const Data &StackVec<Data>::Top() const
    {

        if (this->Empty())
        {
            throw std::length_error("Stack vuoto!");
        }

        return this->Elementi[this->head - 1];
    }

    template <typename Data>
    Data &StackVec<Data>::Top()
    {

        if (this->Empty())
        {
            throw std::length_error("Stack vuoto!");
        }

        return this->Elementi[this->head - 1];
    }

    template <typename Data>
    void StackVec<Data>::Pop()
    {

        if (this->Empty())
        {
            throw std::length_error("Stack vuoto!");
        }

        this->head -= 1;

        if (this->head < (this->size / 2))
        {

            this->Reduce();
        }
    }

    template <typename Data>
    Data StackVec<Data>::TopNPop()
    {

        // Controllo superfluo, in quanto sia il top che il pop controllano la size della struttura.
        /* if (this->Empty())
        {
            throw std::length_error("Stack vuoto!");
        } */

        Data returnData = this->Top();
        this->Pop();
        return returnData;
    }

    template <typename Data>
    void StackVec<Data>::Push(const Data &dataToAdd)
    {

        if (this->head + 1 >= this->size)
        {
            this->Expand();
        }

        this->Elementi[this->head++] = dataToAdd;
    }

    template <typename Data>
    void StackVec<Data>::Push(Data &&dataToAdd)
    {

        if (this->head + 1 >= this->size)
        {
            this->Expand();
        }

        this->Elementi[this->head++] = dataToAdd;
    }

    template <typename Data>
    bool StackVec<Data>::Empty() const noexcept
    {
        return this->head == 0;
    }

    template <typename Data>
    unsigned long inline StackVec<Data>::Size() const noexcept
    {
        return this->head;
    }

    template <typename Data>
    void StackVec<Data>::Clear()
    {

        this->Resize(2);
        this->head = 0;
    }

    template <typename Data>
    void StackVec<Data>::Expand()
    {

        this->Resize(this->size * 2);
    }

    template <typename Data>
    void StackVec<Data>::Reduce()
    {

        this->Resize(this->size * 0.5);
    }

    /* ************************************************************************** */

}
