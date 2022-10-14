
namespace lasd
{


    /* ************************************************************************** */

    template <typename Data>
    HashTableOpnAdr<Data>::HashTableOpnAdr()
    {
        // Implicita chiamata al costruttore di HashTable che setta a e b

        this->table = Vector<Data>(this->m);
        // Questo dovrebbe assegnare a tutti gli elementi dell'array il valore di default 0
        /*Legenda:
            - 0 = vuoto
            - 1 = cancellato
            - 2 = pieno
        */
        this->flags = Vector<char>(this->m);
    }

    template <typename Data>
    HashTableOpnAdr<Data>::HashTableOpnAdr(const ulong &size)
    {
        this->m = size;

        this->table = Vector<Data>(this->m);
        this->flags = Vector<char>(this->m);
    }

    template <typename Data>
    HashTableOpnAdr<Data>::HashTableOpnAdr(const LinearContainer<Data> &container)
    {

        this->m = (container.Size() * 2.0);

        this->table = Vector<Data>(this->m);
        this->flags = Vector<char>(this->m);

        DictionaryContainer<Data>::Insert(container);
        /* for (ulong i = 0; i < container.Size(); i++)
        {
            this->Insert(container[i]);
        } */
    }

    template <typename Data>
    HashTableOpnAdr<Data>::HashTableOpnAdr(const ulong &size, const LinearContainer<Data> &container)
    {

        this->m = size;

        this->table = Vector<Data>(this->m);
        this->flags = Vector<char>(this->m);

        DictionaryContainer<Data>::Insert(container);
        /* for (ulong i = 0; i < container.Size(); i++)
        {
            this->Insert(container[i]);
        } */
    }

    template <typename Data>
    HashTableOpnAdr<Data>::HashTableOpnAdr(const HashTableOpnAdr &otherTable)
    {
        this->m = otherTable.m;
        this->a = otherTable.a;
        this->b = otherTable.b;

        this->bigPrimeNumber = otherTable.bigPrimeNumber;

        this->table = otherTable.table;
        this->flags = otherTable.flags;
        this->size = otherTable.size;
    }

    template <typename Data>
    HashTableOpnAdr<Data>::HashTableOpnAdr(HashTableOpnAdr &&otherTable) noexcept
    {

        std::swap(this->m, otherTable.m);
        std::swap(this->a, otherTable.a);
        std::swap(this->b, otherTable.b);

        std::swap(this->bigPrimeNumber, otherTable.bigPrimeNumber);

        std::swap(this->table, otherTable.table);
        std::swap(this->flags, otherTable.flags);

        std::swap(this->size, otherTable.size);
    }

    template <typename Data>
    HashTableOpnAdr<Data> &HashTableOpnAdr<Data>::operator=(const HashTableOpnAdr<Data> &otherTable)
    {
        HashTable<Data>::operator=(otherTable);

        this->table = otherTable.table;
        this->flags = otherTable.flags;
        this->size = otherTable.size;

        return *this;
    }

    template <typename Data>
    HashTableOpnAdr<Data> &HashTableOpnAdr<Data>::operator=(HashTableOpnAdr<Data> &&otherTable) noexcept
    {
        HashTable<Data>::operator=(otherTable);

        std::swap(this->table, otherTable.table);
        std::swap(this->flags, otherTable.flags);
        std::swap(this->size, otherTable.size);

        return *this;
    }

    template <typename Data>
    bool HashTableOpnAdr<Data>::operator==(const HashTableOpnAdr<Data> &otherTable) const noexcept
    {

        bool result = true;

        if (this->size != otherTable.size)
        {
            result = false;
        }

        Fold([&otherTable, &result](const Data &dato, const void *parametro, void *accumulatore)
             {
                if(!otherTable.Exists(dato)){
                    result = false;
                } },
             0, 0);

        return result;
    }

    template <typename Data>
    bool HashTableOpnAdr<Data>::operator!=(const HashTableOpnAdr<Data> &otherTable) const noexcept
    {
        return !(*this == otherTable);
    }

    template <typename Data>
    void HashTableOpnAdr<Data>::Resize(const ulong &newSize)
    {

        if (this->m == newSize)
            return;

        HashTableOpnAdr<Data> newTable = HashTableOpnAdr<Data>(newSize);

        this->Map([&newTable](Data &dato, void *parametro)
                  { newTable.Insert(dato); },
                  0);

        std::swap(*this, newTable);
    }

    template <typename Data>
    bool HashTableOpnAdr<Data>::Insert(const Data &dataToInsert)
    {
        // Se non trovo l'elemento che sto cercando di inserire nella sequenza di probing dove dovrebbe andare vuol
        // dire che non sto cercando di inserire un duplicato, quindi posso inserirlo
        if (this->Find(dataToInsert) == -1)
        {
            long indexWhereInsert = this->FindEmpty(dataToInsert);

            // Se l'index che mi è stato restituito è diverso da -1 ho trovato uno spazio libero dove inserire l'oggetto
            if (indexWhereInsert != -1)
            {
                this->table[indexWhereInsert] = dataToInsert;
                this->flags[indexWhereInsert] = 2;
                this->size += 1;
                return true;
            }
            else
            {
                // Se non ho trovato nessuno spazio libero in cui inserire un dato, vuol dire che devo ingrandire
                // la table. Faccio prima il resize(che mi rimappa tutto in una nuova tabella con dimensione 2*m)
                // E poi richiamo l'insert. è considerabile ricorsive, in quanto poi ricerco se l'elemento è presente
                // in tabella(non dovrebbe), ma poi cerco comunque un'altra locazione libera. Ha senso????
                this->Resize(this->m * 2);
                this->Insert(dataToInsert);
            }
        }

        return false;
        // else elemento duplicato
    }

    template <typename Data>
    bool HashTableOpnAdr<Data>::Insert(Data &&dataToInsert)
    {
        // Se non trovo l'elemento che sto cercando di inserire nella sequenza di probing dove dovrebbe andare vuol
        // dire che non sto cercando di inserire un duplicato, quindi posso inserirlo
        if (this->Find(dataToInsert) == -1)
        {
            ulong indexWhereInsert = this->FindEmpty(dataToInsert);

            // Se l'index che mi è stato restituito è diverso da -1 ho trovato uno spazio libero dove inserire l'oggetto
            if (indexWhereInsert != -1)
            {
                std::swap(this->table[indexWhereInsert], dataToInsert);
                this->flags[indexWhereInsert] = 2;
                this->size += 1;
                return true;
            }
            else
            {
                // Se non ho trovato nessuno spazio libero in cui inserire un dato, vuol dire che devo ingrandire
                // la table. Faccio prima il resize(che mi rimappa tutto in una nuova tabella con dimensione 2*m)
                // E poi richiamo l'insert. è considerabile ricorsive, in quanto poi ricerco se l'elemento è presente
                // in tabella(non dovrebbe), ma poi cerco comunque un'altra locazione libera. Ha senso????
                this->Resize(this->m * 2);
                this->Insert(dataToInsert);
            }
        }

        return false;
        // else elemento duplicato
    }

    template <typename Data>
    bool HashTableOpnAdr<Data>::Remove(const Data &dataToDelete)
    {
        long indexOfData = this->Find(dataToDelete);

        if (indexOfData != -1)
        {
            this->flags[indexOfData] = 1;
            this->size -= 1;
            return true;
        }

        return false;
        // else l'elemento non è presente nella tabella
    }

    template <typename Data>
    bool HashTableOpnAdr<Data>::Exists(const Data &dataToSearch) const noexcept
    {
        return (this->Find(dataToSearch) != -1);
    }

    template <typename Data>
    void HashTableOpnAdr<Data>::Map(MapFunctor funzione, void *parametro)
    {
        for (ulong i = 0; i < this->m; i++)
        {
            if (this->flags[i] == 2)
                funzione(this->table[i], parametro);
        }
    }

    template <typename Data>
    void HashTableOpnAdr<Data>::Fold(FoldFunctor funzione, const void *parametro, void *accumulatore) const
    {
        for (ulong i = 0; i < this->m; i++)
        {
            if (this->flags[i] == 2)
                funzione(this->table[i], parametro, accumulatore);
        }
    }

    template <typename Data>
    void HashTableOpnAdr<Data>::Clear()
    {
        HashTableOpnAdr<Data> *newHashTable = new HashTableOpnAdr<Data>();
        std::swap(*this, *newHashTable);
        delete newHashTable;
    }

    // Auxiliary Function

    //Uso la sequenza di probing quadratica, in modo da evitare il problema del clustering primario, e per far si che
    //Le prestazioni non degradino troppo visitando solo alcune celle della table, uso la formula consigliata nel
    //Clifford, ovvero (i^2 + i)/2. Questo mi garantisce che se la size della tabella è potenza di due, visiterò tutti
    //gli elementi.(di default la size è potenza di due) 
    template <typename Data>
    ulong HashTableOpnAdr<Data>::HashKey(const Data &data, const ulong &index) const noexcept
    {
        // Applico la funzione universasle di hashing e vi aggiungo l'index a causa del probing
        return ((((this->a * this->trasformationHash(data)) + this->b) % this->bigPrimeNumber) +
                (ulong)(pow(index, 2)+ index) / 2) % this->m;
    }

    template <typename Data>
    long HashTableOpnAdr<Data>::Find(const Data &dataToFind, const ulong &startingIndex) const
    {

        ulong index = startingIndex;
        ulong currentKey = HashKey(dataToFind, index);

        // Controllo che nella sequenza di probing ci sia il dato che sto cercando
        do
        {
            if (this->table[currentKey] == dataToFind && this->flags[currentKey] == 2)
                // Se c'è, ritorno il suo index/chiave
                return currentKey;
            currentKey = HashKey(dataToFind, ++index);

            // Finchè non ho fatto il giro completo di tutta la sequenza
        } while (currentKey != HashKey(dataToFind, 0));

        // Se sono uscito dal while vuol dire che ho scorso tutta la sequenza ma non ho trovato il dato che sto
        // cercando
        return -1;
    }

    template <typename Data>
    long HashTableOpnAdr<Data>::FindEmpty(const Data &dataToFind, const ulong &startingIndex) const
    {

        ulong index = startingIndex;
        ulong currentKey = HashKey(dataToFind, index);

        do
        {

            if (this->flags[currentKey] == 0 || this->flags[currentKey] == 1)
                return currentKey;

            currentKey = HashKey(dataToFind, ++index);

        } while (currentKey != HashKey(dataToFind, 0));

        // Se sono uscito dal while vuol dire che ho scorso tutta la sequenza ma non trovato nessuno spazio lbero
        return -1;
    }

    /* ************************************************************************** */

}
