
namespace lasd
{

    /* ************************************************************************** */

    template <typename Data>
    List<Data>::Node::Node(const Data &elem)
    {

        this->elem = elem;
    }

    template <typename Data>
    List<Data>::Node::Node(Data &&elem) noexcept
    {

        this->elem = elem;
    }

    template <typename Data>
    List<Data>::Node::Node(const Node &nodo)
    {

        elem = nodo.elem;
        next = nodo.next;
    }

    template <typename Data>
    List<Data>::Node::Node(Node &&nodo) noexcept
    {

        std::swap(elem, nodo.elem);
        std::swap(next, nodo.next);
    }

    /* template <typename Data>
    List<Data>::Node::~Node()
    {

        delete next;
    } */

    template <typename Data>
    typename List<Data>::Node &List<Data>::Node::operator=(const Node &nodo)
    {

        Node *nodo_tmp = new Node(nodo);
        std::swap(nodo_tmp, this);
        delete nodo_tmp;
        return *this;
    }

    template <typename Data>
    typename List<Data>::Node &List<Data>::Node::operator=(Node &&nodo)
    {

        std::swap(elem, nodo.elem);
        std::swap(next, nodo.next);
        return *this;
    }

    template <typename Data>
    inline bool List<Data>::Node::operator==(const Node &nodo) const noexcept
    {

        return (elem == nodo.elem && next == nodo.next);
    }

    template <typename Data>
    bool List<Data>::Node::operator!=(const Node &nodo) const noexcept
    {

        bool risultato = !(this == nodo);
        return risultato;
    }

    /* ************************************************************************** */

    // List constructor

    template <typename Data>
    List<Data>::List()
    {
        this->size = 0;
        this->head = nullptr;
    }

    template <typename Data>
    List<Data>::List(const LinearContainer<Data> &elem)
    {

        size = elem.Size();

        if (elem.Empty())
        {
            List<Data> nuovo = List<Data>();
        }

        head = new Node(elem[0]);
        Node *curr = head;

        for (unsigned long index = 1; index < size; ++index)
        {

            Node *temp = new Node(elem[index]);
            curr->next = temp;
            curr = curr->next;
        }
    }

    template <typename Data>
    List<Data>::List(const List<Data> &old_list)
    {

        if (old_list.Empty())
        {
            this->size = 0;
            this->head = nullptr;
        }
        else
        {
            size = old_list.size;

            head = new Node(old_list[0]);
            Node *curr = head;
            Node *old_head = (old_list.head)->next;

            for (unsigned long index = 1; index < old_list.size; ++index)
            {

                Node *temp = new Node(old_head->elem);
                curr->next = temp;
                curr = curr->next;
                old_head = old_head->next;
            }
        }
    }

    template <typename Data>
    List<Data>::List(List<Data> &&old_list)
    {

        std::swap(size, old_list.size);
        std::swap(head, old_list.head);
    }

    template <typename Data>
    List<Data>::~List()
    {

        this->size = 0;
        delete this->head;
    }

    template <typename Data>
    List<Data> &List<Data>::operator=(const List<Data> &elem)
    {

        List<Data> *list_temp = new List<Data>(elem);
        std::swap(*list_temp, *this);
        delete list_temp;
        return *this;
    }

    template <typename Data>
    List<Data> &List<Data>::operator=(List<Data> &&elem) noexcept
    {

        std::swap(size, elem.size);
        std::swap(head, elem.head);
        return *this;
    }

    template <typename Data>
    bool List<Data>::operator==(const List<Data> &list) const noexcept
    {

        Node *testa_1 = head;
        Node *testa_2 = list.head;

        if (size == list.size)
        {

            while (testa_1 != nullptr)
            {

                if (testa_1->elem != testa_2->elem)
                {

                    return false;
                }

                testa_1 = testa_1->next;
                testa_2 = testa_2->next;
            }
        }
        else
        {

            return false;
        }

        return true;
    }

    template <typename Data>
    bool List<Data>::operator!=(const List<Data> &list) const noexcept
    {

        return !(*this == list);
    }

    template <typename Data>
    void List<Data>::InsertAtFront(const Data &dato)
    {

        size += 1;
        Node *new_nodo = new Node(dato);
        new_nodo->next = head;
        head = new_nodo;
    }

    template <typename Data>
    void List<Data>::InsertAtFront(Data &&dato) noexcept
    {

        size += 1;
        Node *new_nodo = new Node(dato);
        new_nodo->next = head;
        head = new_nodo;
    }

    template <typename Data>
    void List<Data>::RemoveFromFront()
    {

        size -= 1;
        Node *temp = head;

        head = head->next;
        temp->next = nullptr;
        delete temp;
    }

    template <typename Data>
    Data List<Data>::FrontNRemove()
    {

        if (this->size == 0)
        {

            throw std::length_error("Lista vuota!");
        }
        else
        {

            Data tmp = head->elem;
            this->RemoveFromFront();

            return tmp;
        }
    }

    template <typename Data>
    void List<Data>::InsertAtBack(const Data &elem)
    {

        if (this->Empty())
        {

            size += 1;
            Node *tmp = new Node(elem);
            head = tmp;
        }
        else
        {

            size += 1;
            Node *tmp = new Node(elem);
            Node *curr = head;
            while (curr->next != nullptr)
            {

                curr = curr->next;
            }

            curr->next = tmp;
        }
    }

    template <typename Data>
    void List<Data>::InsertAtBack(Data &&elem) noexcept
    {

        size += 1;
        Node *tmp = new Node(elem);
        Node *curr = head;
        while (curr.next != nullptr)
        {

            curr = curr->next;
        }

        curr.next = tmp;
    }

    template <typename Data>
    void List<Data>::Clear()
    {

        this->size = 0;
        this->head = nullptr;
    }

    template <typename Data>
    Data &List<Data>::Front() const
    {

        if (this->size == 0)
        {

            throw std::length_error("Lista vuota! Impossibile restituire primo elemento");
        }
        else
        {

            return (this->head)->elem;
        }
    }

    template <typename Data>
    Data &List<Data>::Back() const
    {

        if (this->size == 0)
        {

            throw std::length_error("Lista vuota! Impossibile restituire l'ultimo elemento");
        }
        else
        {

            Node *curr = head;
            while (curr->next != nullptr)
            {

                curr = curr->next;
            }

            return curr->elem;
        }
    }

    template <typename Data>
    Data &List<Data>::operator[](unsigned long index) const
    {

        if (index >= size)
        {

            throw std::out_of_range("Indice maggiore della lunghezza della stringa!");
        }
        else
        {

            Node *curr = head;
            while (index > 0)
            {

                curr = curr->next;
                --index;
            }

            return curr->elem;
        }
    }

    /* ************************************************************************** */

    template <typename Data>
    void List<Data>::Map(MapFunctor funzione, void *parametro)
    {

        MapPreOrder(funzione, parametro);
    }

    template <typename Data>
    void List<Data>::MapPreOrder(const MapFunctor funzione, void *parametro)
    {

        Node *curr = head;
        while (curr != nullptr)
        {

            funzione(curr->elem, parametro);
            curr = curr->next;
        }
    }

    template <typename Data>
    void List<Data>::MapPostOrder(const MapFunctor funzione, void *parametro)
    {

        unsigned long index = size;

        while (index > 0)
        {

            funzione((*this)[--index], parametro);
        }
    }

    template <typename Data>
    void List<Data>::Fold(FoldFunctor funzione, const void *parametro, void *accumulatore) const
    {
        FoldPreOrder(funzione, parametro, accumulatore);
    }

    template <typename Data>
    void List<Data>::FoldPreOrder(FoldFunctor funzione, const void *parametro, void *accumulatore) const
    {

        Node *curr = head;
        while (curr != nullptr)
        {

            funzione(curr->elem, parametro, accumulatore);
            curr = curr->next;
        }
    }

    template <typename Data>
    void List<Data>::FoldPostOrder(FoldFunctor funzione, const void *parametro, void *accumulatore) const
    {

        unsigned long index = size;

        while (index > 0)
        {

            funzione((*this)[--index], parametro, accumulatore);
        }
    }

    template <typename Data>
    void List<Data>::MapPreOrder(const MapFunctor funzione, void *parametro, unsigned long index)
    {

        if (this->Empty())
        {

            throw std::length_error("Lista vuota!");
        }
        else
        {

            if (index > size)
            {

                throw std::out_of_range("Indice oltre la size della lista!");
            }
            else
            {

                Node *curr = head;
                while (index > 0)
                {

                    funzione(curr.elem, parametro);
                    curr = curr->next;
                    --index;
                }
            }
        }
    }

    template <typename Data>
    void List<Data>::MapPostOrder(const MapFunctor funzione, void *parametro, unsigned long index)
    {

        if (this->Empty())
        {

            throw std::length_error("Lista vuota!");
        }
        else
        {

            if (index > size)
            {

                throw std::out_of_range("Indice oltre la size della lista!");
            }
            else
            {

                while (index > 0)
                {

                    Data elemento = this[--index];
                    funzione(elemento, parametro);
                }
            }
        }
    }

    template <typename Data>
    void List<Data>::FoldPreOrder(FoldFunctor funzione, const void *parametro, void *accumulatore, unsigned long index)
    {

        if (this->Empty())
        {

            throw std::length_error("La lista è vuota!");
        }
        else
        {

            if (index > size)
            {

                throw std::out_of_range("Indice oltre la size della lista!");
            }
            else
            {

                Node *curr = head;
                while (index > 0)
                {

                    funzione(curr.elem, parametro, accumulatore);
                    curr = curr.next;
                    --index;
                }
            }
        }
    }

    template <typename Data>
    void List<Data>::FoldPostOrder(FoldFunctor funzione, const void *parametro, void *accumulatore, unsigned long index)
    {

        if (this->Empty())
        {

            throw std::length_error("Lista vuota!");
        }
        else
        {

            if (index > size)
            {

                throw std::out_of_range("Indice oltre la size della lista!");
            }
            else
            {

                while (index > 0)
                {

                    Data elemento = this[index];
                    funzione(elemento, parametro, accumulatore);
                    --index;
                }
            }
        }
    }

}
