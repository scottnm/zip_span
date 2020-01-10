#pragma once

#include <gsl/span>

//
// An iterable over all elements of the source iterable except those which match the predicate
//
template <typename T1, typename T2, typename T3>
class ZipIterable
{
public:
    ZipIterable(
        gsl::span<T1> s1,
        gsl::span<T2> s2,
        gsl::span<T3> s3,
        ptrdiff_t len
        ) :
        s1(s1),
        s2(s2),
        s3(s3),
        len(len)
    {
    }

    typename typedef std::tuple<T1*, T2*, T3*> TItem;

    class ZipIterator
    {
    public:
        ZipIterator(
            TItem current
            ) :
            current(current)
        {
        }

        ZipIterator&
        operator++()
        {
            current =
            {
                std::get<0>(current) + 1,
                std::get<1>(current) + 1,
                std::get<2>(current) + 1,
            };

            return *this;
        }

        bool operator==(
            const ZipIterator& other
            )
        {
            return
                std::get<0>(current) == std::get<0>(other.current) &&
                std::get<1>(current) == std::get<1>(other.current) &&
                std::get<2>(current) == std::get<2>(other.current);
        }

        bool operator!=(
            const ZipIterator& other
            )
        {
            return !(*this == other);
        }

        TItem* operator->() { return &current; }
        TItem& operator *() { return current; }
        const TItem* operator->() const { return &current; }
        const TItem& operator *() const { return current; }

    private:
        TItem current;
    };

    ZipIterator
    begin()
    {
        return ZipIterator(TItem{
            &s1[0],
            &s2[0],
            &s3[0],
            });
    }

    ZipIterator
    end()
    {
        return ZipIterator(TItem{
            &s1[0] + len,
            &s2[0] + len,
            &s3[0] + len,
            });
    }

private:
    const gsl::span<T1> s1;
    const gsl::span<T2> s2;
    const gsl::span<T3> s3;
    const ptrdiff_t len;
};

template<typename T1, typename T2, typename T3>
ZipIterable<T1, T2, T3>
zip_span(
    gsl::span<T1> s1,
    gsl::span<T2> s2,
    gsl::span<T3> s3
    )
{
    return {
        s1,
        s2,
        s3,
        std::min(std::min(s1.size(), s2.size()), s3.size())
        };
}

template<typename T1, size_t N1, typename T2, size_t N2, typename T3, size_t N3>
ZipIterable<T1, T2, T3>
zip_span(
    T1 (&s1)[N1],
    T2 (&s2)[N2],
    T3 (&s3)[N3]
    )
{
    return zip_span<T1, T2, T3>(s1, s2, s3);
}
