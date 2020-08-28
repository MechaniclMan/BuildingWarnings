
#ifndef BuildingWarnings
#define BuildingWarnings

#include "general.h"
#include "da_gamefeature.h"
#include "da_event.h"
#include "da_player.h"

class BuildingWarningsPlayerDataClass : public DAPlayerDataClass {
public:
	virtual void Init() {
		WarningsSounds = true;
	}
	bool WarningsSounds;
};


class BuildingWarningsGameFeatureClass : public DAEventClass, public DAGameFeatureClass, public DAPlayerDataManagerClass<BuildingWarningsPlayerDataClass>   {
public:
	virtual void Init();
	virtual ~BuildingWarningsGameFeatureClass();
	virtual void Damage_Event(DamageableGameObj *Victim, ArmedGameObj *Damager, float Damage, unsigned int Warhead, float Scale, DADamageType::Type Type);
	virtual void Timer_Expired(int Number, unsigned int Data);
	virtual bool Chat_Command_Event(cPlayer *Player,TextMessageEnum Type,const StringClass &Command,const DATokenClass &Text,int ReceiverID);
	void Create_2D_Sound_Enabled_Team(int Team, StringClass Sound);

	bool Announce75;
	bool Announce50;
	bool Announce25;
};

#endif