#include "../binarytree/binarytree.hpp"

namespace lasd
{
    /* ************************************************************************** */

    template <typename Data>
    BST<Data>::BST(const LinearContainer<Data> &container)
    {
        for (ulong i = 0; i < container.Size(); i++)
        {
            // Delego l'inserimento alla funzione apposita
            this->Insert(container[i]);
        }
    }

    template <typename Data>
    BST<Data>::BST(const BST<Data> &otherBST) : BinaryTreeLnk<Data>::BinaryTreeLnk(otherBST) {}

    template <typename Data>
    BST<Data>::BST(BST<Data> &&otherBST) noexcept
    {
        std::swap(this->root, otherBST.root);
        std::swap(this->size, otherBST.size);
    }

    template <typename Data>
    BST<Data> &BST<Data>::operator=(const BST<Data> &otherBST)
    {
        BinaryTreeLnk<Data>::operator=(otherBST);

        return *this;
    }

    template <typename Data>
    BST<Data> &BST<Data>::operator=(BST<Data> &&otherBST) noexcept
    {

        std::swap(this->root, otherBST.root);
        std::swap(this->size, otherBST.size);
        return *this;
    }

    template <typename Data>
    bool BST<Data>::operator==(const BST<Data> &otherBST) const noexcept
    {
        // Devo confrontare i due alberi usando la visita InOrder, in quanto, essendo gli alberi in questione BST
        // confronterò gli elementi in ordine non decrescente, quindi "dal più piccolo al più grande".
        if (this->size != otherBST.size)
        {
            return false;
        }

        BTInOrderIterator<Data> thisIterator = BTInOrderIterator<Data>(*this);

        BTInOrderIterator<Data> otherIterator = BTInOrderIterator<Data>(otherBST);

        while (!thisIterator.Terminated())
        {
            if (*thisIterator != *otherIterator)
            {
                return false;
            }

            ++thisIterator;
            ++otherIterator;
        }

        return true;
    }

    template <typename Data>
    bool BST<Data>::operator!=(const BST<Data> &otherBST) const noexcept
    {
        return !(*this == otherBST);
    }

    template <typename Data>
    const Data &BST<Data>::Min() const
    {
        if (this->size == 0)
            throw std::length_error("BST vuoto, impossibile restituire il minimo!");

        NodeLnk *pointerToMin = FindPointerToMin(this->root);
        return pointerToMin->data;
    }

    template <typename Data>
    const Data &BST<Data>::Max() const
    {
        if (this->size == 0)
            throw std::length_error("BST vuoto, impossibile restituire il massimo!");

        NodeLnk *pointerToMax = FindPointerToMax(this->root);
        return pointerToMax->data;
    }

    template <typename Data>
    const Data &BST<Data>::Predecessor(const Data &dato) const
    {
        if (this->size == 0)
            throw std::length_error("BST vuoto, impossibile trovare il predecessore");

        return (*FindPointerToPredecessor(this->root, dato))->data;
    }

    template <typename Data>
    Data BST<Data>::PredecessorNRemove(const Data &dato)
    {
        if (this->size == 0)
            throw std::length_error("BST vuoto, impossibile restituire e rimuovo il predecessore");

        NodeLnk **pointerToPredecessor = FindPointerToPredecessor(this->root, dato);
        Data dataToReturn = (*pointerToPredecessor)->data;
        delete Detach(*pointerToPredecessor);
        return dataToReturn;
    }

    template <typename Data>
    void BST<Data>::RemovePredecessor(const Data &dato)
    {
        if (this->size == 0)
            throw std::length_error("BST vuoto, impossibile rimuovere il predecessore");

        NodeLnk **pointerToPredecessor = FindPointerToPredecessor(this->root, dato);
        delete Detach(*pointerToPredecessor);
    }

    template <typename Data>
    const Data &BST<Data>::Successor(const Data &dato) const
    {
        if (this->size == 0)
            throw std::length_error("BST vuoto, impossibile restituire il successore");

        return (*FindPointerToSuccessor(this->root, dato))->data;
    }

    template <typename Data>
    Data BST<Data>::SuccessorNRemove(const Data &dato)
    {
        if (this->size == 0)
            throw std::length_error("BST vuoto, impossibile restituire e rimuovere il successore");

        NodeLnk **pointerToSuccessor = FindPointerToSuccessor(this->root, dato);
        // Dall'interno -> stacco il noto, mi viene restituito il puntatore a quel nodo, che passo direttamente al
        // DataNDelete che lo cancella e restituisce il valore
        return DataNDelete(Detach(*pointerToSuccessor));
    }

    template <typename Data>
    void BST<Data>::RemoveSuccessor(const Data &dato)
    {
        if (this->size == 0)
            throw std::length_error("BST vuoto, impossibile rimuovere il successore");

        NodeLnk **pointerToSuccessor = FindPointerToSuccessor(this->root, dato);
        delete Detach(*pointerToSuccessor);
    }

    template <typename Data>
    void BST<Data>::Insert(const Data &datoToInsert)
    {
        NodeLnk *&pointerWhereAdd = FindPointerTo(this->root, datoToInsert);

        if (pointerWhereAdd == nullptr)
        {
            pointerWhereAdd = new NodeLnk(datoToInsert);
            this->size++;
        }
        // else esiste già un nodo con quel valore
    }

    template <typename Data>
    void BST<Data>::Insert(Data &&datoToInsert)
    {
        NodeLnk *&pointerWhereAdd = FindPointerTo(this->root, datoToInsert);

        if (pointerWhereAdd == nullptr)
        {
            pointerWhereAdd = new NodeLnk(std::move(datoToInsert));
            this->size++;
        }
        // else esiste già un nodo con quel valore
    }

    template <typename Data>
    void BST<Data>::Remove(const Data &datoToRemove)
    {

        delete Detach(FindPointerTo(this->root, datoToRemove));
        /* NodeLnk *pointerToNodeToRemove = FindPointerTo(this->root, datoToRemove);
        if (pointerToNodeToRemove != nullptr)
        {
            delete Detach(pointerToNodeToRemove);
        }  */
    }

    template <typename Data>
    bool BST<Data>::Exists(const Data &dataToFind) const noexcept
    {
        NodeLnk *curr = this->root;

        while (curr != nullptr)
        {
            if (dataToFind > curr->data)
            {
                // Se sto cercando un valore maggiore, mi sposto a destra
                curr = curr->rightChild;
            }
            else if (dataToFind < curr->data)
            {
                // Se sto cercando un valore minore, mi sposto a sinistra
                curr = curr->leftChild;
            }
            else
            {
                // Se l'ho trovato ritorno true
                return true;
            }
        }

        // Se sono arrivato alla fine dell'albero senza mai trovare il valore, non esiste
        return false;
    }

    /* ************************************************************************** */

    // Auxiliary member functions

    template <typename Data>
    Data BST<Data>::DataNDelete(NodeLnk *node)
    {
        Data dataToReturn = node->data;
        delete node;
        return dataToReturn;
    }

    template <typename Data>
    typename BST<Data>::NodeLnk *BST<Data>::Detach(typename BST<Data>::NodeLnk *&nodeToDetach) noexcept
    {

        if (nodeToDetach == nullptr)
            return nullptr;

        NodeLnk *nodeToReturn = nullptr;

        if (nodeToDetach->leftChild == nullptr)
        {
            nodeToReturn = Skip2Right(nodeToDetach);
        }
        else if (nodeToDetach->rightChild == nullptr)
        {
            nodeToReturn = Skip2Left(nodeToDetach);
        }
        else
        {
            // Applico """""StaccaMax"""""
            NodeLnk *max = DetachMax(nodeToDetach);
            std::swap(max->data, nodeToDetach->data);
            return max;
        }

        return nodeToReturn;
    }

    template <typename Data>
    typename BST<Data>::NodeLnk *BST<Data>::DetachMin(typename BST<Data>::NodeLnk *&startingNode) noexcept
    {

        // Essendo il minimo, non ha nessuno alla sua sinistra, ma possibilmente qualcuno alla sua destra.
        // Nel caso sia nullptr, sostituisco con nullptr, altrimenti col nodo a destra, che diventerà il nuovo minimo
        return Skip2Right(FindPointerToMin(startingNode));
    }

    template <typename Data>
    typename BST<Data>::NodeLnk *BST<Data>::DetachMax(typename BST<Data>::NodeLnk *&startingNode) noexcept
    {
        // Stesso ragionamento del minimo, ma col massimo
        return Skip2Left(FindPointerToMax(startingNode));
    }

    template <typename Data>
    void BST<Data>::RemoveMax()
    {
        if (this->size == 0)
            throw std::length_error("BST vuoto, impossibile rimuovere il massimo");

        delete DetachMax(this->root);
    }

    template <typename Data>
    void BST<Data>::RemoveMin()
    {
        if (this->size == 0)
            throw std::length_error("BST vuoto, impossibile rimuovere il minimo!");

        delete DetachMin(this->root);
    }

    template <typename Data>
    Data BST<Data>::MaxNRemove()
    {
        if (this->size == 0)
            throw std::length_error("BST vuoto, impossibile restituire e rimuovere il massimo");

        NodeLnk *max = DetachMax(this->root);
        Data dataToReturn = max->data;
        delete max;
        return dataToReturn;
    }

    template <typename Data>
    Data BST<Data>::MinNRemove()
    {
        if (this->size == 0)
            throw std::length_error("BST vuoto, impossibile restituire e rimuovere il minimo!");

        NodeLnk *min = DetachMin(this->root);
        Data dataToReturn = min->data;
        delete min;
        return dataToReturn;
    }

    template <typename Data>
    typename BST<Data>::NodeLnk *BST<Data>::Skip2Left(typename BST<Data>::NodeLnk *&current)
    {

        typename BST<Data>::NodeLnk *leftNode = nullptr;
        if (current != nullptr)
        {
            // swappo il figlio sinistro del nodo su cui lavoro con un nodo "temporaneo"
            std::swap(leftNode, current->leftChild);
            // swappo il nodo temporaneo con quello corrente, in modo da sostituirlo di fatto col suo figlio sinistro
            std::swap(leftNode, current);
            this->size--;
        }

        // ritorno il nodo sostituito, in quanto potrebbe servirmi
        return leftNode;
    }

    template <typename Data>
    typename BST<Data>::NodeLnk *BST<Data>::Skip2Right(typename BST<Data>::NodeLnk *&current)
    {
        typename BST<Data>::NodeLnk *rightNode = nullptr;
        if (current != nullptr)
        {
            // swappo il figlio destro del nodo su cui lavoro con un nodo "temporaneo"
            std::swap(rightNode, current->rightChild);
            // swappo il nodo temporaneo con quello corrente, in modo da sostituirlo di fatto col suo figlio destro
            std::swap(rightNode, current);
            this->size--;
        }

        // ritorno il nodo sostituito, in quanto potrebbe
        return rightNode;
    }

    template <typename Data>
    typename BST<Data>::NodeLnk *&BST<Data>::FindPointerToMin(NodeLnk *&node)
    {
        return const_cast<NodeLnk *&>(static_cast<const BST<Data> *>(this)->FindPointerToMin(node));
    }

    template <typename Data>
    typename BST<Data>::NodeLnk *const &BST<Data>::FindPointerToMin(NodeLnk *const &node) const
    {

        NodeLnk *const *ptr = &node;
        NodeLnk *curr = node;
        if (curr != nullptr)
        {
            // Scendendo tutto a sinistra, finchè c'è almeno un altro figlio...
            while (curr->leftChild != nullptr)
            {
                // parent PUNT al puntatore di quel figlio sinistro
                ptr = &curr->leftChild;
                // current DIVENTA quel figlio sinistro
                curr = curr->leftChild;
            }
            // Quando uscirò, current è il puntatore all'effettivo minimo, mentre parent punta al puntatore che punta
            // a quel figlio minimo, permettendomi di accedervi non "direttamente", ma attraverso il nodo che lo punta
        }

        return *ptr;
    }

    template <typename Data>
    typename BST<Data>::NodeLnk *&BST<Data>::FindPointerToMax(NodeLnk *&node)
    {
        return const_cast<typename BST<Data>::NodeLnk *&>(static_cast<const BST<Data> *>(this)->FindPointerToMax(node));
    }

    template <typename Data>
    typename BST<Data>::NodeLnk *const &BST<Data>::FindPointerToMax(NodeLnk *const &node) const
    {
        typename BST<Data>::NodeLnk *const *ptr = &node;
        typename BST<Data>::NodeLnk *curr = node;
        if (curr != nullptr)
        {
            while (curr->rightChild != nullptr)
            {
                ptr = &curr->rightChild;
                curr = curr->rightChild;
            }
        }

        return *ptr;
    }

    template <typename Data>
    typename BST<Data>::NodeLnk *&BST<Data>::FindPointerTo(typename BST<Data>::NodeLnk *&node, const Data &dato)
    {
        return const_cast<typename BST<Data>::NodeLnk *&>(static_cast<const BST<Data> *>(this)->FindPointerTo(node, dato));
    }

    template <typename Data>
    typename BST<Data>::NodeLnk *const &BST<Data>::FindPointerTo(NodeLnk *const &node, const Data &dato) const
    {

        typename BST<Data>::NodeLnk *const *ptr = &node;
        typename BST<Data>::NodeLnk *curr = node;

        if (curr != nullptr)
        {
            while (curr != nullptr && dato != curr->data)
            {
                if (dato > curr->data)
                {
                    ptr = &(curr->rightChild);
                    curr = curr->rightChild;
                }
                else if (dato < curr->data)
                {
                    ptr = &(curr->leftChild);
                    curr = curr->leftChild;
                }
            }
        }

        return *ptr;
    }

    template <typename Data>
    typename BST<Data>::NodeLnk **BST<Data>::FindPointerToPredecessor(NodeLnk *&node, const Data &dato)
    {
        return const_cast<NodeLnk **>(static_cast<const BST<Data> *>(this)->FindPointerToPredecessor(node, dato));
    }

    template <typename Data>
    typename BST<Data>::NodeLnk *const *BST<Data>::FindPointerToPredecessor(NodeLnk *const &node, const Data &dato) const
    {
        NodeLnk *const *ptr = &node;
        NodeLnk *const *prd = nullptr;
        while (true)
        {
            NodeLnk &curr = **ptr;
            // Se "io" sono più grande del nodo, ho trovato qualcuno più piccolo di me, quindi un predecessore.
            if (dato > curr.data)
            {
                prd = ptr;
                if (curr.rightChild == nullptr)
                {
                    return prd;
                }
                // Se c'è un sottoalbero destro(con nodi sicuramente maggiori), cerco in questo sottoalbero, sperando di
                // trovare qualcuno maggiore di current ma ancora minore di me
                else
                {
                    ptr = &curr.rightChild;
                }
            }
            else
            {
                // Se invece "io" sono più piccolo o uguale del nodo corrente, devo cercare a sinistra, in quanto
                // se cercassi a destra troverei solo nodi più grandi di me
                if (curr.leftChild == nullptr)
                {
                    return prd;
                }
                else
                {
                    // Se io sono effettivamente minore del nodo corrente, mi sposto nel sottoalbero sinistro
                    if (dato < curr.data)
                    {
                        ptr = &curr.leftChild;
                    }
                    else
                    {
                        // Se sono uguale invece trovo il massimo del sottoalbero sinistro, dato che a sinistra sono
                        // sicuramente tutti minori di me e devo trovarne il massimo(definizione di predecessore)
                        return &FindPointerToMax(curr.leftChild);
                    }
                }
            }
        }
    }

    template <typename Data>
    typename BST<Data>::NodeLnk **BST<Data>::FindPointerToSuccessor(NodeLnk *&node, const Data &dato)
    {
        return const_cast<NodeLnk **>(static_cast<const BST<Data> *>(this)->FindPointerToSuccessor(node, dato));
    }

    template <typename Data>
    typename BST<Data>::NodeLnk *const *BST<Data>::FindPointerToSuccessor(NodeLnk *const &node, const Data &dato) const
    {
        NodeLnk *const *ptr = &node;
        NodeLnk *const *prd = nullptr;
        while (true)
        {
            NodeLnk &curr = **ptr;
            // Se "io" sono più piccolo del nodo corrente ho trovato un mio successore, e inizio a cercare a sinistra
            // in quanto potrei trovare nodi più piccoli di quello corrente ma maggiori di me
            if (dato < curr.data)
            {
                prd = ptr;
                if (curr.leftChild == nullptr)
                {
                    return prd;
                }
                else
                {
                    ptr = &curr.leftChild;
                }
            }
            else
            {
                if (curr.rightChild == nullptr)
                {
                    return prd;
                }
                else
                {
                    // Se invece io sono più grande del nodo corrente, cerco nel sottoalbero sinistro, in quanto sono
                    // sicuro ci siano nodi più grandi, e spero ce ne sia uno più grande di me
                    if (dato > curr.data)
                    {
                        ptr = &curr.rightChild;
                    }
                    else
                    {
                        // Se sono proprio uguale al nodo corrente devo cercare il minimo del sottoalbero dei maggiori
                        // definizione di Successore
                        return &FindPointerToMin(curr.rightChild);
                    }
                }
            }
        }
    }

    /* ************************************************************************** */
}