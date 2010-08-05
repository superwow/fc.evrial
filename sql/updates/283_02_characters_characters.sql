UPDATE characters SET
gender = (CAST(SUBSTRING_INDEX(SUBSTRING_INDEX(data, ' ', 37), ' ', -1) AS UNSIGNED) & 0xFF0000) >> 16,
level = CAST(SUBSTRING_INDEX(SUBSTRING_INDEX(data, ' ', 35), ' ', -1) AS UNSIGNED),
xp = CAST(SUBSTRING_INDEX(SUBSTRING_INDEX(data, ' ', 927), ' ', -1) AS UNSIGNED),
money = CAST(SUBSTRING_INDEX(SUBSTRING_INDEX(data, ' ', 1462), ' ', -1) AS UNSIGNED),
playerBytes = CAST(SUBSTRING_INDEX(SUBSTRING_INDEX(data, ' ', 240), ' ', -1) AS UNSIGNED),
playerBytes2 = CAST(SUBSTRING_INDEX(SUBSTRING_INDEX(data, ' ', 241), ' ', -1) AS UNSIGNED),
playerFlags = CAST(SUBSTRING_INDEX(SUBSTRING_INDEX(data, ' ', 237), ' ', -1) AS UNSIGNED)
WHERE LENGTH(SUBSTRING_INDEX(data, ' ', 1592)) < LENGTH(data) && LENGTH(data) <= LENGTH(SUBSTRING_INDEX(data, ' ', 1593));
