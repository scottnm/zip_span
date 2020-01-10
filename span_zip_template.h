#ifndef CONCAT_HELPER
#define CONCAT_HELPER(a,b) a ## b
#endif // CONCAT_HELPER

#ifndef CONCAT
#define CONCAT(a,b) CONCAT_HELPER(a,b)
#endif // CONCAT

#undef DEFINE_ITERABLE
#define DEFINE_ITERABLE(NAME) CONCAT(ZipIterable,NAME)
#undef ITERABLE
#define ITERABLE DEFINE_ITERABLE(TUPLE_NAME)

#undef DEFINE_ITERATOR
#define DEFINE_ITERATOR(NAME) CONCAT(ZipIterator,NAME)
#undef ITERATOR
#define ITERATOR DEFINE_ITERATOR(TUPLE_NAME)

#undef TEMPLATE_PARAM_DECL
#define TEMPLATE_PARAM_DECL(N) \
    , typename T##N

#undef TEMPLATE_SPAN_PARAM_LIST
#define TEMPLATE_SPAN_PARAM_LIST(N) \
    ,gsl::span<T##N> s##N

#undef TEMPLATE_CTOR_SPAN_FIELD_INIT
#define TEMPLATE_CTOR_SPAN_FIELD_INIT(N) \
    s##N(s##N),

#undef TEMPLATE_PARAM
#define TEMPLATE_PARAM(N) \
    ,T##N

#undef TEMPLATE_POINTER_PARAM
#define TEMPLATE_POINTER_PARAM(N) \
    ,T##N*

#undef TEMPLATE_ADVANCE_ITERATOR_ELEMENT
#define TEMPLATE_ADVANCE_ITERATOR_ELEMENT(N) \
    std::get<##N>(current) + 1,

#undef TEMPLATE_CHECK_ELEMENT_EQ
#define TEMPLATE_CHECK_ELEMENT_EQ(N) \
    && std::get<##N>(current) == std::get<##N>(other.current)

#undef TEMPLATE_GET_BEGIN_REF
#define TEMPLATE_GET_BEGIN_REF(N) \
    &s##N[0],

#undef TEMPLATE_GET_END_REF
#define TEMPLATE_GET_END_REF(N) \
    &s##N[0] + len,

#undef TEMPLATE_DEFINE_SPAN_FIELDS
#define TEMPLATE_DEFINE_SPAN_FIELDS(N) \
    const gsl::span<T##N> s##N;

#undef TEMPLATE_MIN_SPAN_SIZE_HEAD
#define TEMPLATE_MIN_SPAN_SIZE_HEAD(N) \
    std::min(s##N.size(),

#undef TEMPLATE_MIN_SPAN_SIZE_TAIL
#define TEMPLATE_MIN_SPAN_SIZE_TAIL(N) \
    )

#undef TEMPLATE_SPAN_VAR_LIST
#define TEMPLATE_SPAN_VAR_LIST(N) \
    ,s##N

template <
    typename T0
    APPLY_TO_TEMPLATE_LIST(TEMPLATE_PARAM_DECL)
    >
class ITERABLE
{
public:
    ITERABLE(
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

    class ITERATOR
    {
    public:
        ITERATOR(
            TItem current
            ) :
            current(current)
        {
        }

        ITERATOR&
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
            const ITERATOR& other
            )
        {
            return std::get<0>(current) == std::get<0>(other.current)
                APPLY_TO_TEMPLATE_LIST(TEMPLATE_CHECK_ELEMENT_EQ);
        }

        bool operator!=(
            const ITERATOR& other
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

    ITERATOR
    begin()
    {
        return ITERATOR(TItem{
            &s0[0],
            APPLY_TO_TEMPLATE_LIST(TEMPLATE_GET_BEGIN_REF)
            });
    }

    ITERATOR
    end()
    {
        return ITERATOR(TItem{
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
ITERABLE<
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

#undef TEMPLATE_PARAM_PLUS_SIZE_DECL
#define TEMPLATE_PARAM_PLUS_SIZE_DECL(M) \
    ,typename T##M, size_t N##M

#undef TEMPLATE_ARRAY_LITERAL_PARAM
#define TEMPLATE_ARRAY_LITERAL_PARAM(M) \
    ,T##M (&s##M)[N##M]

template<
    typename T0, size_t N0
    APPLY_TO_TEMPLATE_LIST(TEMPLATE_PARAM_PLUS_SIZE_DECL)
    >
ITERABLE<
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
