/*
	Building Warnings
	Copyright 2020 Unstoppable

	This plugin is free software: you can redistribute it and/or modify
	it under the terms of the GNU General Public License as published by
	the Free Software Foundation, either version 3 of the License, or
	(at your option) any later version. See GNU General Public License for more details.
*/

#ifndef BuildingWarnings
#define BuildingWarnings

#include "general.h"
#include "da_gamefeature.h"
#include "da_event.h"

#define CompileTime StringFormat("%s %s", __DATE__, __TIME__)
#define Version 1.331f

enum WarnState
{
	WARNSTATE_REPAIRING = 0,
	WARNSTATE_75,
	WARNSTATE_50,
	WARNSTATE_25
};

struct FormatParams
{
	WarnState State;
	StringClass Message;
	int Team;
	GameObject* Building;
	GameObject* Damager;
	StringClass *Out;
};

class BuildingWarningsPlayerDataClass : public DAPlayerDataClass {
public:
	virtual void Init() {
		WarningSounds = true;
	}
	bool WarningSounds;
};

class BuildingWarningsGameFeatureClass : public DAEventClass, public DAGameFeatureClass, public DAPlayerDataManagerClass<BuildingWarningsPlayerDataClass> {
public:
	void SendStateMessage(FormatParams *Params);
	void FormatStateMessage(FormatParams *Params);
protected:
	void Init() override;
	void Settings_Loaded_Event() override;
	void Damage_Event(DamageableGameObj* Victim, ArmedGameObj* Damager, float Damage, unsigned int Warhead, float Scale, DADamageType::Type Type) override;
	void Timer_Expired(int Number, unsigned int Data) override;
	bool Chat_Command_Event(cPlayer *Player,TextMessageEnum Type,const StringClass &Command,const DATokenClass &Text,int ReceiverID);
	void Create_2D_Sound_Enabled_Team(int Team, StringClass Sound);
	~BuildingWarningsGameFeatureClass();
private:
	static const char Sounds[4][2][50];
	static DASettingsClass *INI;

	/* static */ StringClass Format75;
	/* static */ StringClass Format50;
	/* static */ StringClass Format25;
	/* static */ StringClass FormatRepairing;
	/* static */ DynamicVectorClass<StringClass> IncludeList;
	/* static */ DynamicVectorClass<StringClass> ExcludeList;
	/* static */ bool ReportVehicleBuildings;
	/* static */ bool ShowEnemy;
	/* static */ bool UseDAPrefix;
	/* static */ bool UseTeamColors;
	/* static */ float PercentCooldown;
	/* static */ float RepairCooldown;
	/* static */ Vector3 Color75;
	/* static */ Vector3 Color50;
	/* static */ Vector3 Color25;
	/* static */ Vector3 ColorRepairing;
	/* static */ bool Enable75;
	/* static */ bool Enable50;
	/* static */ bool Enable25;
	/* static */ bool EnableRepairing;

	//bool Announce75;
	//bool Announce50;
	//bool Announce25;
};

#endif