#pragma once

#include "ACommandPrefix.h"
#include "parsec.h"
#include "../Stringer.h"
#include "../Utils.h"


class ACommandSearchUserIntArg : public ACommandPrefix
{
public:
	bool run(const char * msg, const char* prefix, ParsecGuest* guests, int guestCount, ParsecGuest * targetUser, int * intArg)
	{
		if (!ACommandPrefix::run(msg, prefix))
		{
			return false;
		}

		try
		{
			std::string str = msg;

			std::string argNumber = std::string() + str.back();
			*intArg = std::stoi(argNumber);

			std::string args = str.substr(strlen(prefix));
			std::string username = args.substr(0, args.size() - 2);

			ParsecGuest target;
			bool found = Utils::findUser(username, guests, guestCount, &target);
			if (!found)
			{
				return false;
			}

			return true;
		}
		catch (const std::exception&)
		{
			return false;
		}
	}
};