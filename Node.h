#if !defined(_DEFINE_LINKNODE)

#define _DEFINE_LINKNODE

//������ڵ㶨��
template <class EleType>
struct LINKNODE
{
	EleType Data;
	LINKNODE<EleType> *Next;
};

#endif
