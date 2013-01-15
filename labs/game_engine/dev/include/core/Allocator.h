#pragma once

#include "types\types.h"

namespace ld3d
{
	class EXPORT_CLASS Allocator
	{
	public:

		virtual void*								Alloc(uint64 bytes)					= 0;
		virtual void								Free(void* mem)						= 0;

		template<typename T>
		boost::shared_ptr<T>						AllocObject()
		{
			T* pObj = (T*)Alloc(sizeof(T));
			
			return boost::shared_ptr<T>(new (pObj)T, boost::bind(&Allocator::FreeObject<T>, this, _1));
		}
		template<typename T, typename TP>
		boost::shared_ptr<T>						AllocObject(TP param)
		{
			T* pObj = (T*)Alloc(sizeof(T));
			
			return boost::shared_ptr<T>(new (pObj) T(param), boost::bind(&Allocator::FreeObject<T>, this, _1));
		}

		template<typename T, typename TP1, typename TP2>
		boost::shared_ptr<T>						AllocObject(TP1 p1, TP2 p2)
		{
			T* pObj = (T*)Alloc(sizeof(T));
			
			return boost::shared_ptr<T>(new (pObj) T(p1, p2), boost::bind(&Allocator::FreeObject<T>, this, _1));
		}

	private:
		template<typename T>
		void										FreeObject(T* pObj)
		{
			pObj->~T();
			Free(pObj);
		}

	protected:

		Allocator(void){}
		virtual ~Allocator(void){}
	};
}