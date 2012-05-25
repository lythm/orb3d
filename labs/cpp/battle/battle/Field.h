#pragma once

namespace battle_engine
{
	class Cell;

	class Field
	{
	public:

		Field(void);
		virtual ~Field(void);


	private:

		boost::function<void (Field*)>												handler_ResetField;
		
		//boost::function<void (Field*, const std::vector<Cell*>&)>					handler_FillCells;

		boost::function<void (Field*, Cell*)>										handler_GenCell;

				
	};


}