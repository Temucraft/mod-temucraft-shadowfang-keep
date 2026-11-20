-- mod-temucraft-shadowfang-keep: the heroic mode of Shadowfang Keep (map 33)
-- The 3.3.5 server's MapDifficulty.dbc has no heroic row for map 33, so the core refuses the heroic mode. Same row
-- (ID 756) as in Temucraft's client MapDifficulty.dbc (patch-T), which shows the heroic choice.
DELETE FROM `mapdifficulty_dbc` WHERE `ID` = 756;
INSERT INTO `mapdifficulty_dbc` (`ID`, `MapID`, `Difficulty`, `Message_Lang_enUS`, `MaxPlayers`, `RaidDuration`, `Difficultystring`) VALUES
(756, 33, 1, '', 5, 86400, 'DUNGEON_DIFFICULTY_5PLAYER_HEROIC');

-- level 80 to enter the heroic mode (the creatures are level 80 to 82)
DELETE FROM `dungeon_access_template` WHERE `id` = 201;
INSERT INTO `dungeon_access_template` (`id`, `map_id`, `difficulty`, `min_level`, `max_level`, `min_avg_item_level`, `comment`) VALUES
(201, 33, 1, 80, 0, 0, 'Shadowfang Keep - Heroic (Cataclysm)');
