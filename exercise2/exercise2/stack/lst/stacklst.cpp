
namespace lasd
{

    /* ************************************************************************** */

    template <typename Data>
    StackLst<Data>::StackLst(const LinearContainer<Data> &container)
    {

        this->size = container.Size();

        this->head = new Node(container[0]);
        Node *currNode = this->head;

        for (ulong i = 1; i < container.Size(); i++)
        {

            Node *newNode = new Node(container[i]);
            currNode->next = newNode;
            currNode = currNode->next;
        }
    }

    template <typename Data>
    StackLst<Data>::StackLst(const StackLst<Data> &otherStack)
    {
        Node *otherCurrNode = otherStack.head;

        for (ulong i = 0; i < otherStack.Size(); i++)
        {
            this->InsertAtBack(otherCurrNode->elem);
            otherCurrNode = otherCurrNode->next;
        }
    }

    template <typename Data>
    StackLst<Data>::StackLst(StackLst<Data> &&otherStack) noexcept
    {

        std::swap(otherStack.head, this->head);
        std::swap(otherStack.size, this->size);
    }

    template <typename Data>
    StackLst<Data>::~StackLst()
    {
        this->size = 0;
        this->head = nullptr;
    }

    template <typename Data>
    StackLst<Data> &StackLst<Data>::operator=(const StackLst<Data> &otherStack)
    {

        StackLst<Data> *newStack = new StackLst<Data>(otherStack);
        std::swap(*this, *newStack);
        delete newStack;
        return *this;
    }

    template <typename Data>
    StackLst<Data> &StackLst<Data>::operator=(StackLst<Data> &&otherStack) noexcept
    {
        std::swap(otherStack.head, this->head);
        std::swap(otherStack.size, this->size);
        return *this;
    }

    template <typename Data>
    bool StackLst<Data>::operator==(const StackLst<Data> &otherStack) const noexcept
    {

        if (this->size != otherStack.size)
            return false;

        Node *currThisNode = this->head;
        Node *currOtherNode = otherStack.head;

        for (ulong i = 0; i < this->size; i++)
        {
            if (currThisNode->elem != currOtherNode->elem)
                return false;
            currThisNode = currThisNode->next;
            currOtherNode = currOtherNode->next;
        }

        return true;
    }

    template <typename Data>
    bool StackLst<Data>::operator!=(const StackLst<Data> &otherStack) const noexcept
    {
        return !(*this == otherStack);
    }

    template <typename Data>
    const Data &StackLst<Data>::Top() const
    {

        if (this->Empty())
        {
            throw std::length_error("Stack vuoto!");
        }

        return (this->head)->elem;
    }

    template <typename Data>
    Data &StackLst<Data>::Top()
    {

        if (this->Empty())
        {
            throw std::length_error("Stack vuoto!");
        }
        
        return (this->head)->elem;
    }

    template <typename Data>
    void StackLst<Data>::Pop()
    {

        if (this->size == 0)
        {
            throw std::length_error("Stack vuoto!");
        }

        this->RemoveFromFront();
    }

    template <typename Data>
    Data StackLst<Data>::TopNPop()
    {

        Data dataToReturn = this->Top();
        this->Pop();
        return dataToReturn;
    }

    template <typename Data>
    void StackLst<Data>::Push(const Data &dataToPush)
    {
        this->InsertAtFront(dataToPush);
    }

    template <typename Data>
    void StackLst<Data>::Push(Data &&dataToPush)
    {
        this->InsertAtFront(dataToPush);
    }

    template <typename Data>
    void StackLst<Data>::Clear()
    {
        this->size = 0;
        this->head = nullptr;
    }

    /* ************************************************************************** */

}
