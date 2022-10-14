
// #include "..."

namespace lasd
{

    /* ************************************************************************** */

    // Node methods

    template <typename Data>
    bool BinaryTree<Data>::Node::operator==(const Node &otherNode) const noexcept
    {

        bool areLeftSubtTreeEquals, areRightSubtTreeEquals;
        // Se hanno elementi diversi ritorno false
        if (this->Element() != otherNode.Element())
        {
            return false;
        }
        // se uno è foglia ma l'altro no ritorno false
        if (this->IsLeaf() ^ otherNode.IsLeaf())
        {
            return false;
        }

        // Se entrambi hanno figlio sinistro li controllo
        if (this->HasLeftChild() && otherNode.HasLeftChild())
        {
            if (this->LeftChild() != otherNode.LeftChild())
            {
                return false;
            }
        } // altrimenti se uno ce l'ha e l'altro no ritorno false
        else if (this->HasLeftChild() ^ otherNode.HasLeftChild())
        {
            return false;
        }

        // Se entrambi hanno figlio destro li controllo
        if (this->HasRightChild() && otherNode.HasRightChild())
        {
            if (this->RightChild() != otherNode.RightChild())
            {
                return false;
            }
        } // altrimenti se uno ce l'ha e l'altro no ritorno false
        else if (this->HasRightChild() ^ otherNode.HasRightChild())
        {
            return false;
        }

        return true;
    }

    template <typename Data>
    bool BinaryTree<Data>::Node::operator!=(const Node &otherNode) const noexcept
    {
        return !(*this == otherNode);
    }

    template <typename Data>
    bool BinaryTree<Data>::Node::IsLeaf() const noexcept
    {
        return !(HasLeftChild() || HasRightChild());
    }

    // Map & Fold function

    template <typename Data>
    void BinaryTree<Data>::Map(MapFunctor funzione, void *parametro)
    {
        MapPreOrder(funzione, parametro);
    }

    template <typename Data>
    void BinaryTree<Data>::Fold(FoldFunctor funzione, const void *parametro, void *accumulatore) const
    {
        FoldPreOrder(funzione, parametro, accumulatore);
    }

    template <typename Data>
    void BinaryTree<Data>::MapPreOrder(MapFunctor funzione, void *parametro)
    {

        if (this->size != 0)
            MapPreOrder(funzione, parametro, &(this->Root()));
    }

    template <typename Data>
    void BinaryTree<Data>::FoldPreOrder(FoldFunctor funzione, const void *parametro, void *accumulatore) const
    {
        if (this->size != 0)
            FoldPreOrder(funzione, parametro, accumulatore, &this->Root());
    }

    template <typename Data>
    void BinaryTree<Data>::MapPostOrder(MapFunctor funzione, void *parametro)
    {

        if (this->size != 0)
            MapPostOrder(funzione, parametro, &(this->Root()));
    }

    template <typename Data>
    void BinaryTree<Data>::FoldPostOrder(FoldFunctor funzione, const void *parametro, void *accumulatore) const
    {

        if (this->size != 0)
            FoldPostOrder(funzione, parametro, accumulatore, &(this->Root()));
    }

    template <typename Data>
    void BinaryTree<Data>::MapInOrder(MapFunctor funzione, void *parametro)
    {
        if (this->size != 0)
            MapInOrder(funzione, parametro, &(this->Root()));
    }

    template <typename Data>
    void BinaryTree<Data>::FoldInOrder(FoldFunctor funzione, const void *parametro, void *accumulatore) const
    {
        if (this->size != 0)
            FoldInOrder(funzione, parametro, accumulatore, &(this->Root()));
    }

    template <typename Data>
    void BinaryTree<Data>::MapBreadth(MapFunctor funzione, void *parametro)
    {
        if (this->size != 0)
            MapBreadth(funzione, parametro, &(this->Root()));
    }

    template <typename Data>
    void BinaryTree<Data>::FoldBreadth(FoldFunctor funzione, const void *parametro, void *accumulatore) const
    {
        if (this->size != 0)
            FoldBreadth(funzione, parametro, accumulatore, &(this->Root()));
    }

    template <typename Data>
    void BinaryTree<Data>::MapPreOrder(MapFunctor funzione, void *parametro, Node *currentRoot)
    {
        funzione(currentRoot->Element(), parametro);

        if (currentRoot->HasLeftChild())
            MapPreOrder(funzione, parametro, &(currentRoot->LeftChild()));

        if (currentRoot->HasRightChild())
            MapPreOrder(funzione, parametro, &(currentRoot->RightChild()));
    }

    template <typename Data>
    void BinaryTree<Data>::FoldPreOrder(FoldFunctor funzione, const void *parametro, void *accumulatore, const Node *currentRoot) const
    {
        if (currentRoot != nullptr)
        {
            funzione(currentRoot->Element(), parametro, accumulatore);

            if (currentRoot->HasLeftChild())
                FoldPreOrder(funzione, parametro, accumulatore, &(currentRoot->LeftChild()));

            if (currentRoot->HasRightChild())
                FoldPreOrder(funzione, parametro, accumulatore, &(currentRoot->RightChild()));
        }
    }

    template <typename Data>
    void BinaryTree<Data>::MapPostOrder(MapFunctor funzione, void *parametro, Node *currentRoot)
    {
        if (currentRoot != nullptr)
        {

            if (currentRoot->HasLeftChild())
                MapPostOrder(funzione, parametro, &(currentRoot->LeftChild()));

            if (currentRoot->HasRightChild())
                MapPostOrder(funzione, parametro, &(currentRoot->RightChild()));

            funzione(currentRoot->Element(), parametro);
        }
    }

    template <typename Data>
    void BinaryTree<Data>::FoldPostOrder(FoldFunctor funzione, const void *parametro, void *accumulatore, const Node *currentRoot) const
    {
        if (currentRoot != nullptr)
        {
            if (currentRoot->HasLeftChild())
                FoldPostOrder(funzione, parametro, accumulatore, &(currentRoot->LeftChild()));

            if (currentRoot->HasRightChild())
                FoldPostOrder(funzione, parametro, accumulatore, &(currentRoot->RightChild()));

            funzione(currentRoot->Element(), parametro, accumulatore);
        }
    }

    template <typename Data>
    void BinaryTree<Data>::MapInOrder(MapFunctor funzione, void *parametro, Node *currentRoot)
    {
        if (currentRoot != nullptr)
        {
            if (currentRoot->HasLeftChild())
                MapInOrder(funzione, parametro, &(currentRoot->LeftChild()));

            funzione(currentRoot->Element(), parametro);

            if (currentRoot->HasRightChild())
                MapInOrder(funzione, parametro, &(currentRoot->RightChild()));
        }
    }

    template <typename Data>
    void BinaryTree<Data>::FoldInOrder(FoldFunctor funzione, const void *parametro, void *accumulatore, const Node *currentRoot) const
    {
        if (currentRoot != nullptr)
        {
            if (currentRoot->HasLeftChild())
                FoldInOrder(funzione, parametro, accumulatore, &(currentRoot->LeftChild()));

            funzione(currentRoot->Element(), parametro, accumulatore);

            if (currentRoot->HasRightChild())
                FoldInOrder(funzione, parametro, accumulatore, &(currentRoot->RightChild()));
        }
    }

    template <typename Data>
    void BinaryTree<Data>::MapBreadth(MapFunctor funzione, void *parametro, Node *currentRoot)
    {
        if (currentRoot != nullptr)
        {
            QueueLst<typename BinaryTree<Data>::Node *> *queue = new QueueLst<typename BinaryTree<Data>::Node *>();
            queue->Enqueue(currentRoot);
            typename BinaryTree<Data>::Node *tmp;

            while (!queue->Empty())
            {

                tmp = queue->HeadNDequeue();
                funzione(tmp->Element(), parametro);

                if (tmp->HasLeftChild())
                    queue->Enqueue(&(tmp->LeftChild()));

                if (tmp->HasRightChild())
                    queue->Enqueue(&(tmp->RightChild()));
            }
        }
    }

    template <typename Data>
    void BinaryTree<Data>::FoldBreadth(FoldFunctor funzione, const void *parametro, void *accumulatore, const Node *currentRoot) const
    {
        if (currentRoot != nullptr)
        {
            QueueLst<const typename BinaryTree<Data>::Node *> *queue = new QueueLst<const typename BinaryTree<Data>::Node *>();
            queue->Enqueue(currentRoot);
            const typename BinaryTree<Data>::Node *tmp;

            while (!queue->Empty())
            {

                tmp = queue->HeadNDequeue();
                funzione(tmp->Element(), parametro, accumulatore);

                if (tmp->HasLeftChild())
                    queue->Enqueue(&(tmp->LeftChild()));

                if (tmp->HasRightChild())
                    queue->Enqueue(&(tmp->RightChild()));
            }
        }
    }

    /* ************************************************************************** */

    // BinaryTree methods

    template <typename Data>
    bool BinaryTree<Data>::operator==(const BinaryTree &otherBinaryTree) const noexcept
    {
        try
        {
            if (this->size != otherBinaryTree.Size())
                return false;
            return (this->Root() == otherBinaryTree.Root());
        }
        catch (std::length_error e)
        {
            if (this->Empty() && otherBinaryTree.Empty())
                return true;

            return false;
        }
    }

    template <typename Data>
    bool BinaryTree<Data>::operator!=(const BinaryTree &otherBinaryTree) const noexcept
    {
        return !(*this == otherBinaryTree);
    }

    /* ************************************************************************** */

    // BTPreOrderIterator methods

    // inizializzo stack vuoto e currentNode a radice dell'albero
    template <typename Data>
    BTPreOrderIterator<Data>::BTPreOrderIterator(const BinaryTree<Data> &binaryTree)
    {
        this->currentNode = &binaryTree.Root();
        this->root = &binaryTree.Root();
    }

    template <typename Data>
    BTPreOrderIterator<Data>::BTPreOrderIterator(const BTPreOrderIterator &otherIterator)
    {

        this->stack = new StackLst<typename BinaryTree<Data>::Node *>(otherIterator.stack);
        this->currentNode = otherIterator.currentNode;
        this->root = otherIterator.root;
    }

    template <typename Data>
    BTPreOrderIterator<Data>::BTPreOrderIterator(BTPreOrderIterator &&otherIterator)
    {

        std::swap(this->currentNode, otherIterator.currentNode);
        std::swap(this->stack, otherIterator.stack);
        std::swap(this->root, otherIterator.root);
    }

    template <typename Data>
    BTPreOrderIterator<Data>::~BTPreOrderIterator()
    {
        this->currentNode = nullptr;
        this->root = nullptr;
        delete this->stack;
    }

    template <typename Data>
    BTPreOrderIterator<Data> &BTPreOrderIterator<Data>::operator=(const BTPreOrderIterator<Data> &otherIterator)
    {
        this->stack = new StackLst<typename BinaryTree<Data>::Node *>(otherIterator.stack);
        this->currentNode = otherIterator.currentNode;
        this->root = otherIterator.root;
        return *this;
    }

    template <typename Data>
    BTPreOrderIterator<Data> &BTPreOrderIterator<Data>::operator=(BTPreOrderIterator<Data> &&otherIterator)
    {
        std::swap(this->currentNode, otherIterator.currentNode);
        std::swap(this->stack, otherIterator.stack);
        std::swap(this->root, otherIterator.root);
        return *this;
    }

    template <typename Data>
    bool BTPreOrderIterator<Data>::operator==(const BTPreOrderIterator<Data> &otherIterator) const noexcept
    {
        return ((this->currentNode == otherIterator.currentNode) && (this->stack == otherIterator.stack) && (this->root == otherIterator.root));
    }

    template <typename Data>
    bool BTPreOrderIterator<Data>::operator!=(const BTPreOrderIterator<Data> &otherIterator) const noexcept
    {
        return !(*this == otherIterator);
    }

    template <typename Data>
    Data &BTPreOrderIterator<Data>::operator*() const
    {
        if (this->Terminated())
            throw std::out_of_range("Operatore terminato, impossibile accedere al valore!");

        return this->currentNode->Element();
    }

    template <typename Data>
    bool BTPreOrderIterator<Data>::Terminated() const noexcept
    {
        return (this->currentNode == nullptr && this->stack->Empty());
    }

    template <typename Data>
    void BTPreOrderIterator<Data>::operator++()
    {
        // Aggiungo allo stack PRIMA il figlio destro, POI il figlio sinistro. Dato che ci stiamo basando su uno stack,
        // in cui vige la regola LIFO, anche se vengo a sapere dell'esistenza di un nodo destro, questo dovrà essere
        // visitato dopo il sottoalbero sinistro della radice.
        // Dopo aver stackato prima il figlio destro, poi il figlio sinistro(se esistenti entrambi), farò un TopNPop.

        if (this->Terminated())
            throw std::out_of_range("Operatore terminato, impossibile scorrere oltre!");

        if (this->currentNode->HasRightChild())
            this->stack->Push(&this->currentNode->RightChild());

        if (this->currentNode->HasLeftChild())
            this->stack->Push(&this->currentNode->LeftChild());

        if (!this->stack->Empty())
            this->currentNode = this->stack->TopNPop();
        else
            this->currentNode = nullptr;
    }

    template <typename Data>
    void BTPreOrderIterator<Data>::Reset() noexcept
    {
        this->currentNode = this->root;
        this->stack->Clear();
    }

    /* ************************************************************************** */

    // BTPostOrderIterator methods
    template <typename Data>
    typename BinaryTree<Data>::Node &BTPostOrderIterator<Data>::LeftMostLeaf(typename BinaryTree<Data>::Node &root) const
    {

        /*Funzione accessoria ricorsiva che mi trova la foglia sinistra minima. Finchè posso andare a sinistra ci
        vado(ricorsivamente), quando non posso più andare a sinistra controlla la destra, se ho la destra riparto
        a cercare la foglia sinistra minima richiamando la funzione stessa */

        if (root.HasLeftChild())
        {
            this->stack->Push(&root);
            return this->LeftMostLeaf(root.LeftChild());
        }
        else if (root.HasRightChild())
        {
            this->stack->Push(&root);
            return this->LeftMostLeaf(root.RightChild());
        }
        else
        {
            return root;
        }
    }

    template <typename Data>
    BTPostOrderIterator<Data>::BTPostOrderIterator(const BinaryTree<Data> &binaryTree)
    {
        this->currentNode = &(this->LeftMostLeaf(binaryTree.Root()));
        this->root = &binaryTree.Root();
    }

    template <typename Data>
    BTPostOrderIterator<Data>::BTPostOrderIterator(const BTPostOrderIterator<Data> &otherIterator)
    {
        this->currentNode = otherIterator.currentNode;
        this->stack = new StackLst<typename BinaryTree<Data>::Node *>(otherIterator.stack);
        this->root = otherIterator.root;
    }

    template <typename Data>
    BTPostOrderIterator<Data>::BTPostOrderIterator(BTPostOrderIterator<Data> &&otherIterator)
    {
        std::swap(this->currentNode, otherIterator.currentNode);
        std::swap(this->stack, otherIterator.stack);
        std::swap(this->root, otherIterator.root);
    }

    template <typename Data>
    BTPostOrderIterator<Data>::~BTPostOrderIterator()
    {
        this->currentNode = nullptr;
        this->root = nullptr;
        delete this->stack;
    }

    template <typename Data>
    BTPostOrderIterator<Data> &BTPostOrderIterator<Data>::operator=(const BTPostOrderIterator<Data> &otherIterator)
    {

        this->currentNode = otherIterator.currentNode;
        this->stack = new StackLst<typename BinaryTree<Data>::Node *>(otherIterator.stack);
        this->root = otherIterator.root;
        return *this;
    }

    template <typename Data>
    BTPostOrderIterator<Data> &BTPostOrderIterator<Data>::operator=(BTPostOrderIterator<Data> &&otherIterator)
    {

        std::swap(this->currentNode, otherIterator.currentNode);
        std::swap(this->stack, otherIterator.stack);
        std::swap(this->root, otherIterator.root);
        return *this;
    }

    template <typename Data>
    bool BTPostOrderIterator<Data>::operator==(const BTPostOrderIterator<Data> &otherIterator) const noexcept
    {
        return ((this->currentNode == otherIterator.currentNode) && (this->stack == otherIterator.stack) && (this->root == otherIterator.root));
    }

    template <typename Data>
    bool BTPostOrderIterator<Data>::operator!=(const BTPostOrderIterator<Data> &otherIterator) const noexcept
    {
        return !(*this == *otherIterator);
    }

    template <typename Data>
    Data &BTPostOrderIterator<Data>::operator*() const
    {
        if (this->Terminated())
            throw std::out_of_range("Iteratore terminato, impossibile accedere al valore");

        return (this->currentNode)->Element();
    }

    template <typename Data>
    void BTPostOrderIterator<Data>::operator++()
    {

        if (this->Terminated())
            throw std::out_of_range("Iteratore terminato, impossibile scorrere oltre");

        if (!this->stack->Empty())
        {
            typename BinaryTree<Data>::Node *topOfTheStack = &(*(this->stack)->Top());

            /*Qui ho tre possibilità:
                -Sto tornando da sinistra e c'è figlio destro
                -Sto tornando da sinistra e NON c'è figlio destro
                -Sto tornando da destra(sono sicuro che il sottoalbero sinistro di mio padre sia già stato visitato, se esiste)
            */

            if (topOfTheStack->HasLeftChild() && this->currentNode == &(topOfTheStack->LeftChild()))
            {
                // Sto tornando da sinistra...
                if (topOfTheStack->HasRightChild())
                {
                    //...e c'è figlio destro
                    this->currentNode = &(LeftMostLeaf(topOfTheStack->RightChild()));
                    return;
                }
            }

            this->currentNode = topOfTheStack;
            this->stack->Pop();
        }
        else
        {
            this->currentNode = nullptr;
        }
    }

    template <typename Data>
    bool BTPostOrderIterator<Data>::Terminated() const noexcept
    {
        return (this->currentNode == nullptr && this->stack->Empty());
    }

    template <typename Data>
    void BTPostOrderIterator<Data>::Reset() noexcept
    {
        if (this->root != nullptr)
        {
            this->stack->Clear();
            this->currentNode = &this->LeftMostLeaf(*this->root);
        }
    }

    /* ************************************************************************** */
    // BTInOrderIterator methods

    // Funzione che ritorna il nodo più a sinistra dell'albero radicato in root
    template <typename Data>
    typename BinaryTree<Data>::Node &BTInOrderIterator<Data>::LeftMostNode(typename BinaryTree<Data>::Node &currentRoot) const
    {

        if (currentRoot.HasLeftChild())
        {
            this->stack->Push(&currentRoot);
            return LeftMostNode(currentRoot.LeftChild());
        }
        else
        {

            return currentRoot;
        }
    }

    template <typename Data>
    BTInOrderIterator<Data>::BTInOrderIterator(const BinaryTree<Data> &binaryTree)
    {

        if (!binaryTree.Empty())
        {
            this->currentNode = &(this->LeftMostNode(binaryTree.Root()));
            this->root = &binaryTree.Root();
        }
    }

    template <typename Data>
    BTInOrderIterator<Data>::BTInOrderIterator(const BTInOrderIterator &otherIterator)
    {
        this->currentNode = otherIterator.currentNode;
        this->stack = new StackLst<typename BinaryTree<Data>::Node *>(*otherIterator.stack);
        this->root = otherIterator.root;
    }

    template <typename Data>
    BTInOrderIterator<Data>::BTInOrderIterator(BTInOrderIterator<Data> &&otherIterator)
    {
        std::swap(this->currentNode, otherIterator.currentNode);
        std::swap(this->stack, otherIterator.stack);
        std::swap(this->root, otherIterator.root);
    }

    template <typename Data>
    BTInOrderIterator<Data>::~BTInOrderIterator()
    {
        this->root = this->currentNode = nullptr;
        delete this->stack;
    }

    template <typename Data>
    BTInOrderIterator<Data> &BTInOrderIterator<Data>::operator=(const BTInOrderIterator &otherIterator)
    {
        this->currentNode = otherIterator.currentNode;
        this->stack = new StackLst<typename BinaryTree<Data>::Node *>(otherIterator.stack);
        this->root = otherIterator.root;
        return *this;
    }

    template <typename Data>
    BTInOrderIterator<Data> &BTInOrderIterator<Data>::operator=(BTInOrderIterator &&otherIterator)
    {
        std::swap(this->currentNode, otherIterator.currentNode);
        std::swap(this->stack, otherIterator.stack);
        std::swap(this->root, otherIterator.root);
        return *this;
    }

    template <typename Data>
    bool BTInOrderIterator<Data>::operator==(const BTInOrderIterator &otherIterator) const noexcept
    {
        return ((this->currentNode == otherIterator.currentNode) && (this->stack == otherIterator.stack) && (this->root == otherIterator.root));
    }

    template <typename Data>
    bool BTInOrderIterator<Data>::operator!=(const BTInOrderIterator &otherIterator) const noexcept
    {
        return !(*this == otherIterator);
    }

    template <typename Data>
    Data &BTInOrderIterator<Data>::operator*() const
    {

        if (this->Terminated())
            throw std::out_of_range("Iteratore terminato, impossibile accedere al valore");

        return (this->currentNode)->Element();
    }

    template <typename Data>
    bool BTInOrderIterator<Data>::Terminated() const noexcept
    {

        return (this->currentNode == nullptr && this->stack->Empty());
    }

    template <typename Data>
    void BTInOrderIterator<Data>::operator++()
    {

        if (this->Terminated())
            throw std::out_of_range("Iteratore terminato, impossibile scorrere oltre");

        if (this->currentNode->HasRightChild())
        {
            this->currentNode = &(this->LeftMostNode(this->currentNode->RightChild()));
        }
        else if (!this->stack->Empty())
            this->currentNode = this->stack->TopNPop();
        else
            this->currentNode = nullptr;
    }

    template <typename Data>
    void BTInOrderIterator<Data>::Reset() noexcept
    {
        if (this->root != nullptr)
        {
            this->stack->Clear();
            this->currentNode = &(this->LeftMostNode(*(this->root)));
        }
    }

    /* ************************************************************************** */
    // BTBreadthIterator methods

    template <typename Data>
    BTBreadthIterator<Data>::BTBreadthIterator(const BinaryTree<Data> &binaryTree)
    {
        if (!binaryTree.Empty())
        {
            this->currentNode = this->root = &(binaryTree.Root());
        }
    }

    template <typename Data>
    BTBreadthIterator<Data>::BTBreadthIterator(const BTBreadthIterator<Data> &otherIterator)
    {

        this->currentNode = otherIterator.currentNode;
        this->root = otherIterator.root;
        this->queue = new QueueLst<typename BinaryTree<Data>::Node *>(otherIterator.queue);
    }

    template <typename Data>
    BTBreadthIterator<Data>::BTBreadthIterator(BTBreadthIterator<Data> &&otherIterator)
    {
        std::swap(this->currentNode, otherIterator.currentNode);
        std::swap(this->queue, otherIterator.queue);
        std::swap(this->root, otherIterator.root);
    }

    template <typename Data>
    BTBreadthIterator<Data> &BTBreadthIterator<Data>::operator=(const BTBreadthIterator<Data> &otherIterator)
    {
        this->currentNode = otherIterator.currentNode;
        this->root = otherIterator.root;
        this->queue = new QueueLst<typename BinaryTree<Data>::Node *>(otherIterator.queue);
        return *this;
    }

    template <typename Data>
    BTBreadthIterator<Data> &BTBreadthIterator<Data>::operator=(BTBreadthIterator<Data> &&otherIterator)
    {
        std::swap(this->currentNode, otherIterator.currentNode);
        std::swap(this->queue, otherIterator.queue);
        std::swap(this->root, otherIterator.root);
        return *this;
    }

    template <typename Data>
    bool BTBreadthIterator<Data>::operator==(const BTBreadthIterator<Data> &otherIterator) const noexcept
    {
        return (this->currentNode == otherIterator.currentNode &&
                this->root == this->root &&
                *(this->queue) == *(otherIterator.queue));
    }

    template <typename Data>
    bool BTBreadthIterator<Data>::operator!=(const BTBreadthIterator<Data> &otherIterator) const noexcept
    {
        return !(*this == otherIterator);
    }

    template <typename Data>
    Data &BTBreadthIterator<Data>::operator*() const
    {
        if (this->Terminated())
            throw std::out_of_range("Iteratore terminato, impossibile accedere al valore");

        return (this->currentNode)->Element();
    }

    template <typename Data>
    bool BTBreadthIterator<Data>::Terminated() const noexcept
    {
        return (this->currentNode == nullptr && this->queue->Empty());
    }

    template <typename Data>
    void BTBreadthIterator<Data>::operator++()
    {
        if (this->Terminated())
            throw std::out_of_range("Iteratore terminato, impossibile scorrere oltre");

        if (this->currentNode->HasLeftChild())
            queue->Enqueue(&this->currentNode->LeftChild());

        if (this->currentNode->HasRightChild())
            queue->Enqueue(&this->currentNode->RightChild());

        if (!this->queue->Empty())
            this->currentNode = this->queue->HeadNDequeue();
        else
            this->currentNode = nullptr;
    }

    template <typename Data>
    void BTBreadthIterator<Data>::Reset() noexcept
    {
        this->queue->Clear();
        this->currentNode = this->root;
    }

}
