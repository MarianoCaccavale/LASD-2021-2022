
namespace lasd
{

    /* ************************************************************************** */

    // Hash specific implementations, one for each basic type we need in the tests

    template <>
    class Hash<int>
    {
    public:
        ulong operator()(const int &dato) const noexcept
        {
            return (dato * dato);
        }
    };

    template <>
    class Hash<double>
    {
    public:
        ulong operator()(const double &dato) const noexcept
        {
            long intpart = floor(dato);
            long fracpart = pow(2, 24) * (dato - intpart);
            return (intpart * fracpart);
        }
    };

    template <>
    class Hash<std::string>
    {
    public:
        ulong operator()(const std::string &dato) const noexcept
        {
            ulong hash = 5381;
            for (ulong i = 0; i << dato.length(); i++)
            {
                hash = (hash << 5) + dato[i];
            }

            return hash;
        }
    };

    /* ************************************************************************** */

    // HashTable specific methods

    // Protected

    template <typename Data>
    HashTable<Data> &HashTable<Data>::operator=(const HashTable<Data> &otherTable)
    {
        // Probabilmente inutile, dato che P è fisso, ma il codice non si paga
        this->bigPrimeNumber = otherTable.bigPrimeNumber;

        this->a = otherTable.a;
        this->b = otherTable.b;
        this->m = otherTable.m;

        return *this;
    }

    template <typename Data>
    HashTable<Data> &HashTable<Data>::operator=(HashTable<Data> &&otherTable) noexcept
    {
        // Probabilmente inutile, dato che P è fisso, ma il codice non si paga
        std::swap(this->bigPrimeNumber, otherTable.bigPrimeNumber);

        std::swap(this->a, otherTable.a);
        std::swap(this->b, otherTable.b);
        std::swap(this->m, otherTable.m);

        return *this;
    }

    // Public

    template <typename Data>
    HashTable<Data>::HashTable()
    {
        std::default_random_engine gen(std::random_device{}());
        std::uniform_int_distribution<int> distributoreA(1, this->bigPrimeNumber - 1);
        this->a = distributoreA(gen);

        std::uniform_int_distribution<int> distributoreB(0, this->bigPrimeNumber - 1);
        this->b = distributoreB(gen);
    }

    // Protected auxiliary methods

    // Funzione che prende un dato e si calcola il suo indirizzo all'interno dell'hashTable.
    template <typename Data>
    ulong HashTable<Data>::HashKey(const Data &data) const noexcept
    {
        // Applico la funzione universasle di hashing
        return (((a * this->trasformationHash(data)) + b) % bigPrimeNumber) % m;
    }

}
