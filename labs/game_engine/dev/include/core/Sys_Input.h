#pragma once

#include "types\types.h"

namespace ld3d
{
	class Sys_Input
	{
	public:

		enum KeyCode
		{
			key_escape          = 0x01,
			key_1               = 0x02,
			key_2               = 0x03,
			key_3               = 0x04,
			key_4               = 0x05,
			key_5               = 0x06,
			key_6               = 0x07,
			key_7               = 0x08,
			key_8               = 0x09,
			key_9               = 0x0A,
			key_0               = 0x0B,
			key_minus           = 0x0C,
			key_equals          = 0x0D,
			key_back            = 0x0E,
			key_tab             = 0x0F,
			key_q               = 0x10,
			key_w               = 0x11,
			key_e              	= 0x12,
			key_r              	= 0x13,
			key_t              	= 0x14,
			key_y              	= 0x15,
			key_u              	= 0x16,
			key_i              	= 0x17,
			key_o              	= 0x18,
			key_p              	= 0x19,
			key_lbracket       	= 0x1A,
			key_rbracket       	= 0x1B,
			key_return         	= 0x1C,
			key_lcontrol       	= 0x1D,
			key_a              	= 0x1E,
			key_s              	= 0x1F,
			key_d              	= 0x20,
			key_f              	= 0x21,
			key_g              	= 0x22,
			key_h              	= 0x23,
			key_j              	= 0x24,
			key_k              	= 0x25,
			key_l              	= 0x26,
			key_semicolon      	= 0x27,
			key_apostrophe		= 0x28,
			key_grave          	= 0x29,
			key_lshift         	= 0x2A,
			key_backslash      	= 0x2B,
			key_z              	= 0x2C,
			key_x              	= 0x2D,
			key_c              	= 0x2E,
			key_v              	= 0x2F,
			key_b              	= 0x30,
			key_n              	= 0x31,
			key_m              	= 0x32,
			key_comma          	= 0x33,
			key_period         	= 0x34,
			key_slash          	= 0x35,
			key_rshift         	= 0x36,
			key_multiply       	= 0x37,
			key_lmenu          	= 0x38,
			key_space          	= 0x39,
			key_capital        	= 0x3A,
			key_f1             	= 0x3B,
			key_f2             	= 0x3C,
			key_f3             	= 0x3D,
			key_f4             	= 0x3E,
			key_f5             	= 0x3F,
			key_f6             	= 0x40,
			key_f7             	= 0x41,
			key_f8             	= 0x42,
			key_f9             	= 0x43,
			key_f10            	= 0x44,
			key_numlock        	= 0x45,
			key_scroll         	= 0x46,
			key_numpad7        	= 0x47,
			key_numpad8        	= 0x48,
			key_numpad9        	= 0x49,
			key_subtract       	= 0x4A,
			key_numpad4        	= 0x4B,
			key_numpad5        	= 0x4C,
			key_numpad6        	= 0x4D,
			key_add            	= 0x4E,
			key_numpad1        	= 0x4F,
			key_numpad2        	= 0x50,
			key_numpad3        	= 0x51,
			key_numpad0        	= 0x52,
			key_decimal        	= 0x53,
			key_oem_102        	= 0x56,
			key_f11            	= 0x57,
			key_f12            	= 0x58,
			key_f13            	= 0x64,
			key_f14            	= 0x65,
			key_f15            	= 0x66, 
			key_kana           	= 0x70, 
			key_abnt_c1        	= 0x73, 
			key_convert        	= 0x79, 
			key_noconvert      	= 0x7B, 
			key_yen            	= 0x7D, 
			key_abnt_c2        	= 0x7E,
			key_numpadequals   	= 0x8D,
			key_prevtrack      	= 0x90,
			key_at             	= 0x91,
			key_colon          	= 0x92,
			key_underline      	= 0x93,
			key_kanji          	= 0x94,
			key_stop           	= 0x95,
			key_ax             	= 0x96,
			key_unlabeled      	= 0x97,
			key_nexttrack      	= 0x99,
			key_numpadenter    	= 0x9C,
			key_rcontrol       	= 0x9D,
			key_mute           	= 0xA0,
			key_calculator     	= 0xA1,
			key_playpause      	= 0xA2,
			key_mediastop      	= 0xA4,
			key_volumedown     	= 0xAE,
			key_volumeup       	= 0xB0,
			key_webhome        	= 0xB2,
			key_numpadcomma    	= 0xB3,
			key_divide         	= 0xB5,
			key_sysrq          	= 0xB7,
			key_rmenu          	= 0xB8,
			key_pause          	= 0xC5,
			key_home           	= 0xC7,
			key_up             	= 0xC8,
			key_prior          	= 0xC9,
			key_left           	= 0xCB,
			key_right          	= 0xCD,
			key_end            	= 0xCF,
			key_down           	= 0xD0,
			key_next           	= 0xD1,
			key_insert         	= 0xD2,
			key_delete         	= 0xD3,
			key_lwin           	= 0xDB,
			key_rwin           	= 0xDC,
			key_apps           	= 0xDD,
			key_power          	= 0xDE,
			key_sleep          	= 0xDF,
			key_wake           	= 0xE3,
			key_websearch      	= 0xE5,
			key_webfavorites   	= 0xE6,
			key_webrefresh     	= 0xE7,
			key_webstop        	= 0xE8,
			key_webforward     	= 0xE9,
			key_webback        	= 0xEA,
			key_mycomputer     	= 0xEB,
			key_mail           	= 0xEC,
			key_mediaselect    	= 0xED,

		};
		struct KeyState
		{
			bool KeyDown(uint8 key) const
			{
				return (keys[key] & 0x80) != 0;
			}

			uint8				keys[256];
		};

		struct MouseState
		{
			bool LButtonDown() const
			{
				return (buttons[0] & 0x80) != 0;
			}
			bool RButtonDown() const
			{
				return (buttons[1] & 0x80) != 0;
			}
			bool MButtonDown() const
			{
				return (buttons[2] & 0x80) != 0;
			}

			int32				x;
			int32				y;

			int32				wheel;

			uint8				buttons[4];
		};
		
	public:


		virtual bool												Initialize(void* app_handle)										= 0;
		virtual void												Release()															= 0;
		virtual void												Update()															= 0;

		
		virtual const KeyState&										GetKeyState()														= 0;
		virtual const MouseState&									GetMouseState()														= 0;

#if defined(WIN32) || defined(WIN64)
		virtual void												HandleMessage(MSG& msg)												= 0;
#endif
	
		Sys_Input(void){}
		virtual ~Sys_Input(void){}
	};


}