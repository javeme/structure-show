#if !defined(_DEFINE_LINKNODE)

#define _DEFINE_LINKNODE

//单链表节点定义
template <class EleType>
struct LINKNODE
{
	EleType Data;
	LINKNODE<EleType> *Next;
};

#endif
