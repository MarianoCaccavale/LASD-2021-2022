
namespace lasd
{

    /* ************************************************************************** */

    // DictionaryContainer specific methods

    template <typename Data>
    void DictionaryContainer<Data>::Insert(const LinearContainer<Data> &container)
    {
        for(ulong i = 0; i < container.Size(); i++){
            this->Insert(container[i]);
        }
    }

    template <typename Data>
    void DictionaryContainer<Data>::Insert(LinearContainer<Data> &&container)
    {
        for(ulong i = 0; i < container.Size(); i++){
            this->Insert(container[i]);
        }
    }

    template <typename Data>
    void DictionaryContainer<Data>::Remove(const LinearContainer<Data> &container)
    {
        for(ulong i = 0; i < container.Size(); i++){
            this->Remove(container[i]);
        }
    }

    /* ************************************************************************** */

    // FoldableContainer

    template <typename Data>
    void AuxFoldExits(const Data &elem, const void *val, void *exits)
    {

        if (elem == *((Data *)val))
        {

            *((bool *)exits) = true;
        }
    }

    template <typename Data>
    bool FoldableContainer<Data>::Exists(const Data &elem) const noexcept
    {

        bool exits = false;
        Fold(&AuxFoldExits<Data>, &elem, &exits);
        return exits;
    }

    /* ************************************************************************** */

    // PreOrderMappableContainer

    template <typename Data>
    void PreOrderMappableContainer<Data>::Map(MapFunctor funzione, void *parametro)
    {
        MapPreOrder(funzione, parametro);
    }

    // PreOrderFoldableContainer

    template <typename Data>
    void PreOrderFoldableContainer<Data>::Fold(FoldFunctor funzione, const void *parametro, void *accumulatore) const
    {

        FoldPreOrder(funzione, parametro, accumulatore);
    }

    // PostOrderMappableContainer
    template <typename Data>
    void PostOrderMappableContainer<Data>::Map(MapFunctor funzione, void *parametro)
    {

        MapPostOrder(funzione, parametro);
    }

    // PostOrderFoldableContainer
    template <typename Data>
    void PostOrderFoldableContainer<Data>::Fold(FoldFunctor funzione, const void *parametro, void *accumulatore) const
    {
        FoldPostOrder(funzione, parametro, accumulatore);
    }

    // InOrderMappableContainer
    template <typename Data>
    void InOrderMappableContainer<Data>::Map(MapFunctor funzione, void *parametro)
    {

        MapInOrder(funzione, parametro);
    }

    // InOrderFoldableContainer
    template <typename Data>
    void InOrderFoldableContainer<Data>::Fold(FoldFunctor funzione, const void *parametro, void *accumulatore) const
    {
        FoldInOrder(funzione, parametro, accumulatore);
    }

    // BreadthMappableContainer
    template <typename Data>
    void BreadthMappableContainer<Data>::Map(MapFunctor funzione, void *parametro)
    {

        MapBreadth(funzione, parametro);
    }

    // BreadthFoldableContainer
    template <typename Data>
    void BreadthFoldableContainer<Data>::Fold(FoldFunctor funzione, const void *parametro, void *accumulatore) const
    {
        FoldBreadth(funzione, parametro, accumulatore);
    }

    /* ************************************************************************** */
}
