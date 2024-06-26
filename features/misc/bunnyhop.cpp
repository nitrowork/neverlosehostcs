// This is an independent project of an individual developer. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: http://www.viva64.com

#include "bunnyhop.h"
#include "prediction_system.h"

void bunnyhop::create_move()
{
	if (globals.local()->get_move_type() == MOVETYPE_LADDER) //-V807
		return;

	static auto last_jumped = false;
	static auto should_jump = false;

	if (!last_jumped && should_jump)
	{
		should_jump = false;
		globals.get_command()->m_buttons |= IN_JUMP;
	}
	else if (globals.get_command()->m_buttons & IN_JUMP)
	{
		if (globals.local()->m_fFlags() & FL_ONGROUND || !globals.local()->m_vecVelocity().z)
		{
			last_jumped = true;
			should_jump = true;
		}
		else 
		{
			globals.get_command()->m_buttons &= ~IN_JUMP;
			last_jumped = false;
		}
	}
	else
	{
		last_jumped = false;
		should_jump = false;
	}
}