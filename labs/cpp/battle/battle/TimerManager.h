#pragma once




class TimerManager
{
public:

	struct TimerNode
	{
		int						interval;
		int						start_tick;

		boost::function<void (void* timer, int interval, void* context)> handler;
		void*					handler_context;

		TimerNode*				prev;
		TimerNode*				next;
	};


	TimerManager(void);
	virtual ~TimerManager(void);

	bool						Init();
	void						Release();
	void						Update();

	void*						RegisterTimer(int interval, void* context, const boost::function<void (void*, int, void*)>& handler);

	template<typename HandlerObject>
	void*						RegisterTimer(int interval, void* context, HandlerObject* obj, const boost::function<void (HandlerObject*, void* , int , void*)>& handler)
	{
		return RegisterTimer(interval, context, boost::bind(handler, obj, _1, _2, _3));
	}
	void						RemoveTimer(void* timer);

private:
	void						InsertNode(TimerNode* pNewNode);
	void						UnLink(TimerNode* pNode);
private:

	TimerNode*					m_head;

};

