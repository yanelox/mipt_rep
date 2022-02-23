template <typename T>
class ICache_Repr
{
    using It = typename ICache_Repr <T>::iterator;

    virtual It begin () = 0;
    virtual It end   () = 0;

    virtual int add    (T &elem) = 0;
    virtual int remove (It elem) = 0;

    virtual ~ICache_Repr () {}
};

template <typename T>
class ICache_Strat
{
    using It = typename ICache_Repr <T>::iterator;

    virtual It pop_choose (It begin, It end);

    virtual ~ICache_Strat () {}
};

template <typename T>
class Cache: private ICache_Repr <T>, private ICache_Strat <T>
{
    Cache (ICache_Repr <T> &repr, ICache_Strat <T> &strat): ICache_Repr <T> (repr), ICache_Strat <T> (strat) {}

    void insert (T &elem)
    {
        int res = add (&elem);

        if (res == -1)
        {
            remove (ICache_Strat <T>::pop_choose (ICache_Repr <T>::begin (), ICache_Repr <T>::end ()));

            add (&elem);
        }
    }
};

int main ()
{
    ;
}