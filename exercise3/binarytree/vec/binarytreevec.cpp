
namespace lasd
{

    /* ************************************************************************** */

    // NodeVec methods

    template <typename Data>
    BinaryTreeVec<Data>::NodeVec::NodeVec(const Data &dato, ulong index, Vector<NodeVec *> *vettoreDiAppartenenza)
    {
        this->data = dato;
        this->index = index;
        this->vecAppartenenza = vettoreDiAppartenenza;
    }

    template <typename Data>
    BinaryTreeVec<Data>::NodeVec::NodeVec(const NodeVec &otherNode)
    {
        this->data = otherNode.data;
        this->index = otherNode.index;
        this->vecAppartenenza = otherNode.vecAppartenenza;
    }

    template <typename Data>
    BinaryTreeVec<Data>::NodeVec::NodeVec(NodeVec &&otherNode)
    {
        std::swap(this->data, otherNode.data);
        std::swap(this->index, otherNode.index);
        std::swap(this->vecAppartenenza, otherNode.vecAppartenenza);
    }

    template <typename Data>
    typename BinaryTreeVec<Data>::NodeVec &BinaryTreeVec<Data>::NodeVec::operator=(const NodeVec &otherNode)
    {
        this->data = otherNode.data;
        this->index = otherNode.index;
        this->vecAppartenenza = otherNode.vecAppartenenza;
        return *this;
    }

    template <typename Data>
    typename BinaryTreeVec<Data>::NodeVec &BinaryTreeVec<Data>::NodeVec::operator=(NodeVec &&otherNode) noexcept
    {
        std::swap(this->data, otherNode.data);
        std::swap(this->index, otherNode.index);
        std::swap(this->vecAppartenenza, otherNode.vecAppartenenza);
        return *this;
    }

    template <typename Data>
    Data &BinaryTreeVec<Data>::NodeVec::Element() noexcept
    {
        return this->data;
    }

    template <typename Data>
    const Data &BinaryTreeVec<Data>::NodeVec::Element() const noexcept
    {
        return this->data;
    }

    template <typename Data>
    bool BinaryTreeVec<Data>::NodeVec::HasLeftChild() const noexcept
    {
        return ((((this->index + 1) * 2) - 1) < this->vecAppartenenza->Size());
    }

    template <typename Data>
    bool BinaryTreeVec<Data>::NodeVec::HasRightChild() const noexcept
    {
        return (((this->index + 1) * 2) < this->vecAppartenenza->Size());
    }

    template <typename Data>
    typename BinaryTreeVec<Data>::NodeVec &BinaryTreeVec<Data>::NodeVec::LeftChild() const
    {

        if ((((this->index + 1) * 2) - 1) >= this->vecAppartenenza->Size())
            throw std::length_error("Impossibile restituire il figlio sinistro, è inesistente");

        return *((*(this->vecAppartenenza))[((this->index + 1) * 2) - 1]);
    }

    template <typename Data>
    typename BinaryTreeVec<Data>::NodeVec &BinaryTreeVec<Data>::NodeVec::RightChild() const
    {
        if (((this->index + 1) * 2) >= this->vecAppartenenza->Size())
            throw std::length_error("Impossibile restituire il figlio destro, è inesistente");

        return *((*(this->vecAppartenenza))[(this->index + 1) * 2]);
    }

    /* ************************************************************************** */

    // BinaryTreeVec methods

    template <typename Data>
    BinaryTreeVec<Data>::BinaryTreeVec()
    {
        this->size = 0;
        this->vector = new Vector<NodeVec *>();
    }

    template <typename Data>
    BinaryTreeVec<Data>::BinaryTreeVec(const LinearContainer<Data> &container)
    {
        this->size = container.Size();
        this->vector = new Vector<NodeVec *>(container.Size());

        for (ulong i = 0; i < container.Size(); i++)
        {
            (*(this->vector))[i] = new NodeVec(container[i], i, this->vector);
        }
    }

    template <typename Data>
    BinaryTreeVec<Data>::BinaryTreeVec(const BinaryTreeVec<Data> &otherTree)
    {
        this->size = otherTree.size;
        this->vector = new Vector<NodeVec *>(*otherTree.vector);
    }

    template <typename Data>
    BinaryTreeVec<Data>::BinaryTreeVec(BinaryTreeVec<Data> &&otherTree)
    {
        std::swap(this->size, otherTree.size);
        std::swap(this->vector, otherTree.vector);
    }

    template <typename Data>
    BinaryTreeVec<Data>::~BinaryTreeVec()
    {
        delete this->vector;
    }

    template <typename Data>
    BinaryTreeVec<Data> &BinaryTreeVec<Data>::operator=(const BinaryTreeVec<Data> &otherTree)
    {
        this->size = otherTree.size;
        this->vector = new Vector<NodeVec *>(*otherTree.vector);
        return *this;
    }

    template <typename Data>
    BinaryTreeVec<Data> &BinaryTreeVec<Data>::operator=(BinaryTreeVec<Data> &&otherTree)
    {
        std::swap(this->size, otherTree.size);
        std::swap(this->vector, otherTree.vector);
        return *this;
    }

    template <typename Data>
    bool BinaryTreeVec<Data>::operator==(const BinaryTreeVec<Data> &otherTree) const noexcept
    {
        if(this->size != otherTree.Size()) return false;
        return (*((*(this->vector))[0]) == *((*(otherTree.vector))[0]));
    }

    template <typename Data>
    bool BinaryTreeVec<Data>::operator!=(const BinaryTreeVec<Data> &otherTree) const noexcept
    {
        return !(*this == otherTree);
    }

    template <typename Data>
    typename BinaryTreeVec<Data>::NodeVec &BinaryTreeVec<Data>::Root() const
    {
        if (this->size == 0)
            throw std::length_error("Albero vuoto, impossibile restituire la root");
        return *((*(this->vector))[0]);
    }

    template <typename Data>
    void BinaryTreeVec<Data>::Clear()
    {
        this->size = 0;
        this->vector->Clear();
    }

    template <typename Data>
    void BinaryTreeVec<Data>::MapBreadth(MapFunctor funzione, void *parametro)
    {
        for (ulong i = 0; i < this->size; i++)
        {
            funzione((*(this->vector))[i]->Element(), parametro);
        }
    }

    template <typename Data>
    void BinaryTreeVec<Data>::FoldBreadth(FoldFunctor funzione, const void *parametro, void *accumulatore)
    {
        for (ulong i = 0; i < this->size; i++)
        {
            funzione((*(this->vector))[i]->Element(), parametro, accumulatore);
        }
    }

}
