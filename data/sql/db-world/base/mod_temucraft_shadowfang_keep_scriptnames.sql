-- mod-temucraft-shadowfang-keep: script names (from the TrinityCore 4.3.4 world database). The instance script keeps AzerothCore's
-- name `instance_shadowfang_keep`: the module's copy replaces AzerothCore's and runs the classic script in the normal mode.
UPDATE `creature_template` SET `ScriptName` = 'boss_baron_ashbury' WHERE `entry` = 46962;
UPDATE `creature_template` SET `ScriptName` = 'boss_lord_walden' WHERE `entry` = 46963;
UPDATE `creature_template` SET `ScriptName` = 'boss_lord_godfrey' WHERE `entry` = 46964;
UPDATE `creature_template` SET `ScriptName` = 'npc_wailing_guardsman' WHERE `entry` = 50613;
UPDATE `creature_template` SET `ScriptName` = 'npc_tormented_officer' WHERE `entry` = 50615;
UPDATE `creature_template` SET `ScriptName` = 'npc_sfk_worgen_spirit' WHERE `entry` = 50834;
UPDATE `creature_template` SET `ScriptName` = 'npc_sfk_worgen_spirit' WHERE `entry` = 50851;
UPDATE `creature_template` SET `ScriptName` = 'npc_sfk_worgen_spirit' WHERE `entry` = 50857;
UPDATE `creature_template` SET `ScriptName` = 'npc_sfk_worgen_spirit' WHERE `entry` = 50869;
DELETE FROM `spell_script_names` WHERE `ScriptName` IN ('spell_ashbury_asphyxiate','spell_ashbury_dark_archangel_form','spell_ashbury_pain_and_suffering','spell_godfrey_cursed_bullets','spell_godfrey_pistol_barrage','spell_godfrey_pistol_barrage_aoe','spell_godfrey_summon_bloodthirsty_ghouls','spell_sfk_forsaken_ability','spell_sfk_shield_of_bones','spell_sfk_summon_worgen_spirit','spell_sfk_unholy_empowerment','spell_sfk_unholy_power','spell_walden_conjure_mystery_toxin','spell_walden_conjure_poisonous_mixture','spell_walden_ice_shards','spell_walden_toxic_catalyst','spell_walden_toxic_coagulent');
INSERT INTO `spell_script_names` (`spell_id`, `ScriptName`) VALUES
(93423, 'spell_ashbury_asphyxiate'),
(93710, 'spell_ashbury_asphyxiate'),
(93757, 'spell_ashbury_dark_archangel_form'),
(93581, 'spell_ashbury_pain_and_suffering'),
(93712, 'spell_ashbury_pain_and_suffering'),
(93629, 'spell_godfrey_cursed_bullets'),
(93761, 'spell_godfrey_cursed_bullets'),
(93520, 'spell_godfrey_pistol_barrage'),
(96344, 'spell_godfrey_pistol_barrage_aoe'),
(93707, 'spell_godfrey_summon_bloodthirsty_ghouls'),
(7054, 'spell_sfk_forsaken_ability'),
(91629, 'spell_sfk_shield_of_bones'),
(93857, 'spell_sfk_summon_worgen_spirit'),
(93844, 'spell_sfk_unholy_empowerment'),
(93686, 'spell_sfk_unholy_power'),
(93735, 'spell_sfk_unholy_power'),
(93695, 'spell_walden_conjure_mystery_toxin'),
(93697, 'spell_walden_conjure_poisonous_mixture'),
(93704, 'spell_walden_conjure_poisonous_mixture'),
(93543, 'spell_walden_ice_shards'),
(93689, 'spell_walden_toxic_catalyst'),
(93617, 'spell_walden_toxic_coagulent');
DELETE FROM `areatrigger_scripts` WHERE `entry` IN (255,256,6422,6424,6425,6431);
INSERT INTO `areatrigger_scripts` (`entry`, `ScriptName`) VALUES
(255, 'at_sfk_gargoyle_event'),
(256, 'at_sfk_gargoyle_event'),
(6422, 'at_sfk_baron_silverlaine_post_floor'),
(6424, 'at_sfk_outside_ivar_bloodfang'),
(6425, 'at_sfk_outside_troups'),
(6431, 'at_sfk_godfrey_intro');
