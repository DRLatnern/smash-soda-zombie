#pragma once

#include "parsec-dso.h"
#include "ACommandStringArg.h"
#include <algorithm>
#include <random>
#include "../Modules/Tournament.h"

class Command2v2 : public ACommandStringArg {
public:
	const COMMAND_TYPE type() override { return COMMAND_TYPE::BOT_MESSAGE; }

	Command2v2(const char* msg, GuestList& guests, GamepadClient& gamepadClient, Tournament tournament)
		: ACommandStringArg(msg, internalPrefixes()), _guests(guests), _gamepadClient(gamepadClient), _tournament(tournament)
	{}

	/// <summary>
	/// When command is first executed.
	/// </summary>
	/// <returns>Boolean</returns>
	bool run() override {

		// No sub command given
		if (!ACommandStringArg::run()) {

			// Start tournament
			if (!MetadataCache::tournament.isInit) {
				_replyMessage = _tournament.setup(1, 2);
				return true;
			}
			else {
				_replyMessage = "[TourneyBot] Usage: https://github.com/MickeyUK/SmashSoda/wiki/Tournaments\0";
				return false;
			}
			
		}

		// Sub commands
		if (_stringArg == "start") _replyMessage = _tournament.start();
		if (_stringArg == "stop") _replyMessage = _tournament.stop();
		if (_stringArg == "shuffle") _replyMessage = _tournament.shuffle();
		if (_stringArg == "brackets") _replyMessage = _tournament.brackets();

		return true;

	}

	/// <summary>
	/// Command prefixes.
	/// </summary>
	/// <returns>Vector</returns>
	static vector<const char*> prefixes() {
		return vector<const char*> { "!2v2" };
	}

protected:

	GuestList& _guests;
	GamepadClient& _gamepadClient;
	Tournament& _tournament;

	/// <summary>
	/// Internal prefixes.
	/// </summary>
	/// <returns>Vector</returns>
	static vector<const char*> internalPrefixes() {
		return vector<const char*> { "!2v2 " };
	}

};