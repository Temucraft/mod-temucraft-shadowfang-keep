/*
 * Small helpers for scripts ported from TrinityCore 4.3.4 to AzerothCore 3.3.5: names TrinityCore has and
 * AzerothCore doesn't, kept here so the ported scripts stay close to the original.
 */
#ifndef TEMUCRAFT_TC_COMPAT_H
#define TEMUCRAFT_TC_COMPAT_H

#include "Position.h"
#include <G3D/Vector3.h>

enum SpellFinishReason : uint8
{
    SPELL_FINISHED_SUCCESSFUL_CAST     = 0,   // AzerothCore: CreatureAI::OnSpellCast
    SPELL_FINISHED_CANCELED            = 1,   // AzerothCore: CreatureAI::OnSpellFailed
    SPELL_FINISHED_CHANNELING_COMPLETE = 2    // AzerothCore: CreatureAI::OnChannelFinished
};

inline G3D::Vector3 PositionToVector3(Position const& p) { return { p.GetPositionX(), p.GetPositionY(), p.GetPositionZ() }; }
inline G3D::Vector3 PositionToVector3(Position const* p) { return PositionToVector3(*p); }

#include "DBCStores.h"
#include "Object.h"
#include "Player.h"
#include <map>
#include <unordered_map>

// TALENT_TREE_* ids come from AzerothCore (3.3.5 TalentTab ids)

// the talent tree with the most points in the player's active spec (TrinityCore's GetPrimaryTalentTree)
inline uint32 TemucraftPrimaryTalentTab(Player const* player)
{
    std::map<uint32, uint32> points;
    for (auto const& [spellId, talent] : player->GetTalentMap())
    {
        if (!talent || talent->State == PLAYERSPELL_REMOVED || !talent->IsInSpec(player->GetActiveSpec()))
            continue;
        TalentEntry const* entry = sTalentStore.LookupEntry(talent->talentID);
        if (!entry)
            continue;
        for (uint8 rank = 0; rank < MAX_TALENT_RANK; ++rank)
            if (entry->RankID[rank] == spellId) { points[entry->TalentTab] += rank + 1; break; }
    }
    uint32 best = 0, most = 0;
    for (auto const& [tab, count] : points)
        if (count > most) { most = count; best = tab; }
    return best;
}

// Cataclysm's alternate power bar (Rhyolith's balance, Staghelm's concentration...): the 3.3.5 client has no such
// bar, so the value is only kept on the server for the scripts.
namespace TemucraftAltPower
{
    inline std::unordered_map<ObjectGuid, int32>& Store() { static std::unordered_map<ObjectGuid, int32> s; return s; }
    inline int32 Get(WorldObject const* o) { auto it = Store().find(o->GetGUID()); return it != Store().end() ? it->second : 0; }
    inline void Set(WorldObject const* o, int32 value) { Store()[o->GetGUID()] = value; }
}

#include "Map.h"
#include "MoveSplineInit.h"
#include "Unit.h"
#include <list>

// TrinityCore's MotionMaster::MoveCyclicPath: a looping spline through the given points
inline void TemucraftMoveCyclicPath(Unit* unit, Position const* points, size_t count, bool walk, bool fly, float velocity)
{
    Movement::PointsArray path;
    path.emplace_back(unit->GetPositionX(), unit->GetPositionY(), unit->GetPositionZ());
    for (size_t i = 0; i < count; ++i)
        path.emplace_back(points[i].GetPositionX(), points[i].GetPositionY(), points[i].GetPositionZ());
    Movement::MoveSplineInit init(unit);
    init.MovebyPath(path);
    init.SetWalk(walk);
    if (fly)
        init.SetFly();
    init.SetCyclic();
    if (velocity > 0.0f)
        init.SetVelocity(velocity);
    init.Launch();
}

// TrinityCore's WorldObject::GetPlayerListInGrid: the living players in range (game masters left out)
inline void TemucraftGetPlayerListInGrid(WorldObject const* source, std::list<Player*>& players, float range)
{
    for (auto const& ref : source->GetMap()->GetPlayers())
        if (Player* player = ref.GetSource())
            if (player->IsAlive() && !player->IsGameMaster() && source->IsWithinDistInMap(player, range))
                players.push_back(player);
}

namespace Acore
{
    // true for objects more than `difference` yards above (or, with reverse, not above) the base object
    class HeightDifferenceCheck
    {
    public:
        HeightDifferenceCheck(WorldObject* base, float difference, bool reverse) : _base(base), _difference(difference), _reverse(reverse) { }
        bool operator()(WorldObject* object) const { return (object->GetPositionZ() - _base->GetPositionZ() > _difference) != _reverse; }
    private:
        WorldObject* _base;
        float _difference;
        bool _reverse;
    };
}

#endif
