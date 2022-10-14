
namespace lasd
{

    /* ************************************************************************** */

    // NodeLnk methods
    template <typename Data>
    BinaryTreeLnk<Data>::NodeLnk::NodeLnk(const Data &dato)
    {
        this->data = dato;
    }

    template <typename Data>
    BinaryTreeLnk<Data>::NodeLnk::NodeLnk(const NodeLnk &otherNode)
    {
        this->data = otherNode.data;
        this->leftChild = otherNode.leftChild;
        this->rightChild = otherNode.rightChild;
    }

    template <typename Data>
    BinaryTreeLnk<Data>::NodeLnk::NodeLnk(NodeLnk &&otherNode)
    {
        std::swap(this->data, otherNode.data);
        std::swap(this->leftChild, otherNode.leftChild);
        std::swap(this->rightChild, otherNode.rightChild);
    }

    template <typename Data>
    bool BinaryTreeLnk<Data>::NodeLnk::operator==(const NodeLnk &otherNode) const noexcept
    {
        return (this->data == otherNode.data &&
                this->leftChild == otherNode.leftChild &&
                this->rightChild == otherNode.rightChild);
    }

    template <typename Data>
    bool BinaryTreeLnk<Data>::NodeLnk::operator!=(const NodeLnk &otherNode) const noexcept
    {
        return !(*this == otherNode);
    }

    template <typename Data>
    typename BinaryTreeLnk<Data>::NodeLnk &BinaryTreeLnk<Data>::NodeLnk::operator=(const NodeLnk &otherNode)
    {
        this->data = otherNode.data;
        this->leftChild = otherNode.leftChild;
        this->rightChild = otherNode.rightChild;
        return *this;
    }

    template <typename Data>
    typename BinaryTreeLnk<Data>::NodeLnk &BinaryTreeLnk<Data>::NodeLnk::operator=(NodeLnk &&otherNode)
    {
        std::swap(this->data, otherNode.data);
        std::swap(this->leftChild, otherNode.leftChild);
        std::swap(this->rightChild, otherNode.rightChild);
        return *this;
    }

    template <typename Data>
    BinaryTreeLnk<Data>::NodeLnk::~NodeLnk()
    {
        if(this->leftChild != nullptr)
            delete this->leftChild;
        if(this->rightChild != nullptr)
            delete this->rightChild;
    }

    template <typename Data>
    Data &BinaryTreeLnk<Data>::NodeLnk::Element() noexcept
    {
        return this->data;
    }

    template <typename Data>
    const Data &BinaryTreeLnk<Data>::NodeLnk::Element() const noexcept
    {
        return this->data;
    }

    template <typename Data>
    bool BinaryTreeLnk<Data>::NodeLnk::HasLeftChild() const noexcept
    {
        return (this->leftChild != nullptr);
    }

    template <typename Data>
    bool BinaryTreeLnk<Data>::NodeLnk::HasRightChild() const noexcept
    {
        return (this->rightChild != nullptr);
    }

    template <typename Data>
    typename BinaryTreeLnk<Data>::NodeLnk &BinaryTreeLnk<Data>::NodeLnk::LeftChild() const
    {
        if (this->leftChild == nullptr)
            throw std::length_error("Impossibile restituire nodo sinistro!");

        return *(this->leftChild);
    }

    template <typename Data>
    typename BinaryTreeLnk<Data>::NodeLnk &BinaryTreeLnk<Data>::NodeLnk::RightChild() const
    {
        if (this->rightChild == nullptr)
            throw std::length_error("Impossibile restituire nodo destro!");

        return *(this->rightChild);
    }

    /* ************************************************************************** */

    // BinaryTreeLnk methods

    template <typename Data>
    BinaryTreeLnk<Data>::BinaryTreeLnk(const LinearContainer<Data> &container)
    {
        this->size = container.Size();

        if (this->size > 0)
        {
            root = new NodeLnk(container[0]);

            QueueLst<NodeLnk *> queue = QueueLst<NodeLnk *>();
            queue.Enqueue(root);

            NodeLnk *curr = root;

            for (ulong i = 1; i < container.Size(); i++)
            {
                if (!curr->HasLeftChild())
                {
                    curr->leftChild = new NodeLnk(container[i]);
                    queue.Enqueue(curr->leftChild);
                }
                else
                {
                    curr->rightChild = new NodeLnk(container[i]);
                    queue.Enqueue(curr->rightChild);
                    queue.Dequeue();
                    curr = queue.Head();
                }
            }
        }
    }

    template <typename Data>
    BinaryTreeLnk<Data>::BinaryTreeLnk(const BinaryTreeLnk<Data> &otherTree)
    {
        this->size = otherTree.size;

        // devo fare la stessa cosa che faccio col costruttore che prende un linear container, ma scorrendo l'albero
        // in quel modo. Uso l'iteratore in quanto la visita è praticamente già fatta

        if (this->size > 0)
        {

            this->root = new NodeLnk(otherTree.Root().Element());

            BTBreadthIterator<Data> supportIterator = BTBreadthIterator<Data>(otherTree);

            QueueLst<NodeLnk *> queue = QueueLst<NodeLnk *>();

            NodeLnk *currentNode = this->root;

            int i = 1;

            ++supportIterator;
            while (!supportIterator.Terminated())
            {

                if (!currentNode->HasLeftChild())
                {
                    currentNode->leftChild = new NodeLnk(*supportIterator);
                    queue.Enqueue(currentNode->leftChild);
                    ++supportIterator;
                }
                else
                {
                    currentNode->rightChild = new NodeLnk(*supportIterator);
                    queue.Enqueue(currentNode->rightChild);
                    currentNode = queue.HeadNDequeue();
                    ++supportIterator;
                }

                i++;
            }
        }
    }

    template <typename Data>
    BinaryTreeLnk<Data>::BinaryTreeLnk(BinaryTreeLnk<Data> &&otherTree) noexcept
    {
        std::swap(this->root, otherTree.root);
        std::swap(this->size, otherTree.size);
    }

    template <typename Data>
    BinaryTreeLnk<Data> &BinaryTreeLnk<Data>::operator=(const BinaryTreeLnk &otherTree)
    {
        this->size = otherTree.size;
        this->root = otherTree.root;
        return *this;
    }

    template <typename Data>
    BinaryTreeLnk<Data> &BinaryTreeLnk<Data>::operator=(BinaryTreeLnk &&otherTree)
    {
        std::swap(this->root, otherTree.root);
        std::swap(this->size, otherTree.size);
        return *this;
    }

    template <typename Data>
    bool BinaryTreeLnk<Data>::operator==(const BinaryTreeLnk &otherTree) const noexcept
    {
        return *(this->root) == *(otherTree.root);
    }

    template <typename Data>
    bool BinaryTreeLnk<Data>::operator!=(const BinaryTreeLnk &otherTree) const noexcept
    {
        return !(*this == otherTree);
    }

    template <typename Data>
    typename BinaryTreeLnk<Data>::NodeLnk &BinaryTreeLnk<Data>::Root() const
    {

        if (this->root == nullptr)
            throw std::length_error("Impossibile restituire la radice, l'albero è vuoto");

        return *root;
    }

    template <typename Data>
    void BinaryTreeLnk<Data>::Clear()
    {
        this->size = 0;
        delete this->root;
        this->root = nullptr;
    }

    /* ************************************************************************** */

}
