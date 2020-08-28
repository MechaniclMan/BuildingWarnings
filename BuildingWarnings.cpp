#include "General.h"
#include "BuildingWarnings.h"
#include "engine.h"
#include "engine_da.h"
#include "da.h"
#include "da_event.h"
#include "da_gamefeature.h"
#include "da_settings.h"
#include "da_translation.h"
#include "da_player.h"

void BuildingWarningsGameFeatureClass::Init()
{
	DAPlayerDataManagerClass<BuildingWarningsPlayerDataClass>::Init();
	Register_Object_Event(DAObjectEvent::DAMAGERECEIVED, DAObjectEvent::ObjectType::BUILDING, 10);
	Register_Event(DAEvent::CHATCOMMAND, 10 );
	Announce75 = true;
	Announce50 = true;
	Announce25 = true;
}

BuildingWarningsGameFeatureClass::~BuildingWarningsGameFeatureClass()
{
	Console_Output("Unloading Building Warnings... - By MasterCan\n");
	Unregister_Object_Event(DAObjectEvent::DAMAGERECEIVED);
}

void BuildingWarningsGameFeatureClass::Damage_Event(DamageableGameObj* Victim, ArmedGameObj* Damager, float Damage, unsigned int Warhead, float Scale, DADamageType::Type Type)
{
	if (Announce75 && (Commands->Get_Health(Victim) + Commands->Get_Shield_Strength(Victim)) > ((Commands->Get_Max_Health(Victim) + Commands->Get_Max_Shield_Strength(Victim)) * 0.74f) && (Commands->Get_Health(Victim) + Commands->Get_Shield_Strength(Victim)) < ((Commands->Get_Max_Health(Victim) + Commands->Get_Max_Shield_Strength(Victim)) * 0.76f))
	{
		DA::Team_Color_Message_With_Team_Color(Victim->Get_Player_Type(), "%sThe %s health at 75 percent", DA::Get_Message_Prefix(), DATranslationManager::Translate(Victim));
		if (Victim->Get_Player_Type() == 0) { Create_2D_Sound_Enabled_Team(0, "M00EVAN_DSGN0070I1EVAN_SND.wav"); }
		if (Victim->Get_Player_Type() == 1) { Create_2D_Sound_Enabled_Team(1, "M00EVAG_DSGN0066I1EVAG_SND.wav"); }
		Announce75 = false;
		Start_Timer(1, 10);
	}
	else if (Announce50 && (Commands->Get_Health(Victim) + Commands->Get_Shield_Strength(Victim)) > ((Commands->Get_Max_Health(Victim) + Commands->Get_Max_Shield_Strength(Victim)) * 0.49f) && (Commands->Get_Health(Victim) + Commands->Get_Shield_Strength(Victim)) < ((Commands->Get_Max_Health(Victim) + Commands->Get_Max_Shield_Strength(Victim)) * 0.51f))
	{
		DA::Team_Color_Message_With_Team_Color(Victim->Get_Player_Type(), "%sThe %s health at 50 percent", DA::Get_Message_Prefix(), DATranslationManager::Translate(Victim));
		if (Victim->Get_Player_Type() == 0) { Create_2D_Sound_Enabled_Team(0, "M00EVAN_DSGN0071I1EVAN_SND.wav"); }
		if (Victim->Get_Player_Type() == 1) { Create_2D_Sound_Enabled_Team(1, "M00EVAG_DSGN0067I1EVAG_SND.wav"); }
		Announce50 = false;
		Start_Timer(2, 10);
	}
	else if (Announce25 && (Commands->Get_Health(Victim) + Commands->Get_Shield_Strength(Victim)) > ((Commands->Get_Max_Health(Victim) + Commands->Get_Max_Shield_Strength(Victim)) * 0.24f) && (Commands->Get_Health(Victim) + Commands->Get_Shield_Strength(Victim)) < ((Commands->Get_Max_Health(Victim) + Commands->Get_Max_Shield_Strength(Victim)) * 0.26f))
	{
		DA::Team_Color_Message_With_Team_Color(Victim->Get_Player_Type(), "%sThe %s health at 25 percent", DA::Get_Message_Prefix(), DATranslationManager::Translate(Victim));
		if (Victim->Get_Player_Type() == 0) { Create_2D_Sound_Enabled_Team(0, "M00EVAN_DSGN0072I1EVAN_SND.wav"); }
		if (Victim->Get_Player_Type() == 1) { Create_2D_Sound_Enabled_Team(1, "M00EVAG_DSGN0068I1EVAG_SND.wav"); }
		Announce25 = false;
		Start_Timer(3, 10);
	}
}

void BuildingWarningsGameFeatureClass::Timer_Expired(int Number, unsigned int Data)
{
	if (Number == 1)
	{
		Announce75 = true;
	}
	else if (Number == 2)
	{
		Announce50 = true;
	}
	else if (Number == 3)
	{
		Announce25 = true;
	}
}

//Only play sound for players that have sounds enabled 
void BuildingWarningsGameFeatureClass::Create_2D_Sound_Enabled_Team(int Team, StringClass Sound)
{
	for (SLNode<cPlayer> *z = Get_Player_List()->Head();z;z = z->Next()) 
	{
		cPlayer *Player = z->Data();
		if (Player->Is_Active() && Get_Player_Data(Player)->WarningsSounds ) 
		{
			if ( Player->Get_Player_Type() == Team )
				DA::Create_2D_Sound_Player(Player, Sound);
		}
	}
}

//Piggy back on existing DA !enablesounds !disablesounds commands to disable building warning sounds  
bool BuildingWarningsGameFeatureClass::Chat_Command_Event(cPlayer *Player,TextMessageEnum Type,const StringClass &Command,const DATokenClass &Text,int ReceiverID)
{
	if (Command == "!enablesounds" || Command == "!enablewarningsounds") 
	{
		Get_Player_Data(Player)->WarningsSounds = true;
		DA::Page_Player(Player,"You will now hear building warning sounds.");
	}
	else if ( Command == "!disablesounds" || Command == "!disablewarningsounds" ) 
	{
		Get_Player_Data(Player)->WarningsSounds = false;
		DA::Page_Player(Player,"You will no longer hear building warning sounds.");
	}
	return true;
}

Register_Game_Feature(BuildingWarningsGameFeatureClass, "Building Warnings - By MasterCan", "BuildingWarnings", 0);