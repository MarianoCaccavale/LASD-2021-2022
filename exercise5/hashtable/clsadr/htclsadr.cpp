
namespace lasd
{

    /* ************************************************************************** */

    template <typename Data>
    HashTableClsAdr<Data>::HashTableClsAdr()
    {
        // Implicita chiamata al costruttore della superclasse, quindi ho che a e b vengono inizializzate. P è
        // costante, e m prende il valore di default, dichiarato nell'interfaccia. Mi basta solo inizializzare l'array

        this->table = Vector<BST<Data>>(this->m);
    }

    template <typename Data>
    HashTableClsAdr<Data>::HashTableClsAdr(const ulong &size)
    {
        // Implicita chiamata al costruttore della superclasse, quindi ho che a e b vengono inizializzate. P è
        // costante, e m lo assegno subito dopo
        this->m = size;

        this->table = Vector<BST<Data>>(size);
    }

    template <typename Data>
    HashTableClsAdr<Data>::HashTableClsAdr(const LinearContainer<Data> &container)
    {
        this->m = (container.Size() * 2.0);

        this->table = Vector<BST<Data>>(this->m);

        DictionaryContainer<Data>::Insert(container);
    }

    template <typename Data>
    HashTableClsAdr<Data>::HashTableClsAdr(const ulong &size, const LinearContainer<Data> &container)
    {
        this->m = size;

        this->table = Vector<BST<Data>>(this->m);

        DictionaryContainer<Data>::Insert(container);
    }

    template <typename Data>
    HashTableClsAdr<Data>::HashTableClsAdr(const HashTableClsAdr<Data> &otherTable)
    {
        this->a = otherTable.a;
        this->b = otherTable.b;

        this->bigPrimeNumber = otherTable.bigPrimeNumber;

        this->m = otherTable.m;

        this->table = otherTable.table;
        this->size = otherTable.size;
    }

    template <typename Data>
    HashTableClsAdr<Data>::HashTableClsAdr(HashTableClsAdr<Data> &&otherTable) noexcept
    {
        std::swap(this->a, otherTable.a);
        std::swap(this->b, otherTable.b);
        std::swap(this->bigPrimeNumber, otherTable.bigPrimeNumber);
        std::swap(this->m, otherTable.m);
        std::swap(this->table, otherTable.table);
        std::swap(this->size, otherTable.size);
    }

    template <typename Data>
    HashTableClsAdr<Data> &HashTableClsAdr<Data>::operator=(const HashTableClsAdr<Data> &otherTable)
    {
        HashTable<Data>::operator=(otherTable);

        this->table = otherTable.table;
        this->size = otherTable.size;

        return *this;
    }

    template <typename Data>
    HashTableClsAdr<Data> &HashTableClsAdr<Data>::operator=(HashTableClsAdr<Data> &&otherTable) noexcept
    {
        HashTable<Data>::operator=(otherTable);

        std::swap(this->table, otherTable.table);
        std::swap(this->size, otherTable.size);

        return *this;
    }

    template <typename Data>
    bool HashTableClsAdr<Data>::operator==(const HashTableClsAdr &otherTable) const noexcept
    {

        bool result = true;

        if (this->size != otherTable.size)
            return false;

        Fold([otherTable, &result](const Data &dato, const void *parametro, void *accumulatore)
             {
            if(!otherTable.Exists(dato)){
                result = false;
            } },
             0, 0);

        return result;
    }

    template <typename Data>
    bool HashTableClsAdr<Data>::operator!=(const HashTableClsAdr &otherTable) const noexcept
    {
        return !(*this == otherTable);
    }

    template <typename Data>
    void HashTableClsAdr<Data>::Resize(const ulong &newSize)
    {

        if (this->m == newSize)
            return;

        HashTableClsAdr<Data> newTable = HashTableClsAdr<Data>(newSize);

        this->Map([&newTable](Data &dato, void *parametro)
                  { newTable.Insert(dato); },
                  0);

        std::swap(*this, newTable);
    }

    template <typename Data>
    bool HashTableClsAdr<Data>::Insert(const Data &dataToInsert)
    {
        // Per prima cosa devo ottenere la chiave il cui slot è quello in cui è mappato il dato
        //  e poi devo andare ad inserire nel Dictionary nello slot "key" il dato
        if (this->table[this->HashKey(dataToInsert)].Insert(dataToInsert))
        {
            this->size += 1;
            return true;
        }
        else
        {
            return false;
        };
    }

    template <typename Data>
    bool HashTableClsAdr<Data>::Insert(Data &&dataToInsert)
    {
        // Stessa cosa di prima ma con il &&
        if (this->table[this->HashKey(dataToInsert)].Insert(dataToInsert))
        {
            this->size += 1;
            return true;
        }
        else
        {
            return false;
        }
    }

    template <typename Data>
    bool HashTableClsAdr<Data>::Remove(const Data &dataToDelete)
    {

        if (this->table[this->HashKey(dataToDelete)].Remove(dataToDelete))
        {
            this->size -= 1;
            return true;
        }
        else
        {
            return false;
        }
    }

    template <typename Data>
    bool HashTableClsAdr<Data>::Exists(const Data &dataToSearch) const noexcept
    {
        return this->table[this->HashKey(dataToSearch)].Exists(dataToSearch);
    }

    template <typename Data>
    void HashTableClsAdr<Data>::Map(MapFunctor funzione, void *parametro)
    {
        for (ulong i = 0; i < this->m; i++)
        {
            this->table[i].Map(funzione, parametro);
        }
    }

    template <typename Data>
    void HashTableClsAdr<Data>::Fold(FoldFunctor funzione, const void *parametro, void *accumulatore) const
    {
        for (ulong i = 0; i < this->m; i++)
        {
            this->table[i].Fold(funzione, parametro, accumulatore);
        }
    }

    template <typename Data>
    void HashTableClsAdr<Data>::Clear()
    {
        HashTableClsAdr<Data> *newHashTable = new HashTableClsAdr<Data>();
        std::swap(*this, *newHashTable);
        this->size = 0;
        delete newHashTable;
    }

    /* ************************************************************************** */

}
