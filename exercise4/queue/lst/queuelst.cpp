
namespace lasd
{

    /* ************************************************************************** */

    template <typename Data>
    QueueLst<Data>::QueueLst()
    {
        this->size = 0;
        this->head = nullptr;
        this->tail = nullptr;
    }

    template <typename Data>
    QueueLst<Data>::QueueLst(const LinearContainer<Data> &container)
    {

        if (container.Size() == 0)
        {
            this->size = 0;
            this->head = 0;
            this->tail = 0;
        }
        else
        {

            for (ulong i = 0; i < container.Size(); i++)
            {
                this->Enqueue(container[i]);
            }
        }
    }

    template <typename Data>
    QueueLst<Data>::QueueLst(const QueueLst<Data> &otherQueue)
    {

        Node *currOtherNode = otherQueue.head;

        for (ulong i = 0; i < otherQueue.size; i++)
        {
            this->Enqueue(currOtherNode->elem);
            currOtherNode = currOtherNode->next;
        }

        delete currOtherNode;
    }

    template <typename Data>
    QueueLst<Data>::QueueLst(QueueLst<Data> &&otherQueue)
    {
        std::swap(this->size, otherQueue.size);
        std::swap(this->head, otherQueue.head);
        std::swap(this->tail, otherQueue.tail);
    }

    template <typename Data>
    QueueLst<Data>::~QueueLst()
    {
        this->size = 0;
        this->head = nullptr;
        this->tail = nullptr;
    }

    template <typename Data>
    QueueLst<Data> &QueueLst<Data>::operator=(const QueueLst<Data> &otherQueue)
    {
        QueueLst<Data> *tmpQueue = new QueueLst<Data>(otherQueue);
        std::swap(*this, *tmpQueue);
        delete tmpQueue;
        return *this;
    }

    template <typename Data>
    QueueLst<Data> &QueueLst<Data>::operator=(QueueLst<Data> &&otherQueue)
    {
        std::swap(this->size, otherQueue.size);
        std::swap(this->head, otherQueue.head);
        std::swap(this->tail, otherQueue.tail);
        return *this;
    }

    template <typename Data>
    bool QueueLst<Data>::operator==(const QueueLst<Data> &otherQueue) const noexcept
    {

        if (this->size != otherQueue.size)
            return false;

        Node *currentThisHead = this->head;
        Node *currentOtherHead = otherQueue.head;

        for (ulong i = 0; i < this->size; i++)
        {

            if (currentThisHead->elem != currentOtherHead->elem)
                return false;

            currentThisHead = currentThisHead->next;
            currentOtherHead = currentOtherHead->next;
        }

        delete currentThisHead;
        delete currentOtherHead;

        return true;
    }

    template <typename Data>
    bool QueueLst<Data>::operator!=(const QueueLst<Data> &otherQueue) const noexcept
    {
        return !(*this == otherQueue);
    }

    template <typename Data>
    const Data &QueueLst<Data>::Head() const
    {
        if (this->size == 0)
            throw std::length_error("Queue vuota!");

        return this->Front();
    }

    template <typename Data>
    Data &QueueLst<Data>::Head()
    {
        if (this->size == 0)
            throw std::length_error("Queue vuota!");
        return this->Front();
    }

    template <typename Data>
    void QueueLst<Data>::Dequeue()
    {
        if (this->size == 0)
            throw std::length_error("Queue vuota!");

        this->RemoveFromFront();

        /* Node *nodeToDelete = this->tail;
        this->tail = (this->tail)->next;
        delete nodeToDelete; */
    }

    template <typename Data>
    Data QueueLst<Data>::HeadNDequeue()
    {
        if (this->size == 0)
            throw std::length_error("Queue vuota!");

        Data dataToReturn = this->Head();
        this->Dequeue();
        return dataToReturn;
    }

    template <typename Data>
    void QueueLst<Data>::Enqueue(const Data &dataToAdd)
    {
        if (this->head == nullptr)
        {

            this->size += 1;
            Node *new_node = new Node(dataToAdd);
            this->head = this->tail = new_node;
        }
        else
        {

            this->size += 1;
            Node *new_node = new Node(dataToAdd);
            (this->tail)->next = new_node;
            this->tail = new_node;
        }
    }

    template <typename Data>
    void QueueLst<Data>::Enqueue(Data &&dataToAdd)
    {
        if (this->head == nullptr)
        {

            this->size += 1;
            Node *new_node = new Node(dataToAdd);
            this->head = this->tail = new_node;
        }
        else
        {

            this->size += 1;
            Node *new_node = new Node(dataToAdd);
            (this->tail)->next = new_node;
            this->tail = new_node;
        }
    }

    // Specific member functions (inherited from Container)

    template <typename Data>
    void QueueLst<Data>::Clear()
    {
        List<Data>::Clear();
        this->head = nullptr;
        this->tail = nullptr;
    }

    /* ************************************************************************** */

}
