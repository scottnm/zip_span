#pragma once

#include <gsl/span>

#define APPLY_TO_TEMPLATE_LIST(MACRO) \
    MACRO(1) \
    MACRO(2) \

#define TEMPLATE_PARAM_DECL(N) \
    , typename T##N

#define TEMPLATE_SPAN_PARAM_LIST(N) \
    ,gsl::span<T##N> s##N

#define TEMPLATE_CTOR_SPAN_FIELD_INIT(N) \
    s##N(s##N),

#define TEMPLATE_PARAM(N) \
    ,T##N

#define TEMPLATE_POINTER_PARAM(N) \
    ,T##N*

#define TEMPLATE_ADVANCE_ITERATOR_ELEMENT(N) \
    std::get<##N>(current) + 1,

#define TEMPLATE_CHECK_ELEMENT_EQ(N) \
    && std::get<##N>(current) == std::get<##N>(other.current)

#define TEMPLATE_GET_BEGIN_REF(N) \
    &s##N[0],

#define TEMPLATE_GET_END_REF(N) \
    &s##N[0] + len,

#define TEMPLATE_DEFINE_SPAN_FIELDS(N) \
    const gsl::span<T##N> s##N;

#define TEMPLATE_MIN_SPAN_SIZE_HEAD(N) \
    std::min(s##N.size(),

#define TEMPLATE_MIN_SPAN_SIZE_TAIL(N) \
    )

#define TEMPLATE_SPAN_VAR_LIST(N) \
    ,s##N

template <
    typename T0
    APPLY_TO_TEMPLATE_LIST(TEMPLATE_PARAM_DECL)
    >
class ZipIterable
{
public:
    ZipIterable(
        ptrdiff_t len,
        gsl::span<T0> s0
        APPLY_TO_TEMPLATE_LIST(TEMPLATE_SPAN_PARAM_LIST)
        ) :
        s0(s0),
        APPLY_TO_TEMPLATE_LIST(TEMPLATE_CTOR_SPAN_FIELD_INIT)
        len(len)
    {
    }

    typename typedef std::tuple<
        T0*
        APPLY_TO_TEMPLATE_LIST(TEMPLATE_POINTER_PARAM)
        > TItem;

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
                APPLY_TO_TEMPLATE_LIST(TEMPLATE_ADVANCE_ITERATOR_ELEMENT)
            };

            return *this;
        }

        bool operator==(
            const ZipIterator& other
            )
        {
            return std::get<0>(current) == std::get<0>(other.current)
                APPLY_TO_TEMPLATE_LIST(TEMPLATE_CHECK_ELEMENT_EQ);
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
            &s0[0],
            APPLY_TO_TEMPLATE_LIST(TEMPLATE_GET_BEGIN_REF)
            });
    }

    ZipIterator
    end()
    {
        return ZipIterator(TItem{
            &s0[0] + len,
            APPLY_TO_TEMPLATE_LIST(TEMPLATE_GET_END_REF)
            });
    }

private:
    const gsl::span<T0> s0;
    APPLY_TO_TEMPLATE_LIST(TEMPLATE_DEFINE_SPAN_FIELDS)
    const ptrdiff_t len;
};

template<
    typename T0
    APPLY_TO_TEMPLATE_LIST(TEMPLATE_PARAM_DECL)
    >
ZipIterable<
    T0
    APPLY_TO_TEMPLATE_LIST(TEMPLATE_PARAM)
    >
zip_span(
    gsl::span<T0> s0
    APPLY_TO_TEMPLATE_LIST(TEMPLATE_SPAN_PARAM_LIST)
    )
{
    return {
        std::min(s0.size(),
        APPLY_TO_TEMPLATE_LIST(TEMPLATE_MIN_SPAN_SIZE_HEAD)
        std::numeric_limits<ptrdiff_t>::max())
        APPLY_TO_TEMPLATE_LIST(TEMPLATE_MIN_SPAN_SIZE_TAIL),
        s0
        APPLY_TO_TEMPLATE_LIST(TEMPLATE_SPAN_VAR_LIST)
        };
}

#define TEMPLATE_PARAM_PLUS_SIZE_DECL(M) \
    ,typename T##M, size_t N##M

#define TEMPLATE_ARRAY_LITERAL_PARAM(M) \
    ,T##M (&s##M)[N##M]

template<
    typename T0, size_t N0
    APPLY_TO_TEMPLATE_LIST(TEMPLATE_PARAM_PLUS_SIZE_DECL)
    >
ZipIterable<
    T0
    APPLY_TO_TEMPLATE_LIST(TEMPLATE_PARAM)
    >
zip_span(
    T0 (&s0)[N0]
    APPLY_TO_TEMPLATE_LIST(TEMPLATE_ARRAY_LITERAL_PARAM)
    )
{
    return zip_span<
        T0
        APPLY_TO_TEMPLATE_LIST(TEMPLATE_PARAM)
        >(
        s0
        APPLY_TO_TEMPLATE_LIST(TEMPLATE_SPAN_VAR_LIST)
        );
}
