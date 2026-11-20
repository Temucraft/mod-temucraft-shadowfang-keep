/*
 * This file is part of the AzerothCore Project. See AUTHORS file for Copyright information
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for
 * more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program. If not, see <http://www.gnu.org/licenses/>.
 */

// mod-temucraft-shadowfang-keep: AzerothCore's own (classic) Shadowfang Keep instance script, unchanged apart from the
// names. The module's instance_shadowfang_keep replaces AzerothCore's script of the same name and hands the normal
// mode to this copy, so the classic dungeon and the Love is in the Air event (Apothecary Hummel) keep working as before.

#include "InstanceScript.h"
#include "Creature.h"
#include "GameObject.h"
#include "Map.h"
#include <sstream>

namespace TemucraftShadowfangKeepClassic
{
// the values of AzerothCore's shadowfang_keep.h, which AzerothCore's own Shadowfang Keep scripts still use
enum DataTypes
{
    TYPE_COURTYARD              = 0,
    TYPE_FENRUS_THE_DEVOURER    = 1,
    TYPE_WOLF_MASTER_NANDOS     = 2,
    MAX_ENCOUNTERS              = 3,
    DATA_APOTHECARY_HUMMEL      = 4,
    DATA_SPAWN_VALENTINE_ADDS   = 5
};

enum SKCreatures
{
    NPC_DND_CRAZED_APOTHECARY_GENERATOR = 36212,
    NPC_APOTHECARY_HUMMEL               = 36296,
    NPC_CRAZED_APOTHECARY               = 36568
};

enum GameObjects
{
    GO_COURTYARD_DOOR           = 18895,
    GO_SORCERER_DOOR            = 18972,
    GO_ARUGAL_DOOR              = 18971
};

enum Spells
{
    SPELL_SUMMON_VALENTINE_ADD = 68610
};

struct instance_shadowfang_keep_classic_InstanceMapScript : public InstanceScript
{
    instance_shadowfang_keep_classic_InstanceMapScript(Map* map) : InstanceScript(map)
    {
        SetHeaders("SK");
    }

    void Initialize() override
    {
        memset(&_encounters, 0, sizeof(_encounters));
    }

    void OnCreatureCreate(Creature* creature) override
    {
        switch (creature->GetEntry())
        {
            case NPC_DND_CRAZED_APOTHECARY_GENERATOR:
                _crazedApothecaryGeneratorGUIDs.push_back(creature->GetGUID());
                break;
            case NPC_APOTHECARY_HUMMEL:
                _apothecaryHummel = creature->GetGUID();
                break;
            case NPC_CRAZED_APOTHECARY:
                if (Creature* hummel = instance->GetCreature(_apothecaryHummel))
                {
                    hummel->AI()->JustSummoned(creature);
                }
                break;
            default:
                break;
        }
    }

    void OnGameObjectCreate(GameObject* gameobject) override
    {
        switch (gameobject->GetEntry())
        {
            case GO_COURTYARD_DOOR:
                if (_encounters[TYPE_COURTYARD] == DONE)
                    HandleGameObject(ObjectGuid::Empty, true, gameobject);
                break;
            case GO_SORCERER_DOOR:
                if (_encounters[TYPE_FENRUS_THE_DEVOURER] == DONE)
                    HandleGameObject(ObjectGuid::Empty, true, gameobject);
                break;
            case GO_ARUGAL_DOOR:
                if (_encounters[TYPE_WOLF_MASTER_NANDOS] == DONE)
                    HandleGameObject(ObjectGuid::Empty, true, gameobject);
                break;
            default:
                break;
        }
    }

    void SetData(uint32 type, uint32 data) override
    {
        switch (type)
        {
            case TYPE_COURTYARD:
            case TYPE_FENRUS_THE_DEVOURER:
            case TYPE_WOLF_MASTER_NANDOS:
                _encounters[type] = data;
                break;
            case DATA_SPAWN_VALENTINE_ADDS:
                for (ObjectGuid guid : _crazedApothecaryGeneratorGUIDs)
                {
                    if (Creature* generator = instance->GetCreature(guid))
                    {
                        generator->CastSpell(nullptr, SPELL_SUMMON_VALENTINE_ADD);
                    }
                }
                break;
            default:
                break;
        }

        if (data == DONE)
            SaveToDB();
    }

    void ReadSaveDataMore(std::istringstream& data) override
    {
        data >> _encounters[0];
        data >> _encounters[1];
        data >> _encounters[2];
    }

    void WriteSaveDataMore(std::ostringstream& data) override
    {
        data << _encounters[0] << ' ' << _encounters[1] << ' ' << _encounters[2];
    }

private:
    uint32 _encounters[MAX_ENCOUNTERS];
    GuidVector _crazedApothecaryGeneratorGUIDs;
    ObjectGuid _apothecaryHummel;
};

InstanceScript* CreateInstanceScript(InstanceMap* map)
{
    return new instance_shadowfang_keep_classic_InstanceMapScript(map);
}
}
