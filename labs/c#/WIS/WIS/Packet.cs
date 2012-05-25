using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace WIS
{
	static class Packet
	{
		public const UInt32 GS_2_WIS_USE_ROOKIE_CARD = 14401;


		public const UInt32 WIS_2_GS_USE_ROOKIE_CARD_RESULT = 15425;


		public enum UseRookieCardResult
		{
			ret_ok,
			ret_expired,
			ret_already_used,
		};

	}
}
